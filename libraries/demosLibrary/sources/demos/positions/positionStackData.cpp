#include "demos/positions/positionStackData.h"

demos::PositionStackData::PositionStackData():
	position{ 0, 0 }
{

}

demos::PositionStackData::PositionStackData(const std::chrono::duration<long double, std::micro>& newDelay, int xPosition, int yPosition):
	delay{ newDelay },
	position{ xPosition,yPosition }
{
	
}