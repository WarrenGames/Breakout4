#include "generic/sounds/loadGameSounds.h"
#include "generic/sounds/soundStructs.h"
#include "logging/logFile.h"

void soundLoad::readLines(LogFile& log, const std::string& filePath, std::vector< SoundSpecifications >& sounds, bool& sndHandlerLoadWasPerfect)
{
	if( std::ifstream file{filePath} )
	{
		SoundData data{};
		while( std::getline(file, data.fileLine) )
		{
			std::istringstream lineStream{data.fileLine};
			soundLoad::loadSoundPath(log, filePath, lineStream, data.soundPath, data.wasLoadingPerfect, data.fileLineNumber);
			soundLoad::loadGroupValue(log, filePath, lineStream, data.groupTag, data.wasLoadingPerfect, data.fileLineNumber);
			soundLoad::putDataIntoVector(log, sounds, data, sndHandlerLoadWasPerfect);
		}
	}
}

void soundLoad::loadSoundPath(LogFile& log, const std::string& filePath, std::istringstream& lineStream, std::string& soundPath, bool& wasLoadingPerfect, unsigned fileLineNumber)
{
	if( !( lineStream >> soundPath ) )
	{
		log.wrReadErrorMessage(filePath, "sound path", fileLineNumber);
		wasLoadingPerfect = false;
	}
}

void soundLoad::loadGroupValue(LogFile& log, const std::string& filePath, std::istringstream& lineStream, int& groupTag, bool& wasLoadingPerfect, unsigned fileLineNumber)
{
	if( !( lineStream >> groupTag ) )
	{
		log.wrReadErrorMessage(filePath, "groupTagValue", fileLineNumber);
		wasLoadingPerfect = false;
	}
	
}

void soundLoad::putDataIntoVector(LogFile& log, std::vector<SoundSpecifications>& sounds, const SoundData& soundData, bool& sndHandlerLoadWasPerfect)
{
	if( soundData.wasLoadingPerfect )
	{
		sounds.emplace_back( SoundSpecifications{log, soundData.soundPath, soundData.groupTag} );
	}
	else{
		sndHandlerLoadWasPerfect = false;
	}
}