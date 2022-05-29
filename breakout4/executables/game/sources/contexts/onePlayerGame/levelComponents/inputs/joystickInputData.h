#ifndef JOYSTICK_INPUT_DATA_H
#define JOYSTICK_INPUT_DATA_H

#include "consts/onePlayerLevelConsts.h"
#include "joystick/joystickEntity.h"
#include <array>

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
	std::array< unsigned, onePlGame::JOYBTN_MAX > joyButtons;
	unsigned crossMoveType;
	std::array< unsigned , onePlGame::JOY_CROSS_MOVE_MAX > crossNum;
	
	explicit JoystickInputData(Essentials& essentials);
	void readJoystickData(Essentials& essentials);
	void writeJoystickFile(Essentials& essentials);
	
	void readDestCrossJoystickData(Essentials& essentials);
	void writeDestCrossJoystickFile(Essentials& essentials);
};

}

#endif //JOYSTICK_INPUT_DATA_H