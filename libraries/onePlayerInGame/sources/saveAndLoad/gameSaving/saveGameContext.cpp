#include "saveAndLoad/gameSaving/saveGameContext.h"
#include "types/essentialsStruct.h"
#include "crossLevel/playerData.h"
#include "saveAndLoad/common/slotsUserInterface.h"
#include "gameSlots/slotConsts.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

void saveGame::mainContext(Essentials& essentials, const PlayerData& playerData)
{
	bool quitSaveGameMenu{false};
	SlotsUserInterface slotsGui{essentials, SaveNameFocusingOnSaving};
	saveGame::mainLoop(essentials, playerData, slotsGui, quitSaveGameMenu);
}

void saveGame::mainLoop(Essentials& essentials, const PlayerData& playerData, SlotsUserInterface& slotsGui, bool& quitSaveGameMenu)
{
	while( false == quitSaveGameMenu )
	{
		essentials.inp.updateEvents();
		slotsGui.update(essentials);
		saveGame::quitContext(essentials, slotsGui, quitSaveGameMenu);
		saveGame::saveASlot(essentials, playerData, slotsGui);
		saveGame::drawEverything(essentials, slotsGui);
	}
}

void saveGame::saveASlot(Essentials& essentials, const PlayerData& playerData, SlotsUserInterface& slotsGui)
{
	slotsGui.saveToFile(essentials, playerData);
}

void saveGame::drawEverything(Essentials& essentials, const SlotsUserInterface& slotsGui)
{
	essentials.rndWnd.clearScreen(BlackColor);
	slotsGui.drawInterface(essentials);
	essentials.rndWnd.displayRenderer();
	SDL_Delay(SdlDelayTime);
}

void saveGame::quitContext(Essentials& essentials, const SlotsUserInterface& slotsGui, bool& quitSaveMenu)
{
	if( slotsGui.isQuitButtonClicked() || essentials.inp.getKeyState(input::KeybOut) || essentials.inp.getSDL_quit() )
	{
		quitSaveMenu = true;
		essentials.inp.setKeyStateToFalse(input::KeybOut);
	}
}