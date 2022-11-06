#ifndef APP_START_LANGUAGE_STRINGS_H
#define APP_START_LANGUAGE_STRINGS_H

#include "prefPath/wxPrefPath.h"
#include "logging/logsStruct.h"
#include "texts/textLoader.h"

struct AppStartData
{
	const wxPrefPathFinder prefPath;
	AppLogFiles logs;
	const std::string savesEditorDataPathStr;
	TextsBlocks headersTexts;
	TextsBlocks gameObjectsTexts;
	TextsBlocks bagBonusesTexts;
	//TextsBlocks campaignLocaleTexts;
	
	explicit AppStartData();
	~AppStartData() = default;
	AppStartData( const AppStartData& ) = delete;
	AppStartData& operator= ( const AppStartData& ) = delete;
	AppStartData( AppStartData&& ) = default;
	AppStartData& operator= ( AppStartData&& ) = default;
	
	operator bool() const;
	
	void loadEverything();
	void loadTexts();
};

std::string getCampaignLocaleTextsFile(const std::string& language, const std::string& fileName);

#endif //APP_START_LANGUAGE_STRINGS_H