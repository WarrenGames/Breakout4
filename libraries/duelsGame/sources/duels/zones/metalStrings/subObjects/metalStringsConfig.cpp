#include "duels/zones/metalStrings/subObjects/metalStringsConfig.h"
#include "consts/duelsSounds.h"

duels::MetalStringsConfig::MetalStringsConfig():
	barrierInWayDuration{4000},
	barrierActivatorType{0},
	soundsListFilePath{ duels::CommonSoundsFilePath },
	channelsConfigFilePath{ duels::CommonChannelsFilePath }
{

}