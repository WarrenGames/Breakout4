#ifndef DUELS_PLAYERS_INPUTS_H
#define DUELS_PLAYERS_INPUTS_H

#include "duels/inGameObjects/playerInputs/inputsTypes.h"
#include "consts/duelsConstexpr.h"
#include "SDL_keycode.h"
#include "SDL_events.h"

struct AppLogFiles;
class PrefPathFinder;

namespace duels{

class PlayersInputs
{
private:
	bool isLoadingPerfect;
	bool escapeState;
	bool sdlQuitState;
	ReadyToUseInputs inputsData;

public:
	explicit PlayersInputs(AppLogFiles& logs, const PrefPathFinder& prefPath);
	~PlayersInputs() = default;
	PlayersInputs( const PlayersInputs& ) = delete;
	PlayersInputs& operator = ( const PlayersInputs& ) = delete;
	PlayersInputs( PlayersInputs&& ) = default;
	PlayersInputs& operator= ( PlayersInputs&& ) = default;
	
	bool wasLoadingPerfect() const;
	
	bool getInputState(unsigned playerNum, std::size_t index) const;
	bool getEscapeState() const;
	bool getSDLQuit() const;
	void setEscapeFalse();
	
	void updateEvents();
	void setInputAsMoveLeft(unsigned playerNum);
	void setInputAsMoveRight(unsigned playerNum);
	void setInputAsNotMoving(unsigned playerNum);
	
	void setInputState(unsigned playerNum, std::size_t index);
	
private:
	void keyboardInputHandle(SDL_Keycode keycode, bool valueToSet);
	void escapeKeyHandle(SDL_Keycode keycode, bool valueToSet);
	void playerKeyboardHandle(SDL_Keycode keycode, bool valueToSet);
	
	bool isThisTheGoodAxis(const SDL_Event& event, unsigned playerNum) const;
	void joystickAxisHandle(const SDL_Event& event, unsigned playerNum);
	
	bool isThisTheGoodHat(const SDL_Event& event, unsigned playerNum) const;
	void joystickHatsHandle(const SDL_Event& event, unsigned playerNum);
	void actWithHatValue(Uint8 hatValue, unsigned playerNum);
	
	bool isThisTheGoodButton(int joystickNumber, unsigned playerNum) const;
	void joystickButtonsHandle(int joystickNumber, Uint8 buttonNum, unsigned playerNum, bool valueToSet);
};

}

#endif //DUELS_PLAYERS_INPUTS_H