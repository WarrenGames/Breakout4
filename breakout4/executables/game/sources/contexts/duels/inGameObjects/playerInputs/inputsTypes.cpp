#include "contexts/duels/inGameObjects/playerInputs/inputsTypes.h"
#include "contexts/duels/inGameObjects/playerInputs/loadInputConfig.h"
#include <cassert>

duels::JoystickFileData::JoystickFileData():
	joystickNumber{0},
	joyMoveType{0},
	axisOrHatNum{0},
	axisMoveThreshold{0},
	buttons(duels::JOY_BTN_MAX, 0)
{
	
}

duels::JoystickInp::JoystickInp( const JoystickFileData& joyFileData ):
	joyNum{ static_cast<Uint8>(joyFileData.joystickNumber) },
	joyMoveType{ joyFileData.joyMoveType },
	axisOrHatNum{ static_cast<Uint8>(joyFileData.axisOrHatNum) },
	axisMoveThreshold{ static_cast<Sint16>(joyFileData.axisMoveThreshold) },
	buttons{static_cast<Uint8>(joyFileData.buttons[0]), static_cast<Uint8>(joyFileData.buttons[1]) }
{
	
}

duels::InputEntity::InputEntity(unsigned devType, const std::vector<SDL_Keycode>& keybInp, const duels::JoystickFileData& joyInfos):
	deviceType{ devType },
	inputEffective(INP_MAX, false),
	keyboardInput{ keybInp },
	joystick{ joyInfos }
{
	assert( keyboardInput.size() == KEY_MAX );
}

duels::ReadyToUseInputs::ReadyToUseInputs(AppLogFiles& logs, const PrefPathFinder& prefPath):
	playerEnt( duels::PLAYER_MAX ),
	isLoadingPerfect{true}
{
	openedJoysticks.emplace_back( sdl2::JoystickEntity{0} );
	openedJoysticks.emplace_back( sdl2::JoystickEntity{1} );
	if( !( duels::loadInputEntity(logs, prefPath, duels::PLAYER_BLUE, playerEnt[duels::PLAYER_BLUE]) 
		&& duels::loadInputEntity(logs, prefPath, duels::PLAYER_RED, playerEnt[duels::PLAYER_RED]) ) )
	{
		isLoadingPerfect = false;
	}
	setJoystickNumWithDeviceType();
}

void duels::ReadyToUseInputs::saveDataToFile(AppLogFiles& logs, const PrefPathFinder& prefPath)
{
	for(unsigned player{0} ; player < duels::PLAYER_MAX ; ++player )
		duels::saveInputData(logs, prefPath, player, playerEnt[player]);
}

void duels::ReadyToUseInputs::setJoystickNumWithDeviceType()
{
	for( auto &inp : playerEnt )
	{
		if( inp )
		{
			if( inp->deviceType == duels::DEVICE_JOYSTICK1 )
				inp->joystick.joyNum = 0;
			else if( inp->deviceType == duels::DEVICE_JOYSTICK2 )
				inp->joystick.joyNum = 1;
		}
	}
}