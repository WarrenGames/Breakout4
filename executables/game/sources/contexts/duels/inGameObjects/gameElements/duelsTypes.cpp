#include "contexts/duels/inGameObjects/gameElements/duelsTypes.h"
#include "logging/logsStruct.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "prefPath/prefPathFinder.h"
#include <algorithm>

duels::LevelOptions::LevelOptions(AppLogFiles& logs, const PrefPathFinder& prefPath):
	bonuses(duels::DuelBonusMax),
	playersScores( duels::PlayerMax, 0 ),
	pointsToPlayInZone{20},
	secondsBeforeNewCoin{10},
	coinsMax{2},
	secondsBeforeNewBall{10},
	ballsMax{2}
{
	if( std::ifstream granularityFile{ path::getConfigDirFile(prefPath, file::BONUS_DEFAULT_GRANULARITY) } )
	{
		for( auto &bonus : bonuses )
		{
			if( !( granularityFile >> bonus ) )
			{
				logs.error << "Error: reading '" << path::getConfigDirFile(prefPath, file::BONUS_DEFAULT_GRANULARITY) << "' file has failed.\n";
			}
			
		}
	}
	else{
		std::fill(bonuses.begin(), bonuses.end(), 0);
	}
}

void duels::LevelOptions::avoidBadMaxValues()
{
	if( coinsMax > 4 )
	{
		coinsMax = 4;
	}
	if( ballsMax > 4 )
	{
		ballsMax = 4;
	}
}

void duels::LevelOptions::setChampionshipEnd(unsigned finalScore, bool& quitZone) const
{
	if( std::any_of(playersScores.cbegin(), playersScores.cend(), [finalScore](auto score){return score >= static_cast<int>(finalScore); } ) )
		quitZone = true;
}
