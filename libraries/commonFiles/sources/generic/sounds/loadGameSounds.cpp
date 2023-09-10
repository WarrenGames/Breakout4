#include "generic/sounds/loadGameSounds.h"
#include "generic/sounds/soundStructs.h"
#include "logging/logsStruct.h"

void soundLoad::readLines(AppLogFiles& logs, const fs::path& filePath, std::vector< SoundSpecifications >& sounds, bool& sndHandlerLoadWasPerfect)
{
	if( std::ifstream file{filePath} )
	{
		SoundData data{};
		while( std::getline(file, data.fileLine) )
		{
			std::istringstream lineStream{data.fileLine};
			soundLoad::loadSoundPath(logs, filePath, lineStream, data.soundPath, data.wasLoadingPerfect, data.fileLineNumber);
			soundLoad::loadGroupValue(logs, filePath, lineStream, data.groupTag, data.wasLoadingPerfect, data.fileLineNumber);
			soundLoad::putDataIntoVector(logs, sounds, data, sndHandlerLoadWasPerfect);
		}
	}
}

void soundLoad::loadSoundPath(AppLogFiles& logs, const fs::path& filePath, std::istringstream& lineStream, fs::path& soundPath, bool& wasLoadingPerfect, unsigned fileLineNumber)
{
	if( !( lineStream >> soundPath ) )
	{
		logs.error.wrReadErrorMessage(filePath, "sound path", fileLineNumber);
		wasLoadingPerfect = false;
	}
}

void soundLoad::loadGroupValue(AppLogFiles& logs, const fs::path& filePath, std::istringstream& lineStream, int& groupTag, bool& wasLoadingPerfect, unsigned fileLineNumber)
{
	if( !( lineStream >> groupTag ) )
	{
		logs.error.wrReadErrorMessage(filePath, "groupTagValue", fileLineNumber);
		wasLoadingPerfect = false;
	}
	
}

void soundLoad::putDataIntoVector(AppLogFiles& logs, std::vector<SoundSpecifications>& sounds, const SoundData& soundData, bool& sndHandlerLoadWasPerfect)
{
	if( soundData.wasLoadingPerfect )
	{
		sounds.emplace_back( SoundSpecifications{logs.error, soundData.soundPath.string(), soundData.groupTag} );
	}
	else{
		sndHandlerLoadWasPerfect = false;
	}
}