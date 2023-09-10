#ifndef DUELS_JOYSTICKS_INFOS_DRAWER_H
#define DUELS_JOYSTICKS_INFOS_DRAWER_H

#include "duels/controls/objects/joystickInfosGraphics.h"
#include <vector>

struct Essentials;
struct AppLogFiles;
namespace sdl2{ class RendererWindow; class Font; }

class JoystickInfosDrawer
{
private:
	std::vector< JoyInfosTextsGraphics > infosTexts;

public:
	JoystickInfosDrawer(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, const TextsBlocks& texts);
	~JoystickInfosDrawer() = default;
	JoystickInfosDrawer( const JoystickInfosDrawer& ) = delete;
	JoystickInfosDrawer& operator= ( const JoystickInfosDrawer& ) = delete;
	JoystickInfosDrawer( JoystickInfosDrawer&& ) = default;
	JoystickInfosDrawer& operator= ( JoystickInfosDrawer&& ) = default;
	
	void update(Essentials& essentials);
	void drawEverything(sdl2::RendererWindow& rndWnd) const;
	void resetTexts(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, const TextsBlocks& texts);

	void runJoystickDetailsInterface(Essentials& essentials, const sdl2::Font& fancyFont);
};

#endif //DUELS_JOYSTICKS_INFOS_DRAWER_H