#include "contexts/onePlayerGame/inGameMainMenu/campaignChoice/graphicalInterface.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/constexprScreen.h"
#include "contexts/onePlayerGame/inGameMainMenu/campaignChoice/consts.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/fontsConsts.h"
#include "consts/sdlColors.h"
#include "consts/constPaths.h"

CampaignChoiceGui::CampaignChoiceGui(Essentials& essentials):
	languageTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::ONE_PLAY_CAMP_CHOICE), campaignChoice::TextMax},
	fancyFont{essentials.logs.error, FancyFontPath, FontBigPointSize},
	shopRaceLevelCount{essentials, path::getRaceLevelList(onePlGame::CampaignWithShop) },
	stdRaceLevelCount{essentials, path::getRaceLevelList(onePlGame::CampaignNoShop) },
	screenTitle{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[campaignChoice::TitleText], WhiteColor, 
						TexturePosition{GameScreenWidth / 2, SQR_SIZE, true, true} },
	shopRaceSelection{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[campaignChoice::WithShopText], GreenColor, MediumGrayColor, 
						TexturePosition{GameScreenWidth / 4, GameScreenHeight * 3 / 4, true, true} },
	noShopRaceSelection{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[campaignChoice::StandardCampaignText], GreenColor, MediumGrayColor, 
						TexturePosition{GameScreenWidth * 3 / 4, GameScreenHeight * 3 / 4, true, true} },
	shopRaceBackground{essentials.logs, essentials.rndWnd, "textures/wallpapers/shopMiniScreen.png", 
						TexturePosition{GameScreenWidth / 4, 6 * SQR_SIZE, true, true} },
	noShopRaceBackground{essentials.logs, essentials.rndWnd, "textures/wallpapers/simpleRaceMiniScreen.png", 
						TexturePosition{GameScreenWidth * 3 / 4, 6 * SQR_SIZE, true, true} },
	shopRaceLvlNumber{essentials.logs, essentials.rndWnd, fancyFont, std::to_string(shopRaceLevelCount.getLevelsNumber() ) + languageTexts[campaignChoice::LevelText], WhiteColor, 
						TexturePosition{GameScreenWidth / 4, GameScreenHeight - SQR_SIZE * 2, true, true} },
	stdRaceLvlNumber{essentials.logs, essentials.rndWnd, fancyFont, std::to_string(stdRaceLevelCount.getLevelsNumber() ) + languageTexts[campaignChoice::LevelText], WhiteColor, 
						TexturePosition{GameScreenWidth * 3 / 4, GameScreenHeight - SQR_SIZE * 2, true, true} }
{

}

void CampaignChoiceGui::drawInterface(Essentials& essentials) const
{
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