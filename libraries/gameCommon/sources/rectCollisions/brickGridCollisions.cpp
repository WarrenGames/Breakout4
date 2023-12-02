#include "rectCollisions/brickGridCollisions.h"
#include "spriteMove/objectMove.h"
#include "types/spriteSize.h"
#include "matrices/matrix2D.h"
#include "types/brickData.h"
#include "customTypes/positionTypes.h"
#include "consts/duelsConstexpr.h"

bool isThereAnElementAtThisPosition(const MatrixTemp2D<BrickData>& levelGrid, const spriteMove::ObjectMoving& move, const Offset& add)
{
	if( levelGrid.isSignedInsideBoundaries(move.get_x_position() / SQR_SIZE + add.x, move.get_y_position() / SQR_SIZE + add.y) )
	{
		return levelGrid(move.get_x_position() / SQR_SIZE + add.x, move.get_y_position() / SQR_SIZE + add.y).index > 0;
	}
	else
		return false;
}

bool canCollideWithGridLeft(const spriteMove::ObjectMoving& move, const SpriteSize& size, int cornerInterval)
{
	return move.get_x_position() % SQR_SIZE < size.w / 2 - cornerInterval;
}

bool canCollideWithGridRight(const spriteMove::ObjectMoving& move, const SpriteSize& size, int cornerInterval)
{
	return move.get_x_position() % SQR_SIZE > SQR_SIZE - size.w / 2 + cornerInterval;
}

bool canCollideWithGridTop(const spriteMove::ObjectMoving& move, const SpriteSize& size, int cornerInterval)
{
	return move.get_y_position() % SQR_SIZE < size.h / 2 - cornerInterval;
}

bool canCollideWithGridBottom(const spriteMove::ObjectMoving& move, const SpriteSize& size, int cornerInterval)
{
	return move.get_y_position() % SQR_SIZE > SQR_SIZE - size.h / 2 + cornerInterval;
}

void testGridCollisions(const MatrixTemp2D<BrickData>& levelGrid, spriteMove::ObjectMoving& move, const SpriteSize& size, bool& wasThereCol)
{
	testCollideWithTopElement(levelGrid, move, size, wasThereCol);
	testCollideWithBottomElement(levelGrid, move, size, wasThereCol);
	testCollideWithLeftElement(levelGrid, move, size, wasThereCol);
	testCollideWithRightElement(levelGrid, move, size, wasThereCol);
	testCollideWithTopLeftCorner(levelGrid, move, size, wasThereCol);
	testCollideWithTopRightCorner(levelGrid, move, size, wasThereCol);
	testCollideWithBottomLeftCorner(levelGrid, move, size, wasThereCol);
	testCollideWithBottomRightCorner(levelGrid, move, size, wasThereCol);
}

void testCollideWithTopElement(const MatrixTemp2D<BrickData>& levelGrid, spriteMove::ObjectMoving& move, const SpriteSize& size, bool& wasThereCol)
{
	if( canCollideWithGridTop(move, size, 0) && isThereAnElementAtThisPosition(levelGrid, move, Offset{0, -1}) && move.get_y_norm() < 0 )
	{
		move.reverse_y_vector();
		move.adjust_y_speed();
		wasThereCol = true;
	}
}

void testCollideWithBottomElement(const MatrixTemp2D<BrickData>& levelGrid, spriteMove::ObjectMoving& move, const SpriteSize& size, bool& wasThereCol)
{
	if( canCollideWithGridBottom(move, size, 0) && isThereAnElementAtThisPosition(levelGrid, move, Offset{0, 1}) && move.get_y_norm() > 0 )
	{
		move.reverse_y_vector();
		move.adjust_y_speed();
		wasThereCol = true;
	}
}

void testCollideWithLeftElement(const MatrixTemp2D<BrickData>& levelGrid, spriteMove::ObjectMoving& move, const SpriteSize& size, bool& wasThereCol)
{
	if( canCollideWithGridLeft(move, size, 0) && isThereAnElementAtThisPosition(levelGrid, move, Offset{-1, 0}) && move.get_x_norm() < 0 )
	{
		move.reverse_x_vector();
		move.adjust_x_speed();
		wasThereCol = true;
	}
}

void testCollideWithRightElement(const MatrixTemp2D<BrickData>& levelGrid, spriteMove::ObjectMoving& move, const SpriteSize& size, bool& wasThereCol)
{
	if( canCollideWithGridRight(move, size, 0) && isThereAnElementAtThisPosition(levelGrid, move, Offset{1, 0}) && move.get_x_norm() > 0 )
	{
		move.reverse_x_vector();
		move.adjust_x_speed();
		wasThereCol = true;
	}
}

void testCollideWithTopLeftCorner(const MatrixTemp2D<BrickData>& levelGrid, spriteMove::ObjectMoving& move, const SpriteSize& size, bool& wasThereCol)
{
	if( canCollideWithGridTop(move, size, duels::BallCornerInterval) && canCollideWithGridLeft(move, size, duels::BallCornerInterval)
		&& isThereAnElementAtThisPosition(levelGrid, move, Offset{-1, -1}) && !( move.get_x_norm() > 0 && move.get_y_norm() > 0 ) )
	{
		giveObjectNewDirection(move, Offset{1, 1});
		wasThereCol = true;
	}
}

void testCollideWithTopRightCorner(const MatrixTemp2D<BrickData>& levelGrid, spriteMove::ObjectMoving& move, const SpriteSize& size, bool& wasThereCol)
{
	if( canCollideWithGridTop(move, size, duels::BallCornerInterval) && canCollideWithGridRight(move, size, duels::BallCornerInterval) 
		&& isThereAnElementAtThisPosition(levelGrid, move, Offset{1, -1}) && !( move.get_x_norm() < 0 && move.get_y_norm() > 0 ) )
	{
		giveObjectNewDirection(move, Offset{-1, 1});
		wasThereCol = true;
	}
}

void testCollideWithBottomLeftCorner(const MatrixTemp2D<BrickData>& levelGrid, spriteMove::ObjectMoving& move, const SpriteSize& size, bool& wasThereCol)
{
	if( canCollideWithGridBottom(move, size, duels::BallCornerInterval) && canCollideWithGridLeft(move, size, duels::BallCornerInterval) 
		&& isThereAnElementAtThisPosition(levelGrid, move, Offset{-1, 1}) && !( move.get_x_norm() > 0 && move.get_y_norm() < 0 ) )
	{
		giveObjectNewDirection(move, Offset{1, -1});
		wasThereCol = true;
	}
}

void testCollideWithBottomRightCorner(const MatrixTemp2D<BrickData>& levelGrid, spriteMove::ObjectMoving& move, const SpriteSize& size, bool& wasThereCol)
{
	if( canCollideWithGridBottom(move, size, duels::BallCornerInterval) && canCollideWithGridRight(move, size, duels::BallCornerInterval) 
		&& isThereAnElementAtThisPosition(levelGrid, move, Offset{1, 1}) && !( move.get_x_norm() < 0 && move.get_y_norm() < 0 ) )
	{
		giveObjectNewDirection(move, Offset{-1, -1});
		wasThereCol = true;
	}
}
