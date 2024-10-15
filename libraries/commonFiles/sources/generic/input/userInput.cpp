#include "generic/input/userInput.h"
#include "SDL_events.h"
#include <cassert>

input::MouseData::MouseData():
	mousePosition{0,0},
	buttonsState( 8, false ),
	wheelState{0}
{
	
}

input::KeyboardData::KeyboardData():
	keycodes{SDLK_ESCAPE, SDLK_RETURN, SDLK_SPACE, SDLK_DELETE, SDLK_F1, SDLK_F2, SDLK_F5, SDLK_F6},
	keysState(input::KeybMax, false)
{
	
}

void input::KeyboardData::updateKeyboard(SDL_Keycode& keycode, bool valueToSet)
{
	for( std::size_t i{0} ; i < keycodes.size() && i < keysState.size() ; ++i )
	{
		if( keycode == keycodes[i] )
		{
			keysState[i] = valueToSet;
		}
	}
}

input::User::User():
	mouse{},
	keyboard{},
	SDL_quit{false}
{
		
}

void input::User::updateEvents()
{
	SDL_Event event;
	mouse.wheelState = 0;
	while( SDL_PollEvent(&event) )
	{
		switch( event.type )
		{
			case SDL_QUIT:
				SDL_quit = true;
				break;
			case SDL_KEYDOWN:
				keyboard.updateKeyboard(event.key.keysym.sym, true);
				break;
			case SDL_KEYUP:
				keyboard.updateKeyboard(event.key.keysym.sym, false);
				break;
			case SDL_MOUSEMOTION:
				updateMousePosition( Offset{event.motion.x, event.motion.y} );
				break;
			case SDL_MOUSEBUTTONDOWN:
				updateMouseButtons(event.button.button, true);
				break;
			case SDL_MOUSEBUTTONUP:
				updateMouseButtons(event.button.button, false);
				break;
			case SDL_MOUSEWHEEL:
				mouse.wheelState = event.wheel.y;
				break;
		}
	}
}

void input::User::updateMousePosition(const Offset& offset)
{
	mouse.mousePosition = offset;
}

void input::User::updateMouseButtons(unsigned buttonNum, bool valueToSet)
{
	assert( buttonNum < mouse.buttonsState.size() );
	mouse.buttonsState[buttonNum] = valueToSet;
}

const Offset& input::User::getMousePosition() const
{
	return mouse.mousePosition;
}

bool input::User::getMouseButtonState(std::size_t buttonIndex) const
{
	assert( buttonIndex < mouse.buttonsState.size() );
	return mouse.buttonsState[buttonIndex];
}

int input::User::getWheelState() const
{
	return mouse.wheelState;
}

void input::User::setMouseButtonToFalse(std::size_t buttonIndex)
{
	assert( buttonIndex < mouse.buttonsState.size() );
	mouse.buttonsState[buttonIndex] = false;
}

void input::User::setKeyStateToFalse(std::size_t keyIndex)
{
	assert( keyIndex < keyboard.keysState.size() );
	keyboard.keysState[keyIndex] = false;
}

bool input::User::getKeyState(std::size_t keyIndex) const
{
	assert( keyIndex < keyboard.keysState.size() );
	return keyboard.keysState[keyIndex];
}

void input::User::setSDL_quitToFalse()
{
	SDL_quit = false;
}

bool input::User::getSDL_quit() const
{
	return SDL_quit;
}
