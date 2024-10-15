#include "widgets/editBoxes/subObjects/boxEvents.h"
#include "SDL_events.h"
#include "SDL_rect.h"
#include <cassert>
#include <algorithm>

BoxEvents::BoxEvents():
	numbersState(BoxEventMax, false),
	specificKeys(BoxEventKeyMax, false),
	lowerCaseLetters(AlphaCaseNum, false),
	upperCaseLetters(AlphaCaseNum, false),
	mouseLeftButton{false},
	mousePosition{0,0}
{
	
}

void BoxEvents::updateEvents(bool& sdlQuit)
{
	bool capsLockState{ getCapsLockState() };
	SDL_Event ev;
	while(SDL_PollEvent(&ev) )
	{
		switch(ev.type)
		{
			case SDL_QUIT:
				sdlQuit = true;
				break;
			case SDL_KEYDOWN:
				fillKeyboardKeys(ev.key.keysym.sym, true, capsLockState);
				break;
			case SDL_KEYUP:
				fillKeyboardKeys(ev.key.keysym.sym, false, capsLockState);
				break;
			case SDL_MOUSEMOTION:
				mousePosition.x = ev.motion.x;
				mousePosition.y = ev.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				updateMouseButton(ev.button.button, true);
				break;
			case SDL_MOUSEBUTTONUP:
				updateMouseButton(ev.button.button, false);
				break;
		}
	}
}

void BoxEvents::fillKeyboardKeys(SDL_Keycode keycode, bool isPressed, bool isCapsLockActive)
{
	fillSpecificKeys(keycode, isPressed);
	fillFigureKeys(keycode, isPressed);
	fillLowerCaseKeys(keycode, isPressed, isCapsLockActive);
	fillUpperCaseKeys(keycode, isPressed, isCapsLockActive);
}

void BoxEvents::fillSpecificKeys(SDL_Keycode keycode, bool isPressed)
{
	if( keycode == SDLK_ESCAPE )
	{
		specificKeys[BoxEventEscape] = isPressed;
	}
	else if( keycode == SDLK_BACKSPACE )
	{
		specificKeys[BoxEventBackspace] = isPressed;
	}
	else if( keycode == SDLK_RETURN || keycode == SDLK_KP_ENTER )
	{
		specificKeys[BoxEventReturn] = isPressed;
	}
	else if( keycode == SDLK_MINUS || keycode == SDLK_KP_MINUS )
	{
		specificKeys[BoxEventMinus] = isPressed;
	}
	else if( keycode == SDLK_SPACE )
	{
		specificKeys[BoxEventSpacebar] = isPressed;
	}
	else if( keycode == SDLK_KP_PERIOD || keycode == SDLK_PERIOD )
	{
		specificKeys[BoxEventDot] = isPressed;
	}
}

void BoxEvents::fillFigureKeys(SDL_Keycode keycode, bool isPressed)
{
	if( keycode == SDLK_0 || keycode == SDLK_KP_0 )
		numbersState[0] = isPressed;
	else if( keycode == SDLK_1 || keycode == SDLK_KP_1 )
		numbersState[1] = isPressed;
	else if( keycode == SDLK_2 || keycode == SDLK_KP_2 )
		numbersState[2] = isPressed;
	else if( keycode == SDLK_3 || keycode == SDLK_KP_3 )
		numbersState[3] = isPressed;
	else if( keycode == SDLK_4 || keycode == SDLK_KP_4 )
		numbersState[4] = isPressed;
	else if( keycode == SDLK_5 || keycode == SDLK_KP_5 )
		numbersState[5] = isPressed;
	else if( keycode == SDLK_6 || keycode == SDLK_KP_6 )
		numbersState[6] = isPressed;
	else if( keycode == SDLK_7 || keycode == SDLK_KP_7 )
		numbersState[7] = isPressed;
	else if( keycode == SDLK_8 || keycode == SDLK_KP_8 )
		numbersState[8] = isPressed;
	else if( keycode == SDLK_9 || keycode == SDLK_KP_9 )
		numbersState[9] = isPressed;
}

