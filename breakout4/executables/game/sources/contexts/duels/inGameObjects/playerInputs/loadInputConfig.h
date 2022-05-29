#ifndef LOAD_INPUT_CONFIG_H
#define LOAD_INPUT_CONFIG_H

#include "contexts/duels/inGameObjects/playerInputs/inputsTypes.h"
#include <memory>

struct AppLogFiles;
class PrefPathFinder;

namespace duels{
	
bool loadInputEntity(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned playerNum, std::unique_ptr<InputEntity>& inputPtr);

bool areInputRessourcesAllocated(AppLogFiles& logs, unsigned deviceType, const std::array<SDL_Keycode, KEY_MAX>& keybData, const JoystickFileData& joyFileData, std::unique_ptr<InputEntity>& inputPtr);

bool loadDeviceType(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned playerNum, unsigned& deviceType);

bool isDeviceTypeRead(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned playerNum, unsigned& deviceType, std::ifstream& deviceFile);

bool loadKeyboardData(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned playerNum, std::array<SDL_Keycode, KEY_MAX>& keybData);

bool areKeyboardDataRead(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned playerNum, std::array<SDL_Keycode, KEY_MAX>& keybData, std::ifstream& keybFile);

bool loadJoystickData(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned playerNum, JoystickFileData& joyFileData);

bool areJoystickDataRead(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned playerNum, JoystickFileData& joyData, std::ifstream& joystickFile);

void saveInputData(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned playerNum, const std::unique_ptr<duels::InputEntity>& inputPtr);

void saveDeviceData(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned playerNum, unsigned deviceType);

void saveKeyboardData(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned playerNum, const std::unique_ptr<duels::InputEntity>& inputPtr);

void saveJoystickData(AppLogFiles& logs, const PrefPathFinder& prefPath, unsigned playerNum, const std::unique_ptr<duels::InputEntity>& inputPtr);

}

#endif //LOAD_INPUT_CONFIG_H