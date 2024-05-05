#include "levelComponents/hellEpisodeThings/hellSkulls/hellSkullGlobal.h"
#include "types/essentialsStruct.h"
#include "crossLevel/playerData.h"
#include "levelComponents/hellEpisodeThings/fireBalls/paths/fireBallPaths.h"
#include "fireBall/fireBallDrawer.h"
#include "explosions/allExplosions.h"
#include "consts/hellConsts.h"

onePlGame::HellSkullGlobal::HellSkullGlobal(Essentials& essentials, const PlayerData& playerData, const FireBallsPaths& fireBallsPaths):
	dataLoader{ essentials, playerData },
	skullPack{ essentials.logs, playerData, fireBallsPaths, dataLoader },
	drawer{essentials},
	triggersNumber{ 0 }
{
	
}

bool onePlGame::HellSkullGlobal::wasLoadingPerfect() const
{
	return dataLoader.wasLoadingPerfect()
		&& skullPack.wasLoadingPerfect()
		&& drawer.wasLoadingPerfect();
}

void onePlGame::HellSkullGlobal::addPendingSkull()
{
	triggersNumber++;
}

void onePlGame::HellSkullGlobal::update(spriteMove::ObjectMoving& ballMove, OnePlayerRacket& racket, const AllExplosions& explosions, const TextureCombo& ballTexture, 
											const SoundPlayer& soundPlayer)
{
	skullPack.moveSkulls();
	skullPack.updateSkulls(drawer, ballMove, explosions, soundPlayer);
	skullPack.withBallCollision(drawer, ballMove, ballTexture);
	skullPack.fireBallCollisionWithRacket(racket, soundPlayer);
	activateSkullIfAny();
}

void onePlGame::HellSkullGlobal::drawHellSkulls(Essentials& essentials, AllExplosions& explosions)
{
	for( auto &skullPtr : skullPack )
	{
		if( skullPtr )
		{
			if( skullPtr->activity.isSkullActive )
			{
				if( skullPtr->activity.isExploding )
				{
					explosions.drawFrame(essentials.rndWnd, skullPtr->skullData.move.get_x_position(), skullPtr->skullData.move.get_y_position(), 
											hell::SkullExplosionIndex, skullPtr->skullData.explosionFrameIndex);
				}
				else{
					drawer.drawHellSkull(essentials, skullPtr->skullData);
				}
			}
		}
	}
}

void onePlGame::HellSkullGlobal::drawFireBalls(Essentials& essentials, FireBallDrawer& fireBallDrawer)
{
	for( auto &skullPtr : skullPack )
	{
		if( skullPtr )
		{
			if( skullPtr->activity.isFireBallActive )
			{
				fireBallDrawer.drawFireBall(essentials, skullPtr->fireBallDrawData, skullPtr->fireBallMove.moveSprite, skullPtr->fireBallStarThings);
			}
		}
	}
}

void onePlGame::HellSkullGlobal::activateSkullIfAny()
{
	for( std::size_t i{0} ; i < dataLoader.size() && i < skullPack.size() && triggersNumber > 0 ; ++i )
	{
		if( skullPack[i] )
		{
			if( false == skullPack[i]->activity.isSkullActive )
			{
				skullPack[i]->activity.isSkullActive = true;
				skullPack[i]->activity.canCollideWithBall = true;
				skullPack[i]->activity.isExploding = false;
				skullPack[i]->resetPositionAndInitialDirection( dataLoader[i] );
				triggersNumber--;
			}
		}
	}
}