/*
The Keyboard config data is located in: 
 * 'prefPath'/The games of the warren/Breakout 4/config/duelsKeyboard1.ini for Blue player
 * 'prefPath'/The games of the warren/Breakout 4/config/duelsKeyboard2.ini for Red player
The joystick config data is located in:
 * 'prefPath'/The games of the warren/Breakout 4/config/duelsJoystick1.ini for Blue player
 * 'prefPath'/The games of the warren/Breakout 4/config/duelsJoystick2.ini for Red player
The Device choice is located in:
 * 'prefPath'/The games of the warren/Breakout 4/config/duelsDevice1.ini for Blue player
 * 'prefPath'/The games of the warren/Breakout 4/config/duelsDevice2.ini for Red player
*/

#include "duels/inGameObjects/playerInputs/loadInputConfig.h"
#include "prefPath/prefPathFinder.h"
#include "logging/logsStruct.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/duelsConstexpr.h"
#include <cassert>

bool duels::loadInputEntity(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned playerNum, std::unique_ptr<InputEntity>& inputPtr)
{
	assert( playerNum < PlayerMax );
	JoystickFileData joyFileData{};
	std::vector<SDL_Keycode> keybData(KeyMax, SDLK_UNKNOWN);
	unsigned deviceType{DeviceKeyboard};
	
	if( duels::loadDeviceType(logs, prefPath, playerNum, deviceType) && duels::loadKeyboardData(logs, prefPath, playerNum, keybData) 
		&& duels::loadJoystickData(logs, prefPath, playerNum, joyFileData) )
	{
		return duels::areInputRessourcesAllocated(logs, deviceType, keybData, joyFileData, inputPtr);
	}
	else{
		logs.error << "Error: the player input data for duels couldn't be loaded properly.\n";
		return false;
	}
}

bool duels::areInputRessourcesAllocated(AppLogFiles& logs, unsigned deviceType, const std::vector<SDL_Keycode>& keybData, const JoystickFileData& joyFileData, 
										std::unique_ptr<InputEntity>& inputPtr)
{
	inputPtr.reset( new InputEntity{deviceType, keybData, joyFileData} );
	if( inputPtr )
	{
		logs.warning << "  The players input data was perfectly loaded in configurations files.\n";
		return true;
	}
	else{
		logs.error << "Error: the input data couldn't be allocated, sorry.\n";
		return false;
	}
}

bool duels::loadDeviceType(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned playerNum, unsigned& deviceType)
{
	if( std::ifstream deviceFile{ path::getDeviceConfigFile(prefPath, playerNum) } )
	{
		return isDeviceTypeRead(logs, prefPath, playerNum, deviceType, deviceFile);
	}
	else{
		logs.error << "Error: couldn't open '" << path::getDeviceConfigFile(prefPath, playerNum) << "' file in order to read device type for duels players.\n";
		return false;
	}
}

bool duels::isDeviceTypeRead(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned playerNum, unsigned& deviceType, std::ifstream& deviceFile)
{
	if( deviceFile >> deviceType )
	{
		return true;
	}
	else{
		logs.error << "Error: couldn't read '" << path::getDeviceConfigFile(prefPath, playerNum) << "' file in order to load device type for duels players.\n";
		return false;
	}
}

bool duels::loadKeyboardData(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned playerNum, std::vector<SDL_Keycode>& keybData)
{
	if( std::ifstream keybFile{ path::getKeyboardConfigFile(prefPath, playerNum) } )
	{
		return duels::areKeyboardDataRead(logs, prefPath, playerNum, keybData, keybFile);
	}
	else{
		logs.error << "Error: couldn't open '" << path::getKeyboardConfigFile(prefPath, playerNum) << "' file in order to read keycodes values.\n";
		return false;
	}
}

bool duels::areKeyboardDataRead(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned playerNum, std::vector<SDL_Keycode>& keybData, std::ifstream& keybFile)
{
	for( auto &keycode : keybData )
	{
		if( !(keybFile >> keycode ) )
		{
			logs.error << "Error: couldn't read data of '" << path::getKeyboardConfigFile(prefPath, playerNum) << "' file for duels.\n";
			return false;
		}
	}
	return true;
}

bool duels::loadJoystickData(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned playerNum, JoystickFileData& joyData)
{
	if( std::ifstream joystickFile{ path::getJoystickConfigFile(prefPath, playerNum) } )
	{
		return duels::areJoystickDataRead(logs, prefPath, playerNum, joyData, joystickFile);
	}
	else{
		logs.error << "Error: couldn't open '" << path::getJoystickConfigFile(prefPath, playerNum) << "' file in order to read joystick data.\n";
		return false;
	}
}

bool duels::areJoystickDataRead(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned playerNum, JoystickFileData& joyData, std::ifstream& joystickFile)
{
	if( joystickFile >> joyData.joystickNumber >> joyData.joyMoveType >> joyData.axisOrHatNum >> joyData.axisMoveThreshold >> joyData.buttons[0] >> joyData.buttons[1] )
	{
		return true;
	}
	else{
		logs.error << "Error: couldn't read joystick data in '" << path::getJoystickConfigFile(prefPath, playerNum) << "' file for duels inputs.\n";
		return false;
	}
}

void duels::saveInputData(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned playerNum, const std::unique_ptr<duels::InputEntity>& inputPtr)
{
	if( inputPtr )
	{
		duels::saveDeviceData(logs, prefPath, playerNum, inputPtr->deviceType);
		duels::saveKeyboardData(logs, prefPath, playerNum, inputPtr);
		duels::saveJoystickData(logs, prefPath, playerNum, inputPtr);
	}
}

void duels::saveDeviceData(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned playerNum, unsigned deviceType)
{
	if( std::ofstream deviceFile{ path::getDeviceConfigFile(prefPath, playerNum) } )
	{
		deviceFile << deviceType << std::endl;
	}
	else{
		logs.error << "Error: couldn't open the device file: " << path::getDeviceConfigFile(prefPath, playerNum) << " to save the device type of the player number " << playerNum << " .\n";
	}
}

void duels::saveKeyboardData(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned playerNum, const std::unique_ptr<duels::InputEntity>& inputPtr)
{
	if( std::ofstream keyboardFile{ path::getKeyboardConfigFile(prefPath, playerNum) } )
	{
		for( auto const &keycode : inputPtr->keyboardInput )
		{
			keyboardFile << keycode << " ";
		}
	}
	else{
		logs.error << "Error: couldn't open the following keyboard config file for duels: " << path::getKeyboardConfigFile(prefPath, playerNum) << " .\n";
	}
}

void duels::saveJoystickData(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned playerNum, const std::unique_ptr<duels::InputEntity>& inputPtr)
{
	if( std::ofstream joystickFile{ path::getJoystickConfigFile(prefPath, playerNum) } )
	{
		joystickFile << static_cast<unsigned>(inputPtr->joystick.joyNum) << " "
					 << static_cast<unsigned>(inputPtr->joystick.joyMoveType) << " "
					 << static_cast<unsigned>(inputPtr->joystick.axisOrHatNum) << " "
					 << static_cast<int>(inputPtr->joystick.axisMoveThreshold) << " "
					 << static_cast<unsigned>(inputPtr->joystick.buttons[0]) << " "
					 << static_cast<unsigned>(inputPtr->joystick.buttons[1]) << " " << std::endl;
	}
	else{
		logs.error << "Error: couldn't open the following joystick config file for duels: " << path::getJoystickConfigFile(prefPath, playerNum) << " .\n";
	}
}
