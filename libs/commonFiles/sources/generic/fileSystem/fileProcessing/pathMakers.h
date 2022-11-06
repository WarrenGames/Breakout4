#ifndef PATH_MAKERS_H
#define PATH_MAKERS_H

#include "generic/fileSystem/fileProcessing/filesNames.h"
#include <string>

class PrefPathFinder;

namespace path{

std::string getChosenLangFile(const PrefPathFinder& prefPath, const std::string& file);
	
std::string getKeyboardConfigFile(const PrefPathFinder& prefPath, unsigned playerNum);

std::string getJoystickConfigFile(const PrefPathFinder& prefPath, unsigned playerNum);

std::string getDeviceConfigFile(const PrefPathFinder& prefPath, unsigned playerNum);

std::string getDuelsLevelGridFile(const std::string& levelName);

std::string getBonusEditBoxesTexturesPath();

std::string getBonusesGranularitySlotPath(const PrefPathFinder& prefPath, unsigned slotNumber);

std::string getEditorLevelsGridsPath(const PrefPathFinder& prefPath);

std::string getOnePlayerJoyCrossFile(const PrefPathFinder& prefPath);

std::string getJoystickDetailsTextsFile(const std::string& chosenLanguage);

std::string getRaceLevelList(unsigned campaignType);

std::string getGameSaveFullPath(const PrefPathFinder& prefPath, unsigned saveSlotNumber);

std::string getStdRaceBestScoresFilePath(const PrefPathFinder& prefPath, unsigned skillLevel);

std::string getShopRaceBestScoresFilePath(const PrefPathFinder& prefPath, unsigned skillLevel);

std::string getLanguageFile(const std::string& chosenLanguage, const std::string& fileName);

std::string getConfigDirFile(const PrefPathFinder& prefPath, const std::string& fileName);

std::string getAvailableLanguages();

std::string getInterfaceScript(const std::string& scriptName);

}

#endif //PATH_MAKERS_H