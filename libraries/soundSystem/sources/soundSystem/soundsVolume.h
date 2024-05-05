#ifndef SOUNDS_VOLUME_LOADER_H
#define SOUNDS_VOLUME_LOADER_H

#include "fileSystem/fileSystem.h"
#include <iosfwd>

struct AppLogFiles;

class SoundVolumeLoader
{
private:
	unsigned globalSoundVolume;
	bool isLoadingPerfect;
	bool soundIsActivated;

public:
	explicit SoundVolumeLoader(AppLogFiles& logs, const fs::path& soundVolumeConfigPath);
	~SoundVolumeLoader() = default;
	SoundVolumeLoader( const SoundVolumeLoader& ) = delete;
	SoundVolumeLoader& operator= ( const SoundVolumeLoader& ) = delete;
	SoundVolumeLoader( SoundVolumeLoader&& ) = default;
	SoundVolumeLoader& operator= ( SoundVolumeLoader&& ) = default;
	
	bool wasLoadingPerfect() const;
	unsigned getLoadedSoundVolume() const;
	bool isSoundActive() const;

private:
	void loadVolumeFile(AppLogFiles& logs, const fs::path& filePath);
	void readAudioConfigFile(AppLogFiles& logs, const fs::path& filePath, std::ifstream& volumeFile);
};

#endif //SOUNDS_VOLUME_LOADER_H