#include "contexts/duels/matchConfig/interface/helpTexts.h"
#include "logging/logsStruct.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "contexts/duels/matchConfig/textFilesLoading/fromStringsToTextures.h"
#include "contexts/duels/duelsConstexpr.h"
#include "consts/fontsConsts.h"
#include <string>
#include <fstream>

ZoneChoiceHelpTexts::ZoneChoiceHelpTexts(AppLogFiles& logs, const std::string& chosenLanguage, sdl2::RendererWindow& rndWnd):
	bonusesHelpTexts{logs.error, path::getLanguageFile(chosenLanguage, file::DUELS_ZONES_BONUSES), duels::DB_MAX},
	zonesNamesTexts{logs.error, path::getLanguageFile(chosenLanguage, file::DUELS_ZONES_NAMES) , duels::ZONE_MAX}
{
	createZoneChoiceTextsTextures(logs, rndWnd, bonusesHelpTexts, bonusesTextures, FONT_MEDIUM_PTSIZE);
	createZoneChoiceTextsTextures(logs, rndWnd, zonesNamesTexts, zonesNamesTextures, FONT_MEDIUM_PTSIZE);
}

bool ZoneChoiceHelpTexts::wasLoadingPerfect() const
{
	return bonusesHelpTexts.wasReadingPerfect() && zonesNamesTexts.wasReadingPerfect();
}

void ZoneChoiceHelpTexts::drawBonusesVignetteText(sdl2::RendererWindow& rndWnd, std::size_t index) const
{
	if( index < bonusesTextures.size() )
	{
		bonusesTextures[index].draw(rndWnd);
	}
}