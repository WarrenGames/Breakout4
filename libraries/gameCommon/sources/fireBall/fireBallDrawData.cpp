#include "fireBall/fireBallDrawData.h"
#include "generic/maths/orientation.h"
#include "fireBall/fireBallConsts.h"
#include <cassert>

FireBallDrawData::FireBallDrawData():
	frameNumber{0}
{
	
}

void FireBallDrawData::animFireBall()
{
	if( anim.hasTimeElapsed( std::chrono::milliseconds{fireBall::AnimDelay} ) )
	{
		anim.joinTimePoints();
		if( frameNumber + 1 < fireBall::AnimFramesNumber )
		{
			frameNumber++;
		}
		else{
			frameNumber = 0;
		}
	}
}
