#ifndef SDL2_JOYSTICK_ENTITY_H
#define SDL2_JOYSTICK_ENTITY_H

#include "wrappers/joystickPtrWrapper.h"
#include "wrappers/hapticPtrWrapper.h"
#include <string>

namespace sdl2{

class JoystickEntity
{
private:
	sdl2::JoystickPtr joystickPtr;
	std::string loadingStatus;
	std::string joystickName;
	SDL_JoystickID joystickNumber;
	unsigned hatNumber;
	unsigned axisNumber;
	unsigned buttonsNumber;
	sdl2::HapticPtr hapticPtr;
	
public:
	explicit JoystickEntity(SDL_JoystickID joystickNum);
	~JoystickEntity() = default;
	JoystickEntity( const JoystickEntity& ) = delete;
	JoystickEntity& operator= ( const JoystickEntity& ) = delete;
	JoystickEntity( JoystickEntity&& ) = default;
	JoystickEntity& operator= ( JoystickEntity&& ) = default;
	operator bool () const;
	
	void loadJoystickData(SDL_JoystickID joystickNum);
	
	const std::string& getLoadingStatus() const;
	SDL_JoystickID getJoystickNumber() const;
	unsigned getHatsNumber() const;
	unsigned getAxesNumber() const;
	unsigned getButtonsNumber() const;
	const std::string& getName() const;
	
	void reset(SDL_JoystickID joystickNum);
	void initializeRumble();
	SDL_Haptic* getHapticPtr() const;
};

}

#endif //SDL2_JOYSTICK_ENTITY_H