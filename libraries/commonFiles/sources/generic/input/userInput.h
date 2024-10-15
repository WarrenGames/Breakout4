#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "customTypes/positionTypes.h"
#include "SDL_keycode.h"
#include <vector>

namespace input{

struct MouseData
{
	Offset mousePosition;
	std::vector< bool > buttonsState;
	int wheelState;
	
	explicit MouseData();
	~MouseData() = default;
	MouseData( const MouseData& ) = default;
	MouseData& operator= ( const MouseData& ) = default;
};

enum{KeybOut, KeybReturn, KeybSpace, KeybDelete, KeybMainPrevious, KeybMainNext, KeybSubPrevious, KeybSubNext, KeybMax};

struct KeyboardData
{
	std::vector< SDL_Keycode > keycodes;
	std::vector< bool > keysState;
	
	explicit KeyboardData();
	~KeyboardData() = default;
	KeyboardData( const KeyboardData& ) = default;
	KeyboardData& operator= ( const KeyboardData& ) = default;
	void updateKeyboard(SDL_Keycode& keycode, bool valueToSet);
};

class User
{	
private:
	input::MouseData mouse;
	input::KeyboardData keyboard;
	bool SDL_quit;

public:
	User();
	~User() = default;
	User( const User& ) = delete;
	User& operator= ( const User& ) = delete;
	User( User&& ) = default;
	User& operator= ( User&& ) = default;
	
	void updateEvents();

private:
	void updateMousePosition(const Offset& offset);
	void updateMouseButtons(unsigned buttonNum, bool valueToSet);

public:
	const Offset& getMousePosition() const;
	bool getMouseButtonState(std::size_t buttonIndex) const;
	int getWheelState() const;
	void setMouseButtonToFalse(std::size_t buttonIndex);
	
	void setKeyStateToFalse(std::size_t keyIndex);
	bool getKeyState(std::size_t keyIndex) const;
	
	void setSDL_quitToFalse();
	bool getSDL_quit() const;
};

}

#endif //USER_INPUT_H