#ifndef IN_GAME_PLAYER_ACTIONS_H
#define IN_GAME_PLAYER_ACTIONS_H

#include "time/accurateTime.h"
#include <vector>

class LevelControls;
namespace demos{ template<typename>class Stack; struct ActionData; }

class PlayerActions
{
private:
	std::vector< bool > actionsStates; //Size should be equal to InputFunctionMax
	AccurateTimeDelay delay;
	bool quitAction;

public:
	PlayerActions();
	~PlayerActions() = default;
	PlayerActions( const PlayerActions& ) = delete;
	PlayerActions& operator= ( const PlayerActions& ) = delete;
	PlayerActions( PlayerActions&& ) = default;
	PlayerActions& operator= ( PlayerActions&& ) = default;
	
	bool getActionState(std::size_t actionIndex) const;
	
	void setActionsWithPlayerInputs(const LevelControls& levelControls);
	void setActionsWithDemoFile(demos::Stack< demos::ActionData >& demoActionData, demos::Stack< demos::ActionData >& levelEndDemoEvent);
	void setActionToFalse(std::size_t actionIndex);
	void setQuitActionFlagToFalse();
	bool getQuitActionFlag() const;
	void joinDemosTimePoint();
	
private:
	void setActionsWithJoystickInput(const LevelControls& levelControls);
	void setActionsWithJoystickHat(const LevelControls& levelControls);
	void setActionsWithHat(bool left, bool right);
	void setActionsWithAxis(const LevelControls& levelControls);
	void setActionsWithJoyButtons(const LevelControls& levelControls);
	
	void setActionsWithKeyboard(const LevelControls& levelControls);
	void setActionWithSingleKey(const LevelControls& levelControls, std::size_t keyIndex, std::size_t actionIndex);
	void setLeftAndRightWithKeyboard(const LevelControls& levelControls);
	
	bool canPopDemoActionDataStack(const demos::ActionData& actionData);
	bool hasTimeElapsed(const demos::ActionData& actionData);
	
	void setCanQuitDemoFlag(demos::Stack< demos::ActionData >& levelEndDemoEvent);
};

#endif //IN_GAME_PLAYER_ACTIONS_H