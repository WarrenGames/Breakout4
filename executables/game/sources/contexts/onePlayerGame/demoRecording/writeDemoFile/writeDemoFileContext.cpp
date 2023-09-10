#include "contexts/onePlayerGame/demoRecording/writeDemoFile/writeDemoFileContext.h"
#include "types/essentialsStruct.h"
#include "crossLevel/playerData.h"
#include "levelComponents/demosObjects/demoMainPackage.h"
#include "contexts/onePlayerGame/demoRecording/writeDemoFile/writeDemoFileInterface.h"
#include "demosLoadingAndSaving/saving/saveDemoFile.h"
#include "consts/sdlColors.h"
#include "consts/constexprScreen.h"
#include "consts/constPaths.h"

void demos::writeDemoFileMainContext(Essentials& essentials, const PlayerData& playerData, const demos::MainPackage& mainPackage)
{
	demos::WriteDemoFileInterface interface{essentials, playerData, mainPackage};
	while( false == interface.quit )
	{
		essentials.inp.updateEvents();
		interface.updateInterface(essentials);
		demos::quitInterface(essentials, interface);
		demos::writeFile(essentials, interface, mainPackage);
		demos::drawInterface(essentials, interface);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void demos::drawInterface(Essentials& essentials, const demos::WriteDemoFileInterface& interface)
{
	essentials.rndWnd.clearScreen(BlackColor);
	interface.drawEverything(essentials);
	essentials.rndWnd.displayRenderer();
	SDL_Delay( SdlDelayTime );
}

void demos::quitInterface(Essentials& essentials, demos::WriteDemoFileInterface& interface)
{
	if( essentials.inp.getKeyState(input::KeybOut) || essentials.inp.getSDL_quit() || interface.quitButton.buttonClicked() )
	{
		interface.quit = true;
	}
}

void demos::writeFile(Essentials& essentials, demos::WriteDemoFileInterface& interface, const demos::MainPackage& mainPackage)
{
	if( interface.saveButton.buttonClicked() )
	{
		interface.quit = true;
		fs::path savingDirectory{ essentials.prefPath.getFsPath() };
		savingDirectory /= DemosFilesDirectory;
		savingDirectory /= interface.fileName;
		saveDemo::openGameDemoFile(savingDirectory, mainPackage);
	}
}