#include "contexts/onePlayerGame/levelComponents/hellEpisodeThings/hellSkulls/inGame/hellSkullElement.h"
#include "contexts/gameCommon/hellSkulls/skullDrawer.h"
#include "contexts/onePlayerGame/levelComponents/hellEpisodeThings/hellSkulls/configuration/skullFileData.h"
#include "contexts/gameCommon/explosions/allExplosions.h"
#include "contexts/onePlayerGame/levelComponents/onePlayerRacket/onePlayerRacket.h"
#include "texturing/texturesCombo.h"
#include "generic/sounds/soundHandler.h"
#include "contexts/gameCommon/rectCollisions/processBouncing.h"
#include "types/spriteSize.h"
#include "consts/constexprScreen.h"
#include "consts/hellConsts.h"
#include <cassert>

onePlGame::HellSkullElement::HellSkullElement(const PathData& toLeftPath, const PathData& toRightPath, const SkullFileData& fileData):
	skullData{ fileData.startingPos, fileData.initialSpeed, fileData.startingDirection },
	toLeftFireBall{ toLeftPath, fileData.startingPos },
	toRightFireBall{ toRightPath, fileData.startingPos },
	randomInterval{ fileData.totalWaitTime, fileData.randomInterval, fileData.seedAdd },
	activity{ fileData }
{

}

void onePlGame::HellSkullElement::resetPositionAndInitialDirection(const SkullFileData& fileData)
{
	skullData.move.setPosition(fileData.startingPos);
	skullData.move.setBothVectors(fileData.startingDirection);
	skullData.move.setSpeed(fileData.initialSpeed);
	skullData.move.adjust_x_speed();
	skullData.move.adjust_y_speed();
	skullData.setDirection();
}

void onePlGame::HellSkullElement::update(const HellSkullDrawer& skullDrawer, const ObjectMoving& ballMove, const AllExplosions& explosions, const SoundHandler& sounds)
{
	screenBounce(skullDrawer);
	skullData.animSkull();
	nextJob(sounds);
	handleRush(ballMove);
	updateExplosion(explosions);
}

void onePlGame::HellSkullElement::updateExplosion(const AllExplosions& explosions)
{
	if( activity.isExploding )
	{
		skullData.animSkullExplosion(explosions.getExplosionDelay(hell::SkullExplosionIndex), 
									explosions.getExplosionFrameNumber(hell::SkullExplosionIndex),
									activity.isSkullActive );
	}
}

void onePlGame::HellSkullElement::screenBounce(const HellSkullDrawer& skullDrawer)
{
	if( activity.canSeekYellowBall && activity.canThrowFireBalls )
	{
		fireBallSkullScreenBounce(skullDrawer);
	}
	else if( activity.canSeekYellowBall && false == activity.canThrowFireBalls )
	{
		toBallRushingSkullScreenBounce(skullDrawer);
	}
	else if( false == activity.canSeekYellowBall && activity.canThrowFireBalls )
	{
		fireBallSkullScreenBounce(skullDrawer);
	}
	else
	{
		fireBallSkullScreenBounce(skullDrawer);
	}
}

void onePlGame::HellSkullElement::fireBallSkullScreenBounce(const HellSkullDrawer& skullDrawer)
{
	bounceAgainInfosBar(skullDrawer);
	bounceAgainScreenBottom(skullDrawer);
	bounceAgainScreenLeft(skullDrawer);
	bounceAgainScreenRight(skullDrawer);
}

void onePlGame::HellSkullElement::toBallRushingSkullScreenBounce(const HellSkullDrawer& skullDrawer)
{
	bounceAgainInfosBar(skullDrawer);
	bounceAgainScreenBottom(skullDrawer);
	bounceAgainScreenLeft(skullDrawer);
	bounceAgainScreenRight(skullDrawer);
}

void onePlGame::HellSkullElement::bounceAgainScreenLeft(const HellSkullDrawer& skullDrawer)
{
	if( skullData.move.get_x_position() - skullDrawer.getTextureWidth(skullData) / 2 <= 0 && skullData.move.get_x_norm() < 0 )
	{
		skullData.move.reverse_x_vector();
		skullData.move.adjust_x_speed();
		skullData.setDirection();
	}
}

