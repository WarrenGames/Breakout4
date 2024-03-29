#include "duels/matchConfig/interface/helpTexts.h"
#include "logging/logsStruct.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "duels/matchConfig/textFilesLoading/fromStringsToTextures.h"
#include "consts/duelsConstexpr.h"
#include "consts/fontsConsts.h"
#include <string>
#include <fstream>

ZoneChoiceHelpTexts::ZoneChoiceHelpTexts(AppLogFiles& logs, const std::string& chosenLanguage, sdl2::RendererWindow& rndWnd):
	bonusesHelpTexts{logs.error, path::getLanguageFile(chosenLanguage, file::DuelsZonesBonuses), duels::DuelBonusMax},
	zonesNamesTexts{logs.error, path::getLanguageFile(chosenLanguage, file::DuelsZonesNames) , duels::ZoneMax}
{
	createZoneChoiceTextsTextures(logs, rndWnd, bonusesHelpTexts, bonusesTextures, FontMediumPointSize);
	createZoneChoiceTextsTextures(logs, rndWnd, zonesNamesTexts, zonesNamesTextures, FontMediumPointSize);
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