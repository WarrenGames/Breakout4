#include "demos/objectDirections/objectDirectionData.h"
#include "demos/consts/demosConsts.h"

demos::TaggedDirectionStackData::TaggedDirectionStackData():
	direction{ 0 },
	itemTagNumber{ 0 }
{
	
}

demos::TaggedDirectionStackData::TaggedDirectionStackData(const std::chrono::duration<long double, std::micro>& newDelay, unsigned newDirection, unsigned tagNumber):
	delay{ newDelay },
	direction{ newDirection },
	itemTagNumber{ tagNumber }
{
	
}