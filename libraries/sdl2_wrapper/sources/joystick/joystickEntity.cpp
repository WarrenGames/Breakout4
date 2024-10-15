#include "joystick/joystickEntity.h"

sdl2::JoystickEntity::JoystickEntity( SDL_JoystickID joystickNum ):
	joystickPtr{ SDL_JoystickOpen(joystickNum) },
	joystickNumber{ joystickNum },
	hatNumber{0},
	axisNumber{0},
	buttonsNumber{0},
	hapticPtr{ SDL_HapticOpenFromJoystick( joystickPtr.get() ) }
{
	loadJoystickData(joystickNum);
	initializeRumble();
}

sdl2::JoystickEntity::operator bool() const
{
	return joystickPtr.get() != nullptr;
}

void sdl2::JoystickEntity::loadJoystickData(SDL_JoystickID joystickNum)
{
	if( joystickPtr )
	{
		hatNumber = static_cast<unsigned>( SDL_JoystickNumHats(joystickPtr.get() ) );
		axisNumber = static_cast<unsigned>( SDL_JoystickNumAxes(joystickPtr.get() ) );
		buttonsNumber = static_cast<unsigned>( SDL_JoystickNumButtons(joystickPtr.get() ) );
		joystickName = SDL_JoystickName(joystickPtr.get());
		loadingStatus = "The joystick #" + std::to_string( joystickNum) + " was loaded pefectly."; 
	}
	else{
		loadingStatus = "Error while loading joystick number " + std::to_string(joystickNum) + " : " + SDL_GetError();
	}
}

const std::string& sdl2::JoystickEntity::getLoadingStatus() const
{
	return loadingStatus;
}

SDL_JoystickID sdl2::JoystickEntity::getJoystickNumber() const
{
	return joystickNumber;
}

unsigned sdl2::JoystickEntity::getHatsNumber() const
{
	return hatNumber;
}

unsigned sdl2::JoystickEntity::getAxesNumber() const
{
	return axisNumber;
}

unsigned sdl2::JoystickEntity::getButtonsNumber() const
{
	return buttonsNumber;
}

const std::string& sdl2::JoystickEntity::getName() const
{
	return joystickName;
}

void sdl2::JoystickEntity::reset(SDL_JoystickID joystickNum)
{
	joystickPtr.reset( SDL_JoystickOpen(joystickNum) );
	hapticPtr.reset( SDL_HapticOpenFromJoystick( joystickPtr.get() ) );
	loadJoystickData(joystickNum);
}

void sdl2::JoystickEntity::initializeRumble()
{
	if( hapticPtr )
	{
		SDL_HapticRumbleInit(hapticPtr.get());
	}
}

SDL_Haptic* sdl2::JoystickEntity::getHapticPtr() const
{
	return hapticPtr.get();
}