#include "contexts/gameStarting/mainMenu/mainMenu.h"
#include "text/sdl2ttf_font.h"
#include "consts/fontsConsts.h"
#include "texts/textLoader.h"
#include "texturing/texturesCombo.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "types/essentialsStruct.h"
#include "contexts/gameStarting/mainMenu/mainMenuWidgets.h"
#include "contexts/onePlayerGame/newGame/newGameContext.h"
#include "contexts/duels/setFinalAchievement/context.h"
#include "contexts/credits/creditsContext.h"
#include "contexts/options/optionsContext.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/fontsConsts.h"

void mainMenu::menu(Essentials& essentials)
{
	if( const sdl2::Font fancyFont{essentials.logs.error, FancyFontPath, FontBigPointSize} )
	{
		if( const TextsBlocks mainMenuTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::MAIN_MENU), mainMenu::Max} )
		{
			mainMenu::Widgets buttons{essentials, fancyFont, mainMenuTexts};
			const TextureCombo background{essentials.logs, essentials.rndWnd, "textures/wallpapers/mainMenu.png", TexturePosition{0, 0} };
			bool quitMenu{false};
			mainMenu::mainLoop(essentials, buttons, quitMenu, background);
		}
	}
}

void mainMenu::mainLoop(Essentials& essentials, mainMenu::Widgets& buttons, bool& quitMenu, const TextureCombo& background)
{
	while( false == quitMenu )
	{
		essentials.inp.updateEvents();
		buttons.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
		mainMenu::quitMenu(essentials, quitMenu, buttons.buttons[mainMenu::Quit]);
		mainMenu::runOnePlayerGame(essentials, buttons.buttons[mainMenu::OnePlayerGame]);
		mainMenu::runDuels(essentials, buttons.buttons[mainMenu::DuelsGame]);
		mainMenu::runCredits(essentials, buttons.buttons[mainMenu::Credits]);
		mainMenu::runOptions(essentials, buttons.buttons[mainMenu::Options]);
		mainMenu::drawEverything(essentials, buttons, quitMenu, background);
	}
}

void mainMenu::drawEverything(Essentials& essentials, mainMenu::Widgets& buttons, bool& quitMenu, const TextureCombo& background)
{
	if( false == quitMenu )
	{
		essentials.rndWnd.clearScreen(BlackColor);
		background.draw(essentials.rndWnd);
		buttons.drawButtons(essentials.rndWnd);
		essentials.rndWnd.displayRenderer();
		SDL_Delay(SdlDelayTime);
	}
}

void mainMenu::quitMenu(Essentials& essentials, bool& quitMenu, const TextButton& quitButton)
{
	if( essentials.inp.getSDL_quit() || essentials.inp.getKeyState(input::KeybOut) || quitButton.buttonClicked() )
	{
		quitMenu = true;
		essentials.inp.setSDL_quitToFalse();
		essentials.inp.setKeyStateToFalse(input::KeybOut);
	}
}

void mainMenu::runOnePlayerGame(Essentials& essentials, const TextButton& gameButton)
{
	if( gameButton.buttonClicked() )
	{
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		onePlGame::newGame::context(essentials);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void mainMenu::runDuels(Essentials& essentials, const TextButton& duelsButton)
{
	if( duelsButton.buttonClicked() )
	{
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		duels::finAchiev::mainContext(essentials);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void mainMenu::runCredits(Essentials& essentials, const TextButton& creditsButton)
{
	if( creditsButton.buttonClicked() )
	{
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		creditsMenu::context(essentials);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void mainMenu::runOptions(Essentials& essentials, const TextButton& optionsButton)
{
	if( optionsButton.buttonClicked() )
	{
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		optionsMenu::mainInterface(essentials);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}