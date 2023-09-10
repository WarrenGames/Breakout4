#include "duels/setFinalAchievement/finalAchievementContext.h"
#include "types/essentialsStruct.h"
#include "texturing/texturesCombo.h"
#include "consts/constexprScreen.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "texts/textLoader.h" 
#include "duels/setFinalAchievement/contextWidgets.h"
#include "consts/sdlColors.h"
#include "consts/fontsConsts.h"

void duels::finAchiev::mainContext(Essentials& essentials, unsigned& finalScore, bool& quitDuels)
{
	if( const TextsBlocks texts{essentials.logs.error, path::getLanguageFile(essentials.language, file::DuelsAchievements), duels::finAchiev::Max } )
	{
		if( const sdl2::Font fancyFont{essentials.logs.error, FancyFontPath, FontBigPointSize} )
		{
			const TextureCombo gradientBg{essentials.logs, essentials.rndWnd, SDL_Rect{ 0, 0, GameScreenWidth, GameScreenHeight}, WhiteColor, {0, 128, 255, 255}, GradientTextureOnY};
			duels::finAchiev::Widgets widgets{essentials, fancyFont, texts, finalScore};
			duels::finAchiev::mainLoop(essentials, widgets, gradientBg, quitDuels);
		}
	}
}

void duels::finAchiev::mainLoop(Essentials& essentials, duels::finAchiev::Widgets& widgets, const TextureCombo& backgroundGradient, bool& quitDuels)
{
	bool quitContext{ false };
	while( false == quitContext )
	{
		essentials.inp.updateEvents();
		duels::finAchiev::quitContext(essentials.inp, quitDuels, quitContext);
		duels::finAchiev::quitContextWithButton(widgets.quitContext, quitDuels, quitContext);
		duels::finAchiev::runZoneChoice(widgets.runDuels, quitContext);
		widgets.update(essentials, essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT));
		duels::finAchiev::drawEverything(essentials, widgets, backgroundGradient);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void duels::finAchiev::quitContext(input::User& inp, bool& quitDuels, bool& quitContext)
{
	if( inp.getSDL_quit() || inp.getKeyState(input::KeybOut) )
	{
		quitContext = true;
		quitDuels = true;
		inp.setKeyStateToFalse(input::KeybOut);
	}
}

void duels::finAchiev::runZoneChoice(const TextButton& textButton, bool& quitContext)
{
	if( textButton.buttonClicked() )
	{
		quitContext = true;
	}
}

void duels::finAchiev::quitContextWithButton(const TextButton& quitButton, bool& quitDuels, bool& quitContext)
{
	if( quitButton.buttonClicked() )
	{
		quitContext = true;
		quitDuels = true;
	}
}

void duels::finAchiev::drawEverything(Essentials& essentials, const duels::finAchiev::Widgets& widgets, const TextureCombo& backgroundGradient)
{
	backgroundGradient.draw(essentials.rndWnd);
	widgets.drawAll(essentials);
	essentials.rndWnd.displayRenderer();
	SDL_Delay(10);
}