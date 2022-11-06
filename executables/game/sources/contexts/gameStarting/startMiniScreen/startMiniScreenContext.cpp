#include "contexts/gameStarting/startMiniScreen/startMiniScreenContext.h"
#include "types/essentialsStruct.h"
#include "texts/textLoader.h"
#include "appStart/miniScreenGui.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "contexts/gameStarting/sdlLogoDisplay/logoDispContext.h"
#include "contexts/gameStarting/mainMenu/mainMenu.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

void cntxt::miniScreen::mainContext(AppLogFiles& logs, const PrefPathFinder& prefPath, const std::string& chosenLang, sdl2::RendererWindow& rndWnd)
{
	if( const TextsBlocks miniScreenTexts{logs.error, path::getLanguageFile( chosenLang, file::START_MINI_SCREEN ), 3 } )
	{
		if( const MiniScreen miniGUI{logs, rndWnd, miniScreenTexts, 64, GameScreenWidth, GameScreenHeight} )
		{
			cntxt::miniScreen::waitForInput(logs, prefPath, chosenLang, rndWnd, miniGUI);
		}
	}
}

void cntxt::miniScreen::waitForInput(AppLogFiles& logs, const PrefPathFinder& prefPath, const std::string& chosenLang, sdl2::RendererWindow& rndWnd, const MiniScreen& miniGUI)
{
	bool quitMiniScreen{false};
	input::User userInput{};
	Essentials essentials{logs, prefPath, chosenLang, rndWnd, userInput};
	
	while( false == quitMiniScreen )
	{
		userInput.updateEvents();
		cntxt::miniScreen::actWithInput(essentials, quitMiniScreen);
		cntxt::miniScreen::drawEverything(rndWnd, miniGUI, quitMiniScreen);
	}
}

void cntxt::miniScreen::actWithInput(Essentials& essentials, bool& quitMiniScreen)
{
	cntxt::miniScreen::actWithSDLQuit(essentials.inp, quitMiniScreen);
	cntxt::miniScreen::actWithEscapeKey(essentials.inp, quitMiniScreen);
	cntxt::miniScreen::runFullScreenGame(essentials, quitMiniScreen);
	cntxt::miniScreen::runWindowedGame(essentials, quitMiniScreen);
}

void cntxt::miniScreen::actWithSDLQuit(input::User& userInput, bool& quitMiniScreen)
{
	if( userInput.getKeyState(input::KeybOut) )
	{
		userInput.setKeyStateToFalse(input::KeybOut);
		quitMiniScreen = true;
	}
}

void cntxt::miniScreen::actWithEscapeKey(input::User& userInput, bool& quitMiniScreen)
{
	if( userInput.getSDL_quit() )
	{
		userInput.setSDL_quitToFalse();
		quitMiniScreen = true;
	}
}

void cntxt::miniScreen::changeScreenLayout(Essentials& essentials, bool& quitMiniScreen, bool isFullScreen, unsigned keyToSetToFalse)
{
	quitMiniScreen = true;
	essentials.rndWnd.changeScreenDefinition(GameScreenWidth, GameScreenHeight);
	essentials.rndWnd.setWindowFullScreen( isFullScreen);
	essentials.rndWnd.centerWindow();
	essentials.rndWnd.clearScreen(BlackColor);
	essentials.rndWnd.displayRenderer();
	essentials.inp.setKeyStateToFalse(keyToSetToFalse);
	logoDisplay::mainContext(essentials);
	mainMenu::menu(essentials);
}

void cntxt::miniScreen::runFullScreenGame(Essentials& essentials, bool& quitMiniScreen)
{
	if( essentials.inp.getKeyState(input::KeybMainPrevious) )
	{
		cntxt::miniScreen::changeScreenLayout(essentials, quitMiniScreen, true, input::KeybMainPrevious);
	}
}

void cntxt::miniScreen::runWindowedGame(Essentials& essentials, bool& quitMiniScreen)
{
	if( essentials.inp.getKeyState(input::KeybSubPrevious) )
	{
		cntxt::miniScreen::changeScreenLayout(essentials, quitMiniScreen, false, input::KeybSubPrevious);
	}
}

void cntxt::miniScreen::drawEverything(sdl2::RendererWindow& rndWnd, const MiniScreen& miniGUI, bool& quitMiniScreen)
{
	if( false == quitMiniScreen )
	{
		miniGUI.drawAll(rndWnd);
		rndWnd.displayRenderer();
		SDL_Delay(SdlDelayTime);
	}
}