#include "contexts/options/optionsContext.h"
#include "types/essentialsStruct.h"
#include "contexts/options/mainMenuData.h"
#include "contexts/options/languages/languageContext.h"
#include "contexts/options/graphics/graphicsContext.h"
#include "contexts/options/audio/audioContext.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

void optionsMenu::mainInterface(Essentials& essentials)
{
	optionsMenu::MainMenu menu{essentials};
	bool quitOptionsMenu{false};
	while( false == quitOptionsMenu )
	{
		essentials.inp.updateEvents();
		menu.updateButtons(essentials);
		optionsMenu::exitMenu(essentials, quitOptionsMenu);
		optionsMenu::exitWithTextButton(menu, quitOptionsMenu);
		optionsMenu::redirectUser(essentials, menu);
		optionsMenu::drawEverything(essentials, menu);
	}
}

void optionsMenu::redirectUser(Essentials& essentials, optionsMenu::MainMenu& menu)
{
	optionsMenu::goToLanguagesPanel(essentials, menu);
	optionsMenu::goToGraphicsPanel(essentials, menu);
	optionsMenu::goToSoundsPanel(essentials, menu);
	optionsMenu::goToMusicPanel(essentials, menu);
}

void optionsMenu::goToLanguagesPanel(Essentials& essentials, optionsMenu::MainMenu& menu)
{
	if( menu.isButtonClicked(optionsMenu::ButtonLanguage) )
	{
		langOptionsMenu::context(essentials);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void optionsMenu::goToGraphicsPanel(Essentials& essentials, optionsMenu::MainMenu& menu)
{
	if( menu.isButtonClicked(optionsMenu::ButtonGraphics) )
	{
		optionsMenu::graphics::graphicsContext(essentials);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void optionsMenu::goToSoundsPanel(Essentials& essentials, optionsMenu::MainMenu& menu)
{
	if( menu.isButtonClicked(optionsMenu::ButtonSounds) )
	{
		audioOptions::mainContext(essentials);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void optionsMenu::goToMusicPanel(Essentials& essentials, optionsMenu::MainMenu& menu)
{
	if( menu.isButtonClicked(optionsMenu::ButtonMusic) )
	{
		audioOptions::mainContext(essentials);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void optionsMenu::drawEverything(Essentials& essentials, const optionsMenu::MainMenu& menu)
{
	essentials.rndWnd.clearScreen(BlackColor);
	menu.drawEverything(essentials);
	essentials.rndWnd.displayRenderer();
	SDL_Delay(SdlDelayTime);
}

void optionsMenu::exitMenu(Essentials& essentials, bool& quitMenu)
{
	if( essentials.inp.getKeyState(input::KeybOut) || essentials.inp.getSDL_quit() )
	{
		quitMenu = true;
		essentials.inp.setKeyStateToFalse(input::KeybOut);
	}
}

void optionsMenu::exitWithTextButton(const optionsMenu::MainMenu& menu, bool& quitMenu)
{
	if( menu.isButtonClicked(optionsMenu::ButtonQuit) )
	{
		quitMenu = true;
	}
}