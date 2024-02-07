#ifndef METAL_STRINGS_DUELS_ZONE_CONTEXT_H
#define METAL_STRINGS_DUELS_ZONE_CONTEXT_H

struct Essentials;
namespace sdl2{ class Font; }

namespace duels{

struct MetalStrings;
struct LevelOptions;
	
namespace strings{
	
	void context(Essentials& essentials, unsigned finalScore, duels::LevelOptions& levelOptions);
	
	void mainLoop(Essentials& essentials, unsigned finalScore, duels::LevelOptions& levelOptions, const sdl2::Font& arial, duels::MetalStrings& global);
	
	void drawEverything(Essentials& essentials, duels::MetalStrings& global);	
}

}

#endif //METAL_STRINGS_DUELS_ZONE_CONTEXT_H