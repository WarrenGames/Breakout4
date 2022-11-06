#include "contexts/onePlayerGame/levelsContexts/antarcticContext.h"
#include "types/essentialsStruct.h"
#include "contexts/onePlayerGame/levelComponents/inputs/userInputs.h"
#include "contexts/onePlayerGame/levelComponents/global/globalGameObject.h"
#include "contexts/onePlayerGame/levelComponents/antarcticEpisodeThings/antarcticPackage.h"
#include "crossLevel/playerData.h"
#include "contexts/onePlayerGame/levelEnd/levelEndContext.h"
#include "contexts/onePlayerGame/gamePaused/gameInPause.h"
#include "contexts/onePlayerGame/levelsContexts/stdLevelContext.h"
#include "contexts/onePlayerGame/levelComponents/inGameBagThings/bagViewContext.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

void antarcticLevel::start(Essentials& essentials, PlayerData& playerData, bool& quitMainMenu)
{
	if( AntarcticPackage antarcticPackage{essentials, playerData} )
	{
		if( LevelComponents levelComponents{essentials, playerData, antarcticPackage.pinguinsData.size() } )
		{
			LevelInputs levelInputs{essentials};
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
	bool quitGame{ false };
	while( false == quitGame )
	{
		levelInputs.updateEvents();
		stdlevel::closeGameWindow(levelInputs, quitGame);
		levelComponents.antarcticUpdate(essentials, levelInputs, playerData, quitGame, antarcticPackage);
		pausedGame::pauseTheAntarcticGame(essentials, levelInputs, levelComponents, antarcticPackage, quitMainMenu, quitGame);
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