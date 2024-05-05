#include "soundSystem/soundsListLoader.h"
#include "sounds/loadSound.h"
#include "logging/logsStruct.h"
#include <fstream>

SoundsListLoader::SoundsListLoader(AppLogFiles& logs, const fs::path& listFile, const fs::path& soundFilesDirectory):
	isLoadingPerfect{true}
{
	openSoundFilesList(logs, listFile, soundFilesDirectory);
}

bool SoundsListLoader::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

std::vector< sdl2::Mix_ChunkPtr >::iterator SoundsListLoader::begin()
{
	return soundsChunks.begin();
}

std::vector< sdl2::Mix_ChunkPtr >::iterator SoundsListLoader::end()
{
	return soundsChunks.end();
}

std::vector< sdl2::Mix_ChunkPtr >& SoundsListLoader::getLoadedData()
{
	return soundsChunks;
}

void SoundsListLoader::openSoundFilesList(AppLogFiles& logs, const fs::path& listFile, const fs::path& soundFilesDirectory)
{
	if( std::ifstream soundListFile{ listFile } )
	{
		readFileLines(logs, soundFilesDirectory, soundListFile );
	}
	else{
		isLoadingPerfect = false;
		logs.error.wrFileOpeningError(listFile.string(), "load the waveform files for the sound system");
	}
}

void SoundsListLoader::readFileLines(AppLogFiles& logs, const fs::path& soundFilesDirectory, std::ifstream& inputFile)
{
	std::string fileLine;
	while( std::getline( inputFile, fileLine ) )
	{
		loadSound(logs, fileLine, soundFilesDirectory);
	}
}

void SoundsListLoader::loadSound(AppLogFiles& logs, const fs::path& fileName, const fs::path& soundFilesDirectory)
{
	if( sdl2::Mix_ChunkPtr sound{ loadSoundChunk( logs.error, soundFilesDirectory / fileName ) } )
	{
		soundsChunks.emplace_back( std::move(sound) );
	}
	else{
		logs.error.wrFileOpeningError(soundFilesDirectory / fileName, "load waveform sound.");
		isLoadingPerfect = false;
	}
}
