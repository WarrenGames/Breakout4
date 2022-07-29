#include "crossLevel/playerData.h"
#include "gameSlots/gameSlotData.h"
#include "logging/logsStruct.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/constPaths.h"
#include <sstream>
#include <cassert>

namespace onePlGame{
	constexpr char BAG_FILES_DIR[] = "data/levels/1player/options/";
	constexpr char EASY_BAG_FILE[] = "easyBagBonuses.cfg";
	constexpr char INTERMEDIATE_BAG_FILE[] = "intermediateBagBonuses.cfg";
	constexpr char HARD_BAG_FILE[] = "hardBagBonuses.cfg";
}

namespace levelConfigFile{
	constexpr unsigned LEVEL_TYPE = 0;
	constexpr unsigned GRID = 10;
	constexpr unsigned MONSTERS = 20;
	constexpr unsigned ELEMENTS = 21;
}

LevelInfos::LevelInfos():
	levelType{onePlGame::EPISODE_SIMPLE}
{
	
}

PlayerData::PlayerData(AppLogFiles& logs, unsigned gameType_, unsigned skillLevel_, const std::string& levelsListPath):
	gameType{gameType_},
	skillLevel{skillLevel_},
	score{0},
	campaignFilesDirectory{ getLevelsPath(gameType_) },
	levelCursor{0},
	bonusesInBag(onePlGame::BONUS_MAX, 0),
	bonusesCosts{	onePlGame::bcost::STICKY_RACK, 
					onePlGame::bcost::RACK_SPEEDUP, 
					onePlGame::bcost::RACK_ENLARGE, 
					onePlGame::bcost::ENLARGE_RIM, 
					onePlGame::bcost::POWER_BALL, 
					onePlGame::bcost::ONE_UP}
{
	assert( bonusesCosts.size() == onePlGame::BONUS_MAX );
	assert( skillLevel < onePlGame::SKILL_LEVEL_MAX && "Error: bad skill level value in 'PlayerData' struct" );
	assert( gameType_ < onePlGame::CAMPAIGN_MAX && "Error: bad campaign value" );
	loadLevelsList(logs, levelsListPath);
	initPlayerData(logs);
}

PlayerData::PlayerData():
	gameType{onePlGame::CAMPAIGN_MAX},
	skillLevel{onePlGame::SKILL_LEVEL_MAX},
	score{0},
	levelCursor{0},
	bonusesInBag(onePlGame::BONUS_MAX, 0),
	bonusesCosts{	onePlGame::bcost::STICKY_RACK, 
					onePlGame::bcost::RACK_SPEEDUP, 
					onePlGame::bcost::RACK_ENLARGE, 
					onePlGame::bcost::ENLARGE_RIM, 
					onePlGame::bcost::POWER_BALL, 
					onePlGame::bcost::ONE_UP}
{
	assert( bonusesCosts.size() == onePlGame::BONUS_MAX );
}

void PlayerData::laterInitialization(AppLogFiles& logs)
{
	//The operator= with the GameSlotData function must be used before using this function
	campaignFilesDirectory = getLevelsPath(gameType);
	loadLevelsList(logs, path::getRaceLevelList(gameType) );
}

PlayerData& PlayerData::operator =( const GameSlotData& slot )
{
	gameType = slot.gameType;
	skillLevel = slot.skillLevel;
	playerLives = slot.playerLives;
	racketSpeed = slot.racketSpeed;
	racketSize = slot.racketSize;
	score = slot.score;
	bonusCoinsNumber = slot.bonusCoinNumber;
	rimsStartState = slot.rimsStartState;
	levelCursor = slot.levelCursor;
	bonusesInBag = slot.bonusesInBag;
	return *this;
}

void PlayerData::loadLevelsList(AppLogFiles& logs, const std::string& levelsListPath)
{
	if( std::ifstream levelsListFile{levelsListPath} )
	{
		logs.warning << ">> Level listing file : " << levelsListPath << " opened with success.\n";
		std::string fileLine;
		while( std::getline(levelsListFile, fileLine) )
		{
			if( fileLine[0] != '#' )
			{
				readLevelConfigFile(logs, fileLine);
			}
		}
	}
	else{
		logs.error << "Error: couldn't load levels listing file: " << levelsListPath << " .\n";
	}
}

void PlayerData::readLevelConfigFile(AppLogFiles& logs, const std::string& levelConfigFileName)
{
	if( std::ifstream levelConfigFile{ campaignFilesDirectory + levelConfigFileName} )
	{
		std::string fileLine;
		LevelInfos levelInfos;
		while( std::getline( levelConfigFile, fileLine ) )
		{
			std::istringstream lineStream{fileLine};
			unsigned index{0};
			if( lineStream >> index )
			{
				triggerLoadingWithIndex(logs, lineStream, levelConfigFileName, levelInfos, index);
			}
			else{
				logs.error << "Error: couldn't trigger the index value of '" << levelConfigFileName << "' file.\n";
			}
		}
		levelsListing.push_back( levelInfos );
	}
	else
	{
		logs.error << "Error: couldn't open the following file: " << campaignFilesDirectory << levelConfigFileName << " .\n";
	}
}

