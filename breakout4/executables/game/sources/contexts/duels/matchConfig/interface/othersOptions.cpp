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
	langTexts{logs.error, path::getLanguageFile(chosenLanguage, file::DUELS_OTHER_OPTIONS), duels::OTH_OPT_MAX}
{
	createTextsData(logs, rndWnd, fancyFont);
	createEditBoxes(logs, rndWnd, levelOptions);
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

void duels::OtherOptions::createTextsData(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont)
{
	for( std::size_t i{0} ; i < langTexts.size() ; ++i )
	{
		texts.emplace_back( TextureCombo{logs, rndWnd, fancyFont, langTexts[i], WHITE_COL, TexturePosition{SQR_SIZE*8, SQR_SIZE*(2 + static_cast<int>(i) )+ SQR_SIZE/4, false, true} } );
	}
}

void duels::OtherOptions::createEditBoxes(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, duels::LevelOptions& levelOptions)
{
	editBoxes.emplace_back( UintEditBox{logs, rndWnd, {GAME_SCREEN_WIDTH - SQR_SIZE*2, SQR_SIZE*2, BOX_W, BOX_H}, FONT_SMALL_PTSIZE, levelOptions.pointsToPlayInZone} );
	editBoxes.emplace_back( UintEditBox{logs, rndWnd, {GAME_SCREEN_WIDTH - SQR_SIZE*2, SQR_SIZE*3, BOX_W, BOX_H}, FONT_SMALL_PTSIZE, levelOptions.secondsBeforeNewCoin} );
	editBoxes.emplace_back( UintEditBox{logs, rndWnd, {GAME_SCREEN_WIDTH - SQR_SIZE*2, SQR_SIZE*4, BOX_W, BOX_H}, FONT_SMALL_PTSIZE, levelOptions.coinsMax} );
	editBoxes.emplace_back( UintEditBox{logs, rndWnd, {GAME_SCREEN_WIDTH - SQR_SIZE*2, SQR_SIZE*5, BOX_W, BOX_H}, FONT_SMALL_PTSIZE, levelOptions.secondsBeforeNewBall} );
	editBoxes.emplace_back( UintEditBox{logs, rndWnd, {GAME_SCREEN_WIDTH - SQR_SIZE*2, SQR_SIZE*6, BOX_W, BOX_H}, FONT_SMALL_PTSIZE, levelOptions.ballsMax} );
}
