#include "appStart/appStartData.h"
#include "generic/fileSystem/fileProcessing/filesNames.h"
#include "gameSlots/slotConsts.h"
#include "consts/consts.h"
#include "consts/constPaths.h"
#include "consts/onePlayerBonusesConsts.h"
#include "consts/constexprScreen.h"
#include <iostream>

constexpr char EditorErrorFile[] = "savesEditorErrorLog.txt";
constexpr char EditorWarningFile[] = "savesEditorWarningLog.txt";

AppStartData::AppStartData():
	prefPath{ CompanyName, GameName, SQR_SIZE },
	savesEditorDataPathStr{ SavesEditorDataPath }
{
	loadEverything();
}

AppStartData::operator bool() const
{
	return prefPath && logs && bagBonusesTexts && gameObjectsTexts && headersTexts;
}

void AppStartData::loadEverything()
{
	if( prefPath )
	{
		std::cout << "Pref path opened with success !\n";
		logs.openFiles( prefPath.getPath().ToStdString(), EditorErrorFile, EditorWarningFile );
		loadTexts();
	}
	else{
		std::cout << "Error: couldn't open 'pref path', because: " << prefPath.getError() << '\n';
	}	
}

void AppStartData::loadTexts()
{
	if( logs )
	{
		headersTexts.initializeTexts(logs.error, savesEditorDataPathStr + "savesEditorHeaders.txt", HeaderMax);
		gameObjectsTexts.initializeTexts(logs.error, savesEditorDataPathStr + "savesEditorGameObjects.txt", IndexMax );
		bagBonusesTexts.initializeTexts(logs.error, savesEditorDataPathStr + "savesEditorBagBonuses.txt", onePlGame::BonusMax );
		//campaignLocaleTexts.initializeTexts(logs.error, getCampaignLocaleTextsFile("english", file::ONE_PLAY_SAVE_AND_LOAD), SaveNameFocusingGameMax);
	}
	else{
		std::cout << "Error: couldn't open 'error log file' and/or 'warning log file' .\n";
	}
}

std::string getCampaignLocaleTextsFile(const std::string& language, const std::string& fileName)
{
	return std::string{"data/language/" + language + "/" + fileName};
}