void onePlGame::HellSkullElement::bounceAgainScreenRight(const HellSkullDrawer& skullDrawer)
{
	if( skullData.move.get_x_position() + skullDrawer.getTextureWidth(skullData) / 2 >= GAME_SCREEN_WIDTH && skullData.move.get_x_norm() > 0 )
	{
		skullData.move.reverse_x_vector();
		skullData.move.adjust_x_speed();
		skullData.setDirection();
	}
}

void onePlGame::HellSkullElement::bounceAgainInfosBar(const HellSkullDrawer& skullDrawer)
{
	if( skullData.move.get_y_position() - skullDrawer.getTextureHeight(skullData) / 2 < SQR_SIZE && skullData.move.get_y_norm() < 0 )
	{
		skullData.move.reverse_y_vector();
		skullData.move.adjust_y_speed();
		skullData.setDirection();
	}
}

void onePlGame::HellSkullElement::bounceAgainScreenBottom(const HellSkullDrawer& skullDrawer)
{
	if( skullData.move.get_y_position() + skullDrawer.getTextureHeight(skullData) / 2 >= GAME_SCREEN_HEIGHT && skullData.move.get_y_norm() > 0 )
	{
		skullData.move.reverse_y_vector();
		skullData.move.adjust_y_speed();
		skullData.setDirection();
	}
}

void onePlGame::HellSkullElement::moveSkull()
{
	if( activity.isSkullActive && false == activity.isExploding )
	{
		skullData.moveSkull();
	}
}

void onePlGame::HellSkullElement::moveFireBall()
{
	if( activity.isFireBallActive )
	{
		switch( activity.pathNumber )
		{
			case hell::FB_PATH_BELL_TRAJ_LEFT:
				toLeftFireBall.update(fireBallMove, fireBallDrawData, activity.isFireBallActive);
				fireBallMove.moveObject();
				break;
			case hell::FB_PATH_BELL_TRAJ_RIGHT:
				toRightFireBall.update(fireBallMove, fireBallDrawData, activity.isFireBallActive);
				fireBallMove.moveObject();
				break;
		}
	}
}

void onePlGame::HellSkullElement::nextJob(const SoundHandler& sounds)
{
	if( activity.canThrowFireBalls && activity.canSeekYellowBall )
	{
		switch( activity.nextJob )
		{
			case hell::SkullThrowFireBall:
				throwFireBall(sounds);
				break;
			case hell::SkullRushToBall:
				rushToPlayerBall();
				break;
			default:
				assert( false && "Error: bad job for hell skull" );
				break;
		}
	}
	else if( activity.canThrowFireBalls && false == activity.canSeekYellowBall )
	{
		throwFireBall(sounds);
	}
	else if( false == activity.canThrowFireBalls && activity.canSeekYellowBall )
	{
		rushToPlayerBall();
	}
}

void onePlGame::HellSkullElement::throwFireBall(const SoundHandler& sounds)
{
	if( activity.canThrowFireBalls && activity.isSkullActive )
	{
		if( isSkullInsideScreen() && false == activity.isFireBallActive && activity.globalTimeHasRewind && randomInterval.canHappen() )
		{
			sounds.playSound(onePlGame::SND_FIRE_BALL);
			activity.isFireBallActive = true;
			activity.globalTimeHasRewind = false;
			activity.nextJob = hell::SkullRushToBall;
			chooseThrowSide();
		}
		if( randomInterval.canSetGlobalPrecedentTimePoint() )
		{
			randomInterval.resetBothTimePoints();
			activity.globalTimeHasRewind = true;
		}
	}
}

void onePlGame::HellSkullElement::rushToPlayerBall()
{
	if( activity.canSeekYellowBall && activity.isSkullActive )
	{
		if( isSkullInsideScreen() && activity.globalTimeHasRewind && randomInterval.canHappen() )
		{
			activity.isRushing = true;
			activity.globalTimeHasRewind = false;
			activity.nextJob = hell::SkullThrowFireBall;
			skullData.move.setSpeed(hell::SkullRushSpeed);
			skullData.move.adjust_x_speed();
			skullData.move.adjust_y_speed();
		}
		if( randomInterval.canSetGlobalPrecedentTimePoint() )
		{
			randomInterval.resetBothTimePoints();
			activity.globalTimeHasRewind = true;
		}
	}
}

