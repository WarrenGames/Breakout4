#include "contexts/onePlayerGame/inGameMainMenu/race/graphicalInterface.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/constexprScreen.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/sdlColors.h"
#include "consts/constPaths.h"

onePlGame::raceMainMenu::Interface::Interface(Essentials& essentials, unsigned campaignType_):
	campaignType{campaignType_},
	languageTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::ONE_PLAY_SHOP_RACE_MENU), onePlGame::raceMainMenu::LANG_MAX},
	fancyFont{essentials.logs.error, FANCYFONTPATH, FONT_BIG_PTSIZE},
	screenTitle{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::raceMainMenu::LANG_TITLE] + getCampTitle(campaignType_), BLACK_COL, 
					TexturePosition{GAME_SCREEN_WIDTH/2, SQR_SIZE*2, true, true} },
	buttons{
		TextButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::raceMainMenu::LANG_SEE_NEXT_LVL], GREEN_COL, MEDIUM_GRAY_COL, 
					TexturePosition{ SQR_SIZE*4, SQR_SIZE*14, true, true} },
		TextButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::raceMainMenu::LANG_RUN_LVL], GREEN_COL, MEDIUM_GRAY_COL, 
					TexturePosition{ SQR_SIZE*4, SQR_SIZE*12, true, true} },
		TextButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::raceMainMenu::LANG_SAVE_GAME], GREEN_COL, MEDIUM_GRAY_COL, 
					TexturePosition{ GAME_SCREEN_WIDTH / 2, SQR_SIZE*14, true, true} },
		TextButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::raceMainMenu::LANG_CHANGE_INP], GREEN_COL, MEDIUM_GRAY_COL, 
					TexturePosition{ GAME_SCREEN_WIDTH / 2, SQR_SIZE*12, true, true} },
		TextButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::raceMainMenu::LANG_QUIT], GREEN_COL, MEDIUM_GRAY_COL, 
					TexturePosition{ GAME_SCREEN_WIDTH - SQR_SIZE * 2, SQR_SIZE*14, true, true} } 
	},
	shopButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::raceMainMenu::LANG_SHOP], GREEN_COL, MEDIUM_GRAY_COL,
					TexturePosition{GAME_SCREEN_WIDTH - SQR_SIZE * 2, SQR_SIZE*12, true, true} },
	screenBackground{essentials.logs, essentials.rndWnd, "textures/wallpapers/firTreeForest.png", TexturePosition{} }
{
	
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
	if( onePlGame::CAMPAIGN_WITH_SHOP == campaignType )
		shopButton.updateButton(mousePosition, mouseButtonState);
}

void onePlGame::raceMainMenu::Interface::drawShopButton(Essentials& essentials) const
{
	if( onePlGame::CAMPAIGN_WITH_SHOP == campaignType )
		shopButton.drawButton(essentials.rndWnd);
}

std::string onePlGame::raceMainMenu::Interface::getCampTitle(unsigned campaignType_)
{
	switch( campaignType_ )
	{
		case onePlGame::CAMPAIGN_WITH_SHOP:
			return languageTexts[onePlGame::raceMainMenu::LANG_SHOP_RACE];
			break;
		case onePlGame::CAMPAIGN_NO_SHOP:
			return languageTexts[onePlGame::raceMainMenu::LANG_STD_RACE];
			break;
		default:
			return "error";
			break;
	}
}