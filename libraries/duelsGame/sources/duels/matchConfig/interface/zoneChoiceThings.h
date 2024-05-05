#ifndef DUELS_ZONE_CHOICE_THINGS_H
#define DUELS_ZONE_CHOICE_THINGS_H

#include "duels/inGameObjects/gameElements/duelsLevelOptions.h"
#include "duels/matchConfig/interface/bonusEditBoxes.h"
#include "duels/matchConfig/graphics/zoneChoiceGraphics.h"
#include "duels/matchConfig/interface/helpTexts.h"
#include "widgets/buttons/textButtonWidget.h"
#include "duels/matchConfig/interface/othersOptions.h"

struct Essentials;

struct ZoneChoiceThings
{
	unsigned selectedZone;
	const sdl2::Font fancyFont;
	const TextsBlocks screenTexts;
	duels::LevelOptions levelOptions;
	duels::BonusEditBoxes bonusBoxes;
	ZoneChoiceGraphics graphics;
	ZoneChoiceHelpTexts helpTexts;
	TextButton inputScreenButton;
	TextButton zoneChoiceButton;
	TextButton runZoneButton;
	const TextureCombo titleText;
	const TextureCombo finalAchievementHint;
	duels::OtherOptions ballAndCoinOptions;
	
	explicit ZoneChoiceThings(Essentials& essentials, unsigned finalAchievementHint);
	~ZoneChoiceThings() = default;
	ZoneChoiceThings( const ZoneChoiceThings& ) = delete;
	ZoneChoiceThings& operator= ( const ZoneChoiceThings& ) = delete;
	ZoneChoiceThings( ZoneChoiceThings&& ) = default;
	ZoneChoiceThings& operator= ( ZoneChoiceThings&& ) = default;
	
	void drawEverything(Essentials& essentials, const Offset& mousePosition);
	void displayHelpText(Essentials& essentials, const Offset& mousePosition) const;
	void displayBonusesVignettesHelpText(Essentials& essentials, const Offset& mousePosition) const;
	void catchUserFocus(Essentials& essentials, const Offset& mousePosition, bool buttonState);
	void updateScoreGraphics(Essentials& essentials);
};

#endif //DUELS_ZONE_CHOICE_THINGS_H