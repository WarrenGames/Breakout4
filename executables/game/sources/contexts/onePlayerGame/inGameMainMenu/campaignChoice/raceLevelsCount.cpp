#include "contexts/onePlayerGame/inGameMainMenu/campaignChoice/raceLevelsCount.h"
#include "types/essentialsStruct.h"
#include <fstream>

RaceLevelsCount::RaceLevelsCount(Essentials& essentials, const fs::path& mainFilePath):
	levelsCount{0},
	isLoadingPerfect{true}
{
	loadFile(essentials, mainFilePath);
}

RaceLevelsCount::operator bool() const
{
	return isLoadingPerfect;
}

unsigned RaceLevelsCount::getLevelsNumber() const
{
	return levelsCount;
}

void RaceLevelsCount::loadFile(Essentials& essentials, const fs::path& mainFilePath)
{
	if( std::ifstream levelFile{mainFilePath} )
	{
		std::string fileLine;
		while( std::getline( levelFile, fileLine ) )
		{
			if( fileLine[0] != '#' )
				levelsCount++;
		}
	}
	else{
		essentials.logs.error << "Error: couldn't load '" << mainFilePath << "' levels file in order to count levels number.\n";
	}
}