#include "hellSkulls/skullData.h"
#include "generic/maths/orientation.h"
#include "hellSkulls/skullConsts.h"
#include <cassert>

SkullData::SkullData():
	direction{0},
	frameNumber{0},
	explosionFrameIndex{0}
{
	
}


SkullData::SkullData(const Offset& pos, double speed, const Offset& moveDirection):
	direction{0},
	frameNumber{0},
	explosionFrameIndex{0},
	move{ AccurCoords{static_cast<double>(pos.x), static_cast<double>(pos.y) }, speed, moveDirection}
{
	setDirection();
}

void SkullData::animSkull()
{
	if( anim.hasTimeElapsed( std::chrono::milliseconds{hellSkull::AnimDelay} ) )
	{
		anim.joinTimePoints();
		if( frameNumber + 1 < hellSkull::AnimFramesNumber )
		{
			frameNumber++;
		}
		else{
			frameNumber = 0;
		}
	}
}

void SkullData::moveSkull()
{
	move.moveObject();
}

void SkullData::setDirection()
{
	direction = static_cast<unsigned>( getDirection(hellSkull::TexturesDirectionsNumber, move.get_x_norm(), move.get_y_norm() ) );
	assert( direction < hellSkull::TexturesDirectionsNumber );
}

void SkullData::animSkullExplosion(unsigned explosionMsDelay, unsigned explosionFramesNumber, bool& isSkullActive)
{
	if( anim.hasTimeElapsed( std::chrono::milliseconds{explosionMsDelay} ) )
	{
		anim.joinTimePoints();
		if( explosionFrameIndex + 1 < explosionFramesNumber )
		{
			explosionFrameIndex++;
		}
		else{
			explosionFrameIndex = 0;
			isSkullActive = false;
		}
	}
}