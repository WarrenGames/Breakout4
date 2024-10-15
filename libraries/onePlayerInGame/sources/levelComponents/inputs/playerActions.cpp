#include "levelComponents/inputs/playerActions.h"
#include "levelComponents/inputs/levelControls.h"
#include "demos/templates/demoStack.h"
#include "demos/inputs/actionData.h"
#include "consts/onePlayerLevelConsts.h"
#include <cassert>

PlayerActions::PlayerActions():
	actionsStates(onePlGame::InputMax, false),
	quitAction{false}
{

}

bool PlayerActions::getActionState(std::size_t actionIndex) const
{
	assert( actionIndex < actionsStates.size() );
	return actionsStates[actionIndex];
}

void PlayerActions::setActionsWithPlayerInputs(const LevelControls& levelControls)
{
	setActionsWithKeyboard(levelControls);
	setActionsWithJoystickInput(levelControls);
}

void PlayerActions::setActionsWithDemoFile(demos::Stack< demos::ActionData >& demoActionData, demos::Stack< demos::ActionData >& levelEndDemoEvent)
{
	while( demoActionData.getCommandsNumber() > 0 && canPopDemoActionDataStack(demoActionData.getLastElement() ) )
	{
		assert( demoActionData.getLastElement().funcEnum < onePlGame::InputMax );
		actionsStates[ demoActionData.getLastElement().funcEnum ] = demoActionData.getLastElement().actionState;
		demoActionData.pop_back();
	}
	setCanQuitDemoFlag(levelEndDemoEvent);
}

void PlayerActions::setActionToFalse(std::size_t actionIndex)
{
	assert( actionIndex < actionsStates.size() );
	actionsStates[actionIndex] = false;
}

void PlayerActions::setQuitActionFlagToFalse()
{
	quitAction = false;
}

bool PlayerActions::getQuitActionFlag() const
{
	return quitAction;
}

void PlayerActions::joinDemosTimePoint()
{
	delay.joinTimePoints();
}

void PlayerActions::setActionsWithJoystickInput(const LevelControls& levelControls)
{
	if( levelControls.isAJoystickPlugged() )
	{
		if( levelControls.getJoystickMoveType() == onePlGame::JoystickMoveHats )
		{
			setActionsWithJoystickHat(levelControls);
		}
		else if( levelControls.getJoystickMoveType() == onePlGame::JoystickMoveAxes )
		{
			setActionsWithAxis(levelControls);
		}
		setActionsWithJoyButtons(levelControls);
	}
}

void PlayerActions::setActionsWithJoystickHat(const LevelControls& levelControls)
{
	switch( levelControls.getHatState() )
	{
		case SDL_HAT_LEFT:
			setActionsWithHat(true, false);
			break;
		case SDL_HAT_RIGHT:
			setActionsWithHat(false, true);
			break;
		case SDL_HAT_UP:
			setActionsWithHat(false, false);
			break;
		case SDL_HAT_DOWN:
			setActionsWithHat(false, false);
			break;
		case SDL_HAT_LEFTUP:
			setActionsWithHat(true, false);
			break;
		case SDL_HAT_LEFTDOWN:
			setActionsWithHat(true, false);
			break;
		case SDL_HAT_RIGHTUP:
			setActionsWithHat(false, true);
			break;
		case SDL_HAT_RIGHTDOWN:
			setActionsWithHat(false, true);
			break;
		case SDL_HAT_CENTERED:
			setActionsWithHat(false, false);
			break;
	}
}

void PlayerActions::setActionsWithHat(bool left, bool right)
{
	actionsStates[onePlGame::InputMoveLeft] = left;
	actionsStates[onePlGame::InputMoveRight] = right;
}

void PlayerActions::setActionsWithAxis(const LevelControls& levelControls)
{
	if( levelControls.getAxisState() < -levelControls.getAxesThreshold() )
	{
		actionsStates[onePlGame::InputMoveLeft] = true;
		actionsStates[onePlGame::InputMoveRight] = false;
	}
	else if( levelControls.getAxisState() > levelControls.getAxesThreshold() )
	{
		actionsStates[onePlGame::InputMoveLeft] = false;
		actionsStates[onePlGame::InputMoveRight] = true;
	}
	else{
		actionsStates[onePlGame::InputMoveLeft] = false;
		actionsStates[onePlGame::InputMoveRight] = false;
	}
}

void PlayerActions::setActionsWithJoyButtons(const LevelControls& levelControls)
{
	actionsStates[onePlGame::InputBallTrace] = levelControls.getButtonState(onePlGame::JoystickButtonBallTrace);
	actionsStates[onePlGame::InputLookBag] = levelControls.getButtonState(onePlGame::JoystickButtonSearchBag);
	actionsStates[onePlGame::InputSwitch] = levelControls.getButtonState(onePlGame::JoystickButtonSwitch);
}

void PlayerActions::setActionsWithKeyboard(const LevelControls& levelControls)
{
	setActionWithSingleKey(levelControls, onePlGame::InputBallTrace, onePlGame::InputBallTrace);
	setActionWithSingleKey(levelControls, onePlGame::InputLookBag, onePlGame::InputLookBag);
	setActionWithSingleKey(levelControls, onePlGame::InputSwitch, onePlGame::InputSwitch);
	setLeftAndRightWithKeyboard(levelControls);
}

void PlayerActions::setActionWithSingleKey(const LevelControls& levelControls, std::size_t keyIndex, std::size_t actionIndex)
{
	assert( actionIndex < onePlGame::InputMax );
	assert( keyIndex < onePlGame::InputMax );
	actionsStates[actionIndex] = levelControls.getKeycodeState(keyIndex);
}

void PlayerActions::setLeftAndRightWithKeyboard(const LevelControls& levelControls)
{
	actionsStates[onePlGame::InputMoveLeft] = levelControls.getKeycodeState(onePlGame::InputMoveLeft);
	actionsStates[onePlGame::InputMoveRight] = levelControls.getKeycodeState(onePlGame::InputMoveRight);
}

bool PlayerActions::canPopDemoActionDataStack(const demos::ActionData& actionData)
{
	return hasTimeElapsed(actionData);
}

bool PlayerActions::hasTimeElapsed(const demos::ActionData& actionData)
{
	if( delay.hasTimeElapsed( std::chrono::duration_cast<std::chrono::microseconds>(actionData.delay) ) )
	{
		assert( actionData.funcEnum < actionsStates.size() );
		actionsStates[actionData.funcEnum] = actionData.actionState;
		return true;
	}
	else{
		return false;
	}
}

void PlayerActions::setCanQuitDemoFlag(demos::Stack< demos::ActionData >& levelEndDemoEvent)
{
	while( levelEndDemoEvent.getCommandsNumber() > 0 && canPopDemoActionDataStack(levelEndDemoEvent.getLastElement() ) )
	{
		assert( levelEndDemoEvent.getLastElement().funcEnum == demos::QuitEventFunc );
		quitAction = true;
		levelEndDemoEvent.pop_back();
	}
}