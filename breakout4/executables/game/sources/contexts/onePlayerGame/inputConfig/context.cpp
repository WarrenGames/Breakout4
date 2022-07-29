#include "contexts/onePlayerGame/inputConfig/context.h"
#include "types/essentialsStruct.h"
#include "contexts/onePlayerGame/inputConfig/inputThings.h"
#include "contexts/options/joystickInterface/joystickInfosInterface.h"

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
	if( essentials.inp.getSDL_quit() || essentials.inp.getKeyState(input::KEYB_OUT) )
	{
		essentials.inp.setKeyStateToFalse(input::KEYB_OUT);
		quit = true;
	}
}

void onePlInputCfg::goToJoystickMenu(Essentials& essentials, onePlGame::InputThings& inputThings)
{
	if( inputThings.joystickMenu.buttonClicked() && inputThings.inputData.joystickData.joystickEntity )
	{
		joyCfg::mainContext(essentials, inputThings.fancyFont, inputThings.inputData.joystickData.joystickEntity);
		essentials.inp.setKeyStateToFalse(input::KEYB_OUT);
		essentials.inp.setMouseButtonToFalse(SDL_BUTTON_LEFT);
	}
}