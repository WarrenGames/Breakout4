#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "prefPath/prefPathFinder.h"
#include "consts/constPaths.h"
#include "consts/onePlayerLevelConsts.h"
#include <cassert>

std::string path::getChosenLangFile(const PrefPathFinder& prefPath, const std::string& file)
{
	return prefPath.getPath() + DEST_LANG_DIR + "/" + file;
}

std::string path::getKeyboardConfigFile(const PrefPathFinder& prefPath, unsigned playerNum)
{
	return prefPath.getPath() + CONFIG_DIR + "/duels/duelsKeyboard" + std::to_string(playerNum + 1) + ".ini";
}

std::string path::getJoystickConfigFile(const PrefPathFinder& prefPath, unsigned playerNum)
{
	return prefPath.getPath() + CONFIG_DIR + "/duels/duelsJoystick" + std::to_string(playerNum + 1) + ".ini";
}

std::string path::getDeviceConfigFile(const PrefPathFinder& prefPath, unsigned playerNum)
{
	return prefPath.getPath() + CONFIG_DIR + "/duels/duelsDevice" + std::to_string(playerNum + 1) + ".ini";
}

std::string path::getDuelsLevelGridFile(const std::string& levelName)
{
	return "data/levels/duels/" + levelName ;
}

std::string path::getBonusEditBoxesTexturesPath()
{
	return "data/textures/duelsBonusEditBoxes.txt";
}

std::string path::getBonusesGranularitySlotPath(const PrefPathFinder& prefPath, unsigned slotNumber)
{
	return prefPath.getPath() + "config/duels/bonusesConfig_" + std::to_string( slotNumber ) + ".ini";
}

std::string path::getEditorLevelsGridsPath(const PrefPathFinder& prefPath)
{
	return prefPath.getPath() + LVL_GRID_SUB_PATH;
}

std::string path::getRaceLevelList(unsigned campaignType)
{
	switch( campaignType )
	{
		case onePlGame::CAMPAIGN_WITH_SHOP:
			return "data/levels/1player/shopRaceLevels.cfg";
			break;
		case onePlGame::CAMPAIGN_NO_SHOP:
			return "data/levels/1player/stdRaceLevels.cfg";
			break;
		default:
			assert( false && "Error: wrong campaign enum" );
			return "error";
			break;
	}
}

std::string path::getGameSaveFullPath(const PrefPathFinder& prefPath, unsigned saveSlotNumber)
{
	return prefPath.getPath() + SAVE_DIR_NAME + "/1player_save" + std::to_string( saveSlotNumber) + ".save";
}

std::string path::getStdRaceBestScoresFilePath(const PrefPathFinder& prefPath, unsigned skillLevel)
{
	assert( skillLevel < onePlGame::SKILL_LEVEL_MAX );
	return prefPath.getPath() + SCORES_DIR_NAME + "/bestScores_stdRace_" + std::to_string(skillLevel) + ".txt";
}

std::string path::getShopRaceBestScoresFilePath(const PrefPathFinder& prefPath, unsigned skillLevel)
{
	assert( skillLevel < onePlGame::SKILL_LEVEL_MAX );
	return prefPath.getPath() + SCORES_DIR_NAME + "/bestScores_shopRace_" + std::to_string(skillLevel) + ".txt";
}

std::string path::getLanguageFile(const std::string& chosenLanguage, const std::string& fileName)
{
	return std::string{"data/language/" + chosenLanguage + "/" + fileName};
}

std::string path::getConfigDirFile(const PrefPathFinder& prefPath, const std::string& fileName)
{
	return prefPath.getPath() + CONFIG_DIR + "/" + fileName;
}

std::string path::getInterfaceScript(const std::string& scriptName)
{
	return std::string{"data/interfaceScripts/" + scriptName };
}