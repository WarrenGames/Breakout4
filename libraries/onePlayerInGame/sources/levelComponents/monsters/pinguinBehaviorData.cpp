#include "levelComponents/monsters/pinguinBehaviorData.h"
#include "soundSystem/soundsPlayer.h"
#include "levelComponents/rims/playerRims.h"
#include "levelComponents/demosObjects/antarcticDemoPackage.h"
#include "types/spriteSize.h"
#include "rectCollisions/objMoveWithRectCollisions.h"
#include "rectCollisions/monsterCollisionsWithRect.h"
#include "pinguins/pinguinConsts.h"
#include "consts/rimsConsts.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/onePlayerSounds.h"
#include "SDL_rect.h"
#include <algorithm>

PinguinBehaviorData::PinguinBehaviorData(const AccurCoords& pinguinPos, double speed, const Offset& dirVectors):
	drawingData{pinguinPos, speed, dirVectors},
	anger{0},
	state{PinguinIsInactive},
	tagNumber{0},
	canPinguinGoOut{false},
	canPinguinQuack{false},
	canCollideWithRacket{true},
	canCollideWithRims{true},
	startingPosition{static_cast<int>(pinguinPos.x), static_cast<int>(pinguinPos.y)},
	startingDir{dirVectors},
	startingSpeed{speed}
{

}

unsigned PinguinBehaviorData::getState() const
{
	return state;
}

void PinguinBehaviorData::setState(unsigned newState)
{
	state = newState;
}

unsigned PinguinBehaviorData::getAnger() const
{
	return anger;
}

const PinguinDrawData& PinguinBehaviorData::getDrawingData() const
{
	return drawingData;
}

PinguinDrawData& PinguinBehaviorData::getDrawingData()
{
	return drawingData;
}

unsigned PinguinBehaviorData::getTagNumber() const
{
	return tagNumber;
}

bool PinguinBehaviorData::doesPinguinLeaveIfAny(unsigned hitTimesThreshold)
{
	if( anger >= hitTimesThreshold )
	{
		state = PinguinIsInactive;
		return true;
	}
	else{
		return false;
	}
}

void PinguinBehaviorData::activePinguin(int newTagNumber)
{
	drawingData.move.setPosition(startingPosition);
	drawingData.move.setBothVectors(startingDir);
	drawingData.move.setSpeed(startingSpeed);
	drawingData.move.adjust_x_speed();
	drawingData.move.adjust_y_speed();
	state = PinguinIsActive;
	anger = 0;
	tagNumber = newTagNumber;
}

void PinguinBehaviorData::movePinguin()
{
	drawingData.move.moveObject();
	
	canCollideWithRims = true;
}

void PinguinBehaviorData::animPinguin()
{
	if( state == PinguinIsActive || state == PinguinStartMindPlayer )
		drawingData.animPinguin();
}

void PinguinBehaviorData::resetRacketCollisionBooleans(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect)
{
	if( false == collision::isThereCollision(racketRect, pinguinRect, drawingData.move.getOffsetPosition(), SQR_SIZE / 2) )
	{
		canPinguinQuack = true;
		canCollideWithRacket = true;
	}
}

void PinguinBehaviorData::makeBounceWithRacket(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect, demos::DemoAntarcticPackage& antarcticPackage)
{
	if( collision::isThereCollision(racketRect, pinguinRect, drawingData.move.getOffsetPosition(), -SQR_SIZE / 64 ) && canCollideWithRacket )
	{
		canCollideWithRacket = false;
		makeBounceVertically(racketRect, pinguinRect);
		makeBounceHorizontally(racketRect, pinguinRect);
		recordPinguinDirection(antarcticPackage);
	}
}

void PinguinBehaviorData::recordPinguinDirection(demos::DemoAntarcticPackage& antarcticPackage) const
{
	if( antarcticPackage.demoKind == demos::GameIsRecording )
	{
		antarcticPackage.pinguinsDirection.emplaceElement(demos::TaggedDirectionStackData{
			std::chrono::microseconds{static_cast<long int>(antarcticPackage.pinguinsDirection.getElapsedMicroSecondsTime())}, 
			drawingData.direction, tagNumber} );
	}
}

