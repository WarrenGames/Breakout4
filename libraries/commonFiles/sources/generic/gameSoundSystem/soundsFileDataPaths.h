#ifndef COMMON_FILES_LIB_SOUNDS_FILE_DATA_PATHS_H
#define COMMON_FILES_LIB_SOUNDS_FILE_DATA_PATHS_H

#include "fileSystem/fileSystem.h"
#include <vector>

class PrefPathFinder;

class SoundSystemFilesPaths
{
private:
	std::vector< fs::path > configFilesPaths;

public:
	explicit SoundSystemFilesPaths(const PrefPathFinder& prefPath, const fs::path& soundsFileList, const fs::path& groupTagCfg);
	~SoundSystemFilesPaths() = default;
	SoundSystemFilesPaths( const SoundSystemFilesPaths& ) = delete;
	SoundSystemFilesPaths& operator= ( const SoundSystemFilesPaths& ) = delete;
	SoundSystemFilesPaths( SoundSystemFilesPaths&& ) = default;
	SoundSystemFilesPaths& operator= ( SoundSystemFilesPaths&& ) = default;
	
	const std::vector< fs::path > & getPaths() const;
	
private:
	void setPaths(const PrefPathFinder& prefPath, const fs::path& soundsFileList, const fs::path& groupTagCfg);
};

#endif //COMMON_FILES_LIB_SOUNDS_FILE_DATA_PATHS_H