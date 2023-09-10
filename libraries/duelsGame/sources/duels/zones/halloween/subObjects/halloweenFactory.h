#ifndef HALLOWEEN_FACTORY_H
#define HALLOWEEN_FACTORY_H

#include "duels/zones/halloween/subObjects/pumpkins/pumpkinFactory.h"
#include "duels/zones/halloween/subObjects/potBubbles/bubblesDrawer.h"
#include "halloween/pumpkins/pumpkinDrawer.h"
#include "halloween/bat/batFactory.h"
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
	~HalloweenFactory() = default;
	HalloweenFactory( const HalloweenFactory& ) = delete;
	HalloweenFactory& operator= ( const HalloweenFactory& ) = delete;
	HalloweenFactory( HalloweenFactory&& ) = default;
	HalloweenFactory& operator= ( HalloweenFactory&& ) = default;
	void update(duels::LevelOptions& levelOptions, duels::GlobalObject& globalObject);
	void drawEverything(Essentials& essentials);
	void activateSpecialBonus(const duels::LevelOptions& levelOptions, unsigned playerNum);
	bool canActivateSpecialBonus(unsigned playerNum);
	
private:
	void startPumpkinsActivity(const HalloweenConfig& halloweenConfig);
};

}
#endif //HALLOWEEN_FACTORY_H