#ifndef BOX_EVENTS_H
#define BOX_EVENTS_H

#include "customTypes/positionTypes.h"
#include "SDL_keycode.h"
#include <string>
#include <vector>

enum{BoxEvent_0, BoxEvent_1, BoxEvent_2, BoxEvent_3, BoxEvent_4, BoxEvent_5, BoxEvent_6, BoxEvent_7, BoxEvent_8, BoxEvent_9, BoxEventMax};

enum{BoxEventEscape, BoxEventBackspace, BoxEventReturn, BoxEventMinus, BoxEventSpacebar, BoxEventDot, BoxEventKeyMax };

constexpr std::size_t AlphaCaseNum = 'z' - 'a' + 1;

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