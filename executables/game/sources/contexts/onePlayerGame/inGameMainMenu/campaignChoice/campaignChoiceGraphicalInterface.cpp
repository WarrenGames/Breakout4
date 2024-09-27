#include "contexts/onePlayerGame/inGameMainMenu/campaignChoice/campaignChoiceGraphicalInterface.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/constexprScreen.h"
#include "contexts/onePlayerGame/inGameMainMenu/campaignChoice/consts.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/fontsConsts.h"
#include "consts/sdlColors.h"
#include "consts/constPaths.h"

constexpr SDL_Color LevelsNumberColor = { 223, 223, 0, 255 };

CampaignChoiceGui::CampaignChoiceGui(Essentials& essentials):
	languageTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::OnePlayerCampaignChoice), campaignChoice::TextMax},
	fancyFont{essentials.logs.error, FancyFontPath, FontBigPointSize},
	shopRaceLevelCount{essentials, path::getRaceLevelList(onePlGame::CampaignWithShop) },
	stdRaceLevelCount{essentials, path::getRaceLevelList(onePlGame::CampaignNoShop) },
	screenTitle{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[campaignChoice::TitleText], WhiteColor, 
						TexturePosition{GameScreenWidth / 2, SQR_SIZE, true, true} },
	backgroundImage{essentials.logs, essentials.rndWnd, "textures/wallpapers/campaignChoice.png" },
	shopRaceSelection{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[campaignChoice::WithShopText], GreenColor, WhiteColor, 
						TexturePosition{GameScreenWidth / 4, GameScreenHeight * 3 / 4, true, true} },
	noShopRaceSelection{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[campaignChoice::StandardCampaignText], GreenColor, WhiteColor, 
						TexturePosition{GameScreenWidth * 3 / 4, GameScreenHeight * 3 / 4, true, true} },
	shopRaceBackground{essentials.logs, essentials.rndWnd, "textures/wallpapers/shopMiniScreen.png", 
						TexturePosition{GameScreenWidth / 4, 6 * SQR_SIZE, true, true} },
	noShopRaceBackground{essentials.logs, essentials.rndWnd, "textures/wallpapers/simpleRaceMiniScreen.png", 
						TexturePosition{GameScreenWidth * 3 / 4, 6 * SQR_SIZE, true, true} },
	shopRaceLvlNumber{essentials.logs, essentials.rndWnd, fancyFont, std::to_string(shopRaceLevelCount.getLevelsNumber() ) + languageTexts[campaignChoice::LevelText], 
						LevelsNumberColor, TexturePosition{GameScreenWidth / 4, GameScreenHeight - SQR_SIZE * 2, true, true} },
	stdRaceLvlNumber{essentials.logs, essentials.rndWnd, fancyFont, std::to_string(stdRaceLevelCount.getLevelsNumber() ) + languageTexts[campaignChoice::LevelText], 
						LevelsNumberColor, TexturePosition{GameScreenWidth * 3 / 4, GameScreenHeight - SQR_SIZE * 2, true, true} }
{

}

void CampaignChoiceGui::drawInterface(Essentials& essentials) const
{
	backgroundImage.draw(essentials.rndWnd);
	screenTitle.draw(essentials.rndWnd);
	shopRaceSelection.drawButton(essentials.rndWnd);
	noShopRaceSelection.drawButton(essentials.rndWnd);
	shopRaceBackground.draw(essentials.rndWnd);
	noShopRaceBackground.draw(essentials.rndWnd);
	shopRaceLvlNumber.draw(essentials.rndWnd);
	stdRaceLvlNumber.draw(essentials.rndWnd);
}

void CampaignChoiceGui::updateInterfaceWithInput(Essentials& essentials)
{
	shopRaceSelection.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	noShopRaceSelection.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
}