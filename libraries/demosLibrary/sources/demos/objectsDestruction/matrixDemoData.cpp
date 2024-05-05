#include "demos/objectsDestruction/matrixDemoData.h"

demos::Matrix2DAction::Matrix2DAction():
	delay{ 0 },
	coords{ 0, 0 }
{
	
}

demos::Matrix2DAction::Matrix2DAction(long double newDelay, const Coord2D& newCoords, const BrickData& newBrick):
	delay{ newDelay },
	coords{ newCoords },
	brickData{ newBrick }
{
	
}