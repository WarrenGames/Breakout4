#include "contexts/onePlayerGame/levelComponents/hellEpisodeThings/fireBalls/inGame/fireBallElement.h"
#include "contexts/onePlayerGame/levelComponents/onePlayerRacket/onePlayerRacket.h"
#include "contexts/onePlayerGame/levelComponents/hellEpisodeThings/fireBalls/configuration/fireBallFileData.h"
#include "generic/sounds/soundHandler.h"
#include "spriteMove/moveVectorSeriesHandle.h"
#include "spriteMove/createPathData.h"
#include "consts/hellConsts.h"
#include "contexts/gameCommon/fireBall/fireBallConsts.h"

onePlGame::FireBallElement::FireBallElement(const spriteMove::VectorsGroup& path, const FireBallFileData& fileData):
	startPosition{ fileData.sqrSizeRelativePos * SQR_SIZE, GAME_SCREEN_HEIGHT + SQR_SIZE * 2 },
	move{ startPosition },
	starThings{ 0, fireBall::TEXTURES_DIRECTIONS_NUMBER, 0 },
	randomInterval{ fileData.totalWaitTime, fileData.randomTimeInterval, fileData.seedAdd },
	isActive{false},
	globalTimeHasRewind{true}
{
	spriteMove::createPathData(move, path, startPosition );
	starThings.createOrientationInfos(move.vectMvtInfos);
}

void onePlGame::FireBallElement::update()
{
	if( isActive )
	{
		spriteMove::handleStarSpriteMove(move, starThings, Offset{ 0, 0} );
		moveFireBall();
		resetPositionIfNeeded();
		drawData.animFireBall();
	}
}

void onePlGame::FireBallElement::updateWithRacket(OnePlayerRacket& racket, const SoundHandler& sounds)
{
	if( isActive )
	{
		if( move.moveSprite.get_y_norm() > 0 )
		{
			if( move.moveSprite.get_x_position() + hell::FireBallWidth / 2 >= racket.rect.x
				&& move.moveSprite.get_x_position() - hell::FireBallWidth / 2 < racket.rect.x + racket.rect.w
				&& move.moveSprite.get_y_position() + hell::FireBallWidth / 2 >= racket.rect.y
				&& move.moveSprite.get_y_position() - hell::FireBallWidth / 2 < racket.rect.y + racket.rect.h )
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
		move.resetMove(startPosition);
	}
	if( randomInterval.canSetGlobalPrecedentTimePoint() )
	{
		randomInterval.resetBothTimePoints();
		globalTimeHasRewind = true;
	}
}

void onePlGame::FireBallElement::moveFireBall()
{
	move.move();
}


void onePlGame::FireBallElement::resetPositionIfNeeded()
{
	if( spriteMove::hasReachedPathEnd(move) )
	{
		isActive = false;
	}
}