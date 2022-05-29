#include "contexts/gameCommon/stalactites/onePlayerStalactiteData.h"
#include "contexts/gameCommon/stalactites/stalactitesConsts.h"
#include "consts/constexprScreen.h"
#include "SDL.h"

OnePlayerStalactiteData::OnePlayerStalactiteData(unsigned totalWaitT, unsigned randomT, unsigned pauseT, const Offset& startingPos):
	totalWaitTime{totalWaitT},
	randomTime{randomT},
	tempRandomNumber{0},
	pauseTime{pauseT},
	commonData{startingPos, stalactites::DEFAULT_DIRECTION},
	random{0, static_cast<int>(randomT), 0 }
{
	tempRandomNumber = random.getRandomValue();
}

void OnePlayerStalactiteData::startRumble()
{
	if( fallSetterDelay.hasTimeElapsed( std::chrono::milliseconds{totalWaitTime - tempRandomNumber} ) )
	{
		commonData.setState(stalactites::STATE_RUMBLE);
	}
}

bool OnePlayerStalactiteData::isStalactiteInsideScreen(const SDL_Rect& collisionRect, int textureWidth, int textureHeight) const
{
	return commonData.getXCoordinate() - textureWidth / 2 + collisionRect.x + collisionRect.w 	>= 0
		&& commonData.getXCoordinate() - textureWidth / 2 + collisionRect.x 					< GAME_SCREEN_WIDTH
		&& commonData.getYCoordinate() - textureHeight / 2 + collisionRect.y + collisionRect.h 	>= 0
		&& commonData.getYCoordinate() - textureHeight / 2 + collisionRect.y					 < GAME_SCREEN_HEIGHT;
}

void OnePlayerStalactiteData::discardFallingIfOffscreen(const SDL_Rect& collisionRect, int textureWidth, int textureHeight)
{
	if( false == isStalactiteInsideScreen(collisionRect, textureWidth, textureHeight) )
	{
		commonData.setState(stalactites::STATE_OUT);
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
		commonData.setState(stalactites::STATE_STATIC);
		tempRandomNumber = random.getRandomValue();
		fallSetterDelay.joinTimePoints();
	}
}