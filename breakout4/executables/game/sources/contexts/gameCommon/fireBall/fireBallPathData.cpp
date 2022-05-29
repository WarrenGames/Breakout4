#include "contexts/gameCommon/fireBall/fireBallPathData.h"
#include "contexts/gameCommon/movements/objectMove.h"
#include "contexts/gameCommon/fireBall/fireBallDrawData.h"
#include <cassert>

FireBallPathData::FireBallPathData(const PathData& loadedPath, const Offset& startPos):
	path{ loadedPath },
	finalPositions{ path },
	startPosition{ startPos },
	moveSegmentNumber{ 0 },
	x_axis_way_accomp{ false },
	y_axis_way_accomp{ false },
	hasPathEnded{ false }
{

}

void FireBallPathData::setWayOnXaxisAccomplished(int xVector, double xPosition, int finalXPos)
{
	if( xVector < 0 && xPosition < finalXPos )
	{
		x_axis_way_accomp = true;
	}
	else if( xVector > 0 && xPosition > finalXPos )
	{
		x_axis_way_accomp = true;
	}
	else if( xVector == 0 )
	{
		x_axis_way_accomp = true;
	}
}

void FireBallPathData::setWayOnYaxisAccomplished(int yVector, double yPosition, int finalYPos)
{
	if( yVector < 0 && yPosition < finalYPos )
	{
		y_axis_way_accomp = true;
	}
	else if( yVector > 0 && yPosition > finalYPos )
	{
		y_axis_way_accomp = true;
	}
	else if( yVector == 0 )
	{
		y_axis_way_accomp = true;
	}
}

void FireBallPathData::checkWay(const ObjectMoving& move)
{
	if( false == hasPathEnded )
	{
		setWayOnXaxisAccomplished(move.get_x_norm(), move.getPosition().x, startPosition.x + finalPositions.getFinalPosition(moveSegmentNumber).x );
		setWayOnYaxisAccomplished(move.get_y_norm(), move.getPosition().y, startPosition.y + finalPositions.getFinalPosition(moveSegmentNumber).y );
	}
}

void FireBallPathData::checkPathSegment(ObjectMoving& move, FireBallDrawData& drawData, bool& isFireBallActive)
{
	if( x_axis_way_accomp && y_axis_way_accomp )
	{
		if( moveSegmentNumber + 1 < path.size() && moveSegmentNumber + 1 < finalPositions.size() )
		{
			moveSegmentNumber++;
			setNewSegment(move, path.getSegment(moveSegmentNumber) );
			drawData.setDirection(move.get_x_norm(), move.get_y_norm() );
		}
		else{
			stopMove(move, isFireBallActive);
		}
		x_axis_way_accomp = false;
		y_axis_way_accomp = false;
	}
}

void FireBallPathData::update(ObjectMoving& move, FireBallDrawData& drawData, bool& isFireBallActive)
{
	checkWay(move);
	checkPathSegment(move, drawData, isFireBallActive);
}

void FireBallPathData::stopMove(ObjectMoving& move, bool& isFireBallActive)
{
	hasPathEnded = true;
	isFireBallActive = false;
	moveSegmentNumber = 0;
	move.stopObject();
	move.setPosition(startPosition);
}

void FireBallPathData::resetMove(ObjectMoving& move)
{
	hasPathEnded = false;
	move.setPosition(startPosition);
	setNewSegment(move, path.getSegment(0) );
	moveSegmentNumber = 0;
	x_axis_way_accomp = false;
	y_axis_way_accomp = false;
}

void FireBallPathData::resetStartPosition(const Offset& newPosition)
{
	startPosition = newPosition;
}

void FireBallPathData::setNewSegment(ObjectMoving& move, const PathSegment& pathSegment) const
{
	move.setSpeed(pathSegment.speed);
	giveObjectNewDirection(move, pathSegment.vector);
}