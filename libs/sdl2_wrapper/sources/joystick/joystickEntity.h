#ifndef SDL2_JOYSTICK_ENTITY_H
#define SDL2_JOYSTICK_ENTITY_H

#include "wrappers/sdl2_ptr.h"
#include <string>

namespace sdl2{

class JoystickEntity
{
private:
	sdl2::JoystickPtr joystick_;
	std::string loadingStatus_;
	std::string joystickName_;
	SDL_JoystickID joystickNumber_;
	unsigned hatNumber_;
	unsigned axisNumber_;
	unsigned buttonsNumber_;
	sdl2::HapticPtr haptic_;
	
public:
	explicit JoystickEntity( SDL_JoystickID joystickNumber );
	~JoystickEntity() = default;
	JoystickEntity( const JoystickEntity& ) = delete;
	JoystickEntity& operator= ( const JoystickEntity& ) = delete;
	JoystickEntity( JoystickEntity&& ) = default;
	JoystickEntity& operator= ( JoystickEntity&& ) = default;
	operator bool () const;
	
	void loadJoystickData(SDL_JoystickID joystickNumber);
	
	const std::string& getLoadingStatus() const;
	SDL_JoystickID getJoystickNumber() const;
	unsigned getHatsNumber() const;
	unsigned getAxesNumber() const;
	unsigned getButtonsNumber() const;
	const std::string& getName() const;
	
	void reset(SDL_JoystickID joystickNumber);
	void initializeRumble();
	SDL_Haptic* getHapticPtr() const;
};

}

#endif //SDL2_JOYSTICK_ENTITY_H