void PinguinBehaviorData::makeBounceVertically(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect)
{
	bounceFromRacketTop(racketRect, pinguinRect);
	bounceFromRacketBottom(racketRect, pinguinRect);
}

void PinguinBehaviorData::bounceFromRacketTop(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect)
{
	if( drawingData.move.get_y_norm() > 0 && racketRect.y >= drawingData.move.get_y_position() + pinguinRect.y + pinguinRect.h )
	{
		drawingData.move.reverse_y_vector();
		drawingData.move.adjust_y_speed();
		drawingData.setDirection();
	}
}

void PinguinBehaviorData::bounceFromRacketBottom(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect)
{
	if( drawingData.move.get_y_norm() < 0 && racketRect.y + racketRect.h > drawingData.move.get_y_position() + pinguinRect.y )
	{
		drawingData.move.reverse_y_vector();
		drawingData.move.adjust_y_speed();
		drawingData.setDirection();
	}
}

void PinguinBehaviorData::makeBounceHorizontally(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect)
{
	if( collision::monsterIsOnLeftOfRacket(racketRect, pinguinRect, Offset{ drawingData.move.get_x_position(), drawingData.move.get_y_position()}, CollisionInterval ) )
	{
		bounceFromRacketLeft();
	}
	else if( collision::monsterIsOnRightOfRacket(racketRect, pinguinRect, Offset{ drawingData.move.get_x_position(), drawingData.move.get_y_position()}, CollisionInterval ) )
	{
		bounceFromRacketRight();
	}
}

void PinguinBehaviorData::bounceFromRacketLeft()
{
	if( drawingData.move.get_x_norm() > 0 )
	{
		drawingData.move.reverse_x_vector();
		drawingData.move.adjust_x_speed();
		drawingData.setDirection();
	}
}

void PinguinBehaviorData::bounceFromRacketRight()
{
	if( drawingData.move.get_x_norm() < 0 )
	{
		drawingData.move.reverse_x_vector();
		drawingData.move.adjust_x_speed();
		drawingData.setDirection();
	}
}

void PinguinBehaviorData::makePinguinQuack(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect, bool playerLeftState, bool playerRightState, const SoundPlayer& soundPlayer,
											demos::DemoAntarcticPackage& antarcticPackage)
{
	if( ( state == PinguinIsActive || state == PinguinStartMindPlayer ) && canPinguinQuack 
		&& collision::isThereCollision(racketRect, pinguinRect, drawingData.move.getOffsetPosition(), CollisionInterval) )
	{
		quackFromItsLeft(racketRect, pinguinRect, playerRightState, soundPlayer, antarcticPackage);
		quackFromItsRight(racketRect, pinguinRect, playerLeftState, soundPlayer, antarcticPackage);
	}
}

void PinguinBehaviorData::quackFromItsLeft(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect, bool playerRightState, const SoundPlayer& soundPlayer, 
												demos::DemoAntarcticPackage& antarcticPackage)
{
	//when player's racket is to the left hand side from pinguin
	if( playerRightState && racketRect.x + racketRect.w < drawingData.move.get_x_position() + pinguinRect.x )
	{
		soundPlayer.playSoundOnGroup(onePlGame::SoundQuack, onePlGame::GroupTagEnemy);
		emplaceQuackSoundToStack(antarcticPackage);
		canPinguinQuack = false;
		anger++;
	}
}

void PinguinBehaviorData::quackFromItsRight(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect, bool playerLeftState, const SoundPlayer& soundPlayer, demos::DemoAntarcticPackage& antarcticPackage)
{
	//when player's racket is to the right hand side from pinguin
	if( playerLeftState && racketRect.x >= drawingData.move.get_x_position() + pinguinRect.x + pinguinRect.w )
	{
		soundPlayer.playSoundOnGroup(onePlGame::SoundQuack, onePlGame::GroupTagEnemy);
		emplaceQuackSoundToStack(antarcticPackage);
		canPinguinQuack = false;
		anger++;
	}
}

