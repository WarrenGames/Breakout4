#ifndef DUELS_METAL_STRINGS_CONFIG_H
#define DUELS_METAL_STRINGS_CONFIG_H

#include "fileSystem/fileSystem.h"

namespace duels{

struct MetalStringsConfig
{
	unsigned barrierInWayDuration;
	unsigned barrierActivatorType;
	fs::path soundsListFilePath;
	fs::path channelsConfigFilePath;
	
	MetalStringsConfig();
	~MetalStringsConfig() = default;
	MetalStringsConfig( const MetalStringsConfig& ) = default;
	MetalStringsConfig& operator= ( const MetalStringsConfig& ) = default;
};

}

#endif //DUELS_METAL_STRINGS_CONFIG_H