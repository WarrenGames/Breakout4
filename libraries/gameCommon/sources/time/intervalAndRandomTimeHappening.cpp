#include "time/intervalAndRandomTimeHappening.h"

IntervalAndRandom::IntervalAndRandom(int bigInterval, int randInterval, unsigned seedAdd):
	globalInterval{ bigInterval },
	randomInterval{ randInterval },
	randomGen{ 0, randInterval, seedAdd },
	currentRandomValue{ randomGen.getRandomValue() }
{
	
}

bool IntervalAndRandom::canSetGlobalPrecedentTimePoint() const
{
	return mainDelay.hasTimeElapsed(std::chrono::milliseconds{globalInterval} );
}

bool IntervalAndRandom::canHappen() const
{
	return randomDelay.hasTimeElapsed( std::chrono::milliseconds{globalInterval - randomInterval + currentRandomValue} );
}

void IntervalAndRandom::resetBothTimePoints()
{
	mainDelay.joinTimePoints();
	randomDelay.joinTimePoints();
	currentRandomValue = randomGen.getRandomValue();
}