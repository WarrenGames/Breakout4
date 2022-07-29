#include "spriteMove/starType.h"
#include "spriteMove/orientation.h"
#include "spriteMove/moveInfos.h"

spriteMove::StarTypeThings::StarTypeThings(int initialDirection, int directionsNumber_, unsigned rotationTimeMilliseconds):
	padDirection{initialDirection},
	turretDirection{initialDirection},
	directionsNumber{ directionsNumber_ },
	rotationTime{ rotationTimeMilliseconds },
	isInOrientationPhase{true},
	isOrientationClockwise{true}
{}
	
void spriteMove::StarTypeThings::orientateWithTiming()
{
	if( rotationTimeDelay.hasTimeElapsed( rotationTime ) )
	{
		rotationTimeDelay.joinTimePoints();
		if( isOrientationClockwise && isInOrientationPhase )
		{
			padDirection--;
			if( padDirection <= -1 )
			{
				padDirection = directionsNumber - 1;
			}
		}
		else if( !isOrientationClockwise && isInOrientationPhase )
		{
			padDirection++;
			if( padDirection >= directionsNumber )
			{
				padDirection = 0;
			}
		}
	}
}

void spriteMove::StarTypeThings::determineClockwiseRotation(unsigned vectorNumber)
{
	if( padDirection > orientationInfos[vectorNumber + 1] )
	{
		if( padDirection - orientationInfos[vectorNumber + 1] <= directionsNumber / 2 )
		{
			isOrientationClockwise = true;
		}
		else{
			isOrientationClockwise = false;
		}
		isInOrientationPhase = true;
	}
	else if( padDirection < orientationInfos[vectorNumber + 1] )
	{
		if( orientationInfos[vectorNumber + 1] - padDirection <= directionsNumber / 2 )
		{
			isOrientationClockwise = false;
		}
		else{
			isOrientationClockwise = true;
		}
		isInOrientationPhase = true;
	}
	else
		isInOrientationPhase = false;
}

int spriteMove::StarTypeThings::getDirPad() const
{
	return padDirection;
}

int spriteMove::StarTypeThings::getDirTurret() const
{
	return turretDirection;
}

void spriteMove::StarTypeThings::createOrientationInfos(const std::vector<spriteMove::MoveInfo>& moveData)
{
	for( auto const &data : moveData )
	{
		orientationInfos.emplace_back( getDirection(directionsNumber, data.vectors.x, data.vectors.y) );
	}
}