#include "contexts/onePlayerGame/newGame/newGameContext.h"
#include "contexts/onePlayerGame/newGame/newGameInterface.h"
#include "types/essentialsStruct.h"
#include "crossLevel/playerData.h"
#include "contexts/onePlayerGame/skillLevelChoice/context.h"
#include "contexts/onePlayerGame/saveAndLoad/gameLoading/gameLoadContext.h"
#include "contexts/onePlayerGame/bestScoresMenu/bestScoresContext.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

void onePlGame::newGame::context(Essentials& essentials)
{
	bool quitNewGameMenu{false};
	onePlGame::newGame::Interface interface{essentials};
	onePlGame::newGame::mainLoop(essentials, interface, quitNewGameMenu);
}

void onePlGame::newGame::mainLoop(Essentials& essentials, onePlGame::newGame::Interface& interface, bool& quitNewGameMenu)
{
	while( false == quitNewGameMenu )
	{
		onePlGame::newGame::update(essentials, interface, quitNewGameMenu);
		onePlGame::newGame::drawEverything(essentials, interface, quitNewGameMenu);
	}
}

void onePlGame::newGame::update(Essentials& essentials, onePlGame::newGame::Interface& interface, bool& quitNewGameMenu)
{
	essentials.inp.updateEvents();
	interface.update(essentials);
	onePlGame::newGame::redirectUser(essentials, interface, quitNewGameMenu);
	onePlGame::newGame::quitContext(essentials, quitNewGameMenu);
}

void onePlGame::newGame::redirectUser(Essentials& essentials, const onePlGame::newGame::Interface& interface, bool& quitNewGameMenu)
{
	onePlGame::newGame::startNewGame(essentials, interface, quitNewGameMenu);
	onePlGame::newGame::loadSavedGame(essentials, interface, quitNewGameMenu);
	onePlGame::newGame::seeDoneScores(essentials, interface, quitNewGameMenu);
	onePlGame::newGame::goBack(essentials, interface, quitNewGameMenu);
}

void onePlGame::newGame::quitContext(Essentials& essentials, bool& quitNewGameMenu)
{
	if( essentials.inp.getSDL_quit() || essentials.inp.getKeyState(input::KeybOut) )
	{
		essentials.inp.setKeyStateToFalse(input::KeybOut);
		quitNewGameMenu = true;
	}
}

void onePlGame::newGame::startNewGame(Essentials& essentials, const onePlGame::newGame::Interface& interface, bool& quitNewGameMenu)
{
	if( interface.newGameButton.buttonClicked() )
	{
		quitNewGameMenu = true;
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		onePlGame::skillChoice::context(essentials);
	}
}

void onePlGame::newGame::loadSavedGame(Essentials& essentials, const onePlGame::newGame::Interface& interface, bool& quitNewGameMenu)
{
	if( interface.loadASavedGame.buttonClicked() )
	{
		quitNewGameMenu = true;
		PlayerData playerData;
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		loadGame::mainContext(essentials, playerData);
	}
}

void onePlGame::newGame::seeDoneScores(Essentials& essentials, const onePlGame::newGame::Interface& interface, bool& quitNewGameMenu)
{
	if( interface.seeDoneScores.buttonClicked() )
	{
		quitNewGameMenu = true;
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		bestScores::context(essentials);
	}
}

void onePlGame::newGame::goBack(Essentials& essentials, const onePlGame::newGame::Interface& interface, bool& quitNewGameMenu)
{
	if( interface.goBackButton.buttonClicked() )
	{
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		quitNewGameMenu = true;
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