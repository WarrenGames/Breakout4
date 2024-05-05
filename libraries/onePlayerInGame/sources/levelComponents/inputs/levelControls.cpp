#include "levelComponents/inputs/levelControls.h"
#include "types/essentialsStruct.h"
#include "demos/templates/demoStack.h"
#include "demos/inputs/actionData.h"
#include <cassert>

LevelControls::LevelControls(Essentials& essentials):
	keysState( onePlGame::InputMax, false),
	configuration{essentials},
	mousePosition{ 0, 0 },
	mouseButtonState( 8, false ),
	lastKeycode{ SDLK_UNKNOWN },
	closeWindow{false}
{	
	
}

void LevelControls::updateEvents(demos::Stack<demos::ActionData>* demoActionData, demos::Stack<demos::ActionData>* levelEndDemoEvent)
{
	while( SDL_PollEvent(&ev) )
	{
		switch( ev.type )
		{
			case SDL_QUIT:
				closeWindow = true;
				recordSdlQuitForDemo(levelEndDemoEvent);
				break;
			case SDL_KEYDOWN:
				actWithKeyboardEvents(ev.key.keysym.sym, true);
				lastKeycode = ev.key.keysym.sym;
				recordKeyboardForDemo(demoActionData, ev.key.keysym.sym, true);
				recordSdlQuitForDemoIfEscaped(levelEndDemoEvent, ev.key.keysym.sym);
				break;
			case SDL_KEYUP:
				actWithKeyboardEvents(ev.key.keysym.sym, false);
				lastKeycode = SDLK_UNKNOWN;
				recordKeyboardForDemo(demoActionData, ev.key.keysym.sym, false);
				break;
			case SDL_MOUSEMOTION:
				setMousePosition(ev.motion.x, ev.motion.y);
				break;
			case SDL_MOUSEBUTTONDOWN:
				setMouseButton(ev.button.button, true);
				break;
			case SDL_MOUSEBUTTONUP:
				setMouseButton(ev.button.button, false);
				break;
			case SDL_JOYBUTTONDOWN:
				actWithJoyButtonEvents(ev.jbutton.button, ev.jbutton.which, true);
				recordJoystickButtonsForDemo(demoActionData, ev.jbutton.button, ev.jbutton.which, true);
				break;
			case SDL_JOYBUTTONUP:
				actWithJoyButtonEvents(ev.jbutton.button, ev.jbutton.which, false);
				recordJoystickButtonsForDemo(demoActionData, ev.jbutton.button, ev.jbutton.which, false);
				break;
			case SDL_JOYAXISMOTION:
				actWithJoyAxesEvents(ev.jaxis.value, ev.jaxis.axis, ev.jaxis.which);
				recordActionWithJoyAxes(demoActionData, ev.jaxis.value, ev.jaxis.axis, ev.jaxis.which);
				fillCrossMoveWithAxes(ev);
				break;
			case SDL_JOYHATMOTION:
				actWithJoyHatsEvents(ev.jhat.value, ev.jhat.hat, ev.jhat.which);
				recordActionWithJoyHat(demoActionData, ev.jhat.value, ev.jhat.hat, ev.jhat.which);
				fillCrossMoveWithHats(ev);
				break;
		}
	}
}

void LevelControls::joinDemosTimePoint()
{
	demoRecordingDelay.joinTimePoints();
}

void LevelControls::actWithKeyboardEvents(SDL_Keycode keycode, bool value)
{
	for( std::size_t i{0} ; i < keysState.size() ; ++i )
	{
		if( keycode == configuration.customKeys[i] )
			keysState[i] = value;
	}
}

void LevelControls::actWithJoyButtonEvents(unsigned buttonNumber, SDL_JoystickID joystickNum, bool value)
{
	assert( configuration.joystickConfig.joyButtons.size() == joystickStates.joyButtons.size() );
	for( std::size_t i{0} ; i < configuration.joystickConfig.joyButtons.size() ; ++i )
	{
		if( buttonNumber == configuration.joystickConfig.joyButtons[i] && joystickNum == configuration.joystickConfig.joystickNumber )
		{
			joystickStates.joyButtons[i] = value;
		}
	}
}

