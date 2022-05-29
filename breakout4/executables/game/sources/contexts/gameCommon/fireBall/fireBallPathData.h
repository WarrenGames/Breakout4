#ifndef FIRE_BALL_PATH_DATA_H
#define FIRE_BALL_PATH_DATA_H

#include "contexts/gameCommon/movements/movePathData.h"
#include "contexts/gameCommon/movements/pathFinalPositions.h"

class ObjectMoving;
struct FireBallDrawData;

class FireBallPathData
{
private:
	PathData path;
	PathFinalPositions finalPositions;
	Offset startPosition;
	unsigned moveSegmentNumber;
	bool x_axis_way_accomp;
	bool y_axis_way_accomp;
	bool hasPathEnded;

public:
	FireBallPathData(const PathData& loadedPath, const Offset& startPos);
	~FireBallPathData() = default;
	FireBallPathData( const FireBallPathData& ) = delete;
	FireBallPathData& operator= ( const FireBallPathData& ) = delete;
	FireBallPathData( FireBallPathData&& ) = default;
	FireBallPathData& operator= ( FireBallPathData&& ) = default;
	
	void update(ObjectMoving& move, FireBallDrawData& drawData, bool& isFireBallActive);
	void resetMove(ObjectMoving& move);
	void resetStartPosition(const Offset& newPosition);
	
private:
	void setWayOnXaxisAccomplished(int xVector, double xPosition, int finalXPos);
	void setWayOnYaxisAccomplished(int yVector, double yPosition, int finalYPos);
	
	void checkWay(const ObjectMoving& move);
	void checkPathSegment(ObjectMoving& move, FireBallDrawData& drawData, bool& isFireBallActive);
	void stopMove(ObjectMoving& move, bool& isFireBallActive);
	void setNewSegment(ObjectMoving& move, const PathSegment& pathSegment) const;
};

#endif //FIRE_BALL_PATH_DATA_H