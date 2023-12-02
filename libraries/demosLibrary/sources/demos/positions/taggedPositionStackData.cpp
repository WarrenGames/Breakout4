#include "demos/positions/taggedPositionStackData.h"
#include "demos/consts/demosConsts.h"

demos::TaggedPositionStackData::TaggedPositionStackData():
	delay{ 0 },
	position{ 0, 0},
	itemTagNumber{ 0 }
{
	
}

demos::TaggedPositionStackData::TaggedPositionStackData(const std::chrono::duration<long double, std::micro>& newDelay, int xPosition, int yPosition, unsigned tagNumber):
	delay{ newDelay },
	position{ xPosition, yPosition },
	itemTagNumber{ tagNumber }
{
	
}