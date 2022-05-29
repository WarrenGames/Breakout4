#ifndef HALLOWEEN_FACTORY_H
#define HALLOWEEN_FACTORY_H

#include "contexts/duels/zones/halloween/subObjects/pumpkins/pumpkinFactory.h"
#include "contexts/duels/zones/halloween/subObjects/potBubbles/bubblesDrawer.h"
#include "contexts/gameCommon/halloween/pumpkins/pumpkinDrawer.h"
#include "contexts/gameCommon/halloween/bat/batFactory.h"
#include "generic/sounds/soundHandler.h"
#include "time/accurateTime.h"

struct HalloweenConfig;
struct Essentials;

namespace duels{ 

class GlobalObject;

class HalloweenFactory
{
private:
	BatObject badBat;
	PumpkinFactory pumpkins;
	PumpkinDrawer pumpkinDrawer;
	SpecialPumpkins specialPumpkins;
	BubblesDrawer bubblesDrawer;
	AccurateTimeDelay genNewPumpkinDelay;
	const SoundHandler sounds;
	
public:
	explicit HalloweenFactory(Essentials& essentials, const HalloweenConfig& halloweenCfg);
	void update(duels::LevelOptions& levelOptions, duels::GlobalObject& globalObject);
	void drawEverything(Essentials& essentials);
	void activateSpecialBonus(const duels::LevelOptions& levelOptions, unsigned playerNum);
	bool canActivateSpecialBonus(unsigned playerNum);
	
private:
	void startPumpkinsActivity(const HalloweenConfig& halloweenConfig);
};

}
#endif //HALLOWEEN_FACTORY_H