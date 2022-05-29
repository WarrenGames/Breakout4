#include "contexts/duels/matchConfig/interface/othersOptions.h"
#include "logging/logsStruct.h"
#include "texturing/texturePosition.h"
#include "contexts/duels/inGameObjects/gameElements/duelsTypes.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/sdlColors.h"
#include "consts/fontsConsts.h"

constexpr int BOX_W = SQR_SIZE;
constexpr int BOX_H = SQR_SIZE / 2;

duels::OtherOptions::OtherOptions(AppLogFiles& logs, const std::string& chosenLanguage, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, duels::LevelOptions& levelOptions):
	langTexts{logs.error, path::getLanguageFile(chosenLanguage, file::DUELS_OTHER_OPTIONS), duels::OTH_OPT_MAX},
	texts{
		TextureCombo{logs, rndWnd, fancyFont, langTexts[duels::PTS_PLAY_IN_ZONE], WHITE_COL, TexturePosition{SQR_SIZE*8, SQR_SIZE*2+SQR_SIZE/4, false, true} },
		TextureCombo{logs, rndWnd, fancyFont, langTexts[duels::SEC_BEF_NEW_COIN], WHITE_COL, TexturePosition{SQR_SIZE*8, SQR_SIZE*3+SQR_SIZE/4, false, true} },
		TextureCombo{logs, rndWnd, fancyFont, langTexts[duels::COIN_IN_ZONE_MAX], WHITE_COL, TexturePosition{SQR_SIZE*8, SQR_SIZE*4+SQR_SIZE/4, false, true} },
		TextureCombo{logs, rndWnd, fancyFont, langTexts[duels::SEC_BEF_NEW_BALL], WHITE_COL, TexturePosition{SQR_SIZE*8, SQR_SIZE*5+SQR_SIZE/4, false, true} },
		TextureCombo{logs, rndWnd, fancyFont, langTexts[duels::BALL_IN_ZONE_MAX], WHITE_COL, TexturePosition{SQR_SIZE*8, SQR_SIZE*6+SQR_SIZE/4, false, true} }
	},
	editBoxes{
		UintEditBox{logs, rndWnd, {GAME_SCREEN_WIDTH - SQR_SIZE*2, SQR_SIZE*2, BOX_W, BOX_H}, FONT_SMALL_PTSIZE, levelOptions.pointsToPlayInZone},
		UintEditBox{logs, rndWnd, {GAME_SCREEN_WIDTH - SQR_SIZE*2, SQR_SIZE*3, BOX_W, BOX_H}, FONT_SMALL_PTSIZE, levelOptions.secondsBeforeNewCoin},
		UintEditBox{logs, rndWnd, {GAME_SCREEN_WIDTH - SQR_SIZE*2, SQR_SIZE*4, BOX_W, BOX_H}, FONT_SMALL_PTSIZE, levelOptions.coinsMax},
		UintEditBox{logs, rndWnd, {GAME_SCREEN_WIDTH - SQR_SIZE*2, SQR_SIZE*5, BOX_W, BOX_H}, FONT_SMALL_PTSIZE, levelOptions.secondsBeforeNewBall},
		UintEditBox{logs, rndWnd, {GAME_SCREEN_WIDTH - SQR_SIZE*2, SQR_SIZE*6, BOX_W, BOX_H}, FONT_SMALL_PTSIZE, levelOptions.ballsMax}
	}
{

}

void duels::OtherOptions::catchUserFocus(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Offset& mousePos, bool mouseButton)
{
	for( auto &box : editBoxes )
		box.catchUserFocus(logs, rndWnd, mousePos, mouseButton);
}

void duels::OtherOptions::drawEverything(sdl2::RendererWindow& rndWnd) const
{
	drawBoxes(rndWnd);
	drawTexts(rndWnd);
}

void duels::OtherOptions::drawBoxes(sdl2::RendererWindow& rndWnd) const
{
	for( auto const &box : editBoxes )
		box.drawBoxWithoutFocus(rndWnd);
}

void duels::OtherOptions::drawTexts(sdl2::RendererWindow& rndWnd) const
{
	for( auto const &text : texts )
		text.draw(rndWnd);
}