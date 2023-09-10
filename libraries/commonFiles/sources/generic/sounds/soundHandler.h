#ifndef SOUND_HANDLER_H
#define SOUND_HANDLER_H

#include "wrappers/sdl2_ptr.h"
#include "generic/sounds/soundStructs.h"
#include <vector>
#include <string>

struct Essentials;
struct AppLogFiles;

class SoundHandler
{
private:
	unsigned soundVolume;
	bool isLoadingPerfect;
	bool isSoundActive;
	std::vector< SoundSpecifications > sounds;

public:
	SoundHandler(Essentials& essentials, const fs::path& sndPathsFile, const fs::path& sndChannelsFile);
	~SoundHandler();
	SoundHandler( const SoundHandler& ) = delete;
	SoundHandler& operator= ( const SoundHandler& ) = delete;
	SoundHandler( SoundHandler&& ) = default;
	SoundHandler& operator= ( SoundHandler&& ) = default;
	
	bool wasLoadingPerfect() const;
	void playSound(std::size_t soundIndex) const;
	std::size_t getSoundsNumber() const;
	
private:
	void sumLoading(AppLogFiles& logs);
	void loadSoundConfigFile(Essentials& essentials, const fs::path& filePath);
	void setVolumeToSounds();
};

#endif //SOUND_HANDLER_H