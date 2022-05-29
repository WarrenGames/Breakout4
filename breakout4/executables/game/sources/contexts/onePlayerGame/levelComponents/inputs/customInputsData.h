#ifndef CUSTOM_INPUTS_DATA_H
#define CUSTOM_INPUTS_DATA_H

#include "contexts/onePlayerGame/levelComponents/inputs/joystickInputData.h"
#include "customTypes/positionTypes.h"
#include "SDL.h"
#include <array>

struct Essentials;

namespace onePlGame{

struct CustomInputData
{
	bool isLoadingPerfect;
	unsigned crossDeviceUse;
	std::array< SDL_Keycode, onePlGame::INP_MAX> customKeys;
	onePlGame::JoystickInputData joystickData;
	
	explicit CustomInputData(Essentials& essentials);
	
	void readKeyboardFile(Essentials& essentials);
	void writeKeyboardFile(Essentials& essentials) const;
	
	void selectCrossMoveDevice();
};

}

#endif //CUSTOM_INPUTS_DATA_H