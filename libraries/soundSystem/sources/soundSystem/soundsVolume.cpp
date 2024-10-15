#include "soundSystem/soundsVolume.h"
#include "logging/logsStruct.h"
#include "SDL_mixer.h"

SoundVolumeLoader::SoundVolumeLoader(AppLogFiles& logs, const fs::path& soundVolumeConfigPath):
	globalSoundVolume{ MIX_MAX_VOLUME / 2 },
	isLoadingPerfect{ true },
	soundIsActivated{ true }
{
	loadVolumeFile(logs, soundVolumeConfigPath );
}

bool SoundVolumeLoader::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

int SoundVolumeLoader::getLoadedSoundVolume() const
{
	return globalSoundVolume;
}

bool SoundVolumeLoader::isSoundActive() const
{
	return soundIsActivated;
}

void SoundVolumeLoader::loadVolumeFile(AppLogFiles& logs, const fs::path& filePath)
{
	if( std::ifstream audioFile{ filePath } )
	{
		readAudioConfigFile(logs, filePath, audioFile);
	}
	else
	{
		logs.error.wrFileOpeningError(filePath, "load the game sound config (whether sound is activated and its volume.");
		isLoadingPerfect = false;
	}
}

void SoundVolumeLoader::readAudioConfigFile(AppLogFiles& logs, const fs::path& filePath, std::ifstream& volumeFile)
{
	if( volumeFile >> soundIsActivated >> globalSoundVolume )
	{
		logs.warning.wrSimpleMessage("The sound config file: " + filePath.string() + " was loaded with success.");
	}
	else{
		logs.error.wrReadErrorMessage(filePath, "sound boolean and sound volume value");
		isLoadingPerfect = false;
	}
}