#include "contexts/onePlayerGame/campaignEnd/campEndInterface.h"
#include "crossLevel/playerData.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

onePlGame::campaignEnd::Interface::Interface(Essentials& essentials, const PlayerData& playerData):
	fancyFont{essentials.logs.error, FANCYFONTPATH, FONT_BIG_PTSIZE},
	localTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::ONE_PLAY_CAMP_END), onePlGame::campaignEnd::MAX},
	wallpaper{essentials.logs, essentials.rndWnd, "textures/wallpapers/campaignEnd.png", TexturePosition{} },
	scoreText{essentials.logs, essentials.rndWnd, fancyFont, localTexts[onePlGame::campaignEnd::HERE_IS_YOUR_SCORE] + std::to_string(playerData.score), YELLOW_COL, 
				TexturePosition{GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT * 3 / 4, true, true} },
	greatings{essentials.logs, essentials.rndWnd, fancyFont, localTexts[onePlGame::campaignEnd::END_ANNOUNCEMENT], WHITE_COL, 
				TexturePosition{ GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2, true, true} },
	checkOutWebSite{essentials.logs, essentials.rndWnd, fancyFont, localTexts[onePlGame::campaignEnd::CHECK_UPDATE_OUT], WHITE_COL, 
				TexturePosition{GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT - SQR_SIZE, true, true} }
{
	
}

void onePlGame::campaignEnd::Interface::drawEverything(Essentials& essentials) const
{
	wallpaper.draw(essentials.rndWnd);
	scoreText.draw(essentials.rndWnd);
	greatings.draw(essentials.rndWnd);
	checkOutWebSite.draw(essentials.rndWnd);
}