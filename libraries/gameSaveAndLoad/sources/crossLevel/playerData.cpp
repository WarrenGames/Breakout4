#include "crossLevel/playerData.h"
#include "gameSlots/gameSlotData.h"
#include "logging/logsStruct.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/onePlayerBonusesConsts.h"
#include "consts/constPaths.h"
#include "consts/rimsConsts.h"
#include "demos/consts/demosConsts.h"
#include <sstream>
#include <cassert>

namespace onePlGame{
	constexpr char BagFilesDirectory[] = "data/levels/1player/options/";
	constexpr char EasyBagFile[] = "easyBagBonuses.cfg";
	constexpr char IntermediateBagFile[] = "intermediateBagBonuses.cfg";
	constexpr char HardBagFile[] = "hardBagBonuses.cfg";
}

PlayerData::PlayerData(AppLogFiles& logs, unsigned campaignType_, unsigned skillLevel_, const fs::path& levelsListPath, unsigned demoEnumValue):
	campaignType{campaignType_},
	skillLevel{skillLevel_},
	playerLives{0},
	racketSize{ onePlGame::SmallRacket },
	racketSpeed{ onePlGame::RacketStartingSpeed },
	score{0},
	bonusCoinsNumber{0},
	rimsStartState{ rims::RimNullState },
	demoKind{ demoEnumValue },
	levelsInfos{logs, campaignType_, levelsListPath},
	levelIndex{0},
	bonusesInBag(onePlGame::BonusMax, 0),
	bonusesCosts{	onePlGame::bcost::StickyRacket, 
					onePlGame::bcost::RacketSpeedUp, 
					onePlGame::bcost::EnlargeRacket, 
					onePlGame::bcost::EnlargeRims, 
					onePlGame::bcost::PowerBall, 
					onePlGame::bcost::OneUp}
{
	assert( bonusesCosts.size() == onePlGame::BonusMax );
	assert( skillLevel < onePlGame::SkillLevelMax && "Error: bad skill level value in 'PlayerData' struct" );
	assert( campaignType_ < onePlGame::CampaignMax && "Error: bad campaign value" );
	assert( demoKind < demos::GameDemoEnumMax && "Error: bad demo kind unsigned value" );
	initPlayerData(logs);
}

PlayerData::PlayerData(unsigned demoEnumValue):
	campaignType{onePlGame::CampaignMax},
	skillLevel{onePlGame::SkillLevelMax},
	playerLives{0},
	racketSize{ onePlGame::SmallRacket },
	racketSpeed{ onePlGame::RacketStartingSpeed },
	score{0},
	bonusCoinsNumber{0},
	rimsStartState{ rims::RimNullState },
	demoKind{ demoEnumValue },
	levelIndex{0},
	bonusesInBag(onePlGame::BonusMax, 0),
	bonusesCosts{	onePlGame::bcost::StickyRacket, 
					onePlGame::bcost::RacketSpeedUp, 
					onePlGame::bcost::EnlargeRacket, 
					onePlGame::bcost::EnlargeRims, 
					onePlGame::bcost::PowerBall, 
					onePlGame::bcost::OneUp}
{
	assert( bonusesCosts.size() == onePlGame::BonusMax );
}

void PlayerData::laterInitialization(AppLogFiles& logs)
{
	//The operator= with the GameSlotData function must be used before using this function
	levelsInfos.setCampaignFilesDirectory(campaignType);
	levelsInfos.loadLevelsList(logs, path::getRaceLevelList(campaignType) );
}

PlayerData& PlayerData::operator= ( const GameSlotData& slot )
{
	campaignType = slot.campaignType;
	skillLevel = slot.skillLevel;
	playerLives = slot.playerLives;
	racketSpeed = slot.racketSpeed;
	racketSize = slot.racketSize;
	score = slot.score;
	bonusCoinsNumber = slot.bonusCoinNumber;
	rimsStartState = slot.rimsStartState;
	levelIndex = slot.levelCursor;
	bonusesInBag = slot.bonusesInBag;
	return *this;
}

void PlayerData::readBonusesInBagConfigurationFile(AppLogFiles& logs, const std::string& filePath)
{
	if( std::ifstream skillBagBonusesConfigFile{onePlGame::BagFilesDirectory + filePath} )
	{
		for( std::size_t i{0} ; i < onePlGame::BonusMax ; ++i )
		{
			assert( i < bonusesInBag.size() );
			if( ! ( skillBagBonusesConfigFile >> bonusesInBag[i] ) )
			{
				logs.error << "Error: couldn't load the " << i << "th bonus in '" << filePath << "' file.\n";
			}
		}
	}
	else{
		logs.error << "Error: couldn't open '" << filePath << "' file in order to load the bag bonuses configuration.\n";
	}
}

void PlayerData::initPlayerData(AppLogFiles& logs)
{
	switch( skillLevel )
	{
		case onePlGame::SkillLevelEasy:
			easyInit();
			readBonusesInBagConfigurationFile(logs, onePlGame::EasyBagFile );
			break;
		case onePlGame::SkillLevelIntermediate:
			intermInit();
			readBonusesInBagConfigurationFile(logs, onePlGame::IntermediateBagFile);
			break;
		case onePlGame::SkillLevelHard:
			hardInit();
			readBonusesInBagConfigurationFile(logs, onePlGame::HardBagFile);
			break;
		default:
			assert( false && "Error: bad skill level value");
			break;
	}
}

void PlayerData::easyInit()
{
	playerLives = 5;
	racketSpeed = 3.2;
	racketSize = onePlGame::MediumRacket;
	bonusCoinsNumber = 0;
	rimsStartState = 0;
}

void PlayerData::intermInit()
{
	playerLives = 3;
	racketSpeed = 3.1;
	racketSize = onePlGame::SmallRacket;
	bonusCoinsNumber = 0;
	rimsStartState = -1;
}

void PlayerData::hardInit()
{
	playerLives = 1;
	racketSpeed = 3;
	racketSize = onePlGame::SmallRacket;
	bonusCoinsNumber = 0;
	rimsStartState = -1;
}

void PlayerData::setCursorToNextLevel()
{
	if( demoKind == demos::GameHasPlayerInputs )
	{
		++levelIndex;
	}
}

bool PlayerData::buyABonusIfPossible(std::size_t bonusIndex)
{
	assert( bonusIndex < onePlGame::BonusMax );
	if( bonusCoinsNumber >= bonusesCosts[bonusIndex] )
	{
		addBonusToBag(bonusIndex);
		bonusCoinsNumber -= bonusesCosts[bonusIndex];
		return true;
	}
	else{
		return false;
	}
}

void PlayerData::addBonusToBag(std::size_t bonusIndex)
{
	assert( bonusIndex < bonusesInBag.size() );
	bonusesInBag[bonusIndex]++;
}

unsigned PlayerData::getLevelType() const
{
	return levelsInfos.getLevelType(levelIndex);
}

std::string PlayerData::getMainLevelFileName() const
{
	return levelsInfos.getMainLevelFileName(levelIndex);
}

std::string PlayerData::getMatrixPath() const
{
	return levelsInfos.getMatrixPath(levelIndex);
}

std::string PlayerData::getElementsFilePath() const
{
	return levelsInfos.getElementsFilePath(levelIndex);
}

std::string PlayerData::getMonstersFilePath() const
{
	return levelsInfos.getMonstersFilePath(levelIndex);
}