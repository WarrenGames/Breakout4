#include "duels/matchConfig/zoneChoice/zoneChoiceContext.h"
#include "types/essentialsStruct.h"
#include "duels/matchConfig/interface/zoneChoiceThings.h"
#include "duels/matchConfig/zoneChoice/zonesChoicePanels.h"
#include "consts/sdlColors.h"

void duels::zoneChoice::context(Essentials& essentials, unsigned& chosenZone)
{
	if( duels::PanelsGraphics panels{essentials.logs, essentials.rndWnd} )
	{
		duels::zoneChoice::mainLoop(essentials, panels, chosenZone);
	}
}

void duels::zoneChoice::mainLoop(Essentials& essentials, duels::PanelsGraphics& panels, unsigned& chosenZone)
{
	bool quit{false};
	while( false == quit )
	{
		essentials.inp.updateEvents();
		duels::zoneChoice::quitScreen(essentials.inp, quit);
		duels::zoneChoice::selectZone(essentials.inp, panels, chosenZone, quit);
		duels::zoneChoice::drawEverything(essentials.rndWnd, panels);
	}
}

void duels::zoneChoice::quitScreen(input::User& inp, bool& quitScreen)
{
	if( inp.getSDL_quit() || inp.getKeyState(input::KeybOut) )
	{
		quitScreen = true;
		inp.setKeyStateToFalse(input::KeybOut);
	}
}

void duels::zoneChoice::drawEverything(sdl2::RendererWindow& rndWnd, duels::PanelsGraphics& panels)
{
	rndWnd.clearScreen(BlackColor);
	panels.drawPanels(rndWnd);
	rndWnd.displayRenderer();
	SDL_Delay(10);
}

void duels::zoneChoice::selectZone(input::User& inp, duels::PanelsGraphics& panels, unsigned& chosenZone, bool& quitScreen)
{
	if( panels.setZoneChoice(inp.getMousePosition(), inp.getMouseButtonState(SDL_BUTTON_LEFT), chosenZone) )
	{
		quitScreen = true;
	}
}