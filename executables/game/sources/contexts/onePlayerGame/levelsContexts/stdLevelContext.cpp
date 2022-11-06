#include "contexts/onePlayerGame/levelsContexts/stdLevelContext.h"
#include "types/essentialsStruct.h"
#include "contexts/onePlayerGame/levelComponents/inputs/userInputs.h"
#include "contexts/onePlayerGame/levelComponents/global/globalGameObject.h"
#include "crossLevel/playerData.h"
#include "contexts/onePlayerGame/levelEnd/levelEndContext.h"
#include "contexts/onePlayerGame/gamePaused/gameInPause.h"
#include "contexts/onePlayerGame/levelComponents/inGameBagThings/bagViewContext.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

void stdlevel::start(Essentials& essentials, PlayerData& playerData, bool& quitMainMenu)
{
	if( LevelComponents levelComponents{essentials, playerData, 0} )
	{
		LevelInputs levelInputs{essentials};
		stdlevel::playGame(essentials, levelInputs, levelComponents, playerData, quitMainMenu);
		levelEnd::startLevelSum(essentials, levelComponents, playerData, quitMainMenu);
	}
	else{
		stdlevel::logLevelComponentsError(essentials);
	}
}

void stdlevel::playGame(Essentials& essentials, LevelInputs& levelInputs, LevelComponents& levelComponents, PlayerData& playerData, bool& quitMainMenu)
{
	bool quitGame{ false };
	while( false == quitGame )
	{
		levelInputs.updateEvents();
		stdlevel::closeGameWindow(levelInputs, quitGame);
		levelComponents.standardLevelUpdate(essentials, levelInputs, playerData, quitGame);
		pausedGame::pauseTheGame(essentials, levelInputs, levelComponents, quitMainMenu, quitGame);
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