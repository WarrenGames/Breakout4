#include "contexts/onePlayerGame/levelComponents/inGameBagThings/bagViewContext.h"
#include "types/essentialsStruct.h"
#include "contexts/onePlayerGame/levelComponents/inputs/userInputs.h"
#include "contexts/onePlayerGame/levelComponents/global/globalGameObject.h"
#include "crossLevel/playerData.h"
#include "contexts/onePlayerGame/levelComponents/inGameBagThings/bagObject.h"
#include "consts/sdlColors.h"

constexpr unsigned BONUS_SWITCHING_DELAY = 325;

void bagView::startBagContext(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, PlayerData& playerData)
{
	if( levelInputs.getFuncState(onePlGame::INP_LOOK_BAG) )
	{
		levelInputs.setFuncState(onePlGame::INP_LOOK_BAG, false);
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
	if( levelInputs.getFuncState(onePlGame::INP_MOVE_RIGHT) && bonusSwitchingDelay.hasTimeElapsed( std::chrono::milliseconds{BONUS_SWITCHING_DELAY} ) )
	{
		playerBag.selectForward();
		levelInputs.setFuncState(onePlGame::INP_MOVE_RIGHT, false);
		bonusSwitchingDelay.joinTimePoints();
	}
}

void bagView::selectPreviousBonus(LevelInputs& levelInputs, PlayerBag& playerBag, AccurateTimeDelay& bonusSwitchingDelay)
{
	if( levelInputs.getFuncState(onePlGame::INP_MOVE_LEFT) && bonusSwitchingDelay.hasTimeElapsed( std::chrono::milliseconds{BONUS_SWITCHING_DELAY} ) )
	{
		playerBag.selectBackward();
		levelInputs.setFuncState(onePlGame::INP_MOVE_LEFT, false);
		bonusSwitchingDelay.joinTimePoints();
	}
}

void bagView::quitContext(LevelInputs& levelInputs, bool& quitBagView)
{
	if( levelInputs.doesUserCloseWindow() || levelInputs.getEscapeState() || levelInputs.getFuncState(onePlGame::INP_LOOK_BAG) )
	{
		quitBagView = true;
		levelInputs.setEscapeToFalse();
		levelInputs.setFuncState(onePlGame::INP_LOOK_BAG, false);
	}
}

void bagView::useBonus(LevelInputs& levelInputs, LevelComponents& levelComponents, PlayerData& playerData, PlayerBag& playerBag)
{
	if( levelInputs.getFuncState(onePlGame::INP_BALL_TRACE) )
	{
		levelComponents.activateBagBonus(playerBag.selectedBonus, playerData);
		levelInputs.setFuncState(onePlGame::INP_LOOK_BAG, false);
		levelInputs.setFuncState(onePlGame::INP_BALL_TRACE, false);
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
	essentials.rndWnd.drawRect(YELLOW_COL, playerBag.selectionRect);
}