void LevelControls::actWithJoyHatsEvents(Uint8 hatValue, Uint8 hatNumber, SDL_JoystickID joystickNum)
{
	if( static_cast<std::size_t>(hatNumber) < joystickStates.joyHats.size() && joystickNum == configuration.joystickConfig.joystickNumber )
	{
		joystickStates.joyHats[ static_cast<std::size_t>(hatNumber)] = hatValue;
	}
}

void LevelControls::actWithJoyAxesEvents(Sint16 axisValue, Uint8 axisNumber, SDL_JoystickID joystickNum)
{
	if( static_cast<std::size_t>(axisNumber) < joystickStates.joyAxes.size() && joystickNum == configuration.joystickConfig.joystickNumber )
	{
		joystickStates.joyAxes[ static_cast<std::size_t>( axisNumber ) ] = axisValue;
	}
}

void LevelControls::recordKeyboardForDemo(demos::Stack<demos::ActionData>* demoActionData, SDL_Keycode keycode, bool value)
{
	if( demoActionData )
	{
		for( unsigned key{0} ; key < configuration.customKeys.size() ; ++key )
		{
			if( keycode == configuration.customKeys[key] )
			{
				recordActionData(demoActionData, key, value);
			}
		}
	}
}

void LevelControls::recordJoystickButtonsForDemo(demos::Stack<demos::ActionData>* demoActionData, unsigned buttonNumber, SDL_JoystickID joystickNum, bool value)
{
	if( demoActionData )
	{
		for( std::size_t i{0} ; i < joystickStates.joyButtons.size() ; ++i )
		{
			if( buttonNumber == configuration.joystickConfig.joyButtons[i] && joystickNum == configuration.joystickConfig.joystickNumber )
			{
				switch( i )
				{
					case onePlGame::JoystickButtonBallTrace:
						recordActionWithJoyBtn(demoActionData, onePlGame::InputBallTrace, value);
						break;
					case onePlGame::JoystickButtonSearchBag:
						recordActionWithJoyBtn(demoActionData, onePlGame::InputLookBag, value);
						break;
					case onePlGame::JoystickButtonSwitch:
						recordActionWithJoyBtn(demoActionData, onePlGame::InputSwitch, value);
						break;
					
				}
			}
		}
	}
}

void LevelControls::recordActionWithJoyBtn(demos::Stack<demos::ActionData>* demoActionData, unsigned inputFunctionNumber, bool value)
{
	assert( inputFunctionNumber >= onePlGame::InputBallTrace && inputFunctionNumber <= onePlGame::InputSwitch );
	recordActionData(demoActionData, inputFunctionNumber, value);
}

void LevelControls::recordActionWithJoyHat(demos::Stack<demos::ActionData>* demoActionData, Uint8 hatValue, Uint8 hatNumber, SDL_JoystickID joystickNum)
{
	if( demoActionData )
	{
		if( static_cast<std::size_t>(hatNumber) < joystickStates.joyHats.size() && joystickNum == configuration.joystickConfig.joystickNumber )
		{
			switch( hatValue )
			{
				case SDL_HAT_CENTERED:
					recordAccordingToHat(demoActionData, false, false);
					break;
				case SDL_HAT_LEFT:
					recordAccordingToHat(demoActionData, true, false);
					break;
				case SDL_HAT_RIGHT:
					recordAccordingToHat(demoActionData, false, true);
					break;
				case SDL_HAT_UP:
					recordAccordingToHat(demoActionData, false, false);
					break;
				case SDL_HAT_DOWN:
					recordAccordingToHat(demoActionData, false, false);
					break;
				case SDL_HAT_LEFTUP:
					recordAccordingToHat(demoActionData, true, false);
					break;
				case SDL_HAT_LEFTDOWN:
					recordAccordingToHat(demoActionData, true, false);
					break;
				case SDL_HAT_RIGHTUP:
					recordAccordingToHat(demoActionData, false, true);
					break;
				case SDL_HAT_RIGHTDOWN:
					recordAccordingToHat(demoActionData, false, true);
					break;
			}
		}
	}
}

