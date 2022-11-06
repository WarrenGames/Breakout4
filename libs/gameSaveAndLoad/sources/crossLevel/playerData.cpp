#include "crossLevel/playerData.h"
#include "gameSlots/gameSlotData.h"
#include "logging/logsStruct.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/constPaths.h"
#include <sstream>
#include <cassert>

namespace onePlGame{
	constexpr char BagFilesDirectory[] = "data/levels/1player/options/";
	constexpr char EasyBagFile[] = "easyBagBonuses.cfg";
	constexpr char IntermediateBagFile[] = "intermediateBagBonuses.cfg";
	constexpr char HardBagFile[] = "hardBagBonuses.cfg";
}

namespace levelConfigFile{
	constexpr unsigned LevelType = 0;
	constexpr unsigned Grid = 10;
	constexpr unsigned Monsters = 20;
	constexpr unsigned Elements = 21;
}

LevelInfos::LevelInfos():
	levelType{onePlGame::EpisodeSimple}
{
	
}

PlayerData::PlayerData(AppLogFiles& logs, unsigned gameType_, unsigned skillLevel_, const std::string& levelsListPath):
	gameType{gameType_},
	skillLevel{skillLevel_},
	score{0},
	campaignFilesDirectory{ getLevelsPath(gameType_) },
	levelCursor{0},
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
	assert( gameType_ < onePlGame::CampaignMax && "Error: bad campaign value" );
	loadLevelsList(logs, levelsListPath);
	initPlayerData(logs);
}

PlayerData::PlayerData():
	gameType{onePlGame::CampaignMax},
	skillLevel{onePlGame::SkillLevelMax},
	score{0},
	levelCursor{0},
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
	campaignFilesDirectory = getLevelsPath(gameType);
	loadLevelsList(logs, path::getRaceLevelList(gameType) );
}

PlayerData& PlayerData::operator= ( const GameSlotData& slot )
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
		case levelConfigFile::LevelType:
			setGameType(logs, lineStream, levelConfigFileName, levelInfos);
			break;
		case levelConfigFile::Grid:
			setFileName(logs, lineStream, levelConfigFileName, levelInfos.levelGridPath);
			break;
		case levelConfigFile::Monsters:
			setFileName(logs, lineStream, levelConfigFileName, levelInfos.monsterFileName);
			break;
		case levelConfigFile::Elements:
			setFileName(logs, lineStream, levelConfigFileName, levelInfos.elementsFileName);
			break;
		default:
			assert( false && "Error: wrong index type:" );
			break;
	}
}

void PlayerData::setGameType(AppLogFiles& logs, std::istringstream& lineStream, const std::string& levelConfigFileName, LevelInfos& levelInfos)
{
	unsigned episodeTypeValue{onePlGame::EpisodeSimple};
	if( lineStream >> episodeTypeValue )
	{
		levelInfos.levelType = episodeTypeValue;
	}
	else{
		logs.error << "Error: couldn't read episode type value in '" << levelConfigFileName << "' file. index = " << levelConfigFile::LevelType << " .\n";
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
		logs.error << "Error: couldn't read grid file name in '" << levelConfigFileName << "' file (index = " << levelConfigFile::Grid << " ).\n";
	}
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

std::string PlayerData::getLevelsPath(std::size_t gameType) const
{
	switch( gameType )
	{
		case onePlGame::CampaignWithShop:
			return "data/levels/1player/shopRace/";
			break;
		case onePlGame::CampaignNoShop:
			return "data/levels/1player/stdRace/";
			break;
		default:
			assert( false && "Error: bad game type value!" );
			return "error!";
			break;
	}
}

void PlayerData::addBonusToBag(std::size_t bonusIndex)
{
	assert( bonusIndex < bonusesInBag.size() );
	bonusesInBag[bonusIndex]++;
}
