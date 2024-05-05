#ifndef SOUNDS_PLAYER_H
#define SOUNDS_PLAYER_H

#include "wrappers/mixerPtrWrapper.h"
#include <vector>

class SoundPlayer
{
private:
	std::vector< sdl2::Mix_ChunkPtr > soundsChunks;
	unsigned expectedGroupTagsNumber;
	bool soundIsActivated;
	bool isLoadingPerfect;

public:
	explicit SoundPlayer(std::vector< sdl2::Mix_ChunkPtr >& loadedSoundsChunks, unsigned expectedSoundsNum, unsigned expectedGroupTagsNum_, bool soundPlayPolicy, unsigned soundVolume);
	~SoundPlayer() = default;
	SoundPlayer( const SoundPlayer& ) = delete;
	SoundPlayer& operator= ( const SoundPlayer& ) = delete;
	SoundPlayer( SoundPlayer&& ) = default;
	SoundPlayer& operator= ( SoundPlayer&& ) = default;
	
	bool wasLoadingPerfect() const;
	void playSoundOnGroup(unsigned soundIndex, unsigned group) const;
	void changeSoundsChunksVolume(unsigned newVolume);
	void moveSounds(std::vector< sdl2::Mix_ChunkPtr >& loadedSoundsChunks);
	void setSoundPlayPolicy(bool policy);
	
	void setErrorFlag();
};

#endif //SOUNDS_PLAYER_H