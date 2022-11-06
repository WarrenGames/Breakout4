#include "contexts/onePlayerGame/levelComponents/inputs/customInputsData.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "types/essentialsStruct.h"
#include <fstream>
#include <cassert>

onePlGame::CustomInputData::CustomInputData(Essentials& essentials):
	isLoadingPerfect{ true },
	crossDeviceUse{ onePlGame::CrossDeviceIsJoystick },
	customKeys{ SDLK_LEFT, SDLK_RIGHT, SDLK_SPACE, SDLK_TAB, SDLK_LSHIFT },
	joystickData{essentials}
{
	readKeyboardFile(essentials);
	selectCrossMoveDevice();
	
	assert( customKeys.size() == onePlGame::InputMax );
}

void onePlGame::CustomInputData::readKeyboardFile(Essentials& essentials)
{
	if( std::ifstream keybFile{ path::getConfigDirFile(essentials.prefPath, file::ONE_PLAY_KEYB_INI) } )
	{
		for( auto &keycode : customKeys )
		{
			if( !( keybFile >> keycode ) )
			{
				essentials.logs.error << "Error: reading failed in '" << path::getConfigDirFile(essentials.prefPath, file::ONE_PLAY_KEYB_INI) << "' file (keyboard configuration.\n";
				isLoadingPerfect = false;
			}
		}
	}
	else{
		essentials.logs.error << "Error: couldn't open '" << path::getConfigDirFile(essentials.prefPath, file::ONE_PLAY_KEYB_INI) << "' file in order to read keyboard configuration.\n";
		isLoadingPerfect = false;
	}
}

void onePlGame::CustomInputData::writeKeyboardFile(Essentials& essentials) const
{
	if( std::ofstream keybFile{ path::getConfigDirFile(essentials.prefPath, file::ONE_PLAY_KEYB_INI) } )
	{
		essentials.logs.error << "Opening '" << path::getConfigDirFile(essentials.prefPath, file::ONE_PLAY_KEYB_INI) << "' file to save one player game keyboard config data.\n";
		for( auto const &keycode : customKeys )
		{
			if( !( keybFile << keycode << " " ) )
			{
				essentials.logs.error << "Error: couldn't write keycode data of 1 player game in '" << path::getConfigDirFile(essentials.prefPath, file::ONE_PLAY_KEYB_INI) << "' file.\n";
			}
		}
	}
	else{
		essentials.logs.error << "Error: couldn't open '" << path::getConfigDirFile(essentials.prefPath, file::ONE_PLAY_KEYB_INI) << "' file in order to write keyboard configuration.\n";
	}
}

void onePlGame::CustomInputData::selectCrossMoveDevice()
{
	if( joystickData.joystickEntity )
	{
		crossDeviceUse = onePlGame::CrossDeviceIsJoystick;
	}
	else{
		crossDeviceUse = onePlGame::CrossDeviceIsMouse;
	}
}