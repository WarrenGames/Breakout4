#ifndef LEVEL_INPUTS_H
#define LEVEL_INPUTS_H

#include "levelComponents/inputs/customInputsData.h"
#include "levelComponents/inputs/joystickData.h"
#include "demos/inputs/actionData.h"
#include "time/accurateTime.h"
#include "SDL_events.h"
#include <vector>
 
struct Essentials;
namespace demos{ template<typename T>class Stack; struct ActionData; }

class LevelControls
{
private:
	SDL_Event ev;
	std::vector< bool > keysState;
	JoystickData joystickStates;
	onePlGame::CustomInputData configuration;
	Offset mousePosition;
	Offset crossMove;
	std::vector< bool > mouseButtonState;
	SDL_Keycode lastKeycode;
	AccurateTimeDelay demoRecordingDelay;
	demos::ActionData tempActionData;
	bool closeWindow;
	
public:
	explicit LevelControls(Essentials& essentials);
	~LevelControls() = default;
	LevelControls( const LevelControls& ) = delete;
	LevelControls& operator= ( const LevelControls& ) = delete;
	LevelControls( LevelControls&& ) = default;
	LevelControls& operator= ( LevelControls&& ) = default;
	
	void updateEvents(demos::Stack<demos::ActionData>* demoActionData, demos::Stack<demos::ActionData>* levelEndDemoEvent);
	void joinDemosTimePoint();
	void recordSdlQuitForDemo(demos::Stack<demos::ActionData>* levelEndDemoEvent);

private:
	void actWithKeyboardEvents(SDL_Keycode keycode, bool value);
	void actWithJoyButtonEvents(unsigned buttonNumber, SDL_JoystickID joystickNum, bool value);
	void actWithJoyHatsEvents(Uint8 hatValue, Uint8 hatNumber, SDL_JoystickID joystickNum);
	void actWithJoyAxesEvents(Sint16 axisValue, Uint8 axisNumber, SDL_JoystickID joystickNum);
	void recordKeyboardForDemo(demos::Stack<demos::ActionData>* demoActionData, SDL_Keycode keycode, bool value);
	void recordJoystickButtonsForDemo(demos::Stack<demos::ActionData>* demoActionData, unsigned buttonNumber, SDL_JoystickID joystickNum, bool value);
	void recordActionWithJoyBtn(demos::Stack<demos::ActionData>* demoActionData, unsigned inputFunctionNumber, bool value);
	void recordActionWithJoyHat(demos::Stack<demos::ActionData>* demoActionData, Uint8 hatValue, Uint8 hatNumber, SDL_JoystickID joystickNum);
	void recordActionWithJoyAxes(demos::Stack<demos::ActionData>* demoActionData, Sint16 axisValue, Uint8 axisNumber, SDL_JoystickID joystickNum);
	void recordAccordingToHat(demos::Stack<demos::ActionData>* demoActionData, bool left, bool right);
	void recordActionData(demos::Stack<demos::ActionData>* demoActionData, unsigned func, bool state);
	void recordSdlQuitForDemoIfEscaped(demos::Stack<demos::ActionData>* levelEndDemoEvent, SDL_Keycode keycode);
	void setMousePosition(int xPosition, int yPosition);
	void setMouseButton(std::size_t buttonIndex, bool value);
	void fillCrossMoveWithHats(SDL_Event& event);
	void fillCrossMove(int xValue, int yValue);
	void fillCrossMoveWithAxes(const SDL_Event& event);
	void handleXCrossAxis(const SDL_Event& event);
	void handleYCrossAxis(const SDL_Event& event);
	
public:
	unsigned getDeviceType() const;
	bool windowAskedToBeClosed() const;
	
	bool getKeycodeState(std::size_t keybFunction) const;
	void setKeycodeFalse(std::size_t keybFunction);
	SDL_Keycode getLastKeycode() const;
	void cancelLastKeycode();
	
	bool getButtonState(std::size_t buttonFunctions) const;
	void setButtonFalse(std::size_t buttonFunctions);
	
	unsigned getJoystickMoveType() const;
	Uint8 getHatState() const;
	Sint16 getAxisState() const;
	Sint16 getAxesThreshold() const;
	
	const Offset& getMousePosition() const;
	bool getMouseButton(std::size_t buttonIndex) const;
	unsigned getCrossMoveDeviceType() const;
	
	const Offset& getCrossMove() const;
	bool isAJoystickPlugged() const;
};



#endif //LEVEL_INPUTS_H
