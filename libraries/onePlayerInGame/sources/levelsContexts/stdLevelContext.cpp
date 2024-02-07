#include "levelsContexts/stdLevelContext.h"
#include "types/essentialsStruct.h"
#include "levelComponents/inputs/userInputs.h"
#include "levelComponents/global/globalGameObject.h"
#include "crossLevel/playerData.h"
#include "levelEnd/levelEndContext.h"
#include "gamePaused/gameInPause.h"
#include "levelComponents/inGameBagThings/bagViewContext.h"
#include "demosLoadingAndSaving/moveStacks/moveDemosStacks.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

void stdlevel::start(Essentials& essentials, PlayerData& playerData, bool& quitMainMenu)
{
	if( LevelComponents levelComponents{essentials, playerData, 0} )
	{
		LevelInputs levelInputs{essentials, playerData};
		stdlevel::playGame(essentials, levelInputs, levelComponents, playerData, quitMainMenu);
		levelEnd::startLevelSum(essentials, levelComponents, playerData, quitMainMenu);
	}
	else{
		stdlevel::logLevelComponentsError(essentials);
	}
}

void stdlevel::startWithDemoRecording(Essentials& essentials, PlayerData& playerData, demos::MainPackage& demosMainPackage, bool& quitMainMenu)
{
	if( LevelComponents levelComponents{essentials, playerData, 0} )
	{
		LevelInputs levelInputs{essentials, playerData};
		stdlevel::playGame(essentials, levelInputs, levelComponents, playerData, quitMainMenu);
		levelEnd::startLevelSum(essentials, levelComponents, playerData, quitMainMenu);
		demos::giveStacksContentsToMainPackage(levelComponents, levelInputs, demosMainPackage);
	}
	else{
		stdlevel::logLevelComponentsError(essentials);
	}
}

void stdlevel::startWithDemoRunning(Essentials& essentials, PlayerData& playerData, demos::MainPackage& demosMainPackage, bool& quitMainMenu)
{
	if( LevelComponents levelComponents{essentials, playerData, 0} )
	{
		LevelInputs levelInputs{essentials, playerData};
		demos::giveStacksToLevelComponents(levelComponents, levelInputs, demosMainPackage);
		stdlevel::playGame(essentials, levelInputs, levelComponents, playerData, quitMainMenu);
		levelEnd::startLevelSum(essentials, levelComponents, playerData, quitMainMenu);
	}
	else{
		stdlevel::logLevelComponentsError(essentials);
	}
}

void stdlevel::playGame(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, PlayerData& playerData, bool& quitMainMenu)
{
	levelComponents.joinDemosTimePoint();
	levelInputs.joinDemosTimePoints();
	bool quitGame{ false };
	while( false == quitGame )
	{
		levelInputs.updateEvents();
		stdlevel::closeGameWindow(levelInputs, quitGame);
		levelComponents.standardLevelUpdate(essentials, levelInputs, playerData, quitGame);
		pausedGame::pauseTheGame(essentials, levelInputs, levelComponents, playerData, quitMainMenu, quitGame);
		bagView::startBagContext(essentials, levelInputs, levelComponents, playerData);
		stdlevel::drawGame(essentials, levelComponents);
	}
}

void stdlevel::drawGame(Essentials& essentials, LevelComponents& levelComponents)
{
	if( essentials.drawFreq.canDrawGame() )
	{
		essentials.rndWnd.clearScreen(BlackColor);
		levelComponents.drawEverything(essentials);
		essentials.rndWnd.displayRenderer();
	}
}

void stdlevel::closeGameWindow(const LevelInputs& levelInputs, bool& quitMainMenu)
{
	if( levelInputs.doesUserCloseWindow() )
	{
		quitMainMenu = true;
	}
}

void stdlevel::logLevelComponentsError(Essentials& essentials)
{
	essentials.logs.error << "There was an error while loading 'level components' ! \n";
}
