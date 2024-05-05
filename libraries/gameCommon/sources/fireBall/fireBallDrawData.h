#ifndef FIRE_BALL_DRAW_DATA_H
#define FIRE_BALL_DRAW_DATA_H

#include "time/accurateTime.h"

struct FireBallDrawData
{
	unsigned frameNumber;
	AccurateTimeDelay anim;
	
	explicit FireBallDrawData();
	FireBallDrawData( const FireBallDrawData& ) = delete;
	FireBallDrawData& operator= ( const FireBallDrawData& ) = delete;
	FireBallDrawData( FireBallDrawData&& ) = default;
	FireBallDrawData& operator= ( FireBallDrawData&& ) = default;
	
	void animFireBall();
	void setDirection(int xNorm, int yNorm);
};

#endif //FIRE_BALL_DRAW_DATA_H