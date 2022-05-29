#include "joystick/joystickEntity.h"

sdl2::JoystickEntity::JoystickEntity( SDL_JoystickID joystickNumber ):
	joystick_{ SDL_JoystickOpen(joystickNumber) },
	joystickNumber_{ joystickNumber },
	hatNumber_{0},
	axisNumber_{0},
	buttonsNumber_{0},
	haptic_{ SDL_HapticOpenFromJoystick( joystick_.get() ) }
{
	loadJoystickData(joystickNumber);
	initializeRumble();
}

sdl2::JoystickEntity::operator bool() const
{
	return joystick_.get() != nullptr;
}

void sdl2::JoystickEntity::loadJoystickData(SDL_JoystickID joystickNumber)
{
	if( joystick_ )
	{
		hatNumber_ = SDL_JoystickNumHats(joystick_.get());
		axisNumber_ = SDL_JoystickNumAxes(joystick_.get());
		buttonsNumber_ = SDL_JoystickNumButtons(joystick_.get());
		joystickName_ = SDL_JoystickName(joystick_.get());
		loadingStatus_ = "The joystick #" + std::to_string( joystickNumber) + " was loaded pefectly."; 
	}
	else{
		loadingStatus_ = "Error while loading joystick number " + std::to_string(joystickNumber) + " : " + SDL_GetError();
	}
}

const std::string& sdl2::JoystickEntity::getLoadingStatus() const
{
	return loadingStatus_;
}

SDL_JoystickID sdl2::JoystickEntity::getJoystickNumber() const
{
	return joystickNumber_;
}

unsigned sdl2::JoystickEntity::getHatsNumber() const
{
	return hatNumber_;
}

unsigned sdl2::JoystickEntity::getAxesNumber() const
{
	return axisNumber_;
}

unsigned sdl2::JoystickEntity::getButtonsNumber() const
{
	return buttonsNumber_;
}

const std::string& sdl2::JoystickEntity::getName() const
{
	return joystickName_;
}

void sdl2::JoystickEntity::reset(SDL_JoystickID joystickNumber)
{
	joystick_.reset( SDL_JoystickOpen(joystickNumber) );
	haptic_.reset( SDL_HapticOpenFromJoystick( joystick_.get() ) );
	loadJoystickData(joystickNumber);
}

void sdl2::JoystickEntity::initializeRumble()
{
	if( haptic_ )
	{
		SDL_HapticRumbleInit(haptic_.get());
	}
}

SDL_Haptic* sdl2::JoystickEntity::getHapticPtr() const
{
	return haptic_.get();
}