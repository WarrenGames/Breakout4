#include "duels/inGameObjects/gameElements/duelsLevelOptions.h"
#include "logging/logsStruct.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "prefPath/prefPathFinder.h"
#include "consts/duelsConstexpr.h"
#include "consts/duelsSounds.h"
#include <algorithm>
#include <cassert>

duels::LevelOptions::LevelOptions(AppLogFiles& logs, const PrefPathFinder& prefPath):
	bonuses(duels::DuelBonusMax),
	playersScores( duels::PlayerMax, 0 ),
	pointsToPlayInZone{20},
	secondsBeforeNewCoin{10},
	coinsMax{2},
	secondsBeforeNewBall{10},
	ballsMax{2},
	currentZoneEnum{ duels::ZoneMax }
{
	if( std::ifstream granularityFile{ path::getConfigDirFile(prefPath, file::BonusDefaultGranularity) } )
	{
		for( auto &bonus : bonuses )
		{
			if( !( granularityFile >> bonus ) )
			{
				logs.error << "Error: reading '" << path::getConfigDirFile(prefPath, file::BonusDefaultGranularity) << "' file has failed.\n";
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

const fs::path& duels::LevelOptions::getSoundsListFilePath() const
{
	switch( currentZoneEnum )
	{
		case duels::ZoneStandard:
			return metalStrings.soundsListFilePath;
			break;
		case duels::ZoneHalloween:
			return halloween.soundsListFilePath;
			break;
		case duels::ZoneStrings:
			return metalStrings.soundsListFilePath;
			break;
		default:
			assert( false && "Error: bad 'current zone enum value." );
			return metalStrings.soundsListFilePath;
			break;
	}
}

const fs::path& duels::LevelOptions::getChannelsConfigFilePath() const
{
	switch( currentZoneEnum )
	{
		case duels::ZoneStandard:
			return metalStrings.channelsConfigFilePath;
			break;
		case duels::ZoneHalloween:
			return halloween.channelsConfigFilePath;
			break;
		case duels::ZoneStrings:
			return metalStrings.channelsConfigFilePath;
			break;
		default:
			assert( false && "Error: bad 'current zone enum value." );
			return metalStrings.channelsConfigFilePath;
			break;
	}
}

unsigned duels::LevelOptions::getExpectedSoundsNumber() const
{
	if( currentZoneEnum == duels::ZoneStandard || currentZoneEnum == duels::ZoneStrings )
	{
		return duels::SoundStandardMax;
	}
	else if( currentZoneEnum == duels::ZoneHalloween )
	{
		return duels::SoundHalloweenMax;
	}
	else{
		return duels::SoundStandardMax;
	}
}

int duels::LevelOptions::getExpectedGroupsTagNumber() const
{
	return static_cast<int>( duels::GroupTagMax );
}