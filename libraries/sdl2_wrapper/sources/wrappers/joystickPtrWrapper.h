#ifndef WRAPPERS_JOYSTICK_PTR_WRAPPER_H
#define WRAPPERS_JOYSTICK_PTR_WRAPPER_H

#include "SDL_joystick.h"
#include <memory>

namespace sdl2{
	struct JoystickDeleter{
		void operator()(SDL_Joystick* ptr) { if (ptr) SDL_JoystickClose(ptr); }
	};
	using JoystickPtr = std::unique_ptr<SDL_Joystick, JoystickDeleter>;
}

#endif //WRAPPERS_JOYSTICK_PTR_WRAPPER_H