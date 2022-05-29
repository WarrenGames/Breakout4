#include "contexts/gameCommon/movements/movePathData.h"
#include <cassert>

void PathData::addPath(const PathSegment& newSegment)
{
	path.emplace_back( newSegment );
}

std::size_t PathData::size() const
{
	return path.size();
}

const PathSegment& PathData::getSegment(std::size_t segmentNumber) const
{
	assert( segmentNumber < path.size() );
	return path[segmentNumber];
}