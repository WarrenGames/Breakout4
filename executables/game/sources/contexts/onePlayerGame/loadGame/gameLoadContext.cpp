#include "contexts/onePlayerGame/loadGame/gameLoadContext.h"
#include "types/essentialsStruct.h"
#include "crossLevel/playerData.h"
#include "saveAndLoad/common/slotsUserInterface.h"
#include "contexts/onePlayerGame/inGameMainMenu/race/raceMainMenuContext.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "gameSlots/slotConsts.h"

void loadGame::mainContext(Essentials& essentials, PlayerData& playerData)
{
	bool quitLoadGameMenu{false};
	SlotsUserInterface slotsGui{essentials, SaveNameFocusingOnLoading};
	const TextureCombo screenBackground{ essentials.logs, essentials.rndWnd, "textures/wallpapers/campaignChoice.png" };
	loadGame::mainLoop(essentials, playerData, slotsGui, screenBackground, quitLoadGameMenu);
}

void loadGame::mainLoop(Essentials& essentials, PlayerData& playerData, SlotsUserInterface& slotsGui, const TextureCombo& screenBackground, bool& quitLoadGameMenu)
{
	while( false == quitLoadGameMenu )
	{
		essentials.inp.updateEvents();
		slotsGui.update(essentials);
		loadGame::quitContext(essentials, slotsGui, quitLoadGameMenu);
		loadGame::loadASlot(essentials, playerData, slotsGui, quitLoadGameMenu);
		loadGame::drawEverything(essentials, slotsGui, screenBackground, quitLoadGameMenu);
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

void loadGame::drawEverything(Essentials& essentials, const SlotsUserInterface& slotsGui, const TextureCombo& screenBackground, bool& quitLoadGameMenu)
{
	if( false == quitLoadGameMenu )
	{
		screenBackground.draw(essentials.rndWnd);
		slotsGui.drawInterface(essentials);
		essentials.rndWnd.displayRenderer();
		SDL_Delay(SdlDelayTime);
	}
}

void loadGame::quitContext(Essentials& essentials, const SlotsUserInterface& slotsGui, bool& quitSaveMenu)
{
	if( slotsGui.isQuitButtonClicked() || essentials.inp.getKeyState(input::KeybOut) || essentials.inp.getSDL_quit() )
	{
		quitSaveMenu = true;
		essentials.inp.setKeyStateToFalse(input::KeybOut);
	}
}