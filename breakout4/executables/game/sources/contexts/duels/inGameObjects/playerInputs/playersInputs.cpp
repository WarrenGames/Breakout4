#include "contexts/duels/inGameObjects/playerInputs/loadInputConfig.h"
#include "contexts/duels/inGameObjects/playerInputs/playersInputs.h"
#include "contexts/duels/inGameObjects/playerInputs/inputsConsts.h"
#include <cassert>

duels::PlayersInputs::PlayersInputs(AppLogFiles& logs, const PrefPathFinder& prefPath):
	isLoadingPerfect{true},
	escapeState{false},
	sdlQuitState{false},
	inputsData{logs, prefPath}
{
	isLoadingPerfect = inputsData.isLoadingPerfect;
}

bool duels::PlayersInputs::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

bool duels::PlayersInputs::getInputState(unsigned playerNum, std::size_t index) const
{
	assert( playerNum < duels::PLAYER_MAX && index < INP_MAX );
	return inputsData.playerEnt[playerNum]->inputEffective[index];
}

bool duels::PlayersInputs::getEscapeState() const
{
	return escapeState;
}

bool duels::PlayersInputs::getSDLQuit() const
{
	return sdlQuitState;
}

void duels::PlayersInputs::setEscapeFalse()
{
	escapeState = false;
}

void duels::PlayersInputs::updateEvents()
{
	assert( inputsData.playerEnt[duels::PLAYER_BLUE] && inputsData.playerEnt[duels::PLAYER_RED] );
	SDL_Event event;
	while( SDL_PollEvent(&event) )
	{
		switch(event.type)
		{
			case SDL_KEYDOWN:
				keyboardInputHandle(event.key.keysym.sym, true);
				break;
			case SDL_KEYUP:
				keyboardInputHandle(event.key.keysym.sym, false);
				break;
			case SDL_JOYAXISMOTION:
				joystickAxisHandle(event, PLAYER_BLUE);
				joystickAxisHandle(event, PLAYER_RED);
				break;
			case SDL_JOYHATMOTION:
				joystickHatsHandle(event, PLAYER_BLUE);
				joystickHatsHandle(event, PLAYER_RED);
				break;
			case SDL_JOYBUTTONDOWN:
				joystickButtonsHandle(event.jbutton.which, event.jbutton.button, PLAYER_BLUE, true);
				joystickButtonsHandle(event.jbutton.which, event.jbutton.button, PLAYER_RED, true);
				break;
			case SDL_JOYBUTTONUP:
				joystickButtonsHandle(event.jbutton.which, event.jbutton.button, PLAYER_BLUE, false);
				joystickButtonsHandle(event.jbutton.which, event.jbutton.button, PLAYER_RED, false);
				break;
			case SDL_QUIT:
				sdlQuitState = true;
				break;
		}
	}
}

void duels::PlayersInputs::setInputAsMoveLeft(unsigned playerNum)
{
	assert( playerNum < duels::PLAYER_MAX );
	inputsData.playerEnt[playerNum]->inputEffective[INP_MOV_LEFT] = true;
	inputsData.playerEnt[playerNum]->inputEffective[INP_MOV_RIGHT] = false;
}

void duels::PlayersInputs::setInputAsMoveRight(unsigned playerNum)
{
	assert( playerNum < duels::PLAYER_MAX );
	inputsData.playerEnt[playerNum]->inputEffective[INP_MOV_LEFT] = false;
	inputsData.playerEnt[playerNum]->inputEffective[INP_MOV_RIGHT] = true;
}

void duels::PlayersInputs::setInputAsNotMoving(unsigned playerNum)
{
	assert( playerNum < duels::PLAYER_MAX );
	inputsData.playerEnt[playerNum]->inputEffective[INP_MOV_LEFT] = false;
	inputsData.playerEnt[playerNum]->inputEffective[INP_MOV_RIGHT] = false;
}

void duels::PlayersInputs::setInputState(unsigned playerNum, std::size_t index)
{
	assert( playerNum < duels::PLAYER_MAX );
	inputsData.playerEnt[playerNum]->inputEffective[index] = false;
}

void duels::PlayersInputs::keyboardInputHandle(SDL_Keycode keycode, bool valueToSet)
{
	escapeKeyHandle(keycode, valueToSet);
	playerKeyboardHandle(keycode, valueToSet);
}

void duels::PlayersInputs::escapeKeyHandle(SDL_Keycode keycode, bool valueToSet)
{
	if( keycode == SDLK_ESCAPE )
		escapeState = valueToSet;
}

