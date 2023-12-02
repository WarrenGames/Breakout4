#ifndef DUELS_BAD_BAT_DATA_H
#define DUELS_BAD_BAT_DATA_H

#include "spriteMove/objectMove.h"
#include "time/accurateTime.h"
#include "halloween/bat/batConsts.h"
#include <vector>

class BadBatData
{
	friend class BadBatDrawer;
	
private:
	std::size_t wingsFrameNumber;
	spriteMove::ObjectMoving batMove;
	AccurateTimeDelay wingsAnim;
	AccurateTimeDelay batMoveDelay;
	std::size_t faceIndex;
	unsigned moveState;
	bool wingsMoveDown;
	const std::vector< Offset > wingsOffsets;

public:
	BadBatData();
	~BadBatData() = default;
	BadBatData( const BadBatData& ) = delete;
	BadBatData& operator= ( const BadBatData& ) = delete;
	BadBatData( BadBatData&& ) = default;
	BadBatData& operator= ( BadBatData&& ) = default;
	
	void update();
	void changeMovementType(unsigned newMoveState, const Offset& newVectors);
	void changeFace(std::size_t newFace);
	const Offset& getOffset() const;
	unsigned getMoveState() const;
	void startBadBatActivity();
	const AccurCoords& getBatPosition() const;
	
private:
	void animation();
	void moveBat();
	void stopBat();
};

#endif //DUELS_BAD_BAT_DATA_H