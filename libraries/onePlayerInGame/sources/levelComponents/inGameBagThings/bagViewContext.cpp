#include "levelComponents/inGameBagThings/bagViewContext.h"
#include "types/essentialsStruct.h"
#include "levelComponents/inputs/userInputs.h"
#include "levelComponents/global/globalGameObject.h"
#include "crossLevel/playerData.h"
#include "levelComponents/inGameBagThings/bagObject.h"
#include "consts/sdlColors.h"

constexpr unsigned BonusSwitchingDelay = 325;

void bagView::startBagContext(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, PlayerData& playerData)
{
	if( levelInputs.getFuncState(onePlGame::InputLookBag) )
	{
		levelInputs.voidSpecialAction(onePlGame::InputLookBag);
		bagView::mainContext(essentials, levelInputs, levelComponents, playerData);
	}
}

void bagView::mainContext(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, PlayerData& playerData)
{
	AccurateTimeDelay bonusSwitchingDelay;
	PlayerBag playerBag{essentials, playerData};
	
	while( false == playerBag.quitBagView )
	{
		bagView::listenToPlayerInputs(levelInputs, levelComponents, playerData, playerBag, bonusSwitchingDelay);
		bagView::drawEverything(essentials, levelComponents, playerBag);
	}
}

void bagView::listenToPlayerInputs(LevelInputs& levelInputs, LevelComponents& levelComponents, PlayerData& playerData, PlayerBag& playerBag, AccurateTimeDelay& bonusSwitchingDelay)
{
	levelInputs.updateEvents();
	bagView::selectNextBonus(levelInputs, playerBag, bonusSwitchingDelay);
	bagView::selectPreviousBonus(levelInputs, playerBag, bonusSwitchingDelay);
	bagView::quitContext(levelInputs, playerBag.quitBagView);
	bagView::useBonus(levelInputs, levelComponents, playerData, playerBag);
}

void bagView::selectNextBonus(LevelInputs& levelInputs, PlayerBag& playerBag, AccurateTimeDelay& bonusSwitchingDelay)
{
	if( levelInputs.getFuncState(onePlGame::InputMoveRight) && bonusSwitchingDelay.hasTimeElapsed( std::chrono::milliseconds{BonusSwitchingDelay} ) )
	{
		playerBag.selectForward();
		levelInputs.voidSpecialAction(onePlGame::InputMoveRight);
		bonusSwitchingDelay.joinTimePoints();
	}
}

void bagView::selectPreviousBonus(LevelInputs& levelInputs, PlayerBag& playerBag, AccurateTimeDelay& bonusSwitchingDelay)
{
	if( levelInputs.getFuncState(onePlGame::InputMoveLeft) && bonusSwitchingDelay.hasTimeElapsed( std::chrono::milliseconds{BonusSwitchingDelay} ) )
	{
		playerBag.selectBackward();
		levelInputs.voidSpecialAction(onePlGame::InputMoveLeft);
		bonusSwitchingDelay.joinTimePoints();
	}
}

void bagView::quitContext(LevelInputs& levelInputs, bool& quitBagView)
{
	if( levelInputs.doesUserCloseWindow() || levelInputs.getLastKeycode() == SDLK_ESCAPE || levelInputs.getFuncState(onePlGame::InputLookBag) )
	{
		quitBagView = true;
		levelInputs.setEscapeToFalse();
		levelInputs.voidSpecialAction(onePlGame::InputLookBag);
	}
}

void bagView::useBonus(LevelInputs& levelInputs, LevelComponents& levelComponents, PlayerData& playerData, PlayerBag& playerBag)
{
	if( levelInputs.getFuncState(onePlGame::InputBallTrace) )
	{
		levelComponents.activateBagBonus(playerBag.selectedBonus, playerData);
		levelInputs.voidSpecialAction(onePlGame::InputLookBag);
		levelInputs.voidSpecialAction(onePlGame::InputBallTrace);
		playerBag.quitBagView = true;
	}
}

void bagView::drawEverything(Essentials& essentials, LevelComponents& levelComponents, const PlayerBag& playerBag)
{
	if( essentials.drawFreq.canDrawGame() )
	{
		levelComponents.drawEverything(essentials);
		playerBag.drawEverything(essentials);
		bagView::drawSelectionRect(essentials, playerBag);
		essentials.rndWnd.displayRenderer();
	}
}

void bagView::drawSelectionRect(Essentials& essentials, const PlayerBag& playerBag)
{
	essentials.rndWnd.drawRect(YellowColor, playerBag.selectionRect);
}