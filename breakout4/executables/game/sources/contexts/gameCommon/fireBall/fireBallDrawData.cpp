#include "contexts/gameCommon/fireBall/fireBallDrawData.h"
#include "generic/maths/orientation.h"
#include "contexts/gameCommon/fireBall/fireBallConsts.h"
#include <cassert>

FireBallDrawData::FireBallDrawData():
	frameNumber{0}
{
	
}

void FireBallDrawData::animFireBall()
{
	if( anim.hasTimeElapsed( std::chrono::milliseconds{fireBall::ANIM_DELAY} ) )
	{
		anim.joinTimePoints();
		if( frameNumber + 1 < fireBall::ANIM_FRAMES_NUMBER )
		{
			frameNumber++;
		}
		else{
			frameNumber = 0;
		}
	}
}
