#ifndef DUELS_METAL_STRINGS_CONFIG_H
#define DUELS_METAL_STRINGS_CONFIG_H

namespace duels{

struct MetalStringsConfig
{
	unsigned barrierInWayDuration;
	unsigned barrierActivatorType;
	
	MetalStringsConfig();
	~MetalStringsConfig() = default;
	MetalStringsConfig( const MetalStringsConfig& ) = default;
	MetalStringsConfig& operator= ( const MetalStringsConfig& ) = default;
};

}

#endif //DUELS_METAL_STRINGS_CONFIG_H