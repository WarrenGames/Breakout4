#include "duels/zones/halloween/halloweenContext.h"
#include "types/essentialsStruct.h"
#include "duels/zones/halloween/subObjects/halloweenGlobalObject.h"
#include "consts/duelsSounds.h"

void duels::halloween::context(Essentials& essentials, unsigned finalScore, duels::LevelOptions& levelOptions)
{
	duels::HalloweenPack halloweenPack{essentials, levelOptions};
		
	if( halloweenPack.wasLoadingPerfect() )
	{
		halloweenPack.zonesCommon.playZoneGreetingsSound( duels::SoundHalloweenOrgan, duels::GroupTagZoneSpecific );
		duels::halloween::mainLoop(essentials, halloweenPack, finalScore, levelOptions);
	}
}
	
void duels::halloween::mainLoop(Essentials& essentials, duels::HalloweenPack& halloweenPack, unsigned finalScore, duels::LevelOptions& levelOptions)
{
	bool quitZone{false};
	while( false == quitZone )
	{
		halloweenPack.update(essentials, levelOptions, quitZone);
		halloweenPack.drawEverything(essentials, levelOptions);
		levelOptions.setChampionshipEnd(finalScore, quitZone);
	}
}
