#ifndef P1_USER_INPUTS_H
#define P1_USER_INPUTS_H

#include "contexts/onePlayerGame/levelComponents/inputs/customInputsData.h"
#include <vector>

struct Offset;
struct Essentials;

class LevelInputs
{
private:
	onePlGame::CustomInputData inputsData;
	std::vector< bool > functionsStates;
	Offset crossMove;
	bool escapeState;
	bool windowClosing;
	Offset mousePosition;
	std::vector< bool > mouseButtons;

public:
	explicit LevelInputs(Essentials& essentials);
	~LevelInputs() = default;
	LevelInputs( const LevelInputs& ) = delete;
	LevelInputs& operator= ( const LevelInputs& ) = delete;
	LevelInputs( LevelInputs&& ) = default;
	LevelInputs& operator= ( LevelInputs&& ) = default;
	
	operator bool() const;
	
	bool getFuncState(std::size_t funcIndex) const;//Need enum{ InputMoveLeft, InputMoveRight, InputBallTrace, InputLookBag, InputSwitch, InputMax };
	void setFuncState(std::size_t funcIndex, bool fillValue);
	bool getEscapeState() const;
	void setEscapeToFalse();
	bool doesUserCloseWindow() const;
	const Offset& getMousePosition() const;
	const Offset& getCrossMove() const;
	unsigned getCrossMoveDeviceType() const;
	bool getMouseButtonState(unsigned buttonNum) const;
	
	void updateEvents();

private:
	void fillInputsWithKeycodes(bool fillValue, SDL_Keycode keycode);
	void setEscapeKeyState(bool fillValue, SDL_Keycode keycode);
	void setMouseCoordinates(const Offset& newPosition);
	void setMouseButtons(unsigned buttonNum, bool valueToSet);
	void joyAxesHandle(const SDL_Event& event);
	void joyHatsHandle(const SDL_Event& event);
	void joyButtonHandle(const SDL_Event& event, bool valueToAppend);
	void setInputFunctionWithJoyButton(unsigned buttonNum, std::size_t configIndex, std::size_t buttonStateIndex, bool valueToAppend);
	
	void fillCrossMoveWithHats(const SDL_Event& event);
	void fillCrossMove(int x_value, int y_value);
	void fillCrossMoveWithAxes(const SDL_Event& event);
	void handleXCrossAxis(const SDL_Event& event);
	void handleYCrossAxis(const SDL_Event& event);
};

#endif //P1_USER_INPUTS_H