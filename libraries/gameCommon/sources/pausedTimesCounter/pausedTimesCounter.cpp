#include "pausedTimesCounter/pausedTimesCounter.h"

PausedTimesCounter::PausedTimesCounter():
	stackedTime{ std::chrono::milliseconds{0} }
{
	
}

void PausedTimesCounter::setPrecedent()
{
	delay.joinTimePoints();
}

void PausedTimesCounter::endPauseAndStackDuration()
{
	stackedTime += delay.getCurrentElapsedMillisecondsTime();
}

const std::chrono::duration< long double, std::milli >& PausedTimesCounter::getStackedTime() const
{
	return stackedTime;
}