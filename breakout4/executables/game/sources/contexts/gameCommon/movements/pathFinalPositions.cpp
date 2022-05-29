#include "contexts/gameCommon/movements/pathFinalPositions.h"
#include "contexts/gameCommon/movements/movePathData.h"
#include <cassert>

PathFinalPositions::PathFinalPositions(const PathData& pathLoader)
{
	populateVector(pathLoader);
}

void PathFinalPositions::populateVector(const PathData& pathLoader)
{
	if( pathLoader.size() > 0 )
	{
		Offset startingPos{ 0, 0 };
		if( pathLoader.size() > 0 )
		{
			for( std::size_t segmentNumber{0} ; segmentNumber < pathLoader.size() ; ++segmentNumber )
			{
				startingPos = combineOffset(startingPos, pathLoader.getSegment(segmentNumber).vector );
				finalPositions.emplace_back( Offset{ startingPos } );
			}
		}
	}
}

std::size_t PathFinalPositions::size() const
{
	return finalPositions.size();
}

const Offset& PathFinalPositions::getFinalPosition(std::size_t segmentNumber) const
{
	assert( segmentNumber < finalPositions.size() );
	return finalPositions[segmentNumber];
}