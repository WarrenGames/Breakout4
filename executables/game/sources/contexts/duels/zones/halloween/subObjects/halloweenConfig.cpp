#include "contexts/duels/zones/halloween/subObjects/halloweenConfig.h"
#include "contexts/gameCommon/halloween/pumpkins/pumpkinConsts.h"

HalloweenConfig::HalloweenConfig():
	pumpkinsSeed(PumpkinColorMax, 1),
	secondsBeforeNewPumpkin{8},
	secondsSinceLastSpecialBonus{10},
	canDisplayWallpaper{true},
	wallpaperIsDaytime{false}
{
	
}

HalloweenConfig::operator bool() const
{
	return pumpkinsSeed.size() == PumpkinColorMax;
}