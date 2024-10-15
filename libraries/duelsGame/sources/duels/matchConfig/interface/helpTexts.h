#ifndef DUELS_ZONE_CHOICE_HELP_TEXTS_H
#define DUELS_ZONE_CHOICE_HELP_TEXTS_H

#include "texturing/texturesCombo.h"
#include "texts/textLoader.h"

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }

class ZoneChoiceHelpTexts
{
private:
	TextsBlocks bonusesHelpTexts;
	TextsBlocks zonesNamesTexts;
	std::vector< TextureCombo > bonusesTextures;
	std::vector< TextureCombo > zonesNamesTextures;
	
public:
	explicit ZoneChoiceHelpTexts(AppLogFiles& logs, const std::string& chosenLanguage, sdl2::RendererWindow& rndWnd);
	~ZoneChoiceHelpTexts() = default;
	ZoneChoiceHelpTexts( const ZoneChoiceHelpTexts& ) = delete;
	ZoneChoiceHelpTexts& operator= ( const ZoneChoiceHelpTexts& ) = delete;
	ZoneChoiceHelpTexts( ZoneChoiceHelpTexts&& ) = default;
	ZoneChoiceHelpTexts& operator= ( ZoneChoiceHelpTexts&& ) = default;
	
	bool wasLoadingPerfect() const;
	
	void drawBonusesVignetteText(sdl2::RendererWindow& rndWnd, std::size_t index) const;
};

#endif //DUELS_ZONE_CHOICE_HELP_TEXTS_H