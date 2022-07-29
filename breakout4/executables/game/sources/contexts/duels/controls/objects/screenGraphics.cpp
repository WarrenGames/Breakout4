#include "contexts/duels/controls/objects/screenGraphics.h"
#include "texts/textLoader.h"
#include "logging/logsStruct.h"
#include "texturing/texturePosition.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "contexts/duels/duelsConstexpr.h"
#include "contexts/duels/controls/inputScreenConsts.h"
#include <cassert>

constexpr int HIGHL_BTN_W = 3;
constexpr int HIGHL_BTN_H = 1;
constexpr char NOT_LOADED[] = "Not loaded";

constexpr int TEXTS_LEFT_MARGIN = SQR_SIZE;

DuelsInpCfgGraphics::DuelsInpCfgGraphics(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, const TextsBlocks& texts):
	screenBackground{logs, rndWnd, SDL_Rect{ 0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT}, BLUE_COL, WHITE_COL, GRAD_TEX_ON_Y},
	screenTitle{logs, rndWnd, fancyFont, texts[duels::TXT_TITLE], BLACK_COL, 
					TexturePosition{GAME_SCREEN_WIDTH / 2, SQR_SIZE, true, true} },
	deviceText{logs, rndWnd, fancyFont, texts[duels::TXT_DEVICE], BLACK_COL, 
					TexturePosition{ TEXTS_LEFT_MARGIN, 4*SQR_SIZE+SQR_SIZE/2, false, true} }
{
	populateInputTextsVector(logs, rndWnd, fancyFont, texts);
	assert( inputTexts.size() == duels::INP_MAX );
}

void DuelsInpCfgGraphics::drawEverything(sdl2::RendererWindow& rndWnd) const
{
	screenBackground.draw(rndWnd);
	deviceText.draw(rndWnd);
	drawInputTexts(rndWnd);
	screenTitle.draw(rndWnd);
}

void DuelsInpCfgGraphics::drawInputTexts(sdl2::RendererWindow& rndWnd) const
{
	for( auto const &text : inputTexts )
		text.draw(rndWnd);
}

void DuelsInpCfgGraphics::populateInputTextsVector(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, const TextsBlocks& texts)
{
	inputTexts.emplace_back( TextureCombo{logs, rndWnd, fancyFont, texts[duels::TXT_MOVE_TO_LEFT], BLACK_COL, 
							TexturePosition{ TEXTS_LEFT_MARGIN, 5*SQR_SIZE+SQR_SIZE/2, false, true} } );
	inputTexts.emplace_back( TextureCombo{logs, rndWnd, fancyFont, texts[duels::TXT_MOVE_TO_RIGHT], BLACK_COL, 
							TexturePosition{ TEXTS_LEFT_MARGIN, 6*SQR_SIZE+SQR_SIZE/2, false, true} } );
	inputTexts.emplace_back( TextureCombo{logs, rndWnd, fancyFont, texts[duels::TXT_USE_BONUS], BLACK_COL, 
							TexturePosition{ TEXTS_LEFT_MARGIN, 7*SQR_SIZE+SQR_SIZE/2, false, true} } );
	inputTexts.emplace_back( TextureCombo{logs, rndWnd, fancyFont, texts[duels::TXT_ZONE_SPEC], BLACK_COL, 
							TexturePosition{ TEXTS_LEFT_MARGIN, 8*SQR_SIZE+SQR_SIZE/2, false, true} } );
}