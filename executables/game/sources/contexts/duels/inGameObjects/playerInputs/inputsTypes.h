#ifndef DUELS_INPUTS_TYPES_H
#define DUELS_INPUTS_TYPES_H

#include "joystick/joystickEntity.h"
#include "contexts/duels/inGameObjects/playerInputs/inputsConsts.h"
#include "prefPath/prefPathFinder.h"
#include "contexts/duels/duelsConstexpr.h"
#include <vector>
#include <memory>

struct AppLogFiles;
namespace duels{

struct JoystickFileData
{
	unsigned joystickNumber;
	unsigned joyMoveType;
	unsigned axisOrHatNum;
	unsigned axisMoveThreshold;
	std::vector<unsigned> buttons;
	
	JoystickFileData();
};
	
struct JoystickInp
{
	Uint8 joyNum;
	unsigned int joyMoveType;
	Uint8 axisOrHatNum;
	Sint16 axisMoveThreshold;
	std::vector<Uint8> buttons;
	
	explicit JoystickInp ( const JoystickFileData& joyFileData );
};

struct InputEntity
{
	unsigned deviceType;
	std::vector< bool > inputEffective;
	std::vector< SDL_Keycode > keyboardInput;
	duels::JoystickInp joystick;
	
	explicit InputEntity(unsigned devType, const std::vector<SDL_Keycode>& keybInp, const JoystickFileData& joyInfos);
};

struct ReadyToUseInputs
{
	std::vector< std::unique_ptr<duels::InputEntity> > playerEnt;
	std::vector< sdl2::JoystickEntity > openedJoysticks;
	bool isLoadingPerfect;
	
	explicit ReadyToUseInputs(AppLogFiles& logs, const PrefPathFinder& prefPath);
	~ReadyToUseInputs() = default;
	
	void saveDataToFile(AppLogFiles& logs, const PrefPathFinder& prefPath);
	void setJoystickNumWithDeviceType();
};

}

#endif //DUELS_INPUTS_TYPES_H