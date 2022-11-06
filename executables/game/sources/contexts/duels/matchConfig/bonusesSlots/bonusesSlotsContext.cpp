#include "contexts/duels/matchConfig/bonusesSlots/bonusesSlotsContext.h"
#include "contexts/duels/matchConfig/bonusesSlots/bonusInterface.h"
#include "contexts/duels/matchConfig/interface/zoneChoiceThings.h"
#include "types/essentialsStruct.h"
#include "consts/sdlColors.h"

void duels::bonuses::context(Essentials& essentials, ZoneChoiceThings& zoneChoiceThings)
{
	if( BonusesInterface interface{essentials} )
	{
		bool quitMenu{false};
		duels::bonuses::mainLoop(essentials, zoneChoiceThings, interface, quitMenu);
	}
	else{
		essentials.logs.error << "Error: couldn't start duels bonuses slot interface.\n";
	}
}

void duels::bonuses::mainLoop(Essentials& essentials, ZoneChoiceThings& zoneChoiceThings, BonusesInterface& interface, bool& quitMenu)
{
	while( false == quitMenu )
	{
		essentials.inp.updateEvents();
		interface.update(essentials);
		duels::bonuses::quitContext(essentials, quitMenu);
		duels::bonuses::quitWithButton(interface, quitMenu);
		duels::bonuses::writeDataWithButtons(essentials, interface);
		duels::bonuses::loadSlot(essentials, zoneChoiceThings, interface, quitMenu);
		duels::bonuses::drawEverything(essentials, zoneChoiceThings, interface, quitMenu);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void duels::bonuses::quitContext(Essentials& essentials, bool& quitMenu)
{
	if( essentials.inp.getKeyState(input::KeybOut) || essentials.inp.getSDL_quit() )
	{
		quitMenu = true;
		essentials.inp.setKeyStateToFalse(input::KeybOut);
	}
}

void duels::bonuses::writeDataWithButtons(Essentials& essentials, const BonusesInterface& interface)
{
	interface.writeData(essentials);
}
void duels::bonuses::loadSlot(Essentials& essentials, ZoneChoiceThings& zoneChoiceThings, const BonusesInterface& interface, bool& quitMenu)
{
	interface.loadDataToCurrent(essentials, zoneChoiceThings, quitMenu);
}

void duels::bonuses::drawEverything(Essentials& essentials, ZoneChoiceThings& zoneChoiceThings, BonusesInterface& interface, bool quitMenu)
{
	if( essentials.drawFreq.canDrawGame() && false == quitMenu )
	{
		essentials.rndWnd.clearScreen(BlackColor);
		zoneChoiceThings.graphics.vignettes.drawVignettes(essentials.rndWnd);
		interface.drawEverything(essentials);
		essentials.rndWnd.displayRenderer();
	}
}

void duels::bonuses::quitWithButton(const BonusesInterface& interface, bool& quitMenu)
{
	if( interface.quit.buttonClicked() )
	{
		quitMenu = true;
	}
}