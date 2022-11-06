#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "prefPath/prefPathFinder.h"
#include "consts/constPaths.h"
#include "consts/onePlayerLevelConsts.h"
#include <cassert>

std::string path::getChosenLangFile(const PrefPathFinder& prefPath, const std::string& file)
{
	return prefPath.getPath() + DestinationLanguageDirectory + "/" + file;
}

std::string path::getKeyboardConfigFile(const PrefPathFinder& prefPath, unsigned playerNum)
{
	return prefPath.getPath() + ConfigurationDirectory + "/duels/duelsKeyboard" + std::to_string(playerNum + 1) + ".ini";
}

std::string path::getJoystickConfigFile(const PrefPathFinder& prefPath, unsigned playerNum)
{
	return prefPath.getPath() + ConfigurationDirectory + "/duels/duelsJoystick" + std::to_string(playerNum + 1) + ".ini";
}

std::string path::getDeviceConfigFile(const PrefPathFinder& prefPath, unsigned playerNum)
{
	return prefPath.getPath() + ConfigurationDirectory + "/duels/duelsDevice" + std::to_string(playerNum + 1) + ".ini";
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
	return prefPath.getPath() + LevelGridSubDirectory;
}

std::string path::getRaceLevelList(unsigned campaignType)
{
	switch( campaignType )
	{
		case onePlGame::CampaignWithShop:
			return onePlGame::ShopRaceLevelListFile;
			break;
		case onePlGame::CampaignNoShop:
			return onePlGame::NoShopRaceLevelListFile;
			break;
		default:
			assert( false && "Error: wrong campaign enum" );
			return "error";
			break;
	}
}

std::string path::getGameSaveFullPath(const PrefPathFinder& prefPath, unsigned saveSlotNumber)
{
	return prefPath.getPath() + GameSavesDirectory + "/1player_save" + std::to_string( saveSlotNumber) + ".save";
}

std::string path::getStdRaceBestScoresFilePath(const PrefPathFinder& prefPath, unsigned skillLevel)
{
	assert( skillLevel < onePlGame::SkillLevelMax );
	return prefPath.getPath() + ScoresDirectory + "/bestScores_stdRace_" + std::to_string(skillLevel) + ".txt";
}

std::string path::getShopRaceBestScoresFilePath(const PrefPathFinder& prefPath, unsigned skillLevel)
{
	assert( skillLevel < onePlGame::SkillLevelMax );
	return prefPath.getPath() + ScoresDirectory + "/bestScores_shopRace_" + std::to_string(skillLevel) + ".txt";
}

std::string path::getLanguageFile(const std::string& chosenLanguage, const std::string& fileName)
{
	return std::string{"data/language/" + chosenLanguage + "/" + fileName};
}

std::string path::getConfigDirFile(const PrefPathFinder& prefPath, const std::string& fileName)
{
	return prefPath.getPath() + ConfigurationDirectory + "/" + fileName;
}

std::string path::getInterfaceScript(const std::string& scriptName)
{
	return std::string{"data/interfaceScripts/" + scriptName };
}