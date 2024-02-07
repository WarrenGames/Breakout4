#ifndef DUELS_HALLOWEEN_SPECIFIC_H
#define DUELS_HALLOWEEN_SPECIFIC_H

struct HalloweenConfig;
struct HalloweenSpecElements;
struct Essentials;
class TextButton;
namespace sdl2{ class RendererWindow; }
namespace input{ class User; }

namespace zoneSpec{
	namespace halloween{
		void mainContext(Essentials& essentials, HalloweenConfig& halloCfg);

		void mainLoop(Essentials& essentials, HalloweenSpecElements& halSpecific);

		void quitScreen(bool& quit, input::User& inp, const TextButton& quitBtn);

		void drawEverything(sdl2::RendererWindow& rndWnd, const HalloweenSpecElements& halloSpec);
	}
}

#endif //DUELS_HALLOWEEN_SPECIFIC_H