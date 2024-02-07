#ifndef DUELS_SIMPLE_ZONE_CONTEXT_H
#define DUELS_SIMPLE_ZONE_CONTEXT_H

struct Essentials;
namespace sdl2{ class Font; }
class AccurateTimeDelay;

namespace duels{
struct LevelOptions;
struct SimpleZone;
class GlobalObject;

namespace simple{
	void context(Essentials& essentials, unsigned finalScore, duels::LevelOptions& levelOptions);
	
	void mainLoop(Essentials& essentials, const sdl2::Font& arial, duels::GlobalObject& global, unsigned finalScore, duels::LevelOptions& levelOptions, duels::SimpleZone& simpleZone);
	
	void drawEverything(Essentials& essentials, duels::GlobalObject& global, duels::SimpleZone& simpleZone);
}
	
}

#endif //DUELS_SIMPLE_ZONE_CONTEXT_H