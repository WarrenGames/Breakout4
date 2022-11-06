#include "contexts/onePlayerGame/levelComponents/inputs/userInputs.h"
#include "types/essentialsStruct.h"
#include <cassert>

LevelInputs::LevelInputs(Essentials& essentials):
	inputsData{essentials},
	functionsStates( onePlGame::InputMax, false ), 
	crossMove{ 0, 0 },
	escapeState{ false },
	windowClosing{ false },
	mousePosition{ 0, 0},
	mouseButtons(8)
{
	std::fill( mouseButtons.begin(), mouseButtons.end(), false);
}

LevelInputs::operator bool() const
{
	return inputsData.isLoadingPerfect;
}

bool LevelInputs::getFuncState(std::size_t funcIndex) const
{
	assert( funcIndex < functionsStates.size() );
	return functionsStates[funcIndex];
}

void LevelInputs::setFuncState(std::size_t funcIndex, bool fillValue)
{
	assert( funcIndex < functionsStates.size() );
	functionsStates[funcIndex] = fillValue;
}

bool LevelInputs::getEscapeState() const
{
	return escapeState;
}

void LevelInputs::setEscapeToFalse()
{
	escapeState = false;
}

bool LevelInputs::doesUserCloseWindow() const
{
	return windowClosing;
}

const Offset& LevelInputs::getMousePosition() const
{
	return mousePosition;
}

const Offset& LevelInputs::getCrossMove() const
{
	return crossMove;
}

unsigned LevelInputs::getCrossMoveDeviceType() const
{
	return inputsData.crossDeviceUse;
}

bool LevelInputs::getMouseButtonState(unsigned buttonNum) const
{
	assert( buttonNum < mouseButtons.size() );
	return mouseButtons[buttonNum];
}

