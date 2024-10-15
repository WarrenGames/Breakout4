#include "inputConfig/inputConfigContext.h"
#include "types/essentialsStruct.h"
#include "inputConfig/inputThings.h"
#include "options/joystickInterface/joystickInfosInterface.h"

void onePlInputCfg::mainContext(Essentials& essentials)
{
	if( onePlGame::InputThings inputThings{essentials} )
	{
		bool quitContext{false};
		while( false == quitContext )
		{
			essentials.inp.updateEvents();
			onePlInputCfg::quitInputConfigContext(quitContext, essentials);
			onePlInputCfg::goToJoystickMenu(essentials, inputThings);
			inputThings.updateEverything(essentials);
			inputThings.drawEverything(essentials);
			essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
		}
		inputThings.writeDataToConfigFiles(essentials);
	}
}

void onePlInputCfg::quitInputConfigContext(bool& quit, Essentials& essentials)
{
	if( essentials.inp.getSDL_quit() || essentials.inp.getKeyState(input::KeybOut) )
	{
		essentials.inp.setKeyStateToFalse(input::KeybOut);
		quit = true;
	}
}

void onePlInputCfg::goToJoystickMenu(Essentials& essentials, onePlGame::InputThings& inputThings)
{
	if( inputThings.joystickMenu.buttonClicked() && inputThings.inputData.joystickConfig.joyEnt )
	{
		joyCfg::mainContext(essentials, inputThings.fancyFont, inputThings.inputData.joystickConfig.joyEnt);
		essentials.inp.setKeyStateToFalse(input::KeybOut);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}