#ifndef IN_GAME_JOYSTICK_DATA_H
#define IN_GAME_JOYSTICK_DATA_H

#include "joystick/joystickEntity.h"
#include <vector>

struct JoystickData
{
	sdl2::JoystickEntity joyEnt;
	std::vector<bool> joyButtons; //size should be equal to 'JoyButtonMax'
	std::vector<Sint16> joyAxes;
	std::vector<Uint8> joyHats;
	SDL_JoystickID joyNum;
	
	JoystickData();
	~JoystickData() = default;
	JoystickData( const JoystickData& ) = delete;
	JoystickData& operator= ( const JoystickData& ) = delete;
	JoystickData( JoystickData&& ) = default;
	JoystickData& operator= ( JoystickData&& ) = default;
};

#endif //IN_GAME_JOYSTICK_DATA_H