#include "contexts/options/audio/musicConfig.h"
#include "texts/textLoader.h"
#include "texturing/texturePosition.h"
#include "types/essentialsStruct.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "sounds/loadSound.h"
#include "customTypes/positionTypes.h"
#include "contexts/options/optionsLanguageConsts.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include <fstream>

constexpr unsigned int VolumeGradientWidth = 8 * SQR_SIZE;
constexpr unsigned int VolumeGradientHeight = SQR_SIZE / 2;

MusicConfig::MusicConfig(Essentials& essentials, const sdl2::Font& font, const TextsBlocks& audioLangTexts):
	isLoadingPerfect{true},
	isMusicActive{true},
	musicExample{ loadMixMusic(essentials.logs.error, "musics/intro.flac") },
	musicTxt{essentials.logs, essentials.rndWnd, font, audioLangTexts[audioLang::Music], WhiteColor, TexturePosition{2*SQR_SIZE, 7*SQR_SIZE, false, true } },
	enabled{essentials.logs, essentials.rndWnd, font, audioLangTexts[audioLang::Enabled], WhiteColor, TexturePosition{4*SQR_SIZE, 7*SQR_SIZE, false, true} },
	disabled{essentials.logs, essentials.rndWnd, font, audioLangTexts[audioLang::Disabled], WhiteColor, TexturePosition{4*SQR_SIZE, 7*SQR_SIZE, false, true} },
	volBar{essentials, {2*SQR_SIZE, 9*SQR_SIZE, VolumeGradientWidth, VolumeGradientHeight}, GreenColor, RedColor, Offset{0, MIX_MAX_VOLUME}, MIX_MAX_VOLUME/2},
	playMusic{essentials.logs, essentials.rndWnd, font, "Play music", GreenColor, MediumGrayColor, SQR_SIZE * 4, SQR_SIZE * 8, true},
	switchMusicBool{essentials.logs, essentials.rndWnd, font, "Enable/disable music", GreenColor, MediumGrayColor, SQR_SIZE * 8, SQR_SIZE * 7, true}
{
	readDataFile(essentials);
}

void MusicConfig::writeDataFile(Essentials& essentials) const
{
	if( std::ofstream musicConfiguration{ path::getConfigDirFile(essentials.prefPath, file::MUSIC_CFG_FILE) } )
	{
		musicConfiguration << isMusicActive << " " << volBar.getVolume();
	}
	else{
		essentials.logs.error.wrFileOpeningError( path::getConfigDirFile(essentials.prefPath, file::MUSIC_CFG_FILE), "save music configuration for the options.");
	}
}

bool MusicConfig::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

void MusicConfig::drawAll(sdl2::RendererWindow& rndWnd) const
{
	musicTxt.draw(rndWnd);
	drawMusicBooleanText(rndWnd);
	volBar.drawAll(rndWnd);
	playMusic.drawButton(rndWnd);
	switchMusicBool.drawButton(rndWnd);
}

void MusicConfig::updateButton(const Offset& mousePosition, bool buttonState)
{
	changeVolume(mousePosition, buttonState);
	playMusic.updateButton(mousePosition.x, mousePosition.y, buttonState);
	switchMusicBool.updateButton(mousePosition.x, mousePosition.y, buttonState);
}

void MusicConfig::updateWithButtons()
{
	invertMusicActiveBool();
	playExampleMusic();
}

void MusicConfig::haltMusic() const
{
	if( Mix_PlayingMusic() )
		Mix_HaltMusic();
}

void MusicConfig::changeVolume(const Offset& mousePosition, bool buttonState)
{
	volBar.changeVolumeLevel(mousePosition, buttonState);
	
	if( volBar.getVolume() < MIX_MAX_VOLUME )
		Mix_VolumeMusic( volBar.getVolume() );
}

void MusicConfig::drawMusicBooleanText(sdl2::RendererWindow& rndWnd) const
{
	if( isMusicActive )
		enabled.draw(rndWnd);
	else{
		disabled.draw(rndWnd);
	}
}

void MusicConfig::invertMusicActiveBool()
{
	if( switchMusicBool.buttonClicked() )
	{
		isMusicActive = !isMusicActive;
	}
}

void MusicConfig::playExampleMusic() const
{
	if( playMusic.buttonClicked() )
	{
		if( Mix_PlayingMusic() == 0 || Mix_PausedMusic() == 1 )
		{
			Mix_PlayMusic(musicExample.get(), 1);
		}
		else
			Mix_PauseMusic();
	}
}

void MusicConfig::readDataFile(Essentials& essentials)
{
	if( std::ifstream soundFile{ path::getConfigDirFile(essentials.prefPath, file::MUSIC_CFG_FILE) } )
	{
		unsigned musicVolume{MIX_MAX_VOLUME};
		if( soundFile >> isMusicActive >> musicVolume )
		{
			volBar.setVolume(musicVolume);
		}
		else{
			essentials.logs.error.wrReadErrorMessage( path::getConfigDirFile(essentials.prefPath, file::MUSIC_CFG_FILE), "'is music active' boolean and music volume.");
			isLoadingPerfect = false;
		}
	}
	else{
		essentials.logs.error.wrFileOpeningError( path::getConfigDirFile(essentials.prefPath, file::MUSIC_CFG_FILE), "read music configuration.");
		isLoadingPerfect = false;
	}
}
