#include "contexts/gameCommon/steamData/steamSample.h"
#include "customTypes/positionTypes.h"

SteamSample::SteamSample(const AccurCoords& startingPosition, double speed, const Offset& direction):
	frameNum{0},
	moveDelay{},
	moveSample{startingPosition, speed, direction}
{
	
}

void SteamSample::move(unsigned time)
{
	if( moveDelay.hasTimeElapsed( std::chrono::milliseconds{time} ) )
	{
		moveSample.moveObject();
		moveDelay.joinTimePoints();
	}
}

void SteamSample::anim(std::size_t frameMax, bool loop)
{
	if( frameNum + 1 < frameMax )
	{
		++frameNum;
	}
	else{
		if( loop )
			frameNum = 0;
	}
}