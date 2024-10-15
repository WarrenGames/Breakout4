#include "levelsContexts/antarcticContext.h"
#include "types/essentialsStruct.h"
#include "levelComponents/inputs/userInputs.h"
#include "levelComponents/global/globalGameObject.h"
#include "levelComponents/antarcticEpisodeThings/antarcticPackage.h"
#include "crossLevel/playerData.h"
#include "levelEnd/levelEndContext.h"
#include "gamePaused/gameInPause.h"
#include "levelsContexts/stdLevelContext.h"
#include "levelComponents/inGameBagThings/bagViewContext.h"
#include "demosLoadingAndSaving/moveStacks/moveDemosStacks.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

void antarcticLevel::start(Essentials& essentials, PlayerData& playerData, bool& quitMainMenu)
{
	if( AntarcticPackage antarcticPackage{essentials, playerData} )
	{
		if( LevelComponents levelComponents{essentials, playerData, antarcticPackage.pinguinsData.size() } )
		{
			LevelInputs levelInputs{essentials, playerData};
			antarcticLevel::playGame(essentials, levelInputs, levelComponents, playerData, antarcticPackage, quitMainMenu);
			levelEnd::startLevelSum(essentials, levelComponents, playerData, quitMainMenu);
		}
		else{
			stdlevel::logLevelComponentsError(essentials);
		}
	}
	else{
		essentials.logs.error << "There was an error with 'antarctic data' loading ! \n";
	}
}

void antarcticLevel::startWithDemoRecording(Essentials& essentials, PlayerData& playerData, demos::MainPackage& demosMainPackage, bool& quitMainMenu)
{
	if( AntarcticPackage antarcticPackage{essentials, playerData} )
	{
		if( LevelComponents levelComponents{essentials, playerData, antarcticPackage.pinguinsData.size() } )
		{
			demos::setStartingBricksMatrixForSavingLatter(levelComponents, demosMainPackage);
			LevelInputs levelInputs{essentials, playerData};
			antarcticLevel::playGame(essentials, levelInputs, levelComponents, playerData, antarcticPackage, quitMainMenu);
			levelEnd::startLevelSum(essentials, levelComponents, playerData, quitMainMenu);
			demos::giveStacksContentsToMainPackage(levelComponents, levelInputs, demosMainPackage);
			demos::giveStacksContentsToMainPackage(antarcticPackage.antarcticDemoPackage, demosMainPackage);
		}
		else{
			stdlevel::logLevelComponentsError(essentials);
		}
	}
	else{
		essentials.logs.error << "There was an error with 'antarctic data' loading ! \n";
	}
}

void antarcticLevel::startWithDemoRunning(Essentials& essentials, PlayerData& playerData, demos::MainPackage& demosMainPackage, bool& quitMainMenu)
{
	if( AntarcticPackage antarcticPackage{essentials, playerData} )
	{
		if( LevelComponents levelComponents{essentials, playerData, antarcticPackage.pinguinsData.size() } )
		{
			LevelInputs levelInputs{essentials, playerData};
			demos::giveStacksToLevelComponents(levelComponents, levelInputs, demosMainPackage);
			demos::giveStacksToLevelComponents(antarcticPackage.antarcticDemoPackage, demosMainPackage);
			antarcticLevel::playGame(essentials, levelInputs, levelComponents, playerData, antarcticPackage, quitMainMenu);
			levelEnd::startLevelSum(essentials, levelComponents, playerData, quitMainMenu);
		}
		else{
			stdlevel::logLevelComponentsError(essentials);
		}
	}
	else{
		essentials.logs.error << "There was an error with 'antarctic data' loading ! \n";
	}
}

void antarcticLevel::playGame(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, PlayerData& playerData, AntarcticPackage& antarcticPackage, bool& quitMainMenu)
{
	levelComponents.joinDemosTimePoint();
	levelInputs.joinDemosTimePoints();
	antarcticPackage.antarcticDemoPackage.joinDemosTimePoints();
	bool quitGame{ false };
	while( false == quitGame )
	{
		levelInputs.updateEvents();
		stdlevel::closeGameWindow(levelInputs, quitGame);
		levelComponents.antarcticUpdate(essentials, levelInputs, playerData, quitGame, antarcticPackage);
		pausedGame::pauseTheAntarcticGame(essentials, levelInputs, levelComponents, playerData, antarcticPackage, quitMainMenu, quitGame);
		bagView::startBagContext(essentials, levelInputs, levelComponents, playerData);
		antarcticLevel::drawGame(essentials, levelComponents, antarcticPackage);
	}
}

void antarcticLevel::drawGame(Essentials& essentials, LevelComponents& levelComponents, AntarcticPackage& antarcticPackage)
{
	if( essentials.drawFreq.canDrawGame() )
	{
		essentials.rndWnd.clearScreen(BlackColor);
		levelComponents.drawEverything(essentials);
		antarcticPackage.drawPinguins(essentials);
		antarcticPackage.drawStalactites(essentials);
		essentials.rndWnd.displayRenderer();
	}
}