void onePlGame::HellSkullElement::chooseThrowSide()
{
	if( skullData.move.get_x_norm() < 0 )
	{
		activity.pathNumber = hell::FB_PATH_BELL_TRAJ_LEFT;
		toLeftFireBall.resetStartPosition(skullData.move.getOffsetPosition() );
		toLeftFireBall.resetMove(fireBallMove);
		fireBallDrawData.setDirection(fireBallMove.get_x_norm(), fireBallMove.get_y_norm() );
	}
	else{
		activity.pathNumber = hell::FB_PATH_BELL_TRAJ_RIGHT;
		toRightFireBall.resetStartPosition(skullData.move.getOffsetPosition() );
		toRightFireBall.resetMove(fireBallMove);
		fireBallDrawData.setDirection(fireBallMove.get_x_norm(), fireBallMove.get_y_norm() );
	}
}

bool onePlGame::HellSkullElement::isSkullInsideScreen() const
{
	return skullData.move.get_x_position() - SQR_SIZE >= 0
		&& skullData.move.get_x_position() + SQR_SIZE < GAME_SCREEN_WIDTH
		&& skullData.move.get_y_position() - SQR_SIZE >= SQR_SIZE //Below info bar 'i.e : SQR_SIZE'
		&& skullData.move.get_y_position() + SQR_SIZE < GAME_SCREEN_HEIGHT;
}

void onePlGame::HellSkullElement::handleRush(const ObjectMoving& ballMove)
{
	if( activity.isRushing )
	{
		if( rushDelay.hasTimeElapsed( std::chrono::milliseconds{100} ) )
		{
			rushDelay.joinTimePoints();
			skullData.move.orientToAGivenObject(ballMove);
			skullData.move.adjust_x_speed();
			skullData.move.adjust_y_speed();
			skullData.setDirection();
		}
	}
}

void onePlGame::HellSkullElement::collisionWithBall(const HellSkullDrawer& skullDrawer, ObjectMoving& ballMove, const TextureCombo& ballTexture)
{
	if( activity.isSkullActive && false == activity.isExploding && activity.canCollideWithBall )
	{
		if( bouncing::objectsCollide(skullData.move, SpriteSize{ skullDrawer.getTextureWidth(skullData), skullDrawer.getTextureHeight(skullData) },
										ballMove, SpriteSize{ ballTexture.sprite.width(), ballTexture.sprite.height()} , 0 ) )
		{
			
			setSkullToExplosion();
			activity.canCollideWithBall = false;
			bouncing::processElementsBouncing(skullData.move, ballMove, SpriteSize{ ballTexture.sprite.width(), ballTexture.sprite.height()} );
			accelerateBall(ballMove);
		}
	}
}

void onePlGame::HellSkullElement::fireBallCollisionWithRacket(OnePlayerRacket& racket, const SoundHandler& sounds)
{
	if( activity.isFireBallActive )
	{
		if( fireBallMove.get_y_norm() > 0 )
		{
			if( fireBallMove.get_x_position() + hell::FireBallWidth / 2 >= racket.rect.x
				&& fireBallMove.get_x_position() - hell::FireBallWidth / 2 < racket.rect.x + racket.rect.w
				&& fireBallMove.get_y_position() + hell::FireBallWidth / 2 >= racket.rect.y
				&& fireBallMove.get_y_position() - hell::FireBallWidth / 2 < racket.rect.y + racket.rect.h )
			{
				activity.isFireBallActive = false;
				sounds.playSound(onePlGame::SND_IMPACT_W_DAMAGE);
				racket.data.startFreeze( std::chrono::milliseconds{2000} );
			}
		}
	}
}

void onePlGame::HellSkullElement::accelerateBall(ObjectMoving& ballMove)
{
	if( activity.isRushing )
	{
		ballMove.incrementSpeed(1);
	}
	else{
		ballMove.incrementSpeed(0.2);
	}
	ballMove.adjust_x_speed();
	ballMove.adjust_y_speed();
}

void onePlGame::HellSkullElement::setSkullToExplosion()
{
	skullData.explosionFrameIndex = 0;
	activity.isExploding = true;
}