#include "contexts/onePlayerGame/levelComponents/hellEpisodeThings/fireBalls/inGame/bottomScreenFireBallsPack.h"
#include "contexts/onePlayerGame/levelComponents/hellEpisodeThings/fireBalls/configuration/fireBallDataLoader.h"
#include "contexts/onePlayerGame/levelComponents/hellEpisodeThings/fireBalls/paths/fireBallPaths.h"
#include "crossLevel/playerData.h"
#include "generic/sounds/soundHandler.h"
#include "logging/logsStruct.h"
#include "consts/hellConsts.h"
#include <bitset>

onePlGame::BottomScrFireBalls::BottomScrFireBalls(AppLogFiles& logs, const PlayerData& playerData, const FireBallDataLoader& dataLoader, const FireBallsPaths& paths)
{
	populateVector(logs, playerData, dataLoader, paths);
}

void onePlGame::BottomScrFireBalls::populateVector(AppLogFiles& logs, const PlayerData& playerData, const FireBallDataLoader& dataLoader, const FireBallsPaths& paths)
{
	if( paths.wasLoadingPerfect() && paths.paths.size() >= hell::FB_PATH_BOTTOM_SCREEN )
	{
		for( auto const &fileData : dataLoader )
		{
			std::bitset< onePlGame::SKILL_LEVEL_MAX > skill{fileData.skillBits};
			if( fileData.behaviorId < paths.paths.size() )
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

void onePlGame::BottomScrFireBalls::update(OnePlayerRacket& racket, const SoundHandler& sounds)
{
	if( moveDelay.hasTimeElapsed( std::chrono::milliseconds{ hell::MOVE_DELAY } ) )
	{
		for( auto &fire : data )
		{
			if( fire )
			{
				fire->update();
				fire->updateWithRacket(racket, sounds);
			}
		}
		moveDelay.joinTimePoints();
	}
}

void onePlGame::BottomScrFireBalls::startActivity(const SoundHandler& sounds)
{
	for( auto &fire : data )
	{
		if( fire )
		{
			fire->startActivity(sounds);
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