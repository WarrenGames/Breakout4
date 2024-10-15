#include "levelComponents/inputs/customInputsData.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "types/essentialsStruct.h"
#include <fstream>
#include <cassert>

onePlGame::CustomInputData::CustomInputData(Essentials& essentials):
	customKeys{ SDLK_LEFT, SDLK_RIGHT, SDLK_SPACE, SDLK_TAB, SDLK_LSHIFT },
	joystickConfig{essentials},
	crossDeviceUse{ onePlGame::CrossDeviceIsJoystick },
	isLoadingPerfect{ true }
{
	readKeyboardFile(essentials);
	selectCrossMoveDevice();
	
	assert( customKeys.size() == onePlGame::InputMax );
}

void onePlGame::CustomInputData::readKeyboardFile(Essentials& essentials)
{
	if( std::ifstream keybFile{ path::getConfigDirFile(essentials.prefPath, file::OnePlayerKeyboardInitialization) } )
	{
		for( auto &keycode : customKeys )
		{
			if( !( keybFile >> keycode ) )
			{
				essentials.logs.error << "Error: reading failed in '" << path::getConfigDirFile(essentials.prefPath, file::OnePlayerKeyboardInitialization) << "' file (keyboard configuration.\n";
				isLoadingPerfect = false;
			}
		}
	}
	else{
		essentials.logs.error << "Error: couldn't open '" << path::getConfigDirFile(essentials.prefPath, file::OnePlayerKeyboardInitialization) << "' file in order to read keyboard configuration.\n";
		isLoadingPerfect = false;
	}
}

void onePlGame::CustomInputData::writeKeyboardFile(Essentials& essentials) const
{
	if( std::ofstream keybFile{ path::getConfigDirFile(essentials.prefPath, file::OnePlayerKeyboardInitialization) } )
	{
		essentials.logs.error << "Opening '" << path::getConfigDirFile(essentials.prefPath, file::OnePlayerKeyboardInitialization) << "' file to save one player game keyboard config data.\n";
		for( auto const &keycode : customKeys )
		{
			if( !( keybFile << keycode << " " ) )
			{
				essentials.logs.error << "Error: couldn't write keycode data of 1 player game in '" << path::getConfigDirFile(essentials.prefPath, file::OnePlayerKeyboardInitialization) << "' file.\n";
			}
		}
	}
	else{
		essentials.logs.error << "Error: couldn't open '" << path::getConfigDirFile(essentials.prefPath, file::OnePlayerKeyboardInitialization) << "' file in order to write keyboard configuration.\n";
	}
}

void onePlGame::CustomInputData::selectCrossMoveDevice()
{
	if( joystickConfig.joyEnt )
	{
		crossDeviceUse = onePlGame::CrossDeviceIsJoystick;
	}
	else{
		crossDeviceUse = onePlGame::CrossDeviceIsMouse;
	}
}