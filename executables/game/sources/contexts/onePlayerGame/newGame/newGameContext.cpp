#include "contexts/onePlayerGame/newGame/newGameContext.h"
#include "contexts/onePlayerGame/newGame/newGameInterface.h"
#include "types/essentialsStruct.h"
#include "consts/sdlColors.h"
#include "consts/onePlayerMenuItems.h"

void onePlGame::newGame::context(Essentials& essentials, unsigned& chosenMenuItem, bool& quitWholeMenus)
{
	bool quitNewGameMenu{false};
	onePlGame::newGame::Interface interface{essentials};
	onePlGame::newGame::mainLoop(essentials, interface, chosenMenuItem, quitNewGameMenu, quitWholeMenus);
}

void onePlGame::newGame::mainLoop(Essentials& essentials, onePlGame::newGame::Interface& interface, unsigned& chosenMenuItem, bool& quitNewGameMenu, bool& quitWholeMenus)
{
	while( false == quitNewGameMenu && false == quitWholeMenus )
	{
		onePlGame::newGame::update(essentials, interface, chosenMenuItem, quitNewGameMenu, quitWholeMenus);
		onePlGame::newGame::drawEverything(essentials, interface, quitNewGameMenu);
	}
}

void onePlGame::newGame::update(Essentials& essentials, onePlGame::newGame::Interface& interface, unsigned& chosenMenuItem, bool& quitNewGameMenu, bool& quitWholeMenus)
{
	essentials.inp.updateEvents();
	interface.update(essentials);
	onePlGame::newGame::redirectUser(essentials, interface, chosenMenuItem, quitNewGameMenu);
	onePlGame::newGame::quitContext(essentials, quitNewGameMenu, quitWholeMenus);
}

void onePlGame::newGame::redirectUser(Essentials& essentials, const onePlGame::newGame::Interface& interface, unsigned& chosenMenuItem, bool& quitNewGameMenu)
{
	onePlGame::newGame::startNewGame(essentials, interface, chosenMenuItem, quitNewGameMenu);
	onePlGame::newGame::loadSavedGame(essentials, interface, chosenMenuItem, quitNewGameMenu);
	onePlGame::newGame::seeDoneScores(essentials, interface, chosenMenuItem, quitNewGameMenu);
	onePlGame::newGame::recordDemo(essentials, interface, chosenMenuItem, quitNewGameMenu);
	onePlGame::newGame::playDemo(essentials, interface, chosenMenuItem, quitNewGameMenu);
	onePlGame::newGame::goBack(essentials, interface, chosenMenuItem, quitNewGameMenu);
}

void onePlGame::newGame::quitContext(Essentials& essentials, bool& quitNewGameMenu, bool& quitWholeMenus)
{
	if( essentials.inp.getSDL_quit() || essentials.inp.getKeyState(input::KeybOut) )
	{
		essentials.inp.setKeyStateToFalse(input::KeybOut);
		quitNewGameMenu = true;
		quitWholeMenus = true;
	}
}

void onePlGame::newGame::startNewGame(Essentials& essentials, const onePlGame::newGame::Interface& interface, unsigned& chosenMenuItem, bool& quitNewGameMenu)
{
	if( interface.newGameButton.buttonClicked() )
	{
		quitNewGameMenu = true;
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		chosenMenuItem = onePlGame::menu::ItemNewGame;
	}
}

void onePlGame::newGame::loadSavedGame(Essentials& essentials, const onePlGame::newGame::Interface& interface, unsigned& chosenMenuItem, bool& quitNewGameMenu)
{
	if( interface.loadASavedGame.buttonClicked() )
	{
		quitNewGameMenu = true;
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		chosenMenuItem = onePlGame::menu::ItemLoadGame;
	}
}

void onePlGame::newGame::seeDoneScores(Essentials& essentials, const onePlGame::newGame::Interface& interface, unsigned& chosenMenuItem, bool& quitNewGameMenu)
{
	if( interface.seeDoneScores.buttonClicked() )
	{
		quitNewGameMenu = true;
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		chosenMenuItem = onePlGame::menu::ItemSeeDoneScores;
	}
}

void onePlGame::newGame::recordDemo(Essentials& essentials, const onePlGame::newGame::Interface& interface, unsigned& chosenMenuItem, bool& quitNewGameMenu)
{
	if( interface.recordDemo.buttonClicked() )
	{
		quitNewGameMenu = true;
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		chosenMenuItem = onePlGame::menu::ItemRecordDemo;
	}
}

void onePlGame::newGame::playDemo(Essentials& essentials, const onePlGame::newGame::Interface& interface, unsigned& chosenMenuItem, bool& quitNewGameMenu)
{
	if( interface.playDemo.buttonClicked() )
	{
		quitNewGameMenu = true;
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		chosenMenuItem = onePlGame::menu::ItemPlayDemo;
	}
}

void onePlGame::newGame::goBack(Essentials& essentials, const onePlGame::newGame::Interface& interface, unsigned& chosenMenuItem, bool& quitNewGameMenu)
{
	if( interface.goBackButton.buttonClicked() )
	{
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		quitNewGameMenu = true;
		chosenMenuItem = onePlGame::menu::ItemGoBack;
	}
}

void onePlGame::newGame::drawEverything(Essentials& essentials, onePlGame::newGame::Interface& interface, bool& quitNewGameMenu)
{
	if( false == quitNewGameMenu )
	{
		if( essentials.drawFreq.canDrawGame() )
		{
			essentials.rndWnd.clearScreen(BlackColor);
			interface.drawEverything(essentials);
			essentials.rndWnd.displayRenderer();
		}
	}
}