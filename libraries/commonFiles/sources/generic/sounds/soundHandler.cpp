#include "generic/sounds/soundHandler.h"
#include "generic/sounds/loadGameSounds.h"
#include "generic/sounds/loadChannelsConfig.h"
#include "logging/logsStruct.h"
#include "types/essentialsStruct.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/sdlMixerConsts.h"
#include <cassert>

SoundHandler::SoundHandler(Essentials& essentials, const fs::path& sndPathsFile, const fs::path& sndChannelsFile):
	soundVolume{MIX_MAX_VOLUME / 2},
	isLoadingPerfect{true},
	isSoundActive{true}
{
	soundLoad::readLines(essentials.logs, sndPathsFile, sounds, isLoadingPerfect);
	loadChanCfg::readLines(essentials.logs, sndChannelsFile, isLoadingPerfect);
	loadSoundConfigFile(essentials, path::getConfigDirFile(essentials.prefPath, file::SoundConfigFile) );
	sumLoading(essentials.logs);
	setVolumeToSounds();
}

SoundHandler::~SoundHandler()
{
	Mix_GroupChannels(0, SdlMixerChannelsNumber - 1, -1);
}

bool SoundHandler::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

void SoundHandler::playSound(std::size_t soundIndex) const
{
	if( isSoundActive && soundIndex < sounds.size() )
	{
		int freeChannel{ Mix_GroupAvailable(sounds[soundIndex].groupTag ) };
		if( freeChannel != -1 && sounds[soundIndex].snd )
		{
			Mix_PlayChannel(freeChannel, sounds[soundIndex].snd.get(), 0);
		}
	}
}

std::size_t SoundHandler::getSoundsNumber() const
{
	return sounds.size();
}

void SoundHandler::sumLoading(AppLogFiles& logs)
{
	if( isLoadingPerfect )
	{
		logs.warning.wrUint(static_cast<unsigned>(sounds.size() ) );
		logs.warning.wrSimpleMessage(" sounds were loaded with success.");
	}
	else{
		logs.error.wrSimpleMessage("Error: something wrong ocurred while loading sounds and/or channels in files.");
	}
}

void SoundHandler::loadSoundConfigFile(Essentials& essentials, const fs::path& filePath)
{
	if( std::ifstream configFile{ path::getConfigDirFile(essentials.prefPath, file::SoundConfigFile) } )
	{
		if( !( configFile >> isSoundActive >> soundVolume ) )
		{
			essentials.logs.error.wrReadErrorMessage(filePath, "sound activation and sound volume");
			isLoadingPerfect = false;
		}
	}
	else{
		essentials.logs.error.wrFileOpeningError(filePath, "sound activation and sound volume");
		isLoadingPerfect = false;
	}
}

void SoundHandler::setVolumeToSounds()
{
	for( auto &sound : sounds )
	{
		Mix_VolumeChunk(sound.snd.get(), soundVolume);
	}
}