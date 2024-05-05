#include "duels/matchConfig/zoneSpecificOptions/halloween/halloweenSpecific.h"
#include "types/essentialsStruct.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "text/sdl2ttf_font.h"
#include "duels/matchConfig/zoneSpecificOptions/halloween/elements.h"
#include "duels/zones/halloween/subObjects/halloweenConfig.h"
#include "texts/textLoader.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/fontsConsts.h"
#include "duels/matchConfig/zoneSpecificOptions/halloween/languageTexts.h"

void zoneSpec::halloween::mainContext(Essentials& essentials, HalloweenConfig& halloCfg)
{
	if( const TextsBlocks halloSpecTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::DuelsHalloweenZoneConfig), language::halloween::Max} )
	{
		if( const sdl2::Font arial{essentials.logs.error, ArialFontPath, FontBigPointSize} )
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
	if( inp.getKeyState(input::KeybOut) || inp.getSDL_quit() || quitBtn.buttonClicked() )
	{
		quit = true;
		inp.setKeyStateToFalse(input::KeybOut);
	}
}

void zoneSpec::halloween::drawEverything(sdl2::RendererWindow& rndWnd, const HalloweenSpecElements& halloSpec)
{
	rndWnd.clearScreen(BlackColor);
	halloSpec.drawEverything(rndWnd);
	rndWnd.displayRenderer();
	SDL_Delay(10);
}