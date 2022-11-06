#include "keycodes/keycodesOverload.h"
#include "SDL_keyboard.h"

std::string getNameFromKeycode(SDL_Keycode keycode)
{
	if( keycode == SDLK_UNKNOWN )
		return std::string{"No key assigned"};
	else
		return std::string{ SDL_GetKeyName(keycode) };
}