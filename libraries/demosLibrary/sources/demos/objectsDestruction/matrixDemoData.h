#ifndef DEMOS_LIB_OBJECT_DESTRUCTION_MATRIX_BRICK_DATA_H
#define DEMOS_LIB_OBJECT_DESTRUCTION_MATRIX_BRICK_DATA_H

#include "matrices/matrixStructs.h"
#include "types/brickData.h"
#include <chrono>

namespace demos{

struct Matrix2DAction
{
	std::chrono::duration<long double, std::micro> delay;
	Coord2D coords;
	BrickData brickData;
	
	explicit Matrix2DAction();
	explicit Matrix2DAction(long double newDelay, const Coord2D& newCoords, const BrickData& newBrick);
	~Matrix2DAction() = default;
	Matrix2DAction( const Matrix2DAction& ) = default;
	Matrix2DAction& operator= ( const Matrix2DAction& ) = default;
};

}

#endif //DEMOS_LIB_OBJECT_DESTRUCTION_MATRIX_BRICK_DATA_H