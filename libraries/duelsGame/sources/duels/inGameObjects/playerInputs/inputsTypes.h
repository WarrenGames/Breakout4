#ifndef DUELS_INPUTS_TYPES_H
#define DUELS_INPUTS_TYPES_H

#include "joystick/joystickEntity.h"
#include "duels/inGameObjects/playerInputs/inputsConsts.h"
#include "prefPath/prefPathFinder.h"
#include "consts/duelsConstexpr.h"
#include "SDL_keycode.h"
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
	~JoystickFileData() = default;
	JoystickFileData( const JoystickFileData& ) = default;
	JoystickFileData& operator= ( const JoystickFileData& ) = default;
	JoystickFileData( JoystickFileData&& ) = default;
	JoystickFileData& operator= ( JoystickFileData&& ) = default;
};
	
struct JoystickInp
{
	unsigned int joyMoveType;
	Uint8 joyNum;
	Uint8 axisOrHatNum;
	Sint16 axisMoveThreshold;
	std::vector<Uint8> buttons;
	
	explicit JoystickInp ( const JoystickFileData& joyFileData );
	~JoystickInp() = default;
	JoystickInp( const JoystickInp& ) = default;
	JoystickInp& operator= ( const JoystickInp& ) = default;
	JoystickInp( JoystickInp&& ) = default;
	JoystickInp& operator= ( JoystickInp&& ) = default;
};

struct InputEntity
{
	unsigned deviceType;
	std::vector< bool > inputEffective;
	std::vector< SDL_Keycode > keyboardInput;
	duels::JoystickInp joystick;
	
	explicit InputEntity(unsigned devType, const std::vector<SDL_Keycode>& keybInp, const JoystickFileData& joyInfos);
	~InputEntity() = default;
	InputEntity( const InputEntity& ) = delete;
	InputEntity& operator= ( const InputEntity& ) = delete;
	InputEntity( InputEntity&& ) = default;
	InputEntity& operator= ( InputEntity&& ) = default;
};

struct ReadyToUseInputs
{
	std::vector< std::unique_ptr<duels::InputEntity> > playerEnt;
	std::vector< sdl2::JoystickEntity > openedJoysticks;
	bool isLoadingPerfect;
	
	explicit ReadyToUseInputs(AppLogFiles& logs, const PrefPathFinder& prefPath);
	~ReadyToUseInputs() = default;
	ReadyToUseInputs( const ReadyToUseInputs& ) = delete;
	ReadyToUseInputs& operator= ( const ReadyToUseInputs& ) = delete;
	ReadyToUseInputs( ReadyToUseInputs&& ) = default;
	ReadyToUseInputs& operator= ( ReadyToUseInputs&& ) = default;
	
	void saveDataToFile(AppLogFiles& logs, const PrefPathFinder& prefPath);
	void setJoystickNumWithDeviceType();
};

}

#endif //DUELS_INPUTS_TYPES_H