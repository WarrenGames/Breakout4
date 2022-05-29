#ifndef SOUND_HANDLER_H
#define SOUND_HANDLER_H

#include "wrappers/sdl2_ptr.h"
#include "generic/sounds/soundStructs.h"
#include <vector>
#include <string>

struct Essentials;

class SoundHandler
{
private:
	unsigned soundVolume;
	bool isLoadingPerfect;
	bool isSoundActive;
	std::vector< SoundSpecifications > sounds;

public:
	SoundHandler(Essentials& essentials, const std::string& sndPathsFile, const std::string& sndChannelsFile);
	~SoundHandler();
	SoundHandler( const SoundHandler& ) = delete;
	SoundHandler& operator= ( const SoundHandler& ) = delete;
	SoundHandler( SoundHandler&& ) = default;
	SoundHandler& operator= ( SoundHandler&& ) = default;
	
	bool wasLoadingPerfect() const;
	void playSound(std::size_t soundIndex) const;
	std::size_t getSoundsNumber() const;
	
private:
	void sumLoading(LogFile& log);
	void loadSoundConfigFile(Essentials& essentials, const std::string& filePath);
	void setVolumeToSounds();
};

#endif //SOUND_HANDLER_H