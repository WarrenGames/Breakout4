#include "contexts/onePlayerGame/inGameMainMenu/race/graphicalInterface.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/constexprScreen.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/fontsConsts.h"
#include "consts/sdlColors.h"
#include "consts/constPaths.h"

onePlGame::raceMainMenu::Interface::Interface(Essentials& essentials, unsigned campaignType_):
	campaignType{campaignType_},
	languageTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::ONE_PLAY_SHOP_RACE_MENU), onePlGame::raceMainMenu::LanguageMax},
	fancyFont{essentials.logs.error, FancyFontPath, FontBigPointSize},
	screenTitle{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::raceMainMenu::LanguageTitle] + getCampTitle(campaignType_), BlackColor, 
					TexturePosition{GameScreenWidth/2, SQR_SIZE*2, true, true} },
	shopButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::raceMainMenu::LanguageShop], GreenColor, MediumGrayColor,
					TexturePosition{GameScreenWidth - SQR_SIZE * 2, SQR_SIZE*12, true, true} },
	screenBackground{essentials.logs, essentials.rndWnd, "textures/wallpapers/firTreeForest.png", TexturePosition{} }
{
	buttons.emplace_back( TextButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::raceMainMenu::LanguageSeeNextLevel], GreenColor, MediumGrayColor, 
										TexturePosition{ SQR_SIZE*4, SQR_SIZE*14, true, true} } );
	buttons.emplace_back( TextButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::raceMainMenu::LanguageRunLevel], GreenColor, MediumGrayColor, 
										TexturePosition{ SQR_SIZE*4, SQR_SIZE*12, true, true} });
	buttons.emplace_back( TextButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::raceMainMenu::LanguageSaveGame], GreenColor, MediumGrayColor, 
										TexturePosition{ GameScreenWidth / 2, SQR_SIZE*14, true, true} } );
	buttons.emplace_back( TextButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::raceMainMenu::LanguageChangeInput], GreenColor, MediumGrayColor, 
										TexturePosition{ GameScreenWidth / 2, SQR_SIZE*12, true, true} } );
	buttons.emplace_back( TextButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::raceMainMenu::LanguageQuit], GreenColor, MediumGrayColor, 
										TexturePosition{ GameScreenWidth - SQR_SIZE * 2, SQR_SIZE*14, true, true} } );
}

void onePlGame::raceMainMenu::Interface::updateButtons(const Offset& mousePosition, bool mouseButtonState)
{
	for( auto &btn : buttons )
	{
		btn.updateButton(mousePosition, mouseButtonState);
	}
}

void onePlGame::raceMainMenu::Interface::drawEverything(Essentials& essentials) const
{
	screenBackground.draw(essentials.rndWnd);
	screenTitle.draw(essentials.rndWnd);
	drawButtons(essentials);
}

void onePlGame::raceMainMenu::Interface::drawButtons(Essentials& essentials) const
{
	for( auto const &btn : buttons )
	{
		btn.drawButton(essentials.rndWnd);
	}
}

void onePlGame::raceMainMenu::Interface::updateShopButton(const Offset& mousePosition, bool mouseButtonState)
{
	if( onePlGame::CampaignWithShop == campaignType )
		shopButton.updateButton(mousePosition, mouseButtonState);
}

void onePlGame::raceMainMenu::Interface::drawShopButton(Essentials& essentials) const
{
	if( onePlGame::CampaignWithShop == campaignType )
		shopButton.drawButton(essentials.rndWnd);
}

std::string onePlGame::raceMainMenu::Interface::getCampTitle(unsigned campaignType_)
{
	switch( campaignType_ )
	{
		case onePlGame::CampaignWithShop:
			return languageTexts[onePlGame::raceMainMenu::LanguageShopRace];
			break;
		case onePlGame::CampaignNoShop:
			return languageTexts[onePlGame::raceMainMenu::LanguageStandardRace];
			break;
		default:
			return "error";
			break;
	}
}