#ifndef CAMPAIGN_CHOICE_GUI_H
#define CAMPAIGN_CHOICE_GUI_H

#include "texts/textLoader.h"
#include "texturing/texturesCombo.h"
#include "text/sdl2ttf_font.h"
#include "contexts/onePlayerGame/inGameMainMenu/campaignChoice/raceLevelsCount.h"
#include "consts/fontsConsts.h"
#include "widgets/buttons/textButtonWidget.h"

struct Essentials;

struct CampaignChoiceGui
{
	const TextsBlocks languageTexts;
	const sdl2::Font fancyFont;
	const RaceLevelsCount shopRaceLevelCount;
	const RaceLevelsCount stdRaceLevelCount;
	const TextureCombo screenTitle;
	TextButton shopRaceSelection;
	TextButton noShopRaceSelection;
	const TextureCombo shopRaceBackground;
	const TextureCombo noShopRaceBackground;
	const TextureCombo shopRaceLvlNumber;
	const TextureCombo stdRaceLvlNumber;
	
	explicit CampaignChoiceGui(Essentials& essentials);
	~CampaignChoiceGui() = default;
	CampaignChoiceGui( const CampaignChoiceGui& ) = delete;
	CampaignChoiceGui& operator= ( const CampaignChoiceGui& ) = delete;
	CampaignChoiceGui( CampaignChoiceGui&& ) = default;
	CampaignChoiceGui& operator= ( CampaignChoiceGui&& ) = default;
	
	void drawInterface(Essentials& essentials) const;
	
	void updateInterfaceWithInput(Essentials& essentials);
};

#endif //CAMPAIGN_CHOICE_GUI_H