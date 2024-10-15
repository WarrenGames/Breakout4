#include "soundSystem/soundsPlayer.h"
#include <cassert>

SoundPlayer::SoundPlayer(std::vector< sdl2::Mix_ChunkPtr >& loadedSoundsChunks, unsigned expectedSoundsNum, int expectedGroupTagsNum_, 
							bool soundPlayPolicy, int soundVolume):
	expectedGroupTagsNumber{ expectedGroupTagsNum_ },
	soundIsActivated{ soundPlayPolicy },
	isLoadingPerfect{ true }
{
	moveSounds(loadedSoundsChunks);
	changeSoundsChunksVolume(soundVolume);
	if( soundsChunks.size() != expectedSoundsNum )
	{
		isLoadingPerfect = false;
	}
}

bool SoundPlayer::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

void SoundPlayer::playSoundOnGroup(unsigned soundIndex, int group) const
{
	assert( soundIndex < soundsChunks.size() );
	assert( group < expectedGroupTagsNumber );
	
	if( soundIsActivated )
	{
		int freeChannel{ Mix_GroupAvailable(group) }; //This line keeps the const of the member function that plays a sound (instead of a 'freeChannel' value member) 
		if( freeChannel != -1 && soundsChunks[soundIndex] )
		{
			Mix_PlayChannel(freeChannel, soundsChunks[soundIndex].get(), 0);
		}
	}
}

void SoundPlayer::changeSoundsChunksVolume(int newVolume)
{
	for(auto &sound : soundsChunks )
	{
		Mix_VolumeChunk(sound.get(), newVolume);
	}
}

void SoundPlayer::moveSounds(std::vector< sdl2::Mix_ChunkPtr >& loadedSoundsChunks)
{
	soundsChunks = std::move( loadedSoundsChunks );
}

void SoundPlayer::setSoundPlayPolicy(bool policy)
{
	soundIsActivated = policy;
}

void SoundPlayer::setErrorFlag()
{
	isLoadingPerfect = false;
}