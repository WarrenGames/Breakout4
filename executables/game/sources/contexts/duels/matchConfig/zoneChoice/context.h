#ifndef DUELS_ZONE_CHOICE_GUI_H
#define DUELS_ZONE_CHOICE_GUI_H

#include <cstdlib>

namespace duels{ class PanelsGraphics; }
namespace sdl2{ class RendererWindow; }
namespace input{ class User; }
struct Essentials;

namespace duels{
	namespace zoneChoice{
		void context(Essentials& essentials, std::size_t& chosenZone);
		void mainLoop(Essentials& essentials, duels::PanelsGraphics& panels, std::size_t& chosenZone);
		void quitScreen(input::User& inp, bool& quitScreen);
		void drawEverything(sdl2::RendererWindow& rndWnd, duels::PanelsGraphics& panels);
		
		void selectZone(input::User& inp, duels::PanelsGraphics& panels, std::size_t& chosenZone, bool& quitScreen);
	}
}

#endif //DUELS_ZONE_CHOICE_GUI_H