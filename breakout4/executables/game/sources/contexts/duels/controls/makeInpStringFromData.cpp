#include "contexts/duels/controls/makeInpStringFromData.h"
#include "texts/textLoader.h"
#include "contexts/duels/inGameObjects/playerInputs/inputsConsts.h"
#include "contexts/duels/inGameObjects/playerInputs/inputsTypes.h"
#include "contexts/duels/controls/inputScreenConsts.h"

std::string duels::getStringFromDeviceType(const std::unique_ptr< duels::InputEntity >& inpData, const TextsBlocks& langText)
{
	if( inpData )
	{
		switch( inpData->deviceType )
		{
			case duels::DEVICE_KEYBOARD:
				return langText[duels::TXT_KEYBOARD];
				break;
			case duels::DEVICE_JOYSTICK1:
				return std::string{ langText[duels::TXT_JOYSTICK] + "1"};
				break;
			case duels::DEVICE_JOYSTICK2:
				return std::string{ langText[duels::TXT_JOYSTICK] + "2"};
				break;
			default:
				return "Error";
				break;
		}
	}
	else{
		return "Allocation error";
	}
}

std::string duels::getStringFromLeftMove(const std::unique_ptr< duels::InputEntity >& inpData, const TextsBlocks& langText)
{
	if( inpData )
	{
		switch( inpData->deviceType )
		{
			case duels::DEVICE_KEYBOARD:
				return SDL_GetKeyName(inpData->keyboardInput[duels::KEY_LEFT]);
				break;
			case duels::DEVICE_JOYSTICK1:
				return duels::getStringFromJoystickMove(inpData, langText);
				break;
			case duels::DEVICE_JOYSTICK2:
				return duels::getStringFromJoystickMove(inpData, langText);
				break;
			default:
				return "Error";
				break;
		}
	}
	else{
		return "Allocation error";
	}
}

std::string duels::getStringFromRightMove(const std::unique_ptr< duels::InputEntity >& inpData, const TextsBlocks& langTexts)
{
	if( inpData )
	{
		switch( inpData->deviceType )
		{
			case duels::DEVICE_KEYBOARD:
				return SDL_GetKeyName(inpData->keyboardInput[duels::KEY_RIGHT]);
				break;
			case duels::DEVICE_JOYSTICK1:
				return duels::getStringFromJoystickMove(inpData, langTexts);
				break;
			case duels::DEVICE_JOYSTICK2:
				return duels::getStringFromJoystickMove(inpData, langTexts);
				break;
			default:
				return "Error";
				break;
		}
	}
	else{
		return "Allocation error";
	}
}

std::string duels::getStringFromActiveBonus(const std::unique_ptr< duels::InputEntity >& inpData, const TextsBlocks& langTexts)
{
	if( inpData )
	{
		switch( inpData->deviceType )
		{
			case duels::DEVICE_KEYBOARD:
				return SDL_GetKeyName(inpData->keyboardInput[duels::KEY_ACTIVBONUS]);
				break;
			case duels::DEVICE_JOYSTICK1:
				return std::string{ langTexts[duels::TXT_BUTTON_NUM] + std::to_string( static_cast<int>(inpData->joystick.buttons[duels::JOY_BTN_BONUS] + 1) ) };
				break;
			case duels::DEVICE_JOYSTICK2:
				return std::string{ langTexts[duels::TXT_BUTTON_NUM] + std::to_string( static_cast<int>(inpData->joystick.buttons[duels::JOY_BTN_BONUS] + 1) ) };
				break;
			default:
				return "Error";
				break;
		}
	}
	else{
		return "Allocation error";
	}
}

std::string duels::getStringFromZoneSpecific(const std::unique_ptr< duels::InputEntity >& inpData, const TextsBlocks& langTexts)
{
	if( inpData )
	{
		switch( inpData->deviceType )
		{
			case duels::DEVICE_KEYBOARD:
				return SDL_GetKeyName(inpData->keyboardInput[duels::KEY_SPE_ZONE]);
				break;
			case duels::DEVICE_JOYSTICK1:
				return std::string{ langTexts[duels::TXT_BUTTON_NUM] + std::to_string( static_cast<int>(inpData->joystick.buttons[duels::JOY_BTN_SPE_ZONE] + 1) ) };
				break;
			case duels::DEVICE_JOYSTICK2:
				return std::string{ langTexts[duels::TXT_BUTTON_NUM] + std::to_string( static_cast<int>(inpData->joystick.buttons[duels::JOY_BTN_SPE_ZONE] + 1) ) };
				break;
			default:
				return "Error";
				break;
		}
	}
	else{
		return "Allocation error";
	}
}

std::string duels::getStringFromJoystickMove(const std::unique_ptr< duels::InputEntity >& inpData, const TextsBlocks& langTexts)
{
	if( inpData )
	{
		switch( inpData->joystick.joyMoveType )
		{
			case duels::JOYMOV_AXES:
				return std::string{ langTexts[duels::TXT_AXIS_NUM] + std::to_string(inpData->joystick.axisOrHatNum + 1) };
				break;
			case duels::JOYMOV_HATS:
				return std::string{ langTexts[duels::TXT_HAT_NUM] + std::to_string(inpData->joystick.axisOrHatNum + 1) };
				break;
			default:
				return "Error";
				break;
		}
	}
	else{
		return "Allocation error";
	}
}
