#include "demos/sounds/soundsStackData.h"
#include "consts/onePlayerLevelConsts.h"

demos::SoundStackData::SoundStackData():
	soundEnum{ 0 },
	groupTag{ 0 }
{
	
}

demos::SoundStackData::SoundStackData(const std::chrono::duration<long double, std::micro>& newDelay, unsigned newSoundEnum, unsigned groupTagEnum):
	delay{ newDelay },
	soundEnum{ newSoundEnum },
	groupTag{ groupTagEnum }
{
	
}
