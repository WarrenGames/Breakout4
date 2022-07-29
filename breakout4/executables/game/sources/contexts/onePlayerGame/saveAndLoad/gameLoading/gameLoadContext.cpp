#include "contexts/onePlayerGame/saveAndLoad/gameLoading/gameLoadContext.h"
#include "types/essentialsStruct.h"
#include "crossLevel/playerData.h"
#include "contexts/onePlayerGame/saveAndLoad/common/slotsUserInterface.h"
#include "contexts/onePlayerGame/inGameMainMenu/race/context.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "gameSlots/slotConsts.h"

void loadGame::mainContext(Essentials& essentials, PlayerData& playerData)
{
	bool quitLoadGameMenu{false};
	SlotsUserInterface slotsGui{essentials, SAVE_NAME_FOCUSING_ON_LOADING};
	loadGame::mainLoop(essentials, playerData, slotsGui, quitLoadGameMenu);
}

void loadGame::mainLoop(Essentials& essentials, PlayerData& playerData, SlotsUserInterface& slotsGui, bool& quitLoadGameMenu)
{
	while( false == quitLoadGameMenu )
	{
		essentials.inp.updateEvents();
		slotsGui.update(essentials);
		loadGame::quitContext(essentials, slotsGui, quitLoadGameMenu);
		loadGame::loadASlot(essentials, playerData, slotsGui, quitLoadGameMenu);
		loadGame::drawEverything(essentials, slotsGui, quitLoadGameMenu);
	}
}

void loadGame::loadASlot(Essentials& essentials, PlayerData& playerData, const SlotsUserInterface& slotsGui, bool& quitLoadGameMenu)
{
	if( slotsGui.canLoadSlot(essentials, playerData) )
	{
		quitLoadGameMenu = true;
		playerData.laterInitialization(essentials.logs);
		onePlGame::raceMainMenu::fromGameSaveContext(essentials, playerData);
	}
}

void loadGame::drawEverything(Essentials& essentials, const SlotsUserInterface& slotsGui, bool& quitLoadGameMenu)
{
	if( false == quitLoadGameMenu )
	{
		essentials.rndWnd.clearScreen(BLACK_COL);
		slotsGui.drawInterface(essentials);
		essentials.rndWnd.displayRenderer();
		SDL_Delay(SDL_DELAY_TIME);
	}
}

void loadGame::quitContext(Essentials& essentials, const SlotsUserInterface& slotsGui, bool& quitSaveMenu)
{
	if( slotsGui.isQuitButtonClicked() || essentials.inp.getKeyState(input::KEYB_OUT) || essentials.inp.getSDL_quit() )
	{
		quitSaveMenu = true;
		essentials.inp.setKeyStateToFalse(input::KEYB_OUT);
	}
}