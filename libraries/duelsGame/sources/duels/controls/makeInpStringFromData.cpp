#include "duels/controls/makeInpStringFromData.h"
#include "texts/textLoader.h"
#include "duels/inGameObjects/playerInputs/inputsConsts.h"
#include "duels/inGameObjects/playerInputs/inputsTypes.h"
#include "duels/controls/inputScreenConsts.h"
#include "SDL_keyboard.h"

std::string duels::getStringFromDeviceType(const std::unique_ptr< duels::InputEntity >& inpData, const TextsBlocks& langText)
{
	if( inpData )
	{
		switch( inpData->deviceType )
		{
			case duels::DeviceKeyboard:
				return langText[duels::TextKeyboard];
				break;
			case duels::DeviceJoystick1:
				return std::string{ langText[duels::TextJoystick] + "1"};
				break;
			case duels::DeviceJoystick2:
				return std::string{ langText[duels::TextJoystick] + "2"};
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
			case duels::DeviceKeyboard:
				return SDL_GetKeyName(inpData->keyboardInput[duels::KeyLeft]);
				break;
			case duels::DeviceJoystick1:
				return duels::getStringFromJoystickMove(inpData, langText);
				break;
			case duels::DeviceJoystick2:
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
			case duels::DeviceKeyboard:
				return SDL_GetKeyName(inpData->keyboardInput[duels::KeyRight]);
				break;
			case duels::DeviceJoystick1:
				return duels::getStringFromJoystickMove(inpData, langTexts);
				break;
			case duels::DeviceJoystick2:
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
			case duels::DeviceKeyboard:
				return SDL_GetKeyName(inpData->keyboardInput[duels::KeyActiveBonus]);
				break;
			case duels::DeviceJoystick1:
				return std::string{ langTexts[duels::TextButtonNumber] + std::to_string( static_cast<int>(inpData->joystick.buttons[duels::JoystickBonusButton] + 1) ) };
				break;
			case duels::DeviceJoystick2:
				return std::string{ langTexts[duels::TextButtonNumber] + std::to_string( static_cast<int>(inpData->joystick.buttons[duels::JoystickBonusButton] + 1) ) };
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
			case duels::DeviceKeyboard:
				return SDL_GetKeyName(inpData->keyboardInput[duels::KeyZoneSpecific]);
				break;
			case duels::DeviceJoystick1:
				return std::string{ langTexts[duels::TextButtonNumber] + std::to_string( static_cast<int>(inpData->joystick.buttons[duels::JoystickZoneSpecificButton] + 1) ) };
				break;
			case duels::DeviceJoystick2:
				return std::string{ langTexts[duels::TextButtonNumber] + std::to_string( static_cast<int>(inpData->joystick.buttons[duels::JoystickZoneSpecificButton] + 1) ) };
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
			case duels::JoystickMoveAxes:
				return std::string{ langTexts[duels::TextAxisNumber] + std::to_string(inpData->joystick.axisOrHatNum + 1) };
				break;
			case duels::JoystickMoveHats:
				return std::string{ langTexts[duels::TextHatNumber] + std::to_string(inpData->joystick.axisOrHatNum + 1) };
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