void PlayerData::triggerLoadingWithIndex(AppLogFiles& logs, std::istringstream& lineStream, const std::string& levelConfigFileName, LevelInfos& levelInfos, unsigned index)
{
	switch( index )
	{
		case levelConfigFile::LEVEL_TYPE:
			setGameType(logs, lineStream, levelConfigFileName, levelInfos);
			break;
		case levelConfigFile::GRID:
			setFileName(logs, lineStream, levelConfigFileName, levelInfos.levelGridPath);
			break;
		case levelConfigFile::MONSTERS:
			setFileName(logs, lineStream, levelConfigFileName, levelInfos.monsterFileName);
			break;
		case levelConfigFile::ELEMENTS:
			setFileName(logs, lineStream, levelConfigFileName, levelInfos.elementsFileName);
			break;
		default:
			assert( false && "Error: wrong index type:" );
			break;
	}
}

void PlayerData::setGameType(AppLogFiles& logs, std::istringstream& lineStream, const std::string& levelConfigFileName, LevelInfos& levelInfos)
{
	unsigned episodeTypeValue{onePlGame::EPISODE_SIMPLE};
	if( lineStream >> episodeTypeValue )
	{
		levelInfos.levelType = episodeTypeValue;
	}
	else{
		logs.error << "Error: couldn't read episode type value in '" << levelConfigFileName << "' file. index = " << levelConfigFile::LEVEL_TYPE << " .\n";
	}
}

void PlayerData::setFileName(AppLogFiles& logs, std::istringstream& lineStream, const std::string& levelConfigFileName, std::string& fileName)
{
	std::string readFileName;
	if( lineStream >> readFileName )
	{
		fileName = campaignFilesDirectory + readFileName;
	}
	else
	{
		logs.error << "Error: couldn't read grid file name in '" << levelConfigFileName << "' file (index = " << levelConfigFile::GRID << " ).\n";
	}
}

void PlayerData::readBonusesInBagConfigurationFile(AppLogFiles& logs, const std::string& filePath)
{
	if( std::ifstream skillBagBonusesConfigFile{onePlGame::BAG_FILES_DIR + filePath} )
	{
		for( std::size_t i{0} ; i < onePlGame::BONUS_MAX ; ++i )
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
		case onePlGame::SKILL_LEVEL_EASY:
			easyInit();
			readBonusesInBagConfigurationFile(logs, onePlGame::EASY_BAG_FILE );
			break;
		case onePlGame::SKILL_LEVEL_INTERMEDIATE:
			intermInit();
			readBonusesInBagConfigurationFile(logs, onePlGame::INTERMEDIATE_BAG_FILE);
			break;
		case onePlGame::SKILL_LEVEL_HARD:
			hardInit();
			readBonusesInBagConfigurationFile(logs, onePlGame::HARD_BAG_FILE);
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
	racketSize = onePlGame::MEDIUM_RACKET;
	bonusCoinsNumber = 0;
	rimsStartState = 0;
}

void PlayerData::intermInit()
{
	playerLives = 3;
	racketSpeed = 3.1;
	racketSize = onePlGame::SMALL_RACKET;
	bonusCoinsNumber = 0;
	rimsStartState = -1;
}

void PlayerData::hardInit()
{
	playerLives = 1;
	racketSpeed = 3;
	racketSize = onePlGame::SMALL_RACKET;
	bonusCoinsNumber = 0;
	rimsStartState = -1;
}

void PlayerData::setCursorToNextLevel()
{
	++levelCursor;
}

const std::string& PlayerData::getMatrixPath() const
{
	assert( levelCursor < levelsListing.size() );
	return levelsListing[levelCursor].levelGridPath;
}

const std::string& PlayerData::getMonstersFilePath() const
{
	assert( levelCursor < levelsListing.size() );
	return levelsListing[levelCursor].monsterFileName;
}

const std::string& PlayerData::getElementsFilePath() const
{
	assert( levelCursor < levelsListing.size() );
	return levelsListing[levelCursor].elementsFileName;
}

unsigned PlayerData::getLevelType() const
{
	assert( levelCursor < levelsListing.size() );
	return levelsListing[levelCursor].levelType;
}

bool PlayerData::buyABonusIfPossible(unsigned bonusIndex)
{
	assert( bonusIndex < onePlGame::BONUS_MAX );
	if( bonusCoinsNumber >= bonusesCosts[bonusIndex] )
	{
		bonusesInBag[bonusIndex]++;
		bonusCoinsNumber -= bonusesCosts[bonusIndex];
		return true;
	}
	else{
		return false;
	}
}

std::string PlayerData::getLevelsPath(unsigned gameType)
{
	switch( gameType )
	{
		case onePlGame::CAMPAIGN_WITH_SHOP:
			return "data/levels/1player/shopRace/";
			break;
		case onePlGame::CAMPAIGN_NO_SHOP:
			return "data/levels/1player/stdRace/";
			break;
		default:
			assert( false && "Error: bad game type value!" );
			return "error!";
			break;
	}
}

void PlayerData::setGameType()
{
	assert( levelCursor < levelsListing.size() );
	gameType = levelsListing[levelCursor].levelType;
}