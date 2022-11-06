#ifndef USUAL_TYPES_H
#define USUAL_TYPES_H

struct Offset
{
	int x;
	int y;
	
	Offset();
	constexpr Offset(int new_x, int new_y):x{new_x},y{new_y}{}
	Offset& operator*(double multi);
};

Offset combineOffset(const Offset& offset1, const Offset& offset2);

Offset computeDiff(const Offset& origin, const Offset& direction);

bool areOffsetCoordinatesTheSame(const Offset& coord1, const Offset& coord2);

struct AccurCoords
{
	double x;
	double y;
	
	explicit AccurCoords();
	explicit AccurCoords(double new_x, double new_y);
	AccurCoords& operator= ( const Offset& offset );
	explicit AccurCoords( const Offset& offset);
};

#endif //USUAL_TYPES_H