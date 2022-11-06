#ifndef RAQUETTE_DATA_H
#define RAQUETTE_DATA_H

//The speed of the raquette start at : '5' the minimum value is 3 and the max 8

#include "time/accurateTime.h"

enum{ MoveToLeft, MoveToRight };

class RacketData
{
private:
	bool isFreezed;
	std::chrono::milliseconds freezeDuration;
	double speed;
	double center_x_position;
	unsigned racketSize;//can be: enum{ SmallRacket, MediumRacket, BigRacket, RacketMax };
	int top_y_position;
	AccurateTimeDelay moveTime;
	AccurateTimeDelay freezeTime;
	
public:
	explicit RacketData(unsigned startSize, double startSpeed, int start_y_position);
	~RacketData() = default;
	RacketData( const RacketData& ) = delete;
	RacketData& operator= ( const RacketData& ) = delete;
	RacketData( RacketData&& ) = default;
	RacketData& operator= ( RacketData&& ) = default;
	
	void moveRacket(unsigned moveDirection, int racketCurrentWidth);
	void moveToLeft(int racketCurrentWidth);
	void moveToRight(int racketCurrentWidth);
	
	void modifySize(int addToSize);
	bool canBeEnlarged() const;
	void enlarge();
	
	unsigned getSize() const;
	
	double getSpeed() const;
	void addToSpeed(double speedToAdd);
	bool canSpeedUp() const;
	
	int get_x_pos() const;
	int get_y_pos() const;
	
	bool canBeFreezed() const;
	bool isRacketFreezed() const;
	void startFreeze(std::chrono::milliseconds newFreezeDuration);
	void unfreezeIfPossible();
};

#endif //RAQUETTE_DATA_H