void PinguinBehaviorData::makeBounceWithRimRect(const SDL_Rect& rimRect, const SDL_Rect& pinguinRect, const SoundPlayer& soundPlayer)
{
	if( PinguinIsActive == state )
	{
		rectCollision::startCollisionTest(drawingData.move, SpriteSize{pinguinRect.w, pinguinRect.h}, rimRect, CollisionInterval, soundPlayer, onePlGame::SoundBallWBgCollision, 2);
	}
}

void PinguinBehaviorData::setPinguinPathWithMouse(const Offset& mousePosition, bool mouseButtonState)
{
	if( mouseButtonState )
	{
		drawingData.move.setBothVectors(Offset{ mousePosition.x - drawingData.move.get_x_position() ,
											mousePosition.y - drawingData.move.get_y_position() }	);
		drawingData.move.adjust_x_speed();
		drawingData.move.adjust_y_speed();
	}
}

void PinguinBehaviorData::startMindPlayer(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect)
{
	if( isPinguinNearXRacketCoordinates(racketRect, pinguinRect, SQR_SIZE * 3) && false == isPinguinOnSameLevelAsRacket() )
	{
		giveObjectNewDirection(drawingData.move, Offset{0, 1});
		state = PinguinStartMindPlayer;
	}
}

bool PinguinBehaviorData::isPinguinNearXRacketCoordinates(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect, int interval) const
{
	return drawingData.move.get_x_position() + pinguinRect.w / 2 >= racketRect.x - interval
		&& drawingData.move.get_x_position() - pinguinRect.w / 2 < racketRect.x + racketRect.w + interval;
}

bool PinguinBehaviorData::isPinguinOnSameLevelAsRacket() const
{
	return drawingData.move.get_y_position() >= GameScreenHeight - SQR_SIZE - SQR_SIZE / 2 - SQR_SIZE / 4 
		&& drawingData.move.get_y_position() < GameScreenHeight - SQR_SIZE - SQR_SIZE / 2 + SQR_SIZE / 4;
}

void PinguinBehaviorData::makeStayOnRacketLevelIfMindPlayer(const SDL_Rect& racketRect)
{
	if( PinguinStartMindPlayer == state && isPinguinOnSameLevelAsRacket() && 0 == drawingData.move.get_x_norm() && 1 == drawingData.move.get_y_norm() )
	{
		if( drawingData.move.get_x_position() < racketRect.x )
		{
			giveObjectNewDirection(drawingData.move, Offset{1, 0});
		}
		else if( drawingData.move.get_x_position() >= racketRect.x + racketRect.w )
		{
			giveObjectNewDirection(drawingData.move, Offset{-1, 0});
		}
	}
}

bool PinguinBehaviorData::isPinguinInsideScreen(const SDL_Rect& pinguinRect) const
{
	return drawingData.move.get_x_position() + pinguinRect.w / 2 >= 0
		&& drawingData.move.get_x_position() - pinguinRect.w / 2 < GameScreenWidth
		&& drawingData.move.get_y_position() + pinguinRect.h / 2 >= 0
		&& drawingData.move.get_y_position() - pinguinRect.h / 2 < GameScreenHeight;
}

void PinguinBehaviorData::emplaceQuackSoundToStack(demos::DemoAntarcticPackage& antarcticPackage) const
{
	if( antarcticPackage.demoKind == demos::GameIsRecording )
	{
		antarcticPackage.pinguinsQuacks.emplaceElement(demos::SoundStackData{ antarcticPackage.pinguinsQuacks.getCurrentElapsedMicroSecondsTime(), 
																				onePlGame::SoundQuack, onePlGame::GroupTagEnemy} );
	}
}