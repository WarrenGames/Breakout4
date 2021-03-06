#include "contexts/onePlayerGame/inGameMainMenu/campaignChoice/context.h"
#include "contexts/onePlayerGame/inGameMainMenu/campaignChoice/graphicalInterface.h"
#include "types/essentialsStruct.h"
#include "contexts/onePlayerGame/inGameMainMenu/race/context.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/constPaths.h"

void campaignChoice::mainContext(Essentials& essentials, unsigned skillLevel)
{
	CampaignChoiceGui interface{essentials};
	bool quitCampChoice{false};
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
		onePlGame::raceMainMenu::context(essentials, skillLevel, onePlGame::CAMPAIGN_WITH_SHOP);
	}
}

void campaignChoice::runStandardRace(Essentials& essentials, unsigned skillLevel, const CampaignChoiceGui& interface, bool& quitCampChoice)
{
	if( interface.noShopRaceSelection.buttonClicked() )
	{
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		quitCampChoice = true;
		onePlGame::raceMainMenu::context(essentials, skillLevel, onePlGame::CAMPAIGN_NO_SHOP);
	}
}

void campaignChoice::drawEverything(Essentials& essentials, const CampaignChoiceGui& interface, bool quitCampChoice)
{
	if( false == quitCampChoice )
	{
		essentials.rndWnd.clearScreen(BLACK_COL);
		interface.drawInterface(essentials);
		essentials.rndWnd.displayRenderer();
		SDL_Delay(SDL_DELAY_TIME);
	}
}

void campaignChoice::quitChoice(Essentials& essentials, bool& quitCampChoice)
{
	if( essentials.inp.getKeyState(input::KEYB_OUT) || essentials.inp.getSDL_quit() )
	{
		essentials.inp.setKeyStateToFalse(input::KEYB_OUT);
		quitCampChoice = true;
	}
}