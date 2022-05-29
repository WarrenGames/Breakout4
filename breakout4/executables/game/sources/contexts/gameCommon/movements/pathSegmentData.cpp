#include "contexts/gameCommon/movements/pathSegmentData.h"

PathSegment::PathSegment():
	vector{ 0, 0 },
	speed{ 0 },
	waitingTime{ 0 }
{
	
}

PathSegment::PathSegment(const Offset& newVector, double newSpeed, std::chrono::milliseconds newWait):
	vector{ newVector },
	speed{ newSpeed },
	waitingTime{ newWait }
{
	
}
