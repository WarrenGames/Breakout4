#include "contexts/onePlayerGame/levelComponents/hellEpisodeThings/fireBalls/inGame/fireBallElement.h"
#include "contexts/gameCommon/movements/movePathData.h"
#include "contexts/onePlayerGame/levelComponents/onePlayerRacket/onePlayerRacket.h"
#include "contexts/onePlayerGame/levelComponents/hellEpisodeThings/fireBalls/configuration/fireBallFileData.h"
#include "generic/sounds/soundHandler.h"
#include "consts/hellConsts.h"

onePlGame::FireBallElement::FireBallElement(const PathData& path, const FireBallFileData& fileData):
	pathData{ path, Offset{ fileData.sqrSizeRelativePos * SQR_SIZE, GAME_SCREEN_HEIGHT + SQR_SIZE * 2 } },
	move{ Offset{ fileData.sqrSizeRelativePos * SQR_SIZE, GAME_SCREEN_HEIGHT + SQR_SIZE * 2 } },
	randomInterval{ fileData.totalWaitTime, fileData.randomTimeInterval, fileData.seedAdd },
	isActive{false},
	globalTimeHasRewind{true}
{
	
}

void onePlGame::FireBallElement::update()
{
	if( isActive )
	{
		pathData.update(move, drawData, isActive);
		moveFireBall();
		drawData.animFireBall();
	}
}

void onePlGame::FireBallElement::updateWithRacket(OnePlayerRacket& racket, const SoundHandler& sounds)
{
	if( isActive )
	{
		if( move.get_y_norm() > 0 )
		{
			if( move.get_x_position() + hell::FireBallWidth / 2 >= racket.rect.x
				&& move.get_x_position() - hell::FireBallWidth / 2 < racket.rect.x + racket.rect.w
				&& move.get_y_position() + hell::FireBallWidth / 2 >= racket.rect.y
				&& move.get_y_position() - hell::FireBallWidth / 2 < racket.rect.y + racket.rect.h )
			{
				isActive = false;
				sounds.playSound(onePlGame::SND_IMPACT_W_DAMAGE);
				racket.data.startFreeze( std::chrono::milliseconds{2000} );
			}
		}
	}
}

void onePlGame::FireBallElement::startActivity(const SoundHandler& sounds)
{
	if( false == isActive && globalTimeHasRewind && randomInterval.canHappen() )
	{
		sounds.playSound(onePlGame::SND_FIRE_BALL);
		isActive = true;
		globalTimeHasRewind = false;
		pathData.resetMove(move);
		drawData.setDirection(move.get_x_norm(), move.get_y_norm() );
	}
	if( randomInterval.canSetGlobalPrecedentTimePoint() )
	{
		randomInterval.resetBothTimePoints();
		globalTimeHasRewind = true;
	}
}

void onePlGame::FireBallElement::moveFireBall()
{
	move.moveObject();
}
