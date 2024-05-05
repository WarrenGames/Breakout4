#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "prefPath/prefPathFinder.h"
#include "consts/constPaths.h"
#include "consts/onePlayerLevelConsts.h"
#include <cassert>

fs::path path::getChosenLangFile(const PrefPathFinder& prefPath, const std::string& file)
{
	fs::path finalPath{ prefPath.getFsPath() };
	finalPath /= DestinationLanguageDirectory;
	finalPath /= file;
	return finalPath;
}

fs::path path::getKeyboardConfigFile(const PrefPathFinder& prefPath, unsigned playerNum)
{
	fs::path finalPath{ prefPath.getFsPath() };
	finalPath /= ConfigurationDirectory;
	finalPath /= "duels/duelsKeyboard" + std::to_string(playerNum + 1) + ".ini";
	return finalPath;
}

fs::path path::getJoystickConfigFile(const PrefPathFinder& prefPath, unsigned playerNum)
{
	fs::path finalPath{ prefPath.getFsPath() };
	finalPath /= ConfigurationDirectory;
	finalPath /= "duels/duelsJoystick" + std::to_string(playerNum + 1) + ".ini";
	return finalPath;
}

fs::path path::getDeviceConfigFile(const PrefPathFinder& prefPath, unsigned playerNum)
{
	fs::path finalPath{ prefPath.getFsPath() };
	finalPath /= ConfigurationDirectory;
	finalPath /= "duels/duelsDevice" + std::to_string(playerNum + 1) + ".ini";
	return finalPath;
}

fs::path path::getDuelsLevelGridFile(const std::string& levelName)
{
	fs::path finalPath{ "data/levels/duels" };
	finalPath /= levelName;
	return finalPath;
}

fs::path path::getBonusesGranularitySlotPath(const PrefPathFinder& prefPath, unsigned slotNumber)
{
	fs::path finalPath{ prefPath.getFsPath() };
	finalPath /= "config/duels/bonusesConfig_" + std::to_string( slotNumber ) + ".ini";
	return finalPath;
}

fs::path path::getRaceLevelList(unsigned campaignType)
{
	switch( campaignType )
	{
		case onePlGame::CampaignWithShop:
			return fs::path{ onePlGame::ShopRaceLevelListFile };
			break;
		case onePlGame::CampaignNoShop:
			return fs::path{ onePlGame::NoShopRaceLevelListFile };
			break;
		default:
			assert( false && "Error: wrong campaign enum" );
			return fs::path{ "error" };
			break;
	}
}

fs::path path::getGameSaveFullPath(const PrefPathFinder& prefPath, unsigned saveSlotNumber)
{
	fs::path finalPath{ prefPath.getFsPath() };
	finalPath /= GameSavesDirectory;
	finalPath /= "1player_save" + std::to_string( saveSlotNumber) + ".save";
	return finalPath;
}

fs::path path::getStdRaceBestScoresFilePath(const PrefPathFinder& prefPath, unsigned skillLevel)
{
	assert( skillLevel < onePlGame::SkillLevelMax );
	fs::path finalPath{ prefPath.getFsPath() };
	finalPath /= ScoresDirectory;
	finalPath /= "bestScores_stdRace_" + std::to_string(skillLevel) + ".txt";
	return finalPath;	
}

fs::path path::getShopRaceBestScoresFilePath(const PrefPathFinder& prefPath, unsigned skillLevel)
{
	assert( skillLevel < onePlGame::SkillLevelMax );
	fs::path finalPath{ prefPath.getFsPath() };
	finalPath /= ScoresDirectory;
	finalPath /= "bestScores_shopRace_" + std::to_string(skillLevel) + ".txt";
	return finalPath;
}

fs::path path::getLanguageFile(const std::string& chosenLanguage, const std::string& fileName)
{
	fs::path finalPath{ "data/language" };
	finalPath /= chosenLanguage;
	finalPath /= fileName;
	return finalPath;
}

fs::path path::getConfigDirFile(const PrefPathFinder& prefPath, const std::string& fileName)
{
	fs::path finalPath{ prefPath.getFsPath() };
	finalPath /= ConfigurationDirectory;
	finalPath /= fileName;
	return finalPath;
}

fs::path path::getDemoConfigFile(const PrefPathFinder& prefPath, const std::string& fileName)
{
	fs::path finalPath{ prefPath.getFsPath() };
	finalPath /= DemosFilesDirectory;
	finalPath /= fileName;
	return finalPath;
}

fs::path path::getInterfaceScript(const std::string& scriptName)
{
	fs::path finalPath{ "data/interfaceScripts" };
	finalPath /= scriptName;
	return finalPath;
}