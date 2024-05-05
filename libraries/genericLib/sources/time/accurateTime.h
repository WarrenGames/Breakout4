#ifndef ACCURATE_TIME_H
#define ACCURATE_TIME_H

#include <chrono>

class AccurateTimeDelay
{
private:
	std::chrono::steady_clock::time_point precedent;
	
public:
	explicit AccurateTimeDelay();
	AccurateTimeDelay( const AccurateTimeDelay& ) = default;
	AccurateTimeDelay& operator= ( const AccurateTimeDelay& ) = default;
	AccurateTimeDelay( AccurateTimeDelay&& ) = default;
	AccurateTimeDelay& operator= ( AccurateTimeDelay&& ) = default;

	bool hasTimeElapsed(std::chrono::milliseconds elapsedTime) const;
	bool hasTimeElapsed(std::chrono::microseconds elapsedTime) const; 
	bool hasTimeElapsed(const std::chrono::duration<long double, std::micro>& delay) const;
	bool hasTimeElapsed(const std::chrono::duration<long double, std::milli>& delay) const;
	
	bool hasTimeNotElapsed(std::chrono::milliseconds elapsedTime) const;
	bool isTimeBetweenBoundaries(std::chrono::milliseconds min, std::chrono::milliseconds max) const;
	void joinTimePoints();
	std::chrono::duration<long double, std::ratio<1> > getCurrentElapsedSecondsTime() const;
	std::chrono::duration<long double, std::milli> getCurrentElapsedMillisecondsTime() const;
	std::chrono::duration<long double, std::micro> getCurrentElapsedMicrosecondsTime() const;
};

#endif //ACCURATE_TIME_H