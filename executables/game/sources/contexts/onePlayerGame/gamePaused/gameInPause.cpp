#include "contexts/onePlayerGame/gamePaused/gameInPause.h"
#include "contexts/onePlayerGame/gamePaused/gamePausedGUI.h"
#include "contexts/onePlayerGame/levelComponents/global/globalGameObject.h"
#include "contexts/onePlayerGame/levelComponents/inputs/userInputs.h"
#include "contexts/onePlayerGame/levelComponents/antarcticEpisodeThings/antarcticPackage.h"
#include "contexts/onePlayerGame/levelComponents/hellEpisodeThings/hellPackage.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

void pausedGame::pauseTheGame(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, bool& quitMainMenu, bool& quitGame)
{
	if( levelInputs.getEscapeState() )
	{
		levelInputs.setEscapeToFalse();
		PausedGameGUI pausedGameGUI{essentials};
		bool quitPause{false};
		while( false == quitPause )
		{
			essentials.inp.updateEvents();
			pausedGameGUI.updateQuitButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT));
			pausedGame::drawPauseGUI(essentials, levelComponents);
			pausedGameGUI.drawEverything(essentials);
			essentials.rndWnd.displayRenderer();
			pausedGame::quitGame(pausedGameGUI, quitMainMenu, quitGame, quitPause);
			pausedGame::goBackToTheGame(essentials, quitPause);
			SDL_Delay(SdlDelayTime);
		}
	}
}

void pausedGame::pauseTheAntarcticGame(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, AntarcticPackage& antarcticPackage, bool& quitMainMenu, bool& quitGame)
{
	if( levelInputs.getEscapeState() )
	{
		levelInputs.setEscapeToFalse();
		PausedGameGUI pausedGameGUI{essentials};
		bool quitPause{false};
		while( false == quitPause )
		{
			essentials.inp.updateEvents();
			pausedGameGUI.updateQuitButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT));
			pausedGame::drawPauseGUI(essentials, levelComponents);
			antarcticPackage.drawPinguins(essentials);
			antarcticPackage.drawStalactites(essentials);
			pausedGameGUI.drawEverything(essentials);
			essentials.rndWnd.displayRenderer();
			pausedGame::quitGame(pausedGameGUI, quitMainMenu, quitGame, quitPause);
			pausedGame::goBackToTheGame(essentials, quitPause);
			SDL_Delay(SdlDelayTime);
		}
	}
}

void pausedGame::pauseTheHellGame(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, onePlGame::HellPackage& hellPackage, bool& quitMainMenu, bool& quitGame)
{
	if( levelInputs.getEscapeState() )
	{
		levelInputs.setEscapeToFalse();
		PausedGameGUI pausedGameGUI{essentials};
		bool quitPause{false};
		while( false == quitPause )
		{
			essentials.inp.updateEvents();
			pausedGameGUI.updateQuitButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT));
			pausedGame::drawPauseGUI(essentials, levelComponents);
			hellPackage.drawEverything(essentials, levelComponents.explosionsSprites);
			pausedGameGUI.drawEverything(essentials);
			essentials.rndWnd.displayRenderer();
			pausedGame::quitGame(pausedGameGUI, quitMainMenu, quitGame, quitPause);
			pausedGame::goBackToTheGame(essentials, quitPause);
			SDL_Delay(SdlDelayTime);
		}
	}
}

void pausedGame::quitGame(const PausedGameGUI& pausedGameGUI, bool& quitMainMenu, bool& quitGame, bool& quiPause)
{
	if( pausedGameGUI.isQuitButtonClicked() )
	{
		quitMainMenu = true;
		quitGame = true;
		quiPause = true;
	}
}

void pausedGame::drawPauseGUI(Essentials& essentials, LevelComponents& levelComponents)
{
	essentials.rndWnd.clearScreen(BlackColor);
	levelComponents.drawEverything(essentials);
}

void pausedGame::goBackToTheGame(Essentials& essentials, bool& quitPause)
{
	if( essentials.inp.getKeyState(input::KeybOut) )
	{
		essentials.inp.setKeyStateToFalse(input::KeybOut);
		quitPause = true;
	}
}