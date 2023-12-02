#ifndef DEMOS_LIB_TAGGED_POSITIONS_STACK_STRUCT_DATA_H
#define DEMOS_LIB_TAGGED_POSITIONS_STACK_STRUCT_DATA_H

#include "customTypes/positionTypes.h"
#include <chrono>

namespace demos{

struct TaggedPositionStackData
{
	std::chrono::duration<long double, std::micro> delay;
	Offset position;
	unsigned itemTagNumber;
	
	explicit TaggedPositionStackData();
	explicit TaggedPositionStackData(const std::chrono::duration<long double, std::micro>& newDelay, int xPosition, int yPosition, unsigned tagNumber);
	~TaggedPositionStackData() = default;
	TaggedPositionStackData( const TaggedPositionStackData& ) = default;
	TaggedPositionStackData& operator= ( const TaggedPositionStackData& ) = default;
	TaggedPositionStackData( TaggedPositionStackData&& ) = default;
	TaggedPositionStackData& operator= ( TaggedPositionStackData&& ) = default;
};

}

#endif //DEMOS_LIB_TAGGED_POSITIONS_STACK_STRUCT_DATA_H