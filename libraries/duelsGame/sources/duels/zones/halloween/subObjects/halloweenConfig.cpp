#include "duels/zones/halloween/subObjects/halloweenConfig.h"
#include "halloween/pumpkins/pumpkinConsts.h"
#include "consts/duelsSounds.h"

HalloweenConfig::HalloweenConfig():
	pumpkinsSeed(PumpkinColorMax, 1),
	secondsBeforeNewPumpkin{8},
	secondsSinceLastSpecialBonus{10},
	soundsListFilePath{ duels::HalloweenSoundsFilePath },
	channelsConfigFilePath{ duels::HalloweenChannelsFilePath },
	canDisplayWallpaper{true},
	wallpaperIsDaytime{false}
{
	
}

HalloweenConfig::operator bool() const
{
	return pumpkinsSeed.size() == PumpkinColorMax;
}