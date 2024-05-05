#ifndef IN_GAME_SOUNDS_LIST_LOADER_H
#define IN_GAME_SOUNDS_LIST_LOADER_H

#include "wrappers/mixerPtrWrapper.h"
#include "fileSystem/fileSystem.h"
#include <vector>
#include <iosfwd>
#include <string>

struct AppLogFiles;

class SoundsListLoader
{
private:
	std::vector< sdl2::Mix_ChunkPtr > soundsChunks;
	bool isLoadingPerfect;
	
public:
	explicit SoundsListLoader(AppLogFiles& logs, const fs::path& listFile, const fs::path& soundFilesDirectory);
	~SoundsListLoader() = default;
	SoundsListLoader( const SoundsListLoader& ) = delete;
	SoundsListLoader& operator= ( const SoundsListLoader& ) = delete;
	SoundsListLoader( SoundsListLoader&& ) = default;
	SoundsListLoader& operator= ( SoundsListLoader&& ) = default;
	
	std::vector< sdl2::Mix_ChunkPtr >::iterator begin();
	std::vector< sdl2::Mix_ChunkPtr >::iterator end();
	std::vector< sdl2::Mix_ChunkPtr >& getLoadedData();
	bool wasLoadingPerfect() const;
	
private:
	void openSoundFilesList(AppLogFiles& logs, const fs::path& listFile, const fs::path& soundFilesDirectory);
	void readFileLines(AppLogFiles& logs, const fs::path& soundFilesDirectory, std::ifstream& inputFile);
	void loadSound(AppLogFiles& logs, const fs::path& fileName, const fs::path& soundFilesDirectory);
};

#endif //IN_GAME_SOUNDS_LIST_LOADER_H