#include "contexts/options/languages/languageContext.h"
#include "contexts/options/languages/languagesMenuGraphics.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

void langOptionsMenu::context(Essentials& essentials)
{
	LanguageOptionsGraphics languagesGraphics{essentials};
	
	langOptionsMenu::useLanguagePanel(essentials, languagesGraphics);
	
	languagesGraphics.writeNewLanguageIfChanged(essentials);
}

void langOptionsMenu::useLanguagePanel(Essentials& essentials, LanguageOptionsGraphics& languagesGraphics)
{
	bool quitPanel{false};
	while( false == quitPanel )
	{
		essentials.inp.updateEvents();
		langOptionsMenu::quitOptionsLanguagePanel(essentials, quitPanel);
		langOptionsMenu::updateLanguagePanel(essentials, languagesGraphics);
		langOptionsMenu::drawLanguagePanel(essentials, languagesGraphics);
	}
}

void langOptionsMenu::updateLanguagePanel(Essentials& essentials, LanguageOptionsGraphics& languagesGraphics)
{
	languagesGraphics.update(essentials);
	languagesGraphics.changeLanguage();
}

void langOptionsMenu::drawLanguagePanel(Essentials& essentials, const LanguageOptionsGraphics& languagesGraphics)
{
	essentials.rndWnd.clearScreen(BlackColor);
	languagesGraphics.drawEverything(essentials);
	essentials.rndWnd.displayRenderer();
	SDL_Delay(SdlDelayTime);
}

void langOptionsMenu::quitOptionsLanguagePanel(Essentials& essentials, bool& quitLanguagePanel)
{
	if( essentials.inp.getSDL_quit() || essentials.inp.getKeyState(input::KeybOut) )
	{
		quitLanguagePanel = true;
		essentials.inp.setKeyStateToFalse(input::KeybOut);
	}
}