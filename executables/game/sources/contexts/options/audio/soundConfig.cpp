#include "contexts/options/audio/soundConfig.h"
#include "texts/textLoader.h"
#include "texturing/texturePosition.h"
#include "types/essentialsStruct.h"
#include "sounds/loadSound.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "customTypes/positionTypes.h"
#include "consts/optionsLanguageConsts.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include <fstream>

constexpr unsigned int VolumeGradientWidth = 8 * SQR_SIZE;
constexpr unsigned int VolumeGradientHeight = SQR_SIZE / 2;

SoundConfig::SoundConfig(Essentials& essentials, const sdl2::Font& font, const TextsBlocks& audioLangTexts):
	isLoadingPerfect{true},
	isSoundActive{true},
	soundExample{ loadSoundChunk(essentials.logs.error, "sounds/halloweenOrgan.wav") },
	soundsTxt{ essentials.logs, essentials.rndWnd, font, audioLangTexts[audioLang::Sound], WhiteColor, TexturePosition{2*SQR_SIZE, 3*SQR_SIZE, false, true} },
	enabled{ essentials.logs, essentials.rndWnd, font, audioLangTexts[audioLang::Enabled], WhiteColor, TexturePosition{4*SQR_SIZE, 3*SQR_SIZE, false, true} },
	disabled{ essentials.logs, essentials.rndWnd, font, audioLangTexts[audioLang::Disabled], WhiteColor, TexturePosition{4*SQR_SIZE, 3*SQR_SIZE, false, true} },
	volBar{essentials, {2*SQR_SIZE, 5*SQR_SIZE, VolumeGradientWidth, VolumeGradientHeight}, GreenColor, RedColor, Offset{0, MIX_MAX_VOLUME}, MIX_MAX_VOLUME/2},
	playSound{essentials.logs, essentials.rndWnd, font, audioLangTexts[audioLang::PlaySound], GreenColor, MediumGrayColor, SQR_SIZE * 4, SQR_SIZE * 4, true},
	switchSoundBool{essentials.logs, essentials.rndWnd, font, audioLangTexts[audioLang::Change], GreenColor, MediumGrayColor, SQR_SIZE*8, SQR_SIZE*3, true}
{
	readDataFile(essentials);
}

SoundConfig::~SoundConfig()
{
	Mix_HaltChannel(0);
}


void SoundConfig::writeDataFile(Essentials& essentials) const
{
	if( std::ofstream soundConfiguration{ path::getConfigDirFile(essentials.prefPath, file::SoundConfigFile) } )
	{
		soundConfiguration << isSoundActive << " " << volBar.getVolume();
	}
	else{
		essentials.logs.error.wrFileOpeningError( path::getConfigDirFile(essentials.prefPath, file::SoundConfigFile), "save sound configuration." );
	}
}

bool SoundConfig::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}


void SoundConfig::drawAll(sdl2::RendererWindow& rndWnd) const
{
	soundsTxt.draw(rndWnd);
	drawSoundBooleanText(rndWnd);
	volBar.drawAll(rndWnd);
	playSound.drawButton(rndWnd);
	switchSoundBool.drawButton(rndWnd);
}

void SoundConfig::updateButton(const Offset& mousePosition, bool buttonState)
{
	changeVolume(mousePosition, buttonState);
	playSound.updateButton(mousePosition.x, mousePosition.y, buttonState);
	switchSoundBool.updateButton(mousePosition.x, mousePosition.y, buttonState);
}

void SoundConfig::updateWithButtons()
{
	invertSoundActiveBool();
	playExampleSound();
}

void SoundConfig::changeVolume(const Offset& mousePosition, bool buttonState)
{
	volBar.changeVolumeLevel(mousePosition, buttonState);
	
	if( volBar.getVolume() < MIX_MAX_VOLUME )
		Mix_VolumeChunk(soundExample.get(), volBar.getVolume() );
}

void SoundConfig::drawSoundBooleanText(sdl2::RendererWindow& rndWnd) const
{
	if( isSoundActive )
		enabled.draw(rndWnd);
	else{
		disabled.draw(rndWnd);
	}
}

void SoundConfig::invertSoundActiveBool()
{
	if( switchSoundBool.buttonClicked() )
	{
		isSoundActive = !isSoundActive;
	}
}

void SoundConfig::playExampleSound() const
{
	if( playSound.buttonClicked() )
	{
		if( soundExample )
			Mix_PlayChannel(0, soundExample.get(), 0);
	}
}

void SoundConfig::readDataFile(Essentials& essentials)
{
	if( std::ifstream soundFile{ path::getConfigDirFile(essentials.prefPath, file::SoundConfigFile) } )
	{
		unsigned soundVolume{0};
		if( soundFile >> isSoundActive >> soundVolume )
		{
			volBar.setVolume(soundVolume);
		}
		else{
			essentials.logs.error.wrReadErrorMessage(path::getConfigDirFile(essentials.prefPath, file::SoundConfigFile), "'is sound active' boolean and 'sound volume'");
			isLoadingPerfect = false;
		}
	}
	else{
		essentials.logs.error.wrFileOpeningError( path::getConfigDirFile(essentials.prefPath, file::SoundConfigFile), "read sound configuration for the options.");
		isLoadingPerfect = false;
	}
}
