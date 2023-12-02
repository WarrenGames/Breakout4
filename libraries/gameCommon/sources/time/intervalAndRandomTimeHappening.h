#ifndef GAME_COMMON_INTERVAL_RANDOM_TIME_HAPPENING_H
#define GAME_COMMON_INTERVAL_RANDOM_TIME_HAPPENING_H

#include "time/accurateTime.h"
#include "random/randomGenerator.h"

class IntervalAndRandom
{
private:
	int globalInterval;
	int randomInterval;
	AccurateTimeDelay mainDelay;
	AccurateTimeDelay randomDelay;
	IntRandomGenerator randomGen;
	int currentRandomValue;
	
public:
	explicit IntervalAndRandom(int bigInterval, int randInterval, unsigned seedAdd);
	~IntervalAndRandom() = default;
	IntervalAndRandom( const IntervalAndRandom& ) = delete;
	IntervalAndRandom& operator= ( const IntervalAndRandom& ) = delete;
	IntervalAndRandom( IntervalAndRandom&& ) = default;
	IntervalAndRandom& operator= ( IntervalAndRandom&& ) = default;
	
	bool canSetGlobalPrecedentTimePoint() const;
	bool canHappen() const;
	void resetBothTimePoints();
};

#endif //GAME_COMMON_INTERVAL_RANDOM_TIME_HAPPENING_H