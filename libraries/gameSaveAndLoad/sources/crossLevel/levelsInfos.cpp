#include "crossLevel/levelsInfos.h"
#include "logging/logsStruct.h"
#include "consts/onePlayerLevelConsts.h"
#include <cassert>

namespace levelConfigFile{
	constexpr unsigned LevelType = 0;
	constexpr unsigned Grid = 10;
	constexpr unsigned Monsters = 20;
	constexpr unsigned Elements = 21;
}

SingleLevelInfos::SingleLevelInfos():
	levelType{onePlGame::EpisodeSimple}
{
	
}

LevelsInfos::LevelsInfos(AppLogFiles& logs, unsigned gameType, const fs::path& levelsListPath):
	campaignFilesDirectory{ getLevelsPath(gameType) }
{
	loadLevelsList(logs, levelsListPath);
}


unsigned LevelsInfos::getLevelType(std::size_t levelIndex) const
{
	assert( levelIndex < levelsListing.size() );
	return levelsListing[levelIndex].levelType;
}

const std::string& LevelsInfos::getMainLevelFileName(std::size_t levelIndex) const
{
	assert( levelIndex < levelsListing.size() );
	return levelsListing[levelIndex].mainLevelFileName;
}

const std::string& LevelsInfos::getMatrixPath(std::size_t levelIndex) const
{
	assert( levelIndex < levelsListing.size() );
	return levelsListing[levelIndex].levelGridPath;
}

const std::string& LevelsInfos::getMonstersFilePath(std::size_t levelIndex) const
{
	assert( levelIndex < levelsListing.size() );
	return levelsListing[levelIndex].monsterFileName;
}

const std::string& LevelsInfos::getElementsFilePath(std::size_t levelIndex) const
{
	assert( levelIndex < levelsListing.size() );
	return levelsListing[levelIndex].elementsFileName;
}

void LevelsInfos::setCampaignFilesDirectory(unsigned gameType)
{
	campaignFilesDirectory = getLevelsPath(gameType);
}

void LevelsInfos::loadLevelsList(AppLogFiles& logs, const fs::path& levelsListPath)
{
	if( std::ifstream levelsListFile{levelsListPath} )
	{
		logs.warning << "Level listing file : " << levelsListPath.string() << " opened with success.\n";
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

std::size_t LevelsInfos::size() const
{
	return levelsListing.size();
}

void LevelsInfos::readLevelConfigFile(AppLogFiles& logs, const std::string& levelConfigFileName)
{
	if( std::ifstream levelConfigFile{ campaignFilesDirectory + levelConfigFileName} )
	{
		std::string fileLine;
		SingleLevelInfos levelInfos;
		levelInfos.mainLevelFileName = levelConfigFileName;
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
		levelsListing.emplace_back( std::move(levelInfos) );
	}
	else
	{
		logs.error << "Error: couldn't open the following file: " << campaignFilesDirectory << levelConfigFileName << " .\n";
	}
}

void LevelsInfos::triggerLoadingWithIndex(AppLogFiles& logs, std::istringstream& lineStream, const std::string& levelConfigFileName, SingleLevelInfos& levelInfos, unsigned index)
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

void LevelsInfos::setGameType(AppLogFiles& logs, std::istringstream& lineStream, const std::string& levelConfigFileName, SingleLevelInfos& levelInfos)
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

void LevelsInfos::setFileName(AppLogFiles& logs, std::istringstream& lineStream, const std::string& levelConfigFileName, std::string& fileName)
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

std::string LevelsInfos::getLevelsPath(std::size_t gameType) const
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
