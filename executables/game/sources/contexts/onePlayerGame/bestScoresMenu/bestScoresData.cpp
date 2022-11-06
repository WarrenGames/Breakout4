#include "contexts/onePlayerGame/bestScoresMenu/bestScoresData.h"
#include "types/essentialsStruct.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "time/dateAndTime.h"
#include "consts/constPaths.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <algorithm>

constexpr std::size_t MaxScoresPerSkill = 10;

ScoreSample::ScoreSample():
	score{0},
	date{ "1970-01-01" },
	scoreFromLastGame{false}
{
	
}

ScoreSample::ScoreSample(unsigned readScore, const std::string& readDate):
	score{readScore},
	date{readDate},
	scoreFromLastGame{false}
{
	
}

ScoreSample::ScoreSample(unsigned lastGameScore):
	score{lastGameScore},
	scoreFromLastGame{true}
{
	date = returnCurrentDate();
}

std::string ScoreSample::getText() const
{
	return std::string{std::to_string(score) + " points, " + date };
}

BestScoresData::BestScoresData(Essentials& essentials, unsigned campaignType):
	scores( onePlGame::SkillLevelMax ),
	campaignTypeValue{campaignType},
	isLoadingPerfect{true}
{
	loadScores(essentials, campaignType);
	sortAllScoresArrays();
}

BestScoresData::BestScoresData(Essentials& essentials, unsigned campaignType, unsigned lastGameScore, unsigned skill, unsigned scoreCampaignType):
	scores( onePlGame::SkillLevelMax ),
	campaignTypeValue{campaignType},
	isLoadingPerfect{true}
{
	assert( skill < onePlGame::SkillLevelMax );
	loadScores(essentials, campaignType);
	addScoreFromLastGame(lastGameScore, skill, scoreCampaignType);
	sortAllScoresArrays();
}

void BestScoresData::loadScores(Essentials& essentials, unsigned campaignType)
{
	for( unsigned skill{0} ; skill < onePlGame::SkillLevelMax ; ++skill )
	{
		switch( campaignType )
		{
			case onePlGame::CampaignWithShop:
				loadScoresList(essentials, skill, path::getShopRaceBestScoresFilePath(essentials.prefPath, skill) );
				break;
			case onePlGame::CampaignNoShop:
				loadScoresList(essentials, skill, path::getStdRaceBestScoresFilePath(essentials.prefPath, skill) );
				break;
		}
	}
}

void BestScoresData::loadScoresList(Essentials& essentials, unsigned skillNumber, const std::string& scoreFilePath)
{
	assert( skillNumber < scores.size() );
	if( std::ifstream scoresFile{ scoreFilePath } )
	{
		std::size_t readLines{0};
		std::string fileLine;
		unsigned playerScore{0};
		std::string date;
		while( std::getline(scoresFile, fileLine) && readLines < MaxScoresPerSkill )
		{
			readLines++;
			std::istringstream lineStream{fileLine};
			if( lineStream >> playerScore >> date )
			{
				scores[skillNumber].emplace_back( ScoreSample{playerScore, date} );
			}
			else{
				isLoadingPerfect = false;
				essentials.logs.error << "Error: loading score line number " << readLines << " failed in the following file: " << scoreFilePath << " .\n";
			}
		}
		
	}
	else{
		isLoadingPerfect = false;
		essentials.logs.error << "Error: couldn't open '" << scoreFilePath << "' file in order to 'load' best scores for skill number #" << skillNumber << " .\n";
	}
}

const ScoreSample& BestScoresData::getSample(std::size_t skill, std::size_t scoreNumber) const
{
	assert( skill < scores.size() );
	assert( scoreNumber < scores[skill].size() );
	return scores[skill][scoreNumber];
}

std::size_t BestScoresData::getScoresNumber(std::size_t skill) const
{
	return scores[skill].size();
}

void BestScoresData::startSaving(Essentials& essentials) const
{
	for( unsigned skill{0} ; skill < onePlGame::SkillLevelMax ; ++skill )
	{
		switch( campaignTypeValue )
		{
			case onePlGame::CampaignWithShop:
				saveScoresToFile(essentials, path::getShopRaceBestScoresFilePath(essentials.prefPath, skill), skill);
				break;
			case onePlGame::CampaignNoShop:
				saveScoresToFile(essentials, path::getStdRaceBestScoresFilePath(essentials.prefPath, skill), skill );
				break;
		}
	}
}

void BestScoresData::saveScoresToFile(Essentials& essentials, const std::string& scoreFilePath, unsigned skill) const
{
	if( std::ofstream scoreFile{ scoreFilePath } )
	{
		for( std::size_t line{0} ; line < scores[skill].size() && line < MaxScoresPerSkill ; ++line )
		{
			scoreFile << scores[skill][line].score << " " << scores[skill][line].date << '\n';
		}
	}
	else{
		essentials.logs.error << "Error: couldn't open '" << scoreFilePath << "' file in order to 'save' best scores for skill number #" << skill << " .\n";
	}
}

void BestScoresData::addScoreFromLastGame(unsigned lastGameScore, unsigned skill, unsigned scoreCampaignType)
{
	if( campaignTypeValue == scoreCampaignType )
	{
		scores[skill].emplace_back(ScoreSample{lastGameScore});
	}
}

void BestScoresData::sortAllScoresArrays()
{
	for( auto &array : scores )
	{
		std::sort(array.begin(), array.end(), [](auto &a, auto &b){return a.score > b.score;} );
	}
}