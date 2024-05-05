#include "gamePaused/gameInPause.h"
#include "gamePaused/gamePausedGUI.h"
#include "levelComponents/global/globalGameObject.h"
#include "levelComponents/inputs/userInputs.h"
#include "crossLevel/playerData.h"
#include "levelComponents/antarcticEpisodeThings/antarcticPackage.h"
#include "levelComponents/hellEpisodeThings/hellPackage.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "demos/consts/demosConsts.h"

void pausedGame::pauseTheGame(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, const PlayerData& playerData, bool& quitMainMenu, bool& quitGame)
{
	if( pausedGame::isNotInRecordOrPlayDemoMode(playerData) )
	{
		if( levelInputs.getLastKeycode() == SDLK_ESCAPE )
		{
			pausedGame::doPauseThings(levelComponents, levelInputs);
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
			pausedGame::endPause(levelComponents);
		}
	}
}

void pausedGame::pauseTheAntarcticGame(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, const PlayerData& playerData, AntarcticPackage& antarcticPackage, bool& quitMainMenu, bool& quitGame)
{
	if( pausedGame::isNotInRecordOrPlayDemoMode(playerData) )
	{
		if( levelInputs.getLastKeycode() == SDLK_ESCAPE )
		{
			pausedGame::doPauseThings(levelComponents, levelInputs);
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
			pausedGame::endPause(levelComponents);
		}
	}
}

void pausedGame::pauseTheHellGame(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, const PlayerData& playerData, onePlGame::HellPackage& hellPackage, bool& quitMainMenu, bool& quitGame)
{
	if( pausedGame::isNotInRecordOrPlayDemoMode(playerData) )
	{
		if( levelInputs.getLastKeycode() == SDLK_ESCAPE )
		{
			pausedGame::doPauseThings(levelComponents, levelInputs);
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
			pausedGame::endPause(levelComponents);
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

void pausedGame::doPauseThings(LevelComponents& levelComponents, LevelInputs& levelInputs)
{
	levelComponents.playedTimeCounter.pauseTheGame();
	levelInputs.setEscapeToFalse();
	levelInputs.cancelLastKeycode();
}

void pausedGame::endPause(LevelComponents& levelComponents)
{
	if( levelComponents.ball.isMainBallActive )
	{
		levelComponents.playedTimeCounter.carryOnTheGame();
	}
}

bool pausedGame::isNotInRecordOrPlayDemoMode(const PlayerData& playerData)
{
	return playerData.demoKind == demos::GameHasPlayerInputs;
}