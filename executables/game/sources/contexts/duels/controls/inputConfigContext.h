#ifndef INPUT_CONFIG_CONTEXT_H
#define INPUT_CONFIG_CONTEXT_H

struct Essentials;
namespace input{ class User; }
namespace sdl2{ class RendererWindow; }

namespace duels{

struct InputScreenGlobal;
	
namespace inputCfg{
	void mainContext(Essentials& essentials);
	
	void contextLoop(Essentials& essentials, bool& quitScreen, duels::InputScreenGlobal& global);
	
	void quitContext(input::User& userInput, bool& quitScreen);
	
	void update(Essentials& essentials, duels::InputScreenGlobal& global);
	
	void drawEverything(Essentials& essentials, const duels::InputScreenGlobal& global);
}

}

#endif //INPUT_CONFIG_CONTEXT_H