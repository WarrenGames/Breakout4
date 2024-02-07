#include "contexts/onePlayerGame/demoLoading/demoLoadingContext.h"
#include "contexts/onePlayerGame/demoLoading/demoLoadingInterface.h"
#include "types/essentialsStruct.h"
#include "exceptions/readErrorExcept.h"
#include "levelComponents/demosObjects/demoMainPackage.h"
#include "crossLevel/playerData.h"
#include "demosLoadingAndSaving/loading/loadDemoFile.h"
#include "levelsContexts/stdLevelContext.h"
#include "levelsContexts/antarcticContext.h"
#include "levelsContexts/hellContext.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/onePlayerLevelConsts.h"

void demosLoading::mainContext(Essentials& essentials)
{
	demosLoading::Interface interface{essentials};
	while( false == interface.quitMenu )
	{
		essentials.inp.updateEvents();
		interface.updateButtons(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
		demosLoading::quitDemoMenu(essentials, interface.quitMenu, interface.quitButton);
		demosLoading::runDemoFile(essentials, interface);
		demosLoading::drawEverything(essentials, interface);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void demosLoading::drawEverything(Essentials& essentials, const demosLoading::Interface& interface)
{
	essentials.rndWnd.clearScreen(BlackColor);
	interface.drawEverything(essentials);
	essentials.rndWnd.displayRenderer();
	SDL_Delay( SdlDelayTime );
}

void demosLoading::runDemoFile(Essentials& essentials, demosLoading::Interface& interface)
{
	if( interface.demoFilesDisplayer.demoData.empty() == false )
	{
		for( auto const &button : interface.demoFilesDisplayer.demoData[interface.demoFilesDisplayer.currentPage] )
		{
			if( button.button.buttonClicked() )
			{
				PlayerData playerData{demos::GameIsDemo};
				demos::MainPackage demosMainPackage{essentials.logs, essentials.prefPath, demos::GameIsDemo};
			
				try{
					loadDemo::openFile(button.demoFilePath, demosMainPackage, playerData);
					playerData.laterInitialization(essentials.logs);
					demosLoading::runLevelWithLoadedDemoData(essentials, playerData, demosMainPackage);
				}
				catch( const ReadError& e )
				{
					interface.setErrorString(essentials, e);
					essentials.logs.error << e.what() << '\n';
				}
			}
		}
	}
}

void demosLoading::runLevelWithLoadedDemoData(Essentials& essentials, PlayerData& playerData, demos::MainPackage& demosMainPackage)
{
	bool quitDemo{false};
	switch( playerData.getLevelType() )
	{
		case onePlGame::EpisodeSimple:
			stdlevel::startWithDemoRunning(essentials, playerData, demosMainPackage, quitDemo);
			break;
		case onePlGame::EpisodeArtic:
			antarcticLevel::startWithDemoRunning(essentials, playerData, demosMainPackage, quitDemo);
			break;
		case onePlGame::EpisodeHell:
			hellLevel::startWithDemoRunning(essentials, playerData, demosMainPackage, quitDemo);
			break;
	}
}

void demosLoading::quitDemoMenu(Essentials& essentials, bool& quitMenu, const TextButton& quitButton)
{
	if( essentials.inp.getSDL_quit() || essentials.inp.getKeyState(input::KeybOut) || quitButton.buttonClicked() )
	{
		quitMenu = true;
		essentials.inp.setKeyStateToFalse(input::KeybOut);
	}
}