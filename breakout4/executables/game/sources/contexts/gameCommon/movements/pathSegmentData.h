#ifndef PATH_SEGEMENT_DATA_H
#define PATH_SEGEMENT_DATA_H

#include "customTypes/positionTypes.h"
#include <chrono>

struct PathSegment
{
	Offset vector;
	double speed;
	std::chrono::milliseconds waitingTime;
	
	explicit PathSegment();
	explicit PathSegment(const Offset& newVector, double newSpeed, std::chrono::milliseconds newWait);
	
	~PathSegment() = default;
	PathSegment( const PathSegment& ) = default;
	PathSegment& operator= ( const PathSegment& ) = default;
};

#endif //PATH_SEGEMENT_DATA_H