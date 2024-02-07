#include "duels/zones/halloween/subObjects/halloweenFactory.h"
#include "duels/inGameObjects/global/duelsGlobalObject.h"
#include "duels/zones/halloween/subObjects/halloweenConfig.h"
#include "types/essentialsStruct.h"
#include "halloween/bat/batConsts.h"
#include "consts/duelsSounds.h"
#include <cassert>

duels::HalloweenFactory::HalloweenFactory(Essentials& essentials, const HalloweenConfig& halloweenCfg):
	badBat{essentials},
	pumpkins{halloweenCfg},
	pumpkinDrawer{essentials},
	specialPumpkins{essentials},
	bubblesDrawer{essentials},
	genNewPumpkinDelay{}
{

}

void duels::HalloweenFactory::update(duels::LevelOptions& levelOptions, duels::GlobalObject& globalObject)
{
	bubblesDrawer.update();
	pumpkins.update(badBat, globalObject.players, levelOptions, pumpkinDrawer);
	badBat.update();
	startPumpkinsActivity(levelOptions.halloween, globalObject.gameSoundSystem.soundSystem.soundPlayer);
	specialPumpkins.update(globalObject.players, levelOptions, badBat);
}

void duels::HalloweenFactory::drawEverything(Essentials& essentials)
{
	badBat.drawBat(essentials.rndWnd);
	pumpkins.drawPumpkins(essentials, pumpkinDrawer);
	specialPumpkins.drawPumpkins(essentials, pumpkinDrawer);
	bubblesDrawer.drawBubbles(essentials.rndWnd);
}

void duels::HalloweenFactory::activateSpecialBonus(const duels::LevelOptions& levelOptions, unsigned playerNum)
{
	specialPumpkins.activateSpecialBonus(levelOptions, playerNum);
}

bool duels::HalloweenFactory::canActivateSpecialBonus(unsigned playerNum)
{
	return specialPumpkins.canActivateSpecialBonus(playerNum);
}

void duels::HalloweenFactory::startPumpkinsActivity(const HalloweenConfig& halloweenConfig, const SoundPlayer& soundPlayer)
{
	if( genNewPumpkinDelay.hasTimeElapsed( std::chrono::milliseconds{halloweenConfig.secondsBeforeNewPumpkin * 1000} ) )
	{
		if( badBat.canStartActivity() && pumpkins.canStartActivity() )
		{
			soundPlayer.playSoundOnGroup(duels::SoundPotBubbles, duels::GroupTagZoneSpecific);
			badBat.startBadBatActivity();
			badBat.changeFace(bat::FaceEffort);
			pumpkins.startPumpkinActivity();
			genNewPumpkinDelay.joinTimePoints();
		}
	}
}