void BoxEvents::fillLowerCaseKeys(SDL_Keycode keycode, bool isPressed, bool isCapsLockActive)
{
	if( false == isCapsLockActive )
	{
		if( keycode >= 'a' && keycode <= 'z' )
		{
			lowerCaseLetters[static_cast<std::size_t>(keycode - 'a')] = isPressed;
		}
	}
}

void BoxEvents::fillUpperCaseKeys(SDL_Keycode keycode, bool isPressed, bool isCapsLockActive)
{
	if( isCapsLockActive )
	{
		if( keycode >= 'a' && keycode <= 'z' )
		{
			upperCaseLetters[static_cast<std::size_t>(keycode - 'a')] = isPressed;
		}
	}
}	

void BoxEvents::updateMouseButton(unsigned buttonNumber, bool clicked)
{
	if( buttonNumber == SDL_BUTTON_LEFT )
		mouseLeftButton = clicked;
}

bool BoxEvents::getNumbersState(unsigned number) const
{
	assert( number < BoxEventMax );
	return numbersState[number];
}

void BoxEvents::setNumberKeyToFalse(unsigned number)
{
	assert( number < BoxEventMax );
	numbersState[number] = false;
}

bool BoxEvents::getSpecificKey(unsigned keyEnum) const
{
	assert( keyEnum < BoxEventKeyMax );
	return specificKeys[keyEnum];
}

void BoxEvents::setSpecificKeyToFalse(unsigned keyEnum)
{
	assert( keyEnum < BoxEventKeyMax );
	specificKeys[keyEnum] = false;
}

bool BoxEvents::getLowerCaseState(char letter) const
{
	assert( letter >= 'a' && letter <= 'z' );
	return lowerCaseLetters[static_cast<std::size_t>(letter - 'a')];
}

void BoxEvents::setLowerCaseStateToFalse(char letter)
{
	assert( letter >= 'a' && letter <= 'z' );
	lowerCaseLetters[static_cast<std::size_t>(letter - 'a')] = false;
}
	
bool BoxEvents::getUpperCaseState(char letter) const
{
	assert( letter >= 'A' && letter <= 'Z' );
	return upperCaseLetters[static_cast<std::size_t>(letter - 'A')];
}

void BoxEvents::setUpperCaseStateToFalse(char letter)
{
	assert( letter >= 'A' && letter <= 'Z' );
	upperCaseLetters[static_cast<std::size_t>(letter - 'A')] = false;
}
bool BoxEvents::getMouseLeftButtonState() const
{
	return mouseLeftButton;
}

void BoxEvents::setMouseLeftButtonToFalse()
{
	mouseLeftButton = false;
}

const Offset& BoxEvents::getMousePosition() const
{
	return mousePosition;
}

void BoxEvents::resetAllKeys()
{
	std::fill( std::begin(lowerCaseLetters), std::end(lowerCaseLetters), false);
	std::fill( std::begin(upperCaseLetters), std::end(upperCaseLetters), false);
	
	std::fill( std::begin( numbersState ), std::end( numbersState ), false );
	std::fill( std::begin( specificKeys ), std::end( specificKeys ), false );
}

bool BoxEvents::getCapsLockState()
{
	SDL_Keymod temp = SDL_GetModState();
	return (temp & KMOD_CAPS) == KMOD_CAPS;
}

bool isUserMouseInBox(const SDL_Rect& boxRect, const Offset& mousePosition)
{
	return mousePosition.x >= boxRect.x && mousePosition.x < boxRect.x + boxRect.w && mousePosition.y >= boxRect.y && mousePosition.y < boxRect.y + boxRect.h;
}

bool isOnlyMinusCharInSintString(const std::string& stringOfValue)
{
	return stringOfValue.size() == 1 && stringOfValue[0] == '-';
}