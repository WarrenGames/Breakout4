#include "contexts/duels/setFinalAchievement/context.h"
#include "types/essentialsStruct.h"
#include "texturing/texturesCombo.h"
#include "consts/constexprScreen.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "texts/textLoader.h" 
#include "contexts/duels/setFinalAchievement/contextWidgets.h"
#include "consts/sdlColors.h"
#include "contexts/duels/matchConfig/context.h"
#include "consts/fontsConsts.h"

void duels::finAchiev::mainContext(Essentials& essentials)
{
	if( const TextsBlocks texts{essentials.logs.error, path::getLanguageFile(essentials.language, file::DUELS_ACHIEVEMENTS), duels::finAchiev::Max } )
	{
		if( const sdl2::Font fancyFont{essentials.logs.error, FancyFontPath, FontBigPointSize} )
		{
			unsigned finalScore{40};
			const TextureCombo gradientBg{essentials.logs, essentials.rndWnd, SDL_Rect{ 0, 0, GameScreenWidth, GameScreenHeight}, WhiteColor, {0, 128, 255, 255}, GradientTextureOnY};
			duels::finAchiev::Widgets widgets{essentials, fancyFont, texts, finalScore};
			duels::finAchiev::mainLoop(essentials, finalScore, widgets, gradientBg);
		}
	}
}

void duels::finAchiev::mainLoop(Essentials& essentials, unsigned& finalScore, duels::finAchiev::Widgets& widgets, const TextureCombo& backgroundGradient)
{
	bool quitCntxt{ false };
	while( false == quitCntxt )
	{
		essentials.inp.updateEvents();
		duels::finAchiev::quitContext(quitCntxt, essentials.inp);
		duels::finAchiev::quitContextWithButton(quitCntxt, widgets.quitContext);
		duels::finAchiev::runZoneChoice(essentials, finalScore, widgets.runDuels);
		widgets.update(essentials, essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT));
		duels::finAchiev::drawEverything(essentials, widgets, backgroundGradient);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void duels::finAchiev::quitContext(bool& quitContext, input::User& inp)
{
	if( inp.getSDL_quit() || inp.getKeyState(input::KeybOut) )
	{
		quitContext = true;
		inp.setKeyStateToFalse(input::KeybOut);
	}
}

void duels::finAchiev::runZoneChoice(Essentials& essentials, unsigned& finalScore, const TextButton& textButton)
{
	if( textButton.buttonClicked() )
	{
		duels::matchConfig::context(essentials, finalScore);
	}
}

void duels::finAchiev::quitContextWithButton(bool& quitContext, const TextButton& quitButton)
{
	if( quitButton.buttonClicked() )
	{
		quitContext = true;
	}
}

void duels::finAchiev::drawEverything(Essentials& essentials, duels::finAchiev::Widgets& widgets, const TextureCombo& backgroundGradient)
{
	backgroundGradient.draw(essentials.rndWnd);
	widgets.drawAll(essentials);
	essentials.rndWnd.displayRenderer();
	SDL_Delay(10);
}