void duels::PlayersInputs::playerKeyboardHandle(SDL_Keycode keycode, bool valueToSet)
{
	for( std::size_t i{0} ; i < inputsData.playerEnt.size() ; ++i )
	{
		for( std::size_t j{0} ; j < inputsData.playerEnt[i]->keyboardInput.size() ; ++j )
		{
			if( inputsData.playerEnt[i]->keyboardInput[j] == keycode && inputsData.playerEnt[i]->keyboardInput[j] != SDLK_ESCAPE )
			{
				assert( j < inputsData.playerEnt[i]->inputEffective.size() );
				inputsData.playerEnt[i]->inputEffective[j] = valueToSet;
			}
		}
	}
}

bool duels::PlayersInputs::isThisTheGoodAxis(const SDL_Event& event, unsigned playerNum) const
{
	return inputsData.openedJoysticks[inputsData.playerEnt[playerNum]->joystick.joyNum]
			&& event.jaxis.which == inputsData.playerEnt[playerNum]->joystick.joyNum
			&& inputsData.playerEnt[playerNum]->joystick.joyMoveType == duels::JOYMOV_AXES 
			&& event.jaxis.axis == inputsData.playerEnt[playerNum]->joystick.axisOrHatNum;
}

void duels::PlayersInputs::joystickAxisHandle(const SDL_Event& event, unsigned playerNum)
{
	assert( playerNum < duels::PLAYER_MAX );
	if( isThisTheGoodAxis(event, playerNum) )
	{
		if( event.jaxis.value >= inputsData.playerEnt[playerNum]->joystick.axisMoveThreshold )
		{
			setInputAsMoveRight(playerNum);
		}
		else if( event.jaxis.value <= -inputsData.playerEnt[playerNum]->joystick.axisMoveThreshold )
		{
			setInputAsMoveLeft(playerNum);
		}
		else{
			setInputAsNotMoving(playerNum);
		}
	}
}

bool duels::PlayersInputs::isThisTheGoodHat(const SDL_Event& event, unsigned playerNum) const
{
	return inputsData.openedJoysticks[inputsData.playerEnt[playerNum]->joystick.joyNum]
			&& event.jhat.which == inputsData.playerEnt[playerNum]->joystick.joyNum 
			&& inputsData.playerEnt[playerNum]->joystick.joyMoveType == duels::JOYMOV_HATS
			&& event.jhat.hat == inputsData.playerEnt[playerNum]->joystick.axisOrHatNum;
}

void duels::PlayersInputs::joystickHatsHandle(const SDL_Event& event, unsigned playerNum)
{
	assert( playerNum < duels::PLAYER_MAX );
	if( isThisTheGoodHat(event, playerNum) )
	{
		actWithHatValue(event.jhat.value, playerNum);
	}
}

void duels::PlayersInputs::actWithHatValue(Uint8 hatValue, unsigned playerNum)
{
	assert( playerNum < duels::PLAYER_MAX );
	if( hatValue == SDL_HAT_LEFTUP || hatValue == SDL_HAT_LEFT || hatValue == SDL_HAT_LEFTDOWN )
	{
		setInputAsMoveLeft(playerNum);
	}
	else if( hatValue == SDL_HAT_RIGHTUP || hatValue == SDL_HAT_RIGHT || hatValue == SDL_HAT_RIGHTDOWN )
	{
		setInputAsMoveRight(playerNum);
	}
	else
		setInputAsNotMoving(playerNum);
}

bool duels::PlayersInputs::isThisTheGoodButton(int joystickNumber, unsigned playerNum) const
{
	return inputsData.openedJoysticks[inputsData.playerEnt[playerNum]->joystick.joyNum] && joystickNumber == inputsData.playerEnt[playerNum]->joystick.joyNum; 
}

void duels::PlayersInputs::joystickButtonsHandle(int joystickNumber, Uint8 buttonNum, unsigned playerNum, bool valueToSet)
{
	assert( playerNum < duels::PLAYER_MAX );
	if( isThisTheGoodButton(joystickNumber, playerNum) )
	{
		if( buttonNum == inputsData.playerEnt[playerNum]->joystick.buttons[duels::JOY_BTN_BONUS] )
			inputsData.playerEnt[playerNum]->inputEffective[INP_ACTIVBONUS] = valueToSet;
			
		if( buttonNum == inputsData.playerEnt[playerNum]->joystick.buttons[duels::JOY_BTN_SPE_ZONE] )
			inputsData.playerEnt[playerNum]->inputEffective[INP_SPE_ZONE] = valueToSet;
	}
}