void LevelControls::recordActionWithJoyAxes(demos::Stack<demos::ActionData>* demoActionData, Sint16 axisValue, Uint8 axisNumber, SDL_JoystickID joystickNum)
{
	if( demoActionData )
	{
		if( joystickNum == configuration.joystickConfig.joystickNumber )
		{
			if( axisNumber == configuration.joystickConfig.axisOrHatNum )
			{
				if( axisValue >= configuration.joystickConfig.axisMoveThreshold )
				{
					recordActionData(demoActionData, onePlGame::InputMoveRight, true);
					recordActionData(demoActionData, onePlGame::InputMoveLeft, false);
				}
				else if( axisValue <= -configuration.joystickConfig.axisMoveThreshold )
				{
					recordActionData(demoActionData, onePlGame::InputMoveRight, false);
					recordActionData(demoActionData, onePlGame::InputMoveLeft, true);
				}
				else{
					recordActionData(demoActionData, onePlGame::InputMoveLeft, false);
					recordActionData(demoActionData, onePlGame::InputMoveRight, false);
				}
			}
		}
	}
}

void LevelControls::recordAccordingToHat(demos::Stack<demos::ActionData>* demoActionData, bool left, bool right)
{
	recordActionData(demoActionData, onePlGame::InputMoveLeft, left);
	recordActionData(demoActionData, onePlGame::InputMoveRight, right);
}

void LevelControls::recordActionData(demos::Stack<demos::ActionData>* demoActionData, unsigned func, bool state)
{
	if( demoActionData->getCommandsNumber() + 1 < demoActionData->getCapacity() )
	{
		tempActionData.delay = demoRecordingDelay.getCurrentElapsedMicrosecondsTime();
		tempActionData.funcEnum = func;
		tempActionData.actionState = state;
		demoActionData->emplaceElement(tempActionData);
	}
	else{
		demoActionData->setSizeNotSufficientFlag();
	}
}

void LevelControls::recordSdlQuitForDemo(demos::Stack<demos::ActionData>* levelEndDemoEvent)
{
	if( levelEndDemoEvent )
	{
		if( levelEndDemoEvent->getCommandsNumber() + 1 < levelEndDemoEvent->getCapacity() )
		{
			tempActionData.delay = demoRecordingDelay.getCurrentElapsedMicrosecondsTime();
			tempActionData.funcEnum = demos::QuitEventFunc;
			tempActionData.actionState = true;
			levelEndDemoEvent->emplaceElement(tempActionData);
		}
		else{
			levelEndDemoEvent->setSizeNotSufficientFlag();
		}
	}
}

void LevelControls::recordSdlQuitForDemoIfEscaped(demos::Stack<demos::ActionData>* levelEndDemoEvent, SDL_Keycode keycode)
{
	if( keycode == SDLK_ESCAPE )
	{
		recordSdlQuitForDemo(levelEndDemoEvent);
	}
}

void LevelControls::setMousePosition(int xPosition, int yPosition)
{
	mousePosition.x = xPosition;
	mousePosition.y = yPosition;
}

void LevelControls::setMouseButton(std::size_t buttonIndex, bool value)
{
	assert( buttonIndex < mouseButtonState.size() );
	mouseButtonState[buttonIndex] = value;
}

