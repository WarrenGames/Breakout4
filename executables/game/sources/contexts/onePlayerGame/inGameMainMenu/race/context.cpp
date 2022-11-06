#include "contexts/onePlayerGame/inGameMainMenu/race/context.h"
#include "contexts/onePlayerGame/inGameMainMenu/race/graphicalInterface.h"
#include "contexts/onePlayerGame/inputConfig/context.h"
#include "crossLevel/playerData.h"
#include "contexts/onePlayerGame/levelsContexts/stdLevelContext.h"
#include "contexts/onePlayerGame/levelsContexts/antarcticContext.h"
#include "contexts/onePlayerGame/levelsContexts/hellContext.h"
#include "contexts/onePlayerGame/bonusesShop/shopContext.h"
#include "contexts/onePlayerGame/seeNextLevel/context.h"
#include "contexts/onePlayerGame/campaignEnd/campaignEndContext.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "contexts/onePlayerGame/saveAndLoad/gameSaving/saveGameContext.h"
#include "contexts/onePlayerGame/bestScoresMenu/bestScoresContext.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/constPaths.h"
#include <cassert>

void onePlGame::raceMainMenu::context(Essentials& essentials, unsigned skillLevel, unsigned raceType)
{
	onePlGame::raceMainMenu::Interface interface{essentials, raceType};
	PlayerData playerData{essentials.logs, raceType, skillLevel, path::getRaceLevelList(raceType) };
	bool quitMainMenu{false};
	onePlGame::raceMainMenu::mainLoop(essentials, interface, playerData, quitMainMenu);
	bestScores::fromGameEndContext(essentials, playerData.score, skillLevel, raceType);
}

void onePlGame::raceMainMenu::fromGameSaveContext(Essentials& essentials, PlayerData& playerData)
{
	onePlGame::raceMainMenu::Interface interface{essentials, playerData.gameType};
	bool quitMainMenu{false};
	onePlGame::raceMainMenu::mainLoop(essentials, interface, playerData, quitMainMenu);
	bestScores::fromGameEndContext(essentials, playerData.score, playerData.skillLevel, playerData.gameType);
}

void onePlGame::raceMainMenu::mainLoop(Essentials& essentials, onePlGame::raceMainMenu::Interface& interface, PlayerData& playerData, bool quitMainMenu)
{
	while( false == quitMainMenu )
	{
		essentials.inp.updateEvents();
		interface.updateButtons(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT));
		interface.updateShopButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT));
		onePlGame::raceMainMenu::redirectUser(essentials, playerData, interface, quitMainMenu);
		onePlGame::raceMainMenu::drawEverything(essentials, interface, quitMainMenu);
	}
}

void onePlGame::raceMainMenu::drawEverything(Essentials& essentials, const onePlGame::raceMainMenu::Interface& interface, bool quitMainMenu)
{
	if( false == quitMainMenu )
	{
		essentials.rndWnd.clearScreen(BlackColor);
		interface.drawEverything(essentials);
		interface.drawShopButton(essentials);
		essentials.rndWnd.displayRenderer();
		SDL_Delay(SdlDelayTime);
	}
}

void onePlGame::raceMainMenu::redirectUser(Essentials& essentials, PlayerData& playerData, const onePlGame::raceMainMenu::Interface& interface, bool& quitMainMenu)
{
	onePlGame::raceMainMenu::quitContext(essentials, interface, quitMainMenu);
	onePlGame::raceMainMenu::goToInputConfig(essentials, interface);
	onePlGame::raceMainMenu::goToSaveGameContext(essentials, playerData, interface);
	onePlGame::raceMainMenu::goToShop(essentials, playerData, interface);
	onePlGame::raceMainMenu::runNextLevel(essentials, playerData, interface, quitMainMenu);
	onePlGame::raceMainMenu::seeNextLevel(essentials, playerData, interface);
	onePlGame::raceMainMenu::displayCampaignEnd(essentials, playerData, quitMainMenu);
}

void onePlGame::raceMainMenu::goToInputConfig(Essentials& essentials, const onePlGame::raceMainMenu::Interface& interface)
{
	if( interface.buttons[onePlGame::raceMainMenu::ButtonChangeInput].buttonClicked() )
	{
		onePlInputCfg::mainContext(essentials);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void onePlGame::raceMainMenu::quitContext(Essentials& essentials, const onePlGame::raceMainMenu::Interface& interface, bool& quitMainMenu)
{
	if( essentials.inp.getKeyState(input::KeybOut) || essentials.inp.getSDL_quit() || interface.buttons[onePlGame::raceMainMenu::ButtonQuit].buttonClicked() )
	{
		essentials.inp.setKeyStateToFalse(input::KeybOut);
		quitMainMenu = true;
	}
}

void onePlGame::raceMainMenu::runNextLevel(Essentials& essentials, PlayerData& playerData, const onePlGame::raceMainMenu::Interface& interface, bool& quitMainMenu)
{
	if( interface.buttons[onePlGame::raceMainMenu::ButtonRunLevel].buttonClicked() )
	{
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		onePlGame::raceMainMenu::selectLevelToRun(essentials, playerData, quitMainMenu);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void onePlGame::raceMainMenu::selectLevelToRun(Essentials& essentials, PlayerData& playerData, bool& quitMainMenu)
{
	if( playerData.levelCursor < playerData.levelsListing.size() )
	{
		assert( playerData.levelCursor < playerData.levelsListing.size() );
		onePlGame::raceMainMenu::runSpecificLevel(essentials, playerData, quitMainMenu);
	}
}

void onePlGame::raceMainMenu::runSpecificLevel(Essentials& essentials, PlayerData& playerData, bool& quitMainMenu)
{
	switch( playerData.getLevelType() )
	{
		case onePlGame::EpisodeSimple:
			stdlevel::start(essentials, playerData, quitMainMenu);
			break;
		case onePlGame::EpisodeArtic:
			antarcticLevel::start(essentials, playerData, quitMainMenu);
			break;
		case onePlGame::EpisodeHell:
			hellLevel::start(essentials, playerData, quitMainMenu);
			break;
	}
}

void onePlGame::raceMainMenu::goToShop(Essentials& essentials, PlayerData& playerData, const onePlGame::raceMainMenu::Interface& interface)
{
	if( interface.shopButton.buttonClicked() && onePlGame::CampaignWithShop == playerData.gameType )
	{
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		onePlayerShop::context(essentials, playerData);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void onePlGame::raceMainMenu::seeNextLevel(Essentials& essentials, PlayerData& playerData, const onePlGame::raceMainMenu::Interface& interface)
{
	if( interface.buttons[onePlGame::raceMainMenu::ButtonSeeNextLevel].buttonClicked() )
	{
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		seeLevel::context(essentials, playerData);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void onePlGame::raceMainMenu::goToSaveGameContext(Essentials& essentials, PlayerData& playerData, const onePlGame::raceMainMenu::Interface& interface)
{
	if( interface.buttons[onePlGame::raceMainMenu::ButtonSaveGame].buttonClicked() )
	{
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		saveGame::mainContext(essentials, playerData);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void onePlGame::raceMainMenu::displayCampaignEnd(Essentials& essentials, const PlayerData& playerData, bool& quitMainMenu)
{
	if( playerData.levelCursor == playerData.levelsListing.size() )
	{
		quitMainMenu = true;
		onePlGame::campaignEnd::context(essentials, playerData);
	}
}