#include "soundSystem/soundSystem.h"
#include "logging/logsStruct.h"
#include "soundsPathsConsts.h"
#include <cassert>

SoundSystem::SoundSystem(AppLogFiles& logs, const std::vector< fs::path >& pathsList, unsigned expectedSoundsNumber, unsigned expectedGroupTagsNumber):
	soundsVolume{ logs, pathsList[sounds::PATH_SND_VOLUME] },
	soundsListLoader{ logs, pathsList[sounds::PATH_SND_WAVEFORM_LIST], pathsList[sounds::PATH_SND_WAVEFORM_DIRECTORY] },
	soundPlayer{ soundsListLoader.getLoadedData(), expectedSoundsNumber, expectedGroupTagsNumber, soundsVolume.isSoundActive(), soundsVolume.getLoadedSoundVolume() },
	soundChannels{ logs, pathsList[sounds::PATH_SND_CHANNEL_CONFIG] }
{
	assert( pathsList.size() == sounds::PATH_SND_MAX );
}

bool SoundSystem::wasLoadingPerfect() const
{
	return soundsVolume.wasLoadingPerfect() 
		&& soundsListLoader.wasLoadingPerfect() 
		&& soundPlayer.wasLoadingPerfect() 
		&& soundChannels.wasLoadingPerfect();
}