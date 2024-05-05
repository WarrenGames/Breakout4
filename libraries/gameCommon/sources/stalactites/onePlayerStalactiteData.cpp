#include "stalactites/onePlayerStalactiteData.h"
#include "stalactites/stalactitesConsts.h"
#include "consts/constexprScreen.h"
#include "SDL_rect.h"

OnePlayerStalactiteData::OnePlayerStalactiteData(unsigned totalWaitT, unsigned randomT, unsigned pauseT, const Offset& startingPos):
	totalWaitTime{totalWaitT},
	randomTime{randomT},
	tempRandomNumber{0},
	pauseTime{pauseT},
	commonData{startingPos, stalactites::DefaultDirection},
	random{0, static_cast<int>(randomT), 0 }
{
	tempRandomNumber = random.getRandomValue();
}

void OnePlayerStalactiteData::startRumble()
{
	if( fallSetterDelay.hasTimeElapsed( std::chrono::milliseconds{totalWaitTime - tempRandomNumber} ) )
	{
		commonData.setState(stalactites::StateRumble);
	}
}

bool OnePlayerStalactiteData::isStalactiteInsideScreen(const SDL_Rect& collisionRect, int textureWidth, int textureHeight) const
{
	return commonData.getXCoordinate() - textureWidth / 2 + collisionRect.x + collisionRect.w 	>= 0
		&& commonData.getXCoordinate() - textureWidth / 2 + collisionRect.x 					< GameScreenWidth
		&& commonData.getYCoordinate() - textureHeight / 2 + collisionRect.y + collisionRect.h 	>= 0
		&& commonData.getYCoordinate() - textureHeight / 2 + collisionRect.y					 < GameScreenHeight;
}

void OnePlayerStalactiteData::discardFallingIfOffscreen(const SDL_Rect& collisionRect, int textureWidth, int textureHeight)
{
	if( false == isStalactiteInsideScreen(collisionRect, textureWidth, textureHeight) )
	{
		commonData.setState(stalactites::StateOut);
	}
}

void OnePlayerStalactiteData::resetToWaitingState(const SDL_Rect& collisionRect, int textureWidth, int textureHeight)
{
	if( false == isStalactiteInsideScreen(collisionRect, textureWidth, textureHeight) )
	{
		resetToStart();
	}
}

void OnePlayerStalactiteData::resetToStart()
{
	if( fallSetterDelay.hasTimeElapsed( std::chrono::milliseconds{totalWaitTime + pauseTime} ) )
	{
		commonData.resetStalactitePosition();
		commonData.setState(stalactites::StateStatic);
		tempRandomNumber = random.getRandomValue();
		fallSetterDelay.joinTimePoints();
	}
}