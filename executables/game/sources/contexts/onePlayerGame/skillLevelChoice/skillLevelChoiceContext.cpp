#include "contexts/onePlayerGame/skillLevelChoice/skillLevelChoiceContext.h"
#include "contexts/onePlayerGame/skillLevelChoice/skillLevelChoiceGraphicalInterface.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

void onePlGame::skillChoice::context(Essentials& essentials, unsigned& chosenSkillLevel, bool& quitWholeMenus)
{
	onePlGame::skillChoice::Interface interface{essentials};
	bool quitChoice{false};
	onePlGame::skillChoice::mainLoop(essentials, interface, chosenSkillLevel, quitChoice, quitWholeMenus);
}

void onePlGame::skillChoice::mainLoop(Essentials& essentials, onePlGame::skillChoice::Interface& interface, unsigned& chosenSkillLevel, bool& quitChoice, bool& quitWholeMenus)
{
	while( false == quitChoice )
	{
		essentials.inp.updateEvents();
		interface.update(essentials);
		onePlGame::skillChoice::redirectUser(essentials, interface, chosenSkillLevel, quitChoice, quitWholeMenus);
		onePlGame::skillChoice::drawEverything(essentials, interface, quitChoice);
	}
}

void onePlGame::skillChoice::redirectUser(Essentials& essentials, const onePlGame::skillChoice::Interface& interface, unsigned& chosenSkillLevel, bool& quitChoice, bool& quitWholeMenus)
{
	onePlGame::skillChoice::checkSkillButtons(essentials, interface, chosenSkillLevel, quitChoice);
	onePlGame::skillChoice::quitContext(essentials, quitChoice, quitWholeMenus);
	onePlGame::skillChoice::checkGoBackButton(interface, quitChoice, quitWholeMenus);
}

void onePlGame::skillChoice::checkSkillButtons(Essentials& essentials, const onePlGame::skillChoice::Interface& interface, unsigned& chosenSkillLevel, bool& quitChoice)
{
	for( unsigned skill{0} ; skill < onePlGame::SkillLevelMax ; ++skill )
	{
		if( interface.skillButtons[skill].buttonClicked() )
		{
			essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
			chosenSkillLevel = skill;
			quitChoice = true;
		}
	}
}

void onePlGame::skillChoice::quitContext(Essentials& essentials, bool& quitChoice, bool& quitWholeMenus)
{
	if( essentials.inp.getSDL_quit() || essentials.inp.getKeyState(input::KeybOut) )
	{
		essentials.inp.setKeyStateToFalse(input::KeybOut);
		quitChoice = true;
		quitWholeMenus = true;
	}
}

void onePlGame::skillChoice::checkGoBackButton(const onePlGame::skillChoice::Interface& interface, bool& quitChoice, bool& quitWholeMenus)
{
	if( interface.goBackButton.buttonClicked() )
	{
		quitChoice = true;
		quitWholeMenus = true;
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

