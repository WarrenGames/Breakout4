#ifndef SPRITE_MOVEMENTS_DATA_H
#define SPRITE_MOVEMENTS_DATA_H

#include "spriteMove/moveInfos.h"
#include "spriteMove/objectMove.h"
#include "time/accurateTime.h"
#include <vector>
#include <chrono>

namespace spriteMove{

struct MovementThings
{
	ObjectMoving moveSprite;
	std::vector<MoveInfo> vectMvtInfos;
	AccurateTimeDelay waitMeasure;
	unsigned int vectorNumber;
	bool x_axis_way_accomp;
	bool y_axis_way_accomp;
	bool isWaiting;
	bool hasStarted;
	bool hasMoveEnded;
	
	explicit MovementThings(const Offset& startPos);
	~MovementThings() = default;
	MovementThings( const MovementThings& ) = delete;
	MovementThings& operator= ( const MovementThings& ) = delete;
	MovementThings( MovementThings&& ) = default;
	MovementThings& operator= ( MovementThings&& ) = default;
	
	void addMoveInfoElement(int vect_x, int vect_y, int final_x_pos, int final_y_pos, double speed, std::chrono::milliseconds wait);
	void initMoveToFirstVector();
	void setStartPosition(int pos_x, int pos_y);
	void setToWaitingState();
	void waitingObserver();
	void atLeastOneVectorInMove();
	void move();
	void setWayOnXaxisAccomplished(int increment);
	void setWayOnYaxisAccomplished(int increment);
	double getAccuratePosX() const;
	double getAccuratePosY() const;
	int getXPos() const;
	int getYPos() const;
	const AccurCoords& getPosition() const;
	
	void resetMove(const Offset& startPos);
};

}

#endif //SPRITE_MOVEMENTS_DATA_H