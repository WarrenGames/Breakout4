#include "levelComponents/balls/ballsThings.h"
#include "levelComponents/freeFunctions/ballWithGridCollisions.h"
#include "levelComponents/rims/rimsGlobal.h"
#include "rectCollisions/objMoveWithRectCollisions.h"
#include "soundSystem/soundsPlayer.h"
#include "crossLevel/playerData.h"
#include "levelComponents/fallingBonuses/fallingBonuses.h"
#include "demos/sounds/soundsStackData.h"
#include "demos/templates/demoStack.h"
#include "demos/consts/demosConsts.h"
#include "consts/constexprScreen.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/onePlayerSounds.h"

constexpr int RacketCollideCorner = 20;

BallThings::BallThings(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, std::size_t monstersNumber):
	isLoadingPerfect{ true },
	isMainBallActive{ false },
	canDetectCollisionSince{ true },
	canTestRimCollisions{true},
	canTestMonstersCollision{ true},
	isBallPowerful{ false },
	canTestRacketCollideBox{false},
	monstersCollisionIsEffective(monstersNumber, true),
	move{ AccurCoords{GameScreenWidth/2, GameScreenHeight - SQR_SIZE * 2}, 0, Offset{1,-1} },
	texture{ logs, rndWnd, "textures/sprites/balls/yellowBall.png" },
	speeds{logs, "data/levels/1player/options/ballSpeeds.cfg"}
{
	if( !( texture.texture && speeds.wasLoadingPerfect() ) )
		isLoadingPerfect = false;
}

BallThings::operator bool() const
{
	return isLoadingPerfect;
}

void BallThings::drawMainBall(sdl2::RendererWindow& rndWnd)
{
	texture.drawToCenter(rndWnd, move.get_x_position(), move.get_y_position() );
}

void BallThings::moveMainBall()
{
	if( moveBallDelay.hasTimeElapsed( std::chrono::microseconds{onePlGame::MicroSecondsRefreshTimeRate} ) )
	{
		move.moveObject();
		
		canDetectCollisionSince = true;
		canTestRimCollisions = true;
		canTestMonstersCollision = true;
		setGridRelativePosition();
		moveBallDelay.joinTimePoints();
	}
}

void BallThings::setGridRelativePosition()
{
	gridRelPos.x = move.get_x_position() / SQR_SIZE;
	gridRelPos.y = move.get_y_position() / SQR_SIZE;
}

void BallThings::handleBallWithRacketCollision(const SDL_Rect& racketRect, unsigned& glueLevel, const SoundPlayer& soundPlayer, demos::Stack< demos::SoundStackData >& soundsStack, 
												unsigned demoKind)
{
	if( isMainBallActive )
	{
		resetBetweenRacketAndBallCollisionPossibility(racketRect);
		detectCollisionBetweenBallAndRacket(racketRect, glueLevel, soundPlayer, soundsStack, demoKind);
	}
}

void BallThings::resetBetweenRacketAndBallCollisionPossibility(const SDL_Rect& racketRect)
{
	SDL_Rect enlargedRacketRect{racketRect};
	setEnlargedRacketRect(enlargedRacketRect, SQR_SIZE / 2);
	if( false == isThereCollisionBetweenRects( enlargedRacketRect, 
												SDL_Rect{move.get_x_position() - texture.sprite.width() / 2, 
														move.get_y_position() - texture.sprite.height() / 2, 
														texture.sprite.width(), 
														texture.sprite.height()} ) )
	{
		canTestRacketCollideBox = true;
	}
}

void BallThings::setEnlargedRacketRect(SDL_Rect& enlargedRacketRect, int interval)
{
	enlargedRacketRect.x -= interval;
	enlargedRacketRect.y -= interval;
	enlargedRacketRect.w += interval * 2;
	enlargedRacketRect.h += interval * 2;
}

bool BallThings::isThereCollisionBetweenRects(const SDL_Rect& racketRect, const SDL_Rect& ballRect)
{
	return	ballRect.x + ballRect.w 	>= racketRect.x 
			&& ballRect.x 				< racketRect.x + racketRect.w 
			&& ballRect.y + ballRect.h >= racketRect.y
			&& ballRect.y 				< racketRect.y + racketRect.h;
}

