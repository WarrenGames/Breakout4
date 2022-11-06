#include "customTypes/positionTypes.h"

Offset::Offset():
	x{0},
	y{0}
{

}
	
Offset& Offset::operator*(double multi)
{ 
	x = static_cast<int>( multi * x );
	y = static_cast<int>( multi * y );
	return *this;
}

Offset combineOffset(const Offset& offset1, const Offset& offset2)
{
	return Offset{ offset1.x + offset2.x, offset1.y + offset2.y};
}

Offset computeDiff(const Offset& origin, const Offset& direction)
{
	return Offset{ direction.x - origin.x, direction.y - origin.y };
}

bool areOffsetCoordinatesTheSame(const Offset& coord1, const Offset& coord2)
{
	return coord1.x == coord2.x && coord1.y == coord2.y;
}

AccurCoords::AccurCoords():
	x{0},
	y{0}
{

}

AccurCoords::AccurCoords(double new_x, double new_y):
	x{new_x},
	y{new_y}
{

}

AccurCoords& AccurCoords::operator= ( const Offset& offset )
{
	this->x = static_cast<double>(offset.x);
	this->y = static_cast<double>(offset.y);
	return *this;
}

AccurCoords::AccurCoords(const Offset& offset):
	x{ static_cast<double>(offset.x) },
	y{ static_cast<double>(offset.y) }
{
	
}
