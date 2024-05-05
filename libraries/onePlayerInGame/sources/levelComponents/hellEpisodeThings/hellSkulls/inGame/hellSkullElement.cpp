#include "levelComponents/hellEpisodeThings/hellSkulls/inGame/hellSkullElement.h"
#include "levelComponents/hellEpisodeThings/hellSkulls/configuration/skullFileData.h"
#include "levelComponents/onePlayerRacket/onePlayerRacket.h"
#include "levelComponents/hellEpisodeThings/fireBalls/paths/fireBallPaths.h"
#include "hellSkulls/skullDrawer.h"
#include "explosions/allExplosions.h"
#include "spriteMove/createPathData.h"
#include "spriteMove/moveVectorSeriesHandle.h"
#include "soundSystem/soundsPlayer.h"
#include "rectCollisions/processBouncing.h"
#include "types/spriteSize.h"
#include "consts/constexprScreen.h"
#include "consts/hellConsts.h"
#include "consts/onePlayerSounds.h"
#include "fireBall/fireBallConsts.h"
#include <cassert>

onePlGame::HellSkullElement::HellSkullElement(const onePlGame::FireBallsPaths& fireBallPaths, const SkullFileData& fileData):
	skullData{ fileData.startingPos, fileData.initialSpeed, fileData.startingDirection },
	toLeftFireBall{ fireBallPaths.paths.getPath(hell::FireBallBellPathWayLeft) },
	toRightFireBall{ fireBallPaths.paths.getPath(hell::FireBallBellPathWayRight) },
	fireBallMove{ Offset{ 0, 0 } },
	fireBallStarThings{ 0, fireBall::TexturesDirectionsNumber, 0 },
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

void onePlGame::HellSkullElement::update(const HellSkullDrawer& skullDrawer, const spriteMove::ObjectMoving& ballMove, const AllExplosions& explosions, const SoundPlayer& soundPlayer)
{
	screenBounce(skullDrawer);
	skullData.animSkull();
	nextJob(soundPlayer);
	handleRush(ballMove);
	updateExplosion(explosions);
	watchFireBallMoveEnd();
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
	if( skullData.move.get_x_position() + skullDrawer.getTextureWidth(skullData) / 2 >= GameScreenWidth && skullData.move.get_x_norm() > 0 )
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
	if( skullData.move.get_y_position() + skullDrawer.getTextureHeight(skullData) / 2 >= GameScreenHeight && skullData.move.get_y_norm() > 0 )
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
		if( activity.pathNumber == hell::FireBallBellPathWayLeft || activity.pathNumber == hell::FireBallBellPathWayRight )
		{
			spriteMove::handleStarSpriteMove(fireBallMove, fireBallStarThings, Offset{ 0, 0 } );
			fireBallMove.moveSprite.moveObject();
		}
	}
}

void onePlGame::HellSkullElement::nextJob(const SoundPlayer& soundPlayer)
{
	if( activity.canThrowFireBalls && activity.canSeekYellowBall )
	{
		switch( activity.nextJob )
		{
			case hell::SkullThrowFireBall:
				throwFireBall(soundPlayer);
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
		throwFireBall(soundPlayer);
	}
	else if( false == activity.canThrowFireBalls && activity.canSeekYellowBall )
	{
		rushToPlayerBall();
	}
}

void onePlGame::HellSkullElement::throwFireBall(const SoundPlayer& soundPlayer)
{
	if( activity.canThrowFireBalls && activity.isSkullActive )
	{
		if( isSkullInsideScreen() && false == activity.isFireBallActive && activity.globalTimeHasRewind && randomInterval.canHappen() )
		{
			soundPlayer.playSoundOnGroup(onePlGame::SoundFireBall, onePlGame::GroupTagEnemy);
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
		activity.pathNumber = hell::FireBallBellPathWayLeft;
		fireBallMove.vectMvtInfos.clear();
		spriteMove::createPathData(fireBallMove, toLeftFireBall, skullData.move.getOffsetPosition() );
		fireBallStarThings.createOrientationInfos(fireBallMove.vectMvtInfos);
		fireBallMove.resetMove(skullData.move.getOffsetPosition() );
	}
	else{
		activity.pathNumber = hell::FireBallBellPathWayRight;
		fireBallMove.vectMvtInfos.clear();
		spriteMove::createPathData(fireBallMove, toRightFireBall, skullData.move.getOffsetPosition() );
		fireBallStarThings.createOrientationInfos(fireBallMove.vectMvtInfos);
		fireBallMove.resetMove(skullData.move.getOffsetPosition() );
	}
}

bool onePlGame::HellSkullElement::isSkullInsideScreen() const
{
	return skullData.move.get_x_position() - SQR_SIZE >= 0
		&& skullData.move.get_x_position() + SQR_SIZE < GameScreenWidth
		&& skullData.move.get_y_position() - SQR_SIZE >= SQR_SIZE //Below info bar 'i.e : SQR_SIZE'
		&& skullData.move.get_y_position() + SQR_SIZE < GameScreenHeight;
}

void onePlGame::HellSkullElement::handleRush(const spriteMove::ObjectMoving& ballMove)
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

void onePlGame::HellSkullElement::collisionWithBall(const HellSkullDrawer& skullDrawer, spriteMove::ObjectMoving& ballMove, const TextureCombo& ballTexture)
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

void onePlGame::HellSkullElement::fireBallCollisionWithRacket(OnePlayerRacket& racket, const SoundPlayer& soundPlayer)
{
	if( activity.isFireBallActive )
	{
		if( fireBallMove.moveSprite.get_y_norm() > 0 )
		{
			if( fireBallMove.moveSprite.get_x_position() + hell::FireBallWidth / 2 >= racket.rect.x
				&& fireBallMove.moveSprite.get_x_position() - hell::FireBallWidth / 2 < racket.rect.x + racket.rect.w
				&& fireBallMove.moveSprite.get_y_position() + hell::FireBallWidth / 2 >= racket.rect.y
				&& fireBallMove.moveSprite.get_y_position() - hell::FireBallWidth / 2 < racket.rect.y + racket.rect.h )
			{
				activity.isFireBallActive = false;
				soundPlayer.playSoundOnGroup(onePlGame::SoundImpactWithDamage, onePlGame::GroupTagNewCoin);
				racket.data.startFreeze( std::chrono::milliseconds{2000} );
			}
		}
	}
}

void onePlGame::HellSkullElement::accelerateBall(spriteMove::ObjectMoving& ballMove)
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

void onePlGame::HellSkullElement::watchFireBallMoveEnd()
{
	if( spriteMove::hasReachedPathEnd(fireBallMove) )
	{
		activity.isFireBallActive = false;
	}
}