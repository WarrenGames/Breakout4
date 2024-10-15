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
	TextsBlocks languageTexts;
	sdl2::Font fancyFont;
	RaceLevelsCount shopRaceLevelCount;
	RaceLevelsCount stdRaceLevelCount;
	TextureCombo screenTitle;
	TextureCombo backgroundImage;
	TextButton shopRaceSelection;
	TextButton noShopRaceSelection;
	TextureCombo shopRaceBackground;
	TextureCombo noShopRaceBackground;
	TextureCombo shopRaceLvlNumber;
	TextureCombo stdRaceLvlNumber;
	
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