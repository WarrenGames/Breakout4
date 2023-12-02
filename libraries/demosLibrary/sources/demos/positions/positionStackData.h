#ifndef DEMOS_LIB_POSITIONS_STACK_STRUCT_DATA_H
#define DEMOS_LIB_POSITIONS_STACK_STRUCT_DATA_H

#include "customTypes/positionTypes.h"
#include <chrono>

namespace demos{

struct PositionStackData
{
	std::chrono::duration<long double, std::micro> delay;
	Offset position;
	
	explicit PositionStackData();
	explicit PositionStackData(const std::chrono::duration<long double, std::micro>& newDelay, int xPosition, int yPosition);
	~PositionStackData() = default;
	PositionStackData( const PositionStackData& ) = default;
	PositionStackData& operator= ( const PositionStackData& ) = default;
	PositionStackData( PositionStackData&& ) = default;
	PositionStackData& operator= ( PositionStackData&& ) = default;
};

}

#endif //DEMOS_LIB_POSITIONS_STACK_STRUCT_DATA_H