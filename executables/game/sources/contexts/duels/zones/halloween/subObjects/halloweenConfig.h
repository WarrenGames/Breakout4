#ifndef HALLOWEEN_CONFIG_H
#define HALLOWEEN_CONFIG_H

#include <vector>

struct HalloweenConfig
{
	std::vector<unsigned> pumpkinsSeed;
	unsigned secondsBeforeNewPumpkin;
	unsigned secondsSinceLastSpecialBonus;
	bool canDisplayWallpaper;
	bool wallpaperIsDaytime;
	
	explicit HalloweenConfig();
	~HalloweenConfig() = default;
	HalloweenConfig( const HalloweenConfig& ) = delete;
	HalloweenConfig& operator= ( const HalloweenConfig& ) = delete;
	HalloweenConfig( HalloweenConfig&& ) = default;
	HalloweenConfig& operator= ( HalloweenConfig&& ) = default; 
	
	operator bool () const;
};

#endif //HALLOWEEN_CONFIG_H