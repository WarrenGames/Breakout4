#ifndef DEMOS_LIB_TAGGED_DIRECTION_STACK_STRUCT_DATA_H
#define DEMOS_LIB_TAGGED_DIRECTION_STACK_STRUCT_DATA_H

#include <chrono>

namespace demos{

struct TaggedDirectionStackData
{
	std::chrono::duration<long double, std::micro> delay;
	unsigned direction;
	unsigned itemTagNumber;
	
	explicit TaggedDirectionStackData();
	explicit TaggedDirectionStackData(const std::chrono::duration<long double, std::micro>& newDelay, unsigned newDirection, unsigned tagNumber);
	~TaggedDirectionStackData() = default;
	TaggedDirectionStackData( const TaggedDirectionStackData& ) = default;
	TaggedDirectionStackData& operator= ( const TaggedDirectionStackData& ) = default;
	TaggedDirectionStackData( TaggedDirectionStackData&& ) = default;
	TaggedDirectionStackData& operator= ( TaggedDirectionStackData&& ) = default;
	
};

}

#endif //DEMOS_LIB_TAGGED_DIRECTION_STACK_STRUCT_DATA_H