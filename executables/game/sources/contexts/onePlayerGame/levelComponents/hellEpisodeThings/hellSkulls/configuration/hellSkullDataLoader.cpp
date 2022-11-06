#include "contexts/onePlayerGame/levelComponents/hellEpisodeThings/hellSkulls/configuration/hellSkullDataLoader.h"
#include "crossLevel/playerData.h"
#include "types/essentialsStruct.h"
#include "consts/onePlayerLevelConsts.h"
#include <sstream>
#include <cassert>

onePlGame::HellSkullDataLoader::HellSkullDataLoader(Essentials& essentials, const PlayerData& playerData):
	isLoadingPerfect{true}
{
	populateSkullDataCont(essentials, playerData);
}

bool onePlGame::HellSkullDataLoader::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

void onePlGame::HellSkullDataLoader::populateSkullDataCont(Essentials& essentials, const PlayerData& playerData)
{
	if( playerData.getLevelType() == onePlGame::EpisodeHell )
	{
		if( std::ifstream skullFile{ playerData.getMonstersFilePath() } )
		{
			essentials.logs.warning << ">> Opening '" << playerData.getMonstersFilePath() << "' file with success in order to load hell skull data.\n";
			readLinesOfConfigFile(essentials, playerData, skullFile);
		}
		else{
			essentials.logs.error << "Error: couldn't open '" << playerData.getMonstersFilePath() << "' file in order to load hell skull data.\n";
			isLoadingPerfect = false;
		}
	}
}

void onePlGame::HellSkullDataLoader::readLinesOfConfigFile(Essentials& essentials, const PlayerData& playerData, std::ifstream& skullFile)
{
	std::string fileLine;
	SkullFileData data;
	std::size_t lineNum{1};
	while( std::getline( skullFile, fileLine ) )
	{
		std::istringstream lineStream{ fileLine };
		if( lineStream >> data.id 
						>> data.skillBits 
						>> data.startingPos.x 
						>> data.startingPos.y 
						>> data.startingDirection.x 
						>> data.startingDirection.y
						>> data.initialSpeed 
						>> data.canThrowFireBalls 
						>> data.canSeekYellowBall )
		{
			data.startingPos.x *= SQR_SIZE;
			data.startingPos.y *= SQR_SIZE;
			skulls.push_back( std::move(data) );
		}
		else{ 
			essentials.logs.error << "Error: failed to load single line of '" << playerData.getMonstersFilePath() << "' file at line number " << lineNum << " .\n";
			isLoadingPerfect = false;
		}
		lineNum++;
	}
}

std::size_t onePlGame::HellSkullDataLoader::size() const
{
	return skulls.size();
}

std::vector< SkullFileData >::const_iterator onePlGame::HellSkullDataLoader::begin() const
{
	return skulls.cbegin();
}

std::vector< SkullFileData >::const_iterator onePlGame::HellSkullDataLoader::end() const
{
	return skulls.cend();
}

const SkullFileData& onePlGame::HellSkullDataLoader::operator[](std::size_t index) const
{
	assert( index < skulls.size() );
	return skulls[index];
}