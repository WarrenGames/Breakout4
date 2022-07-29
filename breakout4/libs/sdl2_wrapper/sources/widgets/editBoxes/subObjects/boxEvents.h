#ifndef BOX_EVENTS_H
#define BOX_EVENTS_H

#include "customTypes/positionTypes.h"
#include "SDL_keycode.h"
#include <string>
#include <vector>

enum{BOX_EV_0, BOX_EV_1, BOX_EV_2, BOX_EV_3, BOX_EV_4, BOX_EV_5, BOX_EV_6, BOX_EV_7, BOX_EV_8, BOX_EV_9, BOX_EV_MAX};

enum{BOX_EV_ESCAPE, BOX_EV_BACKSPACE, BOX_EV_RETURN, BOX_EV_MINUS, BOX_EV_SPACEBAR, BOX_EV_DOT, BOX_EV_KEY_MAX};

constexpr std::size_t ALPHA_CASE_NUM = 'z' - 'a';

struct SDL_Rect;

class BoxEvents
{
private:
	std::vector<bool> numbersState;
	std::vector<bool> specificKeys;
	std::vector<bool> lowerCaseLetters;
	std::vector<bool> upperCaseLetters;
	
	bool mouseLeftButton;
	Offset mousePosition;
	
public:
	BoxEvents();
	~BoxEvents() = default;
	
	BoxEvents( const BoxEvents& ) = delete;
	BoxEvents& operator= ( const BoxEvents& ) = delete;
	
	BoxEvents( BoxEvents&& ) = default;
	BoxEvents& operator= ( BoxEvents&& ) = default;
	
	void updateEvents(bool& sdlQuit);
	void fillKeyboardKeys(SDL_Keycode keycode, bool isPressed, bool isCapsLockActive);
	void fillSpecificKeys(SDL_Keycode keycode, bool isPressed);
	void fillFigureKeys(SDL_Keycode keycode, bool isPressed);
	void fillLowerCaseKeys(SDL_Keycode keycode, bool isPressed, bool isCapsLockActive);
	void fillUpperCaseKeys(SDL_Keycode keycode, bool isPressed, bool isCapsLockActive);
	void updateMouseButton(unsigned buttonNumber, bool clicked);
	
	bool getNumbersState(unsigned number) const;
	void setNumberKeyToFalse(unsigned number);
	
	bool getSpecificKey(unsigned keyEnum) const;
	void setSpecificKeyToFalse(unsigned keyEnum);
	
	bool getLowerCaseState(char letter) const;
	void setLowerCaseStateToFalse(char letter);
	
	bool getUpperCaseState(char letter) const;
	void setUpperCaseStateToFalse(char letter);
	
	bool getMouseLeftButtonState() const;
	void setMouseLeftButtonToFalse();
	const Offset& getMousePosition() const;
	
	void resetAllKeys();
	
	bool getCapsLockState();
};

bool isUserMouseInBox(const SDL_Rect& boxRect, const Offset& mousePosition);

bool isOnlyMinusCharInSintString(const std::string& stringOfValue);
#endif //BOX_EVENTS_H