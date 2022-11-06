#ifndef HALLOWEEN_CONTEXT_H
#define HALLOWEEN_CONTEXT_H

struct Essentials;

namespace duels{

struct HalloweenPack;
struct LevelOptions;

namespace halloween{
	void context(Essentials& essentials, unsigned finalScore, duels::LevelOptions& levelOptions);
	
	void mainLoop(Essentials& essentials, duels::HalloweenPack& halloweenPack, unsigned finalScore, duels::LevelOptions& levelOptions);
}

}

#endif //HALLOWEEN_CONTEXT_H