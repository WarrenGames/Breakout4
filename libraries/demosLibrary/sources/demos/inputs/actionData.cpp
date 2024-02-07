#include "demos/inputs/actionData.h"
#include "consts/onePlayerLevelConsts.h"

demos::ActionData::ActionData():
	funcEnum{ onePlGame::InputMax },
	actionState{ false }
{
	
}

demos::ActionData::ActionData(const std::chrono::duration<long double, std::micro>& newDelay, unsigned newFunc, bool action):
	delay{ newDelay },
	funcEnum{ newFunc },
	actionState{ action }
{
	
}