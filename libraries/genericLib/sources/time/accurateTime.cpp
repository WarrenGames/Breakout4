#include "time/accurateTime.h"

AccurateTimeDelay::AccurateTimeDelay():
	precedent{std::chrono::steady_clock::now()}
{
	
}

bool AccurateTimeDelay::hasTimeElapsed(std::chrono::milliseconds elapsedTime) const
{
	return std::chrono::steady_clock::now() - precedent >= elapsedTime;
}

bool AccurateTimeDelay::hasTimeElapsed(std::chrono::microseconds elapsedTime) const
{
	return std::chrono::steady_clock::now() - precedent >= elapsedTime;
}

bool AccurateTimeDelay::hasTimeElapsed(const std::chrono::duration<long double, std::micro>& delay) const
{
	return std::chrono::steady_clock::now() - precedent >= delay;
}

bool AccurateTimeDelay::hasTimeElapsed(const std::chrono::duration<long double, std::milli>& delay) const
{
	return std::chrono::steady_clock::now() - precedent >= delay;
}

bool AccurateTimeDelay::hasTimeNotElapsed(std::chrono::milliseconds elapsedTime) const
{
	return std::chrono::steady_clock::now() - precedent < elapsedTime;
}

bool AccurateTimeDelay::isTimeBetweenBoundaries(std::chrono::milliseconds min, std::chrono::milliseconds max) const
{
	return std::chrono::steady_clock::now() - precedent >= min && std::chrono::steady_clock::now() - precedent < max;
}

void AccurateTimeDelay::joinTimePoints()
{
	precedent = std::chrono::steady_clock::now();
}

std::chrono::duration<long double, std::ratio<1> > AccurateTimeDelay::getCurrentElapsedSecondsTime() const
{
	return std::chrono::steady_clock::now() - precedent;
}

std::chrono::duration<long double, std::milli> AccurateTimeDelay::getCurrentElapsedMillisecondsTime() const
{
	return std::chrono::steady_clock::now() - precedent;
}

std::chrono::duration<long double, std::micro> AccurateTimeDelay::getCurrentElapsedMicrosecondsTime() const
{
	return std::chrono::steady_clock::now() - precedent;
}