#ifndef PATHS_FINAL_POSITIONS_H
#define PATHS_FINAL_POSITIONS_H

#include "customTypes/positionTypes.h"
#include <vector>

class PathData;

class PathFinalPositions
{
private:
	std::vector< Offset > finalPositions;

public:
	PathFinalPositions() = default;
	PathFinalPositions(const PathData& pathsLoader);
	~PathFinalPositions() = default;
	PathFinalPositions( const PathFinalPositions& ) = default;
	PathFinalPositions& operator= ( const PathFinalPositions& ) = default;
	PathFinalPositions( PathFinalPositions&& ) = default;
	PathFinalPositions& operator= ( PathFinalPositions&& ) = default;
	
	void populateVector(const PathData& pathsLoader);
	std::size_t size() const;
	const Offset& getFinalPosition(std::size_t segmentNumber) const;
};

#endif //PATHS_FINAL_POSITIONS_H