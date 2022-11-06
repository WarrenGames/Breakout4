#include "contexts/duels/controls/objects/joysticksInfosDrawer.h"
#include "contexts/options/joystickInterface/joystickInfosInterface.h"
#include "types/essentialsStruct.h"
#include "contexts/duels/duelsConstexpr.h"

JoystickInfosDrawer::JoystickInfosDrawer(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, const TextsBlocks& texts)
{
	infosTexts.emplace_back( JoyInfosTextsGraphics{logs, rndWnd, fancyFont, duels::PlayerBlue, texts} );
	infosTexts.emplace_back( JoyInfosTextsGraphics{logs, rndWnd, fancyFont, duels::PlayerRed, texts} );
}

void JoystickInfosDrawer::update(Essentials& essentials)
{
	for( auto &playerInf : infosTexts )
	{
		playerInf.update(essentials);
	}
}

void JoystickInfosDrawer::drawEverything(sdl2::RendererWindow& rndWnd) const
{
	for( auto const &playerInf : infosTexts )
	{
		playerInf.drawTexts(rndWnd);
	}
}

void JoystickInfosDrawer::resetTexts(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, const TextsBlocks& texts)
{
	for( unsigned player{0} ; player < infosTexts.size() ; ++player )
		infosTexts[player].resetTexts(logs, rndWnd, fancyFont, player, texts);
}

void JoystickInfosDrawer::runJoystickDetailsInterface(Essentials& essentials, const sdl2::Font& fancyFont)
{
	for( auto const &playerInf : infosTexts )
	{
		if( playerInf.seeJoystickInfos.buttonClicked() )
		{
			joyCfg::mainContext(essentials, fancyFont, playerInf.joyEnt);
			essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
			essentials.inp.setKeyStateToFalse(input::KeybOut);
		}
	}
}