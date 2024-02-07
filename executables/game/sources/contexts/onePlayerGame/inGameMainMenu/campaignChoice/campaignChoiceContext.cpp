#include "contexts/onePlayerGame/inGameMainMenu/campaignChoice/campaignChoiceContext.h"
#include "contexts/onePlayerGame/inGameMainMenu/campaignChoice/campaignChoiceGraphicalInterface.h"
#include "types/essentialsStruct.h"
#include "contexts/onePlayerGame/inGameMainMenu/race/raceMainMenuContext.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/constPaths.h"

void campaignChoice::mainContext(Essentials& essentials, unsigned skillLevel, bool& quitWholeMenus)
{
	CampaignChoiceGui interface{essentials};
	bool quitCampChoice{quitWholeMenus};
	while( false == quitCampChoice )
	{
		essentials.inp.updateEvents();
		campaignChoice::quitChoice(essentials, quitCampChoice);
		campaignChoice::updateInterface(essentials, interface);
		campaignChoice::redirectPlayer(essentials, skillLevel, interface, quitCampChoice);
		campaignChoice::drawEverything(essentials, interface, quitCampChoice);
	}
}

void campaignChoice::updateInterface(Essentials& essentials, CampaignChoiceGui& interface)
{
	interface.updateInterfaceWithInput(essentials);
}

void campaignChoice::redirectPlayer(Essentials& essentials, unsigned skillLevel, const CampaignChoiceGui& interface, bool& quitCampChoice)
{
	campaignChoice::runShopRace(essentials, skillLevel, interface, quitCampChoice);
	campaignChoice::runStandardRace(essentials, skillLevel, interface, quitCampChoice);
}

void campaignChoice::runShopRace(Essentials& essentials, unsigned skillLevel, const CampaignChoiceGui& interface, bool& quitCampChoice)
{
	if( interface.shopRaceSelection.buttonClicked() )
	{
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		quitCampChoice = true;
		onePlGame::raceMainMenu::context(essentials, skillLevel, onePlGame::CampaignWithShop);
	}
}

void campaignChoice::runStandardRace(Essentials& essentials, unsigned skillLevel, const CampaignChoiceGui& interface, bool& quitCampChoice)
{
	if( interface.noShopRaceSelection.buttonClicked() )
	{
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		quitCampChoice = true;
		onePlGame::raceMainMenu::context(essentials, skillLevel, onePlGame::CampaignNoShop);
	}
}

void campaignChoice::drawEverything(Essentials& essentials, const CampaignChoiceGui& interface, bool quitCampChoice)
{
	if( false == quitCampChoice )
	{
		essentials.rndWnd.clearScreen(BlackColor);
		interface.drawInterface(essentials);
		essentials.rndWnd.displayRenderer();
		SDL_Delay(SdlDelayTime);
	}
}

void campaignChoice::quitChoice(Essentials& essentials, bool& quitCampChoice)
{
	if( essentials.inp.getKeyState(input::KeybOut) || essentials.inp.getSDL_quit() )
	{
		essentials.inp.setKeyStateToFalse(input::KeybOut);
		quitCampChoice = true;
	}
}