#ifndef PATH_MAKERS_H
#define PATH_MAKERS_H

#include "generic/fileSystem/fileProcessing/filesNames.h"
#include "fileSystem/fileSystem.h"
#include <string>

class PrefPathFinder;

namespace path{

fs::path getChosenLangFile(const PrefPathFinder& prefPath, const std::string& file);
	
fs::path getKeyboardConfigFile(const PrefPathFinder& prefPath, unsigned playerNum);

fs::path getJoystickConfigFile(const PrefPathFinder& prefPath, unsigned playerNum);

fs::path getDeviceConfigFile(const PrefPathFinder& prefPath, unsigned playerNum);

fs::path getDuelsLevelGridFile(const std::string& levelName);

fs::path getBonusesGranularitySlotPath(const PrefPathFinder& prefPath, unsigned slotNumber);

fs::path getRaceLevelList(unsigned campaignType);

fs::path getGameSaveFullPath(const PrefPathFinder& prefPath, unsigned saveSlotNumber);

fs::path getStdRaceBestScoresFilePath(const PrefPathFinder& prefPath, unsigned skillLevel);

fs::path getShopRaceBestScoresFilePath(const PrefPathFinder& prefPath, unsigned skillLevel);

fs::path getLanguageFile(const std::string& chosenLanguage, const std::string& fileName);

fs::path getConfigDirFile(const PrefPathFinder& prefPath, const std::string& fileName);

fs::path getDemoConfigFile(const PrefPathFinder& prefPath, const std::string& fileName);

fs::path getInterfaceScript(const std::string& scriptName);

}

#endif //PATH_MAKERS_H