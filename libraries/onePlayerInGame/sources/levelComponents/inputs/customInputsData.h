#ifndef CUSTOM_INPUTS_DATA_H
#define CUSTOM_INPUTS_DATA_H

#include "levelComponents/inputs/joystickInputData.h"
#include "customTypes/positionTypes.h"
#include "SDL_keycode.h"
#include <vector>

struct Essentials;

namespace onePlGame{

struct CustomInputData
{
	std::vector< SDL_Keycode > customKeys;
	onePlGame::JoystickInputData joystickConfig;
	unsigned crossDeviceUse;
	bool isLoadingPerfect;
	
	explicit CustomInputData(Essentials& essentials);
	~CustomInputData() = default;
	CustomInputData( const CustomInputData& ) = delete;
	CustomInputData& operator= ( const CustomInputData& ) = delete;
	CustomInputData( CustomInputData&& ) = default;
	CustomInputData& operator= ( CustomInputData&& ) = default;
	
	void readKeyboardFile(Essentials& essentials);
	void writeKeyboardFile(Essentials& essentials) const;
	
	void selectCrossMoveDevice();
};

}

#endif //CUSTOM_INPUTS_DATA_H