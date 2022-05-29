#ifndef MOVE_PATH_DATA_H
#define MOVE_PATH_DATA_H

#include "contexts/gameCommon/movements/pathSegmentData.h"
#include <vector>

class PathData
{
private:
	std::vector< PathSegment > path;

public:
	explicit PathData() = default;
	~PathData() = default;
	PathData( const PathData& ) = default;
	PathData& operator= ( const PathData& ) = default;
	PathData( PathData&& ) = default;
	PathData& operator= ( PathData&& ) = default;
	
	void addPath(const PathSegment& newSegment);
	std::size_t size() const;
	const PathSegment& getSegment(std::size_t segmentNumber) const;
};

#endif //MOVE_PATH_DATA_H