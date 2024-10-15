#include "levelComponents/inputs/joystickData.h"
#include "consts/onePlayerLevelConsts.h"
#include <algorithm>

JoystickData::JoystickData():
	joyEnt{ 0 },
	joyButtons( onePlGame::JoystickButtonMax, false ),
	joyAxes{},
	joyHats{},
	joyNum{ 0 }
{
	if( joyEnt )
	{
		joyAxes.resize( joyEnt.getAxesNumber() );
		joyHats.resize( joyEnt.getHatsNumber() );
		
		std::fill(joyAxes.begin(), joyAxes.end(), 0);
		std::fill(joyHats.begin(), joyHats.end(), SDL_HAT_CENTERED );
	}
}