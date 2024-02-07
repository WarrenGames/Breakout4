#include "levelComponents/hellEpisodeThings/fireBalls/configuration/fireBallDataLoader.h"
#include "crossLevel/playerData.h"
#include "types/essentialsStruct.h"
#include "consts/onePlayerLevelConsts.h"
#include <sstream>

onePlGame::FireBallDataLoader::FireBallDataLoader(Essentials& essentials, const PlayerData& playerData):
	isLoadingPerfect{true}
{
	populateFireBallsCont(essentials, playerData);
}

bool onePlGame::FireBallDataLoader::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

void onePlGame::FireBallDataLoader::populateFireBallsCont(Essentials& essentials, const PlayerData& playerData)
{
	if( playerData.getLevelType() == onePlGame::EpisodeHell )
	{
		if( std::ifstream fireBallsFile{ playerData.getElementsFilePath() } )
		{
			essentials.logs.warning << "Opening '" << playerData.getElementsFilePath() << "' file with success in order to load hell fire balls data.\n";
			readLinesOfConfigFile(essentials, playerData, fireBallsFile);
		}
		else{
			essentials.logs.error << "Error: couldn't open '" << playerData.getElementsFilePath() << "' file in order to load hell fire balls data.\n";
			isLoadingPerfect = false;
		}
	}
}

void onePlGame::FireBallDataLoader::readLinesOfConfigFile(Essentials& essentials, const PlayerData& playerData, std::ifstream& fireBallFile)
{
	std::string fileLine;
	FireBallFileData data;
	std::size_t lineNum{1};
	while( std::getline( fireBallFile, fileLine ) )
	{
		std::istringstream lineStream{ fileLine };
		if( lineStream  >> data.id 
						>> data.behaviorId 
						>> data.skillBits 
						>> data.sqrSizeRelativePos 
						>> data.totalWaitTime 
						>> data.randomTimeInterval 
						>> data.seedAdd )
		{
			fireBalls.push_back( data );
		}
		else{
			essentials.logs.error << "Error: failed to load single line of '" << playerData.getElementsFilePath() << "' file at line number " << lineNum << " .\n";
			isLoadingPerfect = false;
		}
		lineNum++;
	}
}

std::vector< FireBallFileData >::const_iterator onePlGame::FireBallDataLoader::begin() const
{
	return fireBalls.cbegin();
}

std::vector< FireBallFileData >::const_iterator onePlGame::FireBallDataLoader::end() const
{
	return fireBalls.cend();
}