#include "demos/sounds/soundsStackData.h"
#include "consts/onePlayerLevelConsts.h"

demos::SoundStackData::SoundStackData():
	soundEnum{ onePlGame::SoundMax }
{
	
}

demos::SoundStackData::SoundStackData(const std::chrono::duration<long double, std::micro>& newDelay, unsigned newSoundEnum):
	delay{ newDelay },
	soundEnum{ newSoundEnum }
{
	
}