void LevelInputs::updateEvents()
{
	SDL_Event event;
	while( SDL_PollEvent(&event) )
	{
		switch(event.type)
		{
			case SDL_QUIT:
				windowClosing = true;
				break;
			case SDL_KEYDOWN:
				fillInputsWithKeycodes(true, event.key.keysym.sym);
				setEscapeKeyState(true, event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				fillInputsWithKeycodes(false, event.key.keysym.sym);
				setEscapeKeyState(false, event.key.keysym.sym);
				break;
			case SDL_MOUSEMOTION:
				setMouseCoordinates(Offset{event.motion.x, event.motion.y});
				break;
			case SDL_MOUSEBUTTONDOWN:
				setMouseButtons(event.button.button, true);
				break;
			case SDL_MOUSEBUTTONUP:
				setMouseButtons(event.button.button, false);
				break;
			case SDL_JOYAXISMOTION:
				joyAxesHandle(event);
				fillCrossMoveWithAxes(event);
				break;
			case SDL_JOYHATMOTION:
				joyHatsHandle(event);
				fillCrossMoveWithHats(event);
				break;
			case SDL_JOYBUTTONDOWN:
				joyButtonHandle(event, true);
				break;
			case SDL_JOYBUTTONUP:
				joyButtonHandle(event, false);
				break;
		}
	}
}

void LevelInputs::fillInputsWithKeycodes(bool fillValue, SDL_Keycode keycode)
{
	for( std::size_t i{0} ; i < onePlGame::InputMax ; ++i )
	{
		if( keycode == inputsData.customKeys[i] )
		{
			functionsStates[i] = fillValue;
		}
	}
}

void LevelInputs::setEscapeKeyState(bool fillValue, SDL_Keycode keycode)
{
	if( keycode == SDLK_ESCAPE )
	{
		escapeState = fillValue;
	}
}

void LevelInputs::setMouseCoordinates(const Offset& newPosition)
{
	mousePosition = newPosition;
}

void LevelInputs::setMouseButtons(unsigned buttonNum, bool valueToSet)
{
	assert( buttonNum < mouseButtons.size() );
	mouseButtons[buttonNum] = valueToSet;
}

void LevelInputs::joyAxesHandle(const SDL_Event& event)
{
	if( inputsData.joystickData.joyMoveType == onePlGame::JoystickMoveAxes && static_cast<unsigned>(event.jaxis.axis) == inputsData.joystickData.axisOrHatNum )
	{
		if( event.jaxis.value >= static_cast<Sint32>(inputsData.joystickData.axisMoveThreshold) )
		{
			functionsStates[onePlGame::InputMoveLeft] = false;
			functionsStates[onePlGame::InputMoveRight] = true;
		}
		else if( event.jaxis.value <= static_cast<Sint32>(-inputsData.joystickData.axisMoveThreshold) )
		{
			functionsStates[onePlGame::InputMoveLeft] = true;
			functionsStates[onePlGame::InputMoveRight] = false;
		}
		else{
			functionsStates[onePlGame::InputMoveLeft] = false;
			functionsStates[onePlGame::InputMoveRight] = false;
		}
	}
}

void LevelInputs::joyHatsHandle(const SDL_Event& event)
{
	if( inputsData.joystickData.joyMoveType == onePlGame::JoystickMoveHats && static_cast<unsigned>(event.jhat.hat) == inputsData.joystickData.axisOrHatNum )
	{
		if( event.jhat.value == SDL_HAT_RIGHT || event.jhat.value == SDL_HAT_RIGHTUP || event.jhat.value == SDL_HAT_RIGHTDOWN )
		{
			functionsStates[onePlGame::InputMoveLeft] = false;
			functionsStates[onePlGame::InputMoveRight] = true;
		}
		else if( event.jhat.value == SDL_HAT_LEFT || event.jhat.value == SDL_HAT_LEFTUP || event.jhat.value == SDL_HAT_LEFTDOWN )
		{
			functionsStates[onePlGame::InputMoveLeft] = true;
			functionsStates[onePlGame::InputMoveRight] = false;
		}
		else if( event.jhat.value == SDL_HAT_CENTERED )
		{
			functionsStates[onePlGame::InputMoveLeft] = false;
			functionsStates[onePlGame::InputMoveRight] = false;
		}
	}
}

void LevelInputs::joyButtonHandle(const SDL_Event& event, bool valueToAppend)
{
	setInputFunctionWithJoyButton(event.jbutton.button, onePlGame::JoysticButtonBallTrace, onePlGame::InputBallTrace, valueToAppend);
	setInputFunctionWithJoyButton(event.jbutton.button, onePlGame::JoysticButtonSearchBag, onePlGame::InputLookBag, valueToAppend);
	setInputFunctionWithJoyButton(event.jbutton.button, onePlGame::JoysticButtonSwitch, onePlGame::InputSwitch, valueToAppend);
}

void LevelInputs::setInputFunctionWithJoyButton(unsigned buttonNum, std::size_t configIndex, std::size_t buttonStateIndex, bool valueToAppend)
{
	if( buttonNum == inputsData.joystickData.joyButtons[configIndex] )
	{
		functionsStates[buttonStateIndex] = valueToAppend;
	}
}

void LevelInputs::fillCrossMoveWithHats(const SDL_Event& event)
{
	if( inputsData.joystickData.crossMoveType == onePlGame::JoystickMoveHats ) 
	{
		for( std::size_t i{0} ; i < onePlGame::JoystickCrossMoveMax ; ++i )
		{
			if( static_cast<unsigned>(event.jhat.hat) == inputsData.joystickData.crossNum[i] )
			{
				switch( event.jhat.value )
				{
					case SDL_HAT_CENTERED:
						fillCrossMove(0, 0);
						break;
					case SDL_HAT_DOWN:
						fillCrossMove(0, -1);
						break;
					case SDL_HAT_UP:
						fillCrossMove(0, 1);
						break;
					case SDL_HAT_LEFT:
						fillCrossMove(-1, 0);
						break;
					case SDL_HAT_RIGHT:
						fillCrossMove(1, 0);
						break;
					case SDL_HAT_LEFTDOWN:
						fillCrossMove(-1, -1);
						break;
					case SDL_HAT_LEFTUP:
						fillCrossMove(-1, 1);
						break;
					case SDL_HAT_RIGHTDOWN:
						fillCrossMove(1, -1);
						break;
					case SDL_HAT_RIGHTUP:
						fillCrossMove(1, 1);
						break;
					default:
						fillCrossMove(0, 0);
						break;
				}
			}
		}
	}	
}

void LevelInputs::fillCrossMove(int x_value, int y_value)
{
	crossMove.x = x_value;
	crossMove.y = y_value;
}

void LevelInputs::fillCrossMoveWithAxes(const SDL_Event& event)
{
	if( inputsData.joystickData.crossMoveType == onePlGame::JoystickMoveAxes )
	{
		handleXCrossAxis(event);
		handleYCrossAxis(event);
	}
}

void LevelInputs::handleXCrossAxis(const SDL_Event& event)
{
	if( event.jaxis.axis == inputsData.joystickData.crossNum[onePlGame::JoystickCrossMoveX] )
	{
		if( event.jaxis.value >= static_cast<Sint32>(inputsData.joystickData.axisMoveThreshold) )
		{
			crossMove.x = 1;
		}
		else if( event.jaxis.value <= static_cast<Sint32>(-inputsData.joystickData.axisMoveThreshold) )
		{
			crossMove.x = -1;
		}
		else{
			crossMove.x = 0;
		}
	}
}

void LevelInputs::handleYCrossAxis(const SDL_Event& event)
{
	if( event.jaxis.axis == inputsData.joystickData.crossNum[onePlGame::JoystickCrossMoveY] )
	{
		if( event.jaxis.value >= static_cast<Sint32>(inputsData.joystickData.axisMoveThreshold) )
		{
			crossMove.y -= 1;
		}
		else if( event.jaxis.value <= static_cast<Sint32>(-inputsData.joystickData.axisMoveThreshold) )
		{
			crossMove.y += 1;
		}
		else{
			crossMove.y = 0;
		}
	}
}