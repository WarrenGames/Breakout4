#include "contexts/onePlayerGame/levelsContexts/hellContext.h"
#include "types/essentialsStruct.h"
#include "contexts/onePlayerGame/levelComponents/inputs/userInputs.h"
#include "contexts/onePlayerGame/levelComponents/global/globalGameObject.h"
#include "contexts/onePlayerGame/levelComponents/hellEpisodeThings/hellPackage.h"
#include "crossLevel/playerData.h"
#include "contexts/onePlayerGame/levelEnd/levelEndContext.h"
#include "contexts/onePlayerGame/gamePaused/gameInPause.h"
#include "contexts/onePlayerGame/levelsContexts/stdLevelContext.h"
#include "contexts/onePlayerGame/levelComponents/inGameBagThings/bagViewContext.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

void hellLevel::start(Essentials& essentials, PlayerData& playerData, bool& quitMainMenu)
{
	if( onePlGame::HellPackage hellPackage{essentials, playerData} )
	{
		if( LevelComponents levelComponents{essentials, playerData, 0 } )
		{
			LevelInputs levelInputs{essentials};
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
	bool quitGame{ false };
	while( false == quitGame )
	{
		levelInputs.updateEvents();
		stdlevel::closeGameWindow(levelInputs, quitGame);
		levelComponents.hellUpdate(essentials, levelInputs, playerData, quitGame, hellPackage);
		pausedGame::pauseTheHellGame(essentials, levelInputs, levelComponents, hellPackage, quitMainMenu, quitGame);
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