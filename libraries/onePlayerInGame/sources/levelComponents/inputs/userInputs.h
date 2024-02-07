#ifndef P1_USER_INPUTS_H
#define P1_USER_INPUTS_H

#include "levelComponents/inputs/playerActions.h"
#include "levelComponents/inputs/levelControls.h"
#include "demos/inputs/actionData.h"
#include "demos/templates/demoStack.h"

struct Essentials;
struct PlayerData;
namespace demos{ struct MainPackage; }

class LevelInputs
{
private:
	unsigned demoKind;
	PlayerActions playerActions;
	LevelControls levelControls;
	demos::Stack< demos::ActionData > inputDemoData;
	demos::Stack< demos::ActionData > levelEndDemoEvent;

public:
	explicit LevelInputs(Essentials& essentials, const PlayerData& playerData);
	~LevelInputs() = default;
	LevelInputs( const LevelInputs& ) = delete;
	LevelInputs& operator= ( const LevelInputs& ) = delete;
	LevelInputs( LevelInputs&& ) = default;
	LevelInputs& operator= ( LevelInputs&& ) = default;

	void updateEvents();
	void voidSpecialAction(std::size_t funcEnum);
	
	bool doesUserCloseWindow() const;
	void setEscapeToFalse();
	const Offset& getMousePosition() const;
	bool getMouseButtonState(std::size_t buttonIndex) const;
	bool getFuncState(std::size_t funcEnum) const;
	unsigned getCrossMoveDeviceType() const;
	
	const Offset& getCrossMove() const;
	
	SDL_Keycode getLastKeycode() const;
	void cancelLastKeycode();
	
	void joinDemosTimePoints();
	void moveMainPackageToInputs(demos::MainPackage& demosMainPackage);//Needed to run a 'pre-recorded' demo (not to 'record' a demo)
	void giveStacksContentsToMainPackage(demos::MainPackage& demosMainPackage);//Needed to 'record' a demo (not to 'run' a demo)
	void addQuitEvent();
};

#endif //P1_USER_INPUTS_H