#include "contexts/duels/controls/inputConfigContext.h"
#include "contexts/duels/duelsConstexpr.h"
#include "contexts/duels/controls/objects/mainObject.h"
#include "types/essentialsStruct.h"

void duels::inputCfg::mainContext(Essentials& essentials)
{
	duels::InputScreenGlobal global{essentials};
	bool quitScreen{ false };
	duels::inputCfg::contextLoop(essentials, quitScreen, global);
	global.saveInputsDataToFile(essentials);
}

void duels::inputCfg::contextLoop(Essentials& essentials, bool& quitScreen, duels::InputScreenGlobal& global)
{	
	while( false == quitScreen )
	{
		essentials.inp.updateEvents();
		duels::inputCfg::quitContext(essentials.inp, quitScreen);
		duels::inputCfg::update(essentials, global);
		global.runJoystickDetailsInterface(essentials);
		duels::inputCfg::drawEverything(essentials, global);
	}
}

void duels::inputCfg::quitContext(input::User& userInput, bool& quitScreen)
{
	if( userInput.getSDL_quit() || userInput.getKeyState(input::KeybOut) )
	{
		quitScreen = true;
		userInput.setKeyStateToFalse(input::KeybOut);
	}
}

void duels::inputCfg::update(Essentials& essentials, duels::InputScreenGlobal& global)
{
	global.update(essentials);
	
	essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
}

void duels::inputCfg::drawEverything(Essentials& essentials, const duels::InputScreenGlobal& global)
{
	global.drawEverything(essentials);
	essentials.rndWnd.displayRenderer();
	SDL_Delay(SdlDelayTime);
}