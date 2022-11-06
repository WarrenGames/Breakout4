#include "contexts/onePlayerGame/skillLevelChoice/context.h"
#include "contexts/onePlayerGame/skillLevelChoice/graphicalInterface.h"
#include "contexts/onePlayerGame/inGameMainMenu/campaignChoice/context.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

void onePlGame::skillChoice::context(Essentials& essentials)
{
	onePlGame::skillChoice::Interface interface{essentials};
	bool quitChoice{false};
	onePlGame::skillChoice::mainLoop(essentials, interface, quitChoice);
}

void onePlGame::skillChoice::mainLoop(Essentials& essentials, onePlGame::skillChoice::Interface& interface, bool& quitChoice)
{
	while( false == quitChoice )
	{
		essentials.inp.updateEvents();
		interface.update(essentials);
		onePlGame::skillChoice::redirectUser(essentials, interface, quitChoice);
		onePlGame::skillChoice::drawEverything(essentials, interface, quitChoice);
	}
}

void onePlGame::skillChoice::redirectUser(Essentials& essentials, const onePlGame::skillChoice::Interface& interface, bool& quitChoice)
{
	onePlGame::skillChoice::checkSkillButtons(essentials, interface, quitChoice);
	onePlGame::skillChoice::quitContext(essentials, quitChoice);
	onePlGame::skillChoice::checkGoBackButton(interface, quitChoice);
}

void onePlGame::skillChoice::checkSkillButtons(Essentials& essentials, const onePlGame::skillChoice::Interface& interface, bool& quitChoice)
{
	for( unsigned skill{0} ; skill < onePlGame::SkillLevelMax ; ++skill )
	{
		if( interface.skillButtons[skill].buttonClicked() )
		{
			essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
			campaignChoice::mainContext(essentials, skill);
			essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
			quitChoice = true;
		}
	}
}

void onePlGame::skillChoice::quitContext(Essentials& essentials, bool& quitChoice)
{
	if( essentials.inp.getSDL_quit() || essentials.inp.getKeyState(input::KeybOut) )
	{
		essentials.inp.setKeyStateToFalse(input::KeybOut);
		quitChoice = true;
	}
}

void onePlGame::skillChoice::checkGoBackButton(const onePlGame::skillChoice::Interface& interface, bool& quitChoice)
{
	if( interface.goBackButton.buttonClicked() )
	{
		quitChoice = true;
		
	}
}

void onePlGame::skillChoice::drawEverything(Essentials& essentials, onePlGame::skillChoice::Interface& interface, bool& quitChoice)
{
	if( false == quitChoice )
	{
		if( essentials.drawFreq.canDrawGame() )
		{
			essentials.rndWnd.clearScreen(BlackColor);
			interface.drawEverything(essentials);
			essentials.rndWnd.displayRenderer();
		}
	}
}

