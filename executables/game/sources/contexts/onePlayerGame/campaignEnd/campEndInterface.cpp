#include "contexts/onePlayerGame/campaignEnd/campEndInterface.h"
#include "crossLevel/playerData.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

onePlGame::campaignEnd::Interface::Interface(Essentials& essentials, const PlayerData& playerData):
	fancyFont{essentials.logs.error, FancyFontPath, FontBigPointSize},
	localTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::OnePlayerCampaignEnd), onePlGame::campaignEnd::Max},
	wallpaper{essentials.logs, essentials.rndWnd, "textures/wallpapers/campaignEnd.png", TexturePosition{} },
	scoreText{essentials.logs, essentials.rndWnd, fancyFont, localTexts[onePlGame::campaignEnd::HereIsYourScore] + std::to_string(playerData.score), YellowColor, 
				TexturePosition{GameScreenWidth / 2, GameScreenHeight * 3 / 4, true, true} },
	greatings{essentials.logs, essentials.rndWnd, fancyFont, localTexts[onePlGame::campaignEnd::EndAnnouncement], WhiteColor, 
				TexturePosition{ GameScreenWidth / 2, GameScreenHeight / 2, true, true} },
	checkOutWebSite{essentials.logs, essentials.rndWnd, fancyFont, localTexts[onePlGame::campaignEnd::CheckUpdateOut], WhiteColor, 
				TexturePosition{GameScreenWidth / 2, GameScreenHeight - SQR_SIZE, true, true} }
{
	
}

void onePlGame::campaignEnd::Interface::drawEverything(Essentials& essentials) const
{
	wallpaper.draw(essentials.rndWnd);
	scoreText.draw(essentials.rndWnd);
	greatings.draw(essentials.rndWnd);
	checkOutWebSite.draw(essentials.rndWnd);
}