#ifndef ONE_PLAYER_STALACTITE_DATA_H
#define ONE_PLAYER_STALACTITE_DATA_H

#include "customTypes/positionTypes.h"
#include "contexts/gameCommon/stalactites/stalactitesData.h"
#include "random/randomGenerator.h"
#include "time/accurateTime.h"

struct SDL_Rect;

struct OnePlayerStalactiteData
{	

	unsigned totalWaitTime;
	unsigned randomTime;
	unsigned tempRandomNumber;
	unsigned pauseTime;
	StalactiteData commonData;
	IntRandomGenerator random;
	AccurateTimeDelay fallSetterDelay;

	explicit OnePlayerStalactiteData(unsigned totalWaitT, unsigned randomT, unsigned pauseT, const Offset& startingPos);
	~OnePlayerStalactiteData() = default;
	OnePlayerStalactiteData( const OnePlayerStalactiteData& ) = delete;
	OnePlayerStalactiteData& operator= ( const OnePlayerStalactiteData& ) = delete;
	OnePlayerStalactiteData( OnePlayerStalactiteData&& ) = default;
	OnePlayerStalactiteData& operator= ( OnePlayerStalactiteData&& ) = default;
	
	void startRumble();
	bool isStalactiteInsideScreen(const SDL_Rect& collisionRect, int textureWidth, int textureHeight) const;
	void discardFallingIfOffscreen(const SDL_Rect& collisionRect, int textureWidth, int textureHeight);
	void resetToWaitingState(const SDL_Rect& collisionRect, int textureWidth, int textureHeight);
	void resetToStart();
};

#endif //ONE_PLAYER_STALACTITE_DATA_H