void BallThings::detectCollisionBetweenBallAndRacket(const SDL_Rect& racketRect, unsigned& glueLevel, const SoundPlayer& soundPlayer, 
														demos::Stack< demos::SoundStackData >& soundsStack, unsigned demoKind)
{
	if( canTestRacketCollideBox 
		&& isThereCollisionBetweenRects(racketRect, 
														SDL_Rect{move.get_x_position() - texture.sprite.width() / 2, 
														move.get_y_position() - texture.sprite.height() / 2, 
														texture.sprite.width(), 
														texture.sprite.height()}) )
	{
		if( glueLevel == 0 )
		{
			determineBallBounceWithRacket(racketRect, soundPlayer, soundsStack, demoKind);
			canTestRacketCollideBox = false;
		}
		else{
			glueLevel--;
			isMainBallActive = false;
		}
	}
}

void BallThings::determineBallBounceWithRacket(const SDL_Rect& racketRect, const SoundPlayer& soundPlayer, demos::Stack< demos::SoundStackData >& soundsStack, unsigned demoKind)
{
	if( move.get_y_position() + texture.sprite.height() / 2 < racketRect.y + racketRect.h )
	{
		bounceMakeBallGoesUpward(racketRect, soundPlayer, soundsStack, demoKind);
	}
	else{
		soundPlayer.playSoundOnGroup(onePlGame::SoundRacketWithBallCollision, onePlGame::GroupTagRacketWithBallCollision);
		stackSoundOfBallWithRacketCollision(soundsStack, demoKind);
		move.reverse_x_vector();
		move.adjust_x_speed();
	}
}

void BallThings::bounceMakeBallGoesUpward(const SDL_Rect& racketRect, const SoundPlayer& soundPlayer, demos::Stack< demos::SoundStackData >& soundsStack, unsigned demoKind)
{
	if( move.get_x_position() + texture.sprite.width() / 2 < racketRect.x + RacketCollideCorner )
	{
		soundPlayer.playSoundOnGroup(onePlGame::SoundRacketWithBallCollision, onePlGame::GroupTagRacketWithBallCollision);
		stackSoundOfBallWithRacketCollision(soundsStack, demoKind);
		giveObjectNewDirection(move, Offset{-1, -1} );
	}
	else if( move.get_x_position() - texture.sprite.width() / 2 >= racketRect.x + racketRect.w - RacketCollideCorner )
	{
		soundPlayer.playSoundOnGroup(onePlGame::SoundRacketWithBallCollision, onePlGame::GroupTagRacketWithBallCollision);
		stackSoundOfBallWithRacketCollision(soundsStack, demoKind);
		giveObjectNewDirection(move, Offset{1, -1} );
	}
	else{
		soundPlayer.playSoundOnGroup(onePlGame::SoundRacketWithBallCollision, onePlGame::GroupTagRacketWithBallCollision);
		stackSoundOfBallWithRacketCollision(soundsStack, demoKind);
		move.reverse_y_vector();
		move.adjust_y_speed();
	}
}

void BallThings::testCollisionWithRims(const OnePlayerRimsSystem& rims, const SoundPlayer& soundPlayer)
{	
	if( canTestRimCollisions )
	{
		for( auto const &rect : rims )
		{
			rectCollision::startCollisionTest(move, SpriteSize{texture.sprite.width(), texture.sprite.height()}, rect, rectCollision::BallInterval, soundPlayer, 
												onePlGame::SoundBallWBgCollision, 2);
		}
		canTestRimCollisions = false;
	}
}

SpriteSize BallThings::getTexSize() const
{
	return SpriteSize{ texture.sprite.width(), texture.sprite.height() };
}

void stackSoundOfBallWithRacketCollision(demos::Stack< demos::SoundStackData >& soundsStack, unsigned demoKind)
{
	if( demoKind == demos::GameIsRecording )
	{
		soundsStack.emplaceElement(demos::SoundStackData{ soundsStack.getCurrentElapsedMicroSecondsTime(), onePlGame::SoundRacketWithBallCollision, 
									onePlGame::GroupTagRacketWithBallCollision } );
	}
}