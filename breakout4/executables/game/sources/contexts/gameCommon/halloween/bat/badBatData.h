#ifndef DUELS_BAD_BAT_DATA_H
#define DUELS_BAD_BAT_DATA_H

#include "contexts/gameCommon/movements/objectMove.h"
#include "time/accurateTime.h"
#include "contexts/gameCommon/halloween/bat/batConsts.h"
#include <array>

class BadBatData
{
	friend class BadBatDrawer;
	
private:
	std::size_t wingsFrameNumber;
	ObjectMoving batMove;
	AccurateTimeDelay wingsAnim;
	AccurateTimeDelay batMoveDelay;
	bool wingsMoveDown;
	std::size_t faceIndex;
	unsigned moveState;
	const std::array< const Offset, bat::WING_IMG_NUMBER > wingsOffsets;

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