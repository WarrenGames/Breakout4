#ifndef JOYSTICK_INPUT_DATA_H
#define JOYSTICK_INPUT_DATA_H

#include "consts/onePlayerLevelConsts.h"
#include "joystick/joystickEntity.h"
#include <vector>

struct Essentials;

namespace onePlGame{
	
enum{ JOY_CROSS_MOVE_X, JOY_CROSS_MOVE_Y, JOY_CROSS_MOVE_MAX };
	
struct JoystickInputData
{
	bool isLoadingPerfect;
	sdl2::JoystickEntity joystickEntity;
	unsigned joystickNumber;
	unsigned joyMoveType;
	unsigned axisOrHatNum;
	Sint32 axisMoveThreshold;
	std::vector< unsigned > joyButtons;
	unsigned crossMoveType;
	std::vector< unsigned > crossNum;
	
	explicit JoystickInputData(Essentials& essentials);
	void readJoystickData(Essentials& essentials);
	void writeJoystickFile(Essentials& essentials);
	
	void readDestCrossJoystickData(Essentials& essentials);
	void writeDestCrossJoystickFile(Essentials& essentials);
};

}

#endif //JOYSTICK_INPUT_DATA_H