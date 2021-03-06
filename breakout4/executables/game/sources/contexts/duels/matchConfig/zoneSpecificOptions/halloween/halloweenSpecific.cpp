#include "contexts/duels/matchConfig/zoneSpecificOptions/halloween/halloweenSpecific.h"
#include "types/essentialsStruct.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "text/sdl2ttf_font.h"
#include "contexts/duels/matchConfig/zoneSpecificOptions/halloween/elements.h"
#include "contexts/duels/zones/halloween/subObjects/halloweenConfig.h"
#include "texts/textLoader.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/fontsConsts.h"
#include "contexts/duels/matchConfig/zoneSpecificOptions/halloween/languageTexts.h"

void zoneSpec::halloween::mainContext(Essentials& essentials, HalloweenConfig& halloCfg)
{
	if( const TextsBlocks halloSpecTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::DUELS_ZONE_HALLOWEEN_CFG), language::halloween::MAX} )
	{
		if( const sdl2::Font arial{essentials.logs.error, ARIALFONTPATH, FONT_BIG_PTSIZE} )
		{
			HalloweenSpecElements halloweenSpec{essentials.logs, essentials.rndWnd, halloSpecTexts, arial, halloCfg};
			zoneSpec::halloween::mainLoop(essentials, halloweenSpec);
		}
	}
}

void zoneSpec::halloween::mainLoop(Essentials& essentials, HalloweenSpecElements& halSpecific)
{
	bool quit{false};
	while( false == quit )
	{
		essentials.inp.updateEvents();
		zoneSpec::halloween::quitScreen(quit, essentials.inp, halSpecific.quitBtn);
		halSpecific.quitBtn.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT));
		halSpecific.boxesValueEditing(essentials.logs, essentials.rndWnd, essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT));
		halSpecific.catchWallpaperBoolBoxFocus(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT));
		zoneSpec::halloween::drawEverything(essentials.rndWnd, halSpecific);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}

void zoneSpec::halloween::quitScreen(bool& quit, input::User& inp, const TextButton& quitBtn)
{
	if( inp.getKeyState(input::KEYB_OUT) || inp.getSDL_quit() || quitBtn.buttonClicked() )
	{
		quit = true;
		inp.setKeyStateToFalse(input::KEYB_OUT);
	}
}

void zoneSpec::halloween::drawEverything(sdl2::RendererWindow& rndWnd, const HalloweenSpecElements& halloSpec)
{
	rndWnd.clearScreen(BLACK_COL);
	halloSpec.drawEverything(rndWnd);
	rndWnd.displayRenderer();
	SDL_Delay(10);
}