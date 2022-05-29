#include "contexts/gameCommon/fireBall/fireBallDrawData.h"
#include "generic/maths/orientation.h"
#include "contexts/gameCommon/fireBall/fireBallConsts.h"
#include <cassert>

FireBallDrawData::FireBallDrawData():
	direction{0},
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

void FireBallDrawData::setDirection(int xNorm, int yNorm)
{
	direction = static_cast<unsigned>( getDirection(fireBall::TEXTURES_DIRECTIONS_NUMBER, xNorm, yNorm ) );
	assert( direction < fireBall::TEXTURES_DIRECTIONS_NUMBER );
}