void LevelControls::fillCrossMoveWithHats(SDL_Event& event)
{
	if( configuration.joystickConfig.crossMoveType == onePlGame::JoystickMoveHats )
	{
		for( std::size_t i{0} ; i < onePlGame::JoystickCrossMoveMax ; ++i )
		{
			if( static_cast<unsigned>(event.jhat.hat) == configuration.joystickConfig.crossNum[i] )
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

void LevelControls::fillCrossMove(int xValue, int yValue)
{
	crossMove.x = xValue;
	crossMove.y = yValue;
}

void LevelControls::fillCrossMoveWithAxes(const SDL_Event& event)
{
	if( configuration.joystickConfig.crossMoveType == onePlGame::JoystickMoveAxes )
	{
		handleXCrossAxis(event);
		handleYCrossAxis(event);
	}
}

void LevelControls::handleXCrossAxis(const SDL_Event& event)
{
	if( event.jaxis.axis == configuration.joystickConfig.crossNum[onePlGame::JoystickCrossMoveX] )
	{
		if( event.jaxis.value >= static_cast<Sint32>(configuration.joystickConfig.axisMoveThreshold) )
		{
			crossMove.x = 1;
		}
		else if( event.jaxis.value <= static_cast<Sint32>(-configuration.joystickConfig.axisMoveThreshold) )
		{
			crossMove.x = -1;
		}
		else{
			crossMove.x = 0;
		}
	}
}

void LevelControls::handleYCrossAxis(const SDL_Event& event)
{
	if( event.jaxis.axis == configuration.joystickConfig.crossNum[onePlGame::JoystickCrossMoveY] )
	{
		if( event.jaxis.value >= static_cast<Sint32>(configuration.joystickConfig.axisMoveThreshold) )
		{
			crossMove.y -= 1;
		}
		else if( event.jaxis.value <= static_cast<Sint32>(-configuration.joystickConfig.axisMoveThreshold) )
		{
			crossMove.y += 1;
		}
		else{
			crossMove.y = 0;
		}
	}
}

bool LevelControls::windowAskedToBeClosed() const
{
	return closeWindow;
}

bool LevelControls::getKeycodeState(std::size_t keybFunction) const
{
	assert( keybFunction < keysState.size() );
	return keysState[keybFunction];
}

void LevelControls::setKeycodeFalse(std::size_t keybFunction)
{
	assert( keybFunction < keysState.size() );
	keysState[keybFunction] = false;
}

SDL_Keycode LevelControls::getLastKeycode() const
{
	return lastKeycode;
}

void LevelControls::cancelLastKeycode()
{
	lastKeycode = SDLK_UNKNOWN;
}

bool LevelControls::getButtonState(std::size_t buttonFunction) const
{
	assert( buttonFunction < joystickStates.joyButtons.size() );
	return joystickStates.joyButtons[buttonFunction];
}

void LevelControls::setButtonFalse(std::size_t buttonFunction)
{
	assert( buttonFunction < joystickStates.joyButtons.size() );
	joystickStates.joyButtons[buttonFunction] = false;
}

unsigned LevelControls::getJoystickMoveType() const
{
	return configuration.joystickConfig.joyMoveType;
}

Uint8 LevelControls::getHatState() const
{
	assert( configuration.joystickConfig.axisOrHatNum < joystickStates.joyHats.size()  );
	return joystickStates.joyHats[ configuration.joystickConfig.axisOrHatNum ];
}

Sint16 LevelControls::getAxisState() const 
{
	assert( configuration.joystickConfig.axisOrHatNum < joystickStates.joyAxes.size() );
	return joystickStates.joyAxes[ configuration.joystickConfig.axisOrHatNum ];
}

Sint16 LevelControls::getAxesThreshold() const
{
	return static_cast<Sint16>( configuration.joystickConfig.axisMoveThreshold );
}

const Offset& LevelControls::getMousePosition() const
{
	return mousePosition;
}

bool LevelControls::getMouseButton(std::size_t buttonIndex) const
{
	assert( buttonIndex < mouseButtonState.size() );
	return mouseButtonState[buttonIndex];
}

unsigned LevelControls::getCrossMoveDeviceType() const
{
	return configuration.crossDeviceUse;
}

const Offset& LevelControls::getCrossMove() const
{
	return crossMove;
}

bool LevelControls::isAJoystickPlugged() const
{
	return joystickStates.joyEnt;
}