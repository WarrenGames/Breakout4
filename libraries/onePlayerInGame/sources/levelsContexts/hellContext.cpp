#include "levelsContexts/hellContext.h"
#include "types/essentialsStruct.h"
#include "levelComponents/inputs/userInputs.h"
#include "levelComponents/global/globalGameObject.h"
#include "levelComponents/hellEpisodeThings/hellPackage.h"
#include "crossLevel/playerData.h"
#include "levelEnd/levelEndContext.h"
#include "gamePaused/gameInPause.h"
#include "levelsContexts/stdLevelContext.h"
#include "levelComponents/inGameBagThings/bagViewContext.h"
#include "demosLoadingAndSaving/moveStacks/moveDemosStacks.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

void hellLevel::start(Essentials& essentials, PlayerData& playerData, bool& quitMainMenu)
{
	if( onePlGame::HellPackage hellPackage{essentials, playerData} )
	{
		if( LevelComponents levelComponents{essentials, playerData, 0 } )
		{
			LevelInputs levelInputs{essentials, playerData};
			hellLevel::playGame(essentials, levelInputs, levelComponents, playerData, hellPackage, quitMainMenu);
			levelEnd::startLevelSum(essentials, levelComponents, playerData, quitMainMenu);
		}
		else{
			stdlevel::logLevelComponentsError(essentials);
		}
	}
	else{
		essentials.logs.error << "There was an error with 'hell package' data loading ! \n";
	}
}

void hellLevel::startWithDemoRecording(Essentials& essentials, PlayerData& playerData, demos::MainPackage& demosMainPackage, bool& quitMainMenu)
{
	if( onePlGame::HellPackage hellPackage{essentials, playerData} )
	{
		if( LevelComponents levelComponents{essentials, playerData, 0 } )
		{
			LevelInputs levelInputs{essentials, playerData};
			hellLevel::playGame(essentials, levelInputs, levelComponents, playerData, hellPackage, quitMainMenu);
			levelEnd::startLevelSum(essentials, levelComponents, playerData, quitMainMenu);
			demos::giveStacksContentsToMainPackage(levelComponents, levelInputs, demosMainPackage);
		}
		else{
			stdlevel::logLevelComponentsError(essentials);
		}
	}
	else{
		essentials.logs.error << "There was an error with 'hell package' data loading ! \n";
	}
}

void hellLevel::startWithDemoRunning(Essentials& essentials, PlayerData& playerData, demos::MainPackage& demosMainPackage, bool& quitMainMenu)
{
	if( onePlGame::HellPackage hellPackage{essentials, playerData} )
	{
		if( LevelComponents levelComponents{essentials, playerData, 0 } )
		{
			LevelInputs levelInputs{essentials, playerData};
			demos::giveStacksToLevelComponents(levelComponents, levelInputs, demosMainPackage);
			hellLevel::playGame(essentials, levelInputs, levelComponents, playerData, hellPackage, quitMainMenu);
			levelEnd::startLevelSum(essentials, levelComponents, playerData, quitMainMenu);
		}
		else{
			stdlevel::logLevelComponentsError(essentials);
		}
	}
	else{
		essentials.logs.error << "There was an error with 'hell package' data loading ! \n";
	}
}

void hellLevel::playGame(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, PlayerData& playerData, onePlGame::HellPackage& hellPackage, bool& quitMainMenu)
{
	levelComponents.joinDemosTimePoint();
	levelInputs.joinDemosTimePoints();
	bool quitGame{ false };
	while( false == quitGame )
	{
		levelInputs.updateEvents();
		stdlevel::closeGameWindow(levelInputs, quitGame);
		levelComponents.hellUpdate(essentials, levelInputs, playerData, quitGame, hellPackage);
		pausedGame::pauseTheHellGame(essentials, levelInputs, levelComponents, playerData, hellPackage, quitMainMenu, quitGame);
		bagView::startBagContext(essentials, levelInputs, levelComponents, playerData);
		hellLevel::drawGame(essentials, levelComponents, hellPackage);
	}
}

void hellLevel::drawGame(Essentials& essentials, LevelComponents& levelComponents, onePlGame::HellPackage& hellPackage)
{
	if( essentials.drawFreq.canDrawGame() )
	{
		essentials.rndWnd.clearScreen(BlackColor);
		levelComponents.drawEverything(essentials);
		hellPackage.drawEverything(essentials, levelComponents.explosionsSprites);
		essentials.rndWnd.displayRenderer();
	}
}