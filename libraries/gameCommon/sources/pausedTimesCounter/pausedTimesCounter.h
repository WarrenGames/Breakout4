#ifndef GAME_COMMON_PAUSED_TIMES_COUNTER_H
#define GAME_COMMON_PAUSED_TIMES_COUNTER_H

#include "time/accurateTime.h"

class PausedTimesCounter
{
private:
	AccurateTimeDelay delay;
	std::chrono::duration< long double, std::milli > stackedTime;

public:
	explicit PausedTimesCounter();
	~PausedTimesCounter() = default;
	PausedTimesCounter( const PausedTimesCounter& ) = delete;
	PausedTimesCounter& operator= ( const PausedTimesCounter& ) = delete;
	PausedTimesCounter( PausedTimesCounter&& ) = default;
	PausedTimesCounter& operator= ( PausedTimesCounter&& ) = default;
	
	void setPrecedent();
	void endPauseAndStackDuration();
	
	const std::chrono::duration< long double, std::milli >& getStackedTime() const;
};

#endif //GAME_COMMON_PAUSED_TIMES_COUNTER_H