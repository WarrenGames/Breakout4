#ifndef JOYSTICK_INPUT_DATA_H
#define JOYSTICK_INPUT_DATA_H

#include "consts/onePlayerLevelConsts.h"
#include "joystick/joystickEntity.h"
#include <vector>

struct Essentials;

namespace onePlGame{
	
enum{ JoystickCrossMoveX, JoystickCrossMoveY, JoystickCrossMoveMax };
	
struct JoystickInputData
{
	sdl2::JoystickEntity joyEnt;//Needed to go in joytsick config menu in options menu
	SDL_JoystickID joystickNumber;
	unsigned joyMoveType;
	unsigned axisOrHatNum;
	unsigned crossMoveType;
	Sint32 axisMoveThreshold;
	std::vector< unsigned > joyButtons;
	std::vector< unsigned > crossNum;
	bool isLoadingPerfect;
	
	explicit JoystickInputData(Essentials& essentials);
	~JoystickInputData() = default;
	JoystickInputData( const JoystickInputData& ) = delete;
	JoystickInputData& operator= ( const JoystickInputData& ) = delete;
	JoystickInputData( JoystickInputData&& ) = default;
	JoystickInputData& operator= ( JoystickInputData&& ) = default;
	
	void readJoystickData(Essentials& essentials);
	void writeJoystickFile(Essentials& essentials);
	
	void readDestCrossJoystickData(Essentials& essentials);
	void writeDestCrossJoystickFile(Essentials& essentials);
};

}

#endif //JOYSTICK_INPUT_DATA_H