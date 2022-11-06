#ifndef CUSTOM_INPUTS_DATA_H
#define CUSTOM_INPUTS_DATA_H

#include "contexts/onePlayerGame/levelComponents/inputs/joystickInputData.h"
#include "customTypes/positionTypes.h"
#include "SDL_keycode.h"
#include <vector>

struct Essentials;

namespace onePlGame{

struct CustomInputData
{
	bool isLoadingPerfect;
	unsigned crossDeviceUse;
	std::vector< SDL_Keycode > customKeys;
	onePlGame::JoystickInputData joystickData;
	
	explicit CustomInputData(Essentials& essentials);
	
	void readKeyboardFile(Essentials& essentials);
	void writeKeyboardFile(Essentials& essentials) const;
	
	void selectCrossMoveDevice();
};

}

#endif //CUSTOM_INPUTS_DATA_H