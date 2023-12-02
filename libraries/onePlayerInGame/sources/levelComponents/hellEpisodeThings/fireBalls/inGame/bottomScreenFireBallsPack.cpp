#include "levelComponents/hellEpisodeThings/fireBalls/inGame/bottomScreenFireBallsPack.h"
#include "levelComponents/hellEpisodeThings/fireBalls/configuration/fireBallDataLoader.h"
#include "levelComponents/hellEpisodeThings/fireBalls/paths/fireBallPaths.h"
#include "crossLevel/playerData.h"
#include "soundSystem/soundsPlayer.h"
#include "logging/logsStruct.h"
#include "consts/hellConsts.h"
#include <bitset>

onePlGame::BottomScrFireBalls::BottomScrFireBalls(AppLogFiles& logs, const PlayerData& playerData, const FireBallDataLoader& dataLoader, const FireBallsPaths& paths)
{
	populateVector(logs, playerData, dataLoader, paths);
}

void onePlGame::BottomScrFireBalls::populateVector(AppLogFiles& logs, const PlayerData& playerData, const FireBallDataLoader& dataLoader, const FireBallsPaths& paths)
{
	if( paths.wasLoadingPerfect() && paths.paths.getMovesCount() >= hell::FireBallPathBottomScreen )
	{
		for( auto const &fileData : dataLoader )
		{
			std::bitset< onePlGame::SkillLevelMax > skill{fileData.skillBits};
			if( fileData.behaviorId < paths.paths.getMovesCount() )
			{
				if( skill[playerData.skillLevel] )
				{
					data.emplace_back( std::make_unique<onePlGame::FireBallElement>( paths.paths.getPath(fileData.behaviorId), fileData ) );
				}
				else{
					data.emplace_back( nullptr );
				}
			}
			else{
				logs.error << "Error: bad 'behaviorId' value: " << fileData.behaviorId << " for the bottom screen fire balls.\n";
			}
		}
	}
	else{
		logs.error << "Error: couldn't load 'bottom fire balls' because fire balls paths data wasn't well loaded.\n";
	}
}

void onePlGame::BottomScrFireBalls::update(OnePlayerRacket& racket, const SoundPlayer& soundPlayer)
{
	if( moveDelay.hasTimeElapsed( std::chrono::milliseconds{ hell::MoveDelay } ) )
	{
		moveDelay.joinTimePoints();
		for( auto &fire : data )
		{
			if( fire )
			{
				fire->update();
				fire->updateWithRacket(racket, soundPlayer);
			}
		}
	}
}

void onePlGame::BottomScrFireBalls::startActivity(const SoundPlayer& soundPlayer)
{
	for( auto &fire : data )
	{
		if( fire )
		{
			fire->startActivity(soundPlayer);
		}
	}
}

std::vector< std::unique_ptr< onePlGame::FireBallElement > >::const_iterator onePlGame::BottomScrFireBalls::begin() const
{
	return data.cbegin();
}

std::vector< std::unique_ptr< onePlGame::FireBallElement > >::const_iterator onePlGame::BottomScrFireBalls::end() const
{
	return data.cend();
}