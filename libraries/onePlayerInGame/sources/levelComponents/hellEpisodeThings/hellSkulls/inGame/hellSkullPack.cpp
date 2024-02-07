#include "levelComponents/hellEpisodeThings/hellSkulls/inGame/hellSkullPack.h"
#include "crossLevel/playerData.h"
#include "levelComponents/onePlayerRacket/onePlayerRacket.h"
#include "levelComponents/hellEpisodeThings/hellSkulls/configuration/hellSkullDataLoader.h"
#include "levelComponents/hellEpisodeThings/fireBalls/paths/fireBallPaths.h"
#include "logging/logsStruct.h"
#include "consts/hellConsts.h"
#include <cassert>

onePlGame::HellSkullPack::HellSkullPack(AppLogFiles& logs, const PlayerData& playerData, const FireBallsPaths& fireBallsPaths, const HellSkullDataLoader& dataLoader):
	isLoadingPerfect{ true }
{
	populateVector(logs, playerData, fireBallsPaths, dataLoader);
}

void onePlGame::HellSkullPack::populateVector(AppLogFiles& logs, const PlayerData& playerData, const FireBallsPaths& fireBallsPaths, const HellSkullDataLoader& dataLoader)
{
	assert( playerData.skillLevel < SkillLevelMax );
	if( fireBallsPaths.paths.getMovesCount() == hell::FireBallPathMax )
	{
		if( dataLoader.size() > 0 )
		{
			for( auto const &data : dataLoader )
			{
				std::bitset< SkillLevelMax > skill{data.skillBits};
				if( skill[playerData.skillLevel] )
				{
					hellSkulls.emplace_back( std::make_unique<HellSkullElement>(fireBallsPaths, data ) );
				}
				else{
					hellSkulls.emplace_back( nullptr );
				}
			}
		}
		else{
			isLoadingPerfect = false;
			logs.error << "Error: the hell skull file data was not loaded properly, it's size being equal to 0 .\n";
		}
	}
	else{
		isLoadingPerfect = false;
		logs.error << "Error: the fire balls paths data size is wrong; expected: " << hell::FireBallPathMax << " whereas the real size is: " << fireBallsPaths.paths.getMovesCount() << " .\n";
	}
}

bool onePlGame::HellSkullPack::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

void onePlGame::HellSkullPack::updateSkulls(const HellSkullDrawer& skullDrawer, const spriteMove::ObjectMoving& ballMove, const AllExplosions& explosions, const SoundPlayer& soundPlayer)
{
	for( auto &skull : hellSkulls )
	{
		if( skull )
		{
			skull->update(skullDrawer, ballMove, explosions, soundPlayer);
		}
	}
}

void onePlGame::HellSkullPack::withBallCollision(const HellSkullDrawer& skullDrawer, spriteMove::ObjectMoving& ballMove, const TextureCombo& ballTexture)
{
	for( auto &skull : hellSkulls )
	{
		if( skull )
		{
			skull->collisionWithBall( skullDrawer, ballMove, ballTexture );
		}
	}
}

void onePlGame::HellSkullPack::fireBallCollisionWithRacket(OnePlayerRacket& racket, const SoundPlayer& soundPlayer)
{
	for( auto &skull : hellSkulls )
	{
		if( skull )
		{
			skull->fireBallCollisionWithRacket(racket, soundPlayer);
		}
	}
}

void onePlGame::HellSkullPack::moveSkulls()
{
	if( moveDelay.hasTimeElapsed( std::chrono::milliseconds{hell::MoveDelay} ) )
	{
		for( auto &skull : hellSkulls )
		{
			if( skull )
			{
				skull->moveSkull();
				skull->moveFireBall();
			}
		}
		moveDelay.joinTimePoints();
	}
}

std::size_t onePlGame::HellSkullPack::size() const
{
	return hellSkulls.size();
}

std::vector< std::unique_ptr< onePlGame::HellSkullElement > >::const_iterator onePlGame::HellSkullPack::begin() const
{
	return hellSkulls.cbegin();
}

std::vector< std::unique_ptr< onePlGame::HellSkullElement > >::const_iterator onePlGame::HellSkullPack::end() const
{
	return hellSkulls.cend();
}

std::unique_ptr< onePlGame::HellSkullElement >& onePlGame::HellSkullPack::operator[](std::size_t index)
{
	assert( index < hellSkulls.size() );
	return hellSkulls[index];
}