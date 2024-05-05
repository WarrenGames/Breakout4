#include "levelComponents/antarcticEpisodeThings/stalactites/onePlayerStalactitesLoading.h"
#include "crossLevel/playerData.h"
#include "types/essentialsStruct.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/constexprScreen.h"
#include <sstream>
#include <fstream>
#include <string>
#include <bitset>

onePlGame::StalactitesLoading::StalactitesLoading(Essentials& essentials, const PlayerData& playerData):
	isLoadingPerfect{ true }
{
	loadStalactitesConfig(essentials, playerData);
	logEverythingWentFine(essentials, playerData);
}

bool onePlGame::StalactitesLoading::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

std::vector< OnePlayerStalactiteData >& onePlGame::StalactitesLoading::getData()
{
	return data;
}

void onePlGame::StalactitesLoading::loadStalactitesConfig(Essentials& essentials, const PlayerData& playerData)
{
	if( std::ifstream stalactiteFile{ playerData.getElementsFilePath() } )
	{
		unsigned lineNum{1};
		std::string fileLine;
		while( std::getline(stalactiteFile, fileLine) )
		{
			std::istringstream lineStream{fileLine};
			loadSingleStalactite(essentials, playerData, lineStream, lineNum);
			lineNum++;
		}
	}
	else{
		essentials.logs.error << "Error: couldn't load '" << playerData.getElementsFilePath() << "' file in order to load stalactites data.\n";
		isLoadingPerfect = false;
	}
}

void onePlGame::StalactitesLoading::loadSingleStalactite(Essentials& essentials, const PlayerData& playerData, std::istringstream& lineStream, unsigned lineNum)
{
	unsigned totalWaitTime{0};
	unsigned randomTime{0};
	AccurCoords squareUintPos;
	unsigned skillUint{0};
	unsigned pauseTime{0};
	if( lineStream >> skillUint >> squareUintPos.x >> squareUintPos.y >> totalWaitTime >> randomTime >> pauseTime )
	{
		std::bitset<onePlGame::SkillLevelMax> skillBitset{skillUint};
		if( skillBitset[playerData.skillLevel] )
		{
			data.emplace_back( OnePlayerStalactiteData{totalWaitTime, randomTime, pauseTime, 
						Offset{	static_cast<int>( squareUintPos.x * SQR_SIZE ), 
								static_cast<int>( squareUintPos.y * SQR_SIZE ) } } );
		}
	}
	else{
		essentials.logs.error << "Error: loading stalactite element for one player game failed at line #" << lineNum << " \n";
		isLoadingPerfect = false;
	}
}

void onePlGame::StalactitesLoading::logEverythingWentFine(Essentials& essentials, const PlayerData& playerData) const
{
	if( isLoadingPerfect )
	{
		essentials.logs.warning << data.size() << " stalactites total were loaded for one player game with ";
		switch( playerData.skillLevel )
		{
			case onePlGame::SkillLevelEasy:
				essentials.logs.warning << " easy skill.\n";
				break;
			case onePlGame::SkillLevelIntermediate:
				essentials.logs.warning << " intermediate skill.\n";
				break;
			case onePlGame::SkillLevelHard:
				essentials.logs.warning << " hard skill.\n";
				break;
		}
		essentials.logs.error.flushLog();
	}
}