#ifndef DUELS_INPUTS_TYPES_H
#define DUELS_INPUTS_TYPES_H

#include "joystick/joystickEntity.h"
#include "contexts/duels/inGameObjects/playerInputs/inputsConsts.h"
#include "prefPath/prefPathFinder.h"
#include "contexts/duels/duelsConstexpr.h"
#include <array>
#include <memory>

struct AppLogFiles;
namespace duels{

struct JoystickFileData
{
	unsigned joystickNumber;
	unsigned joyMoveType;
	unsigned axisOrHatNum;
	unsigned axisMoveThreshold;
	std::array<unsigned, duels::JOY_BTN_MAX> buttons;
	
	JoystickFileData();
};
	
struct JoystickInp
{
	Uint8 joyNum;
	unsigned int joyMoveType;
	Uint8 axisOrHatNum;
	Sint16 axisMoveThreshold;
	std::array<Uint8, duels::JOY_BTN_MAX> buttons;
	
	explicit JoystickInp ( const JoystickFileData& joyFileData );
};

struct InputEntity
{
	unsigned deviceType;
	std::array<bool, INP_MAX> inputEffective;
	std::array<SDL_Keycode, KEY_MAX> keyboardInput;
	duels::JoystickInp joystick;
	
	explicit InputEntity(unsigned devType, const std::array<SDL_Keycode, KEY_MAX>& keybInp, const JoystickFileData& joyInfos);
};

struct ReadyToUseInputs
{
	bool isLoadingPerfect;
	std::array< std::unique_ptr<duels::InputEntity>, duels::PLAYER_MAX > playerEnt;
	std::array< sdl2::JoystickEntity, duels::PLAYER_MAX > openedJoysticks;
	
	explicit ReadyToUseInputs(AppLogFiles& logs, const PrefPathFinder& prefPath);
	~ReadyToUseInputs() = default;
	
	void saveDataToFile(AppLogFiles& logs, const PrefPathFinder& prefPath);
	void setJoystickNumWithDeviceType();
};

}

#endif //DUELS_INPUTS_TYPES_H