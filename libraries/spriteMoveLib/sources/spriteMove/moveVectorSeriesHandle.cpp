#include "spriteMove/moveVectorSeriesHandle.h"
#include "spriteMove/objectMove.h"
#include "spriteMove/spriteMoveData.h"
#include "spriteMove/starType.h"
#include "spriteMove/moveInfos.h"
#include "spriteMove/moveConsts.h"

void spriteMove::handleStarSpriteMove(spriteMove::MovementThings& move, spriteMove::StarTypeThings& starSprite, const Offset& increment)
{
	if( false == move.vectMvtInfos.empty() )
	{
		spriteMove::waitFirstTimeIfAny(move, starSprite);
		move.setWayOnXaxisAccomplished(increment.x);
		move.setWayOnYaxisAccomplished(increment.y);
		
		if( spriteMove::canCarryOnWithSameDir(move, starSprite) )
		{
			//If there's at least one vector to browse and the direction is the same
			move.atLeastOneVectorInMove();
		}
		else if( spriteMove::canCarryOnWithDifferentDir(move, starSprite) )
		{
			//If reaching a new node but direction of next vector is different and there's still a vector path to browse
			starSprite.determineClockwiseRotation(move.vectorNumber);
			starSprite.orientateWithTiming();
		}
		else if( spriteMove::hasReachedPathEnd(move) )
		{
			//If sprite has reached the end of its path and destruction condition is 'DestroyReachPathEnd'
			//idMainSprite.spriteState = CSpriteMustBeErased;
			move.hasMoveEnded = true;
			move.moveSprite.stopObject();
		}
		else{	
			move.move();
		}
	}
}

void spriteMove::handleAnim1DirMove(spriteMove::MovementThings& move, spriteMove::StarTypeThings& starSprite, const Offset& increment)
{
	if( false == move.vectMvtInfos.empty() )
	{
		waitFirstTimeIfAny(move, starSprite);
		move.setWayOnXaxisAccomplished(increment.x);
		move.setWayOnYaxisAccomplished(increment.y);
		if( move.x_axis_way_accomp && move.y_axis_way_accomp && move.vectorNumber + 1 < move.vectMvtInfos.size())
		{
			move.atLeastOneVectorInMove();
		}
		else if( move.x_axis_way_accomp && move.y_axis_way_accomp && move.vectorNumber + 1 == move.vectMvtInfos.size() )
		{
			move.hasMoveEnded = true;
		}
		else{
			move.move();
		}
	}
}

void spriteMove::waitFirstTimeIfAny(spriteMove::MovementThings& move, spriteMove::StarTypeThings& starSprite)
{
	if( false == move.hasStarted && move.vectMvtInfos[0].wait.count() > 0 )
	{
		move.hasStarted = true;
		move.isWaiting = true;
		move.waitMeasure.joinTimePoints();
		starSprite.determineClockwiseRotation(move.vectorNumber);
		starSprite.orientateWithTiming();
	}
}

bool spriteMove::canCarryOnWithSameDir(const spriteMove::MovementThings& move, const spriteMove::StarTypeThings& starSprite)
{
	return move.x_axis_way_accomp 
		&& move.y_axis_way_accomp 
		&& move.vectorNumber + 1 < move.vectMvtInfos.size()
		&& starSprite.padDirection == starSprite.orientationInfos[move.vectorNumber + 1];
}

bool spriteMove::canCarryOnWithDifferentDir(const spriteMove::MovementThings& move, const spriteMove::StarTypeThings& starSprite)
{
	return move.x_axis_way_accomp 
		&& move.y_axis_way_accomp 
		&& move.vectorNumber + 1 < move.vectMvtInfos.size()
		&& starSprite.padDirection != starSprite.orientationInfos[move.vectorNumber + 1];
}

bool spriteMove::hasReachedPathEnd(const spriteMove::MovementThings& move)
{
	return move.x_axis_way_accomp 
		&& move.y_axis_way_accomp 
		&& move.vectorNumber + 1 == move.vectMvtInfos.size();
}