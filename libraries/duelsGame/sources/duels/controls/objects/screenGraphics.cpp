#include "duels/controls/objects/screenGraphics.h"
#include "texts/textLoader.h"
#include "logging/logsStruct.h"
#include "texturing/texturePosition.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/duelsConstexpr.h"
#include "duels/controls/inputScreenConsts.h"
#include <cassert>

constexpr int TextsLeftMargin = SQR_SIZE;

DuelsInpCfgGraphics::DuelsInpCfgGraphics(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, const TextsBlocks& texts):
	screenBackground{logs, rndWnd, SDL_Rect{ 0, 0, GameScreenWidth, GameScreenHeight}, BlueColor, WhiteColor, GradientTextureOnY},
	screenTitle{logs, rndWnd, fancyFont, texts[duels::TextTitle], BlackColor, TexturePosition{GameScreenWidth / 2, SQR_SIZE, true, true} },
	deviceText{logs, rndWnd, fancyFont, texts[duels::TextDevice], BlackColor, TexturePosition{ TextsLeftMargin, 4*SQR_SIZE+SQR_SIZE/2, false, true} }
{
	populateInputTextsVector(logs, rndWnd, fancyFont, texts);
	assert( inputTexts.size() == duels::InputMax );
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
	inputTexts.emplace_back( TextureCombo{logs, rndWnd, fancyFont, texts[duels::TextMoveToLeft], BlackColor, 
							TexturePosition{ TextsLeftMargin, 5*SQR_SIZE+SQR_SIZE/2, false, true} } );
	inputTexts.emplace_back( TextureCombo{logs, rndWnd, fancyFont, texts[duels::TextMoveToRight], BlackColor, 
							TexturePosition{ TextsLeftMargin, 6*SQR_SIZE+SQR_SIZE/2, false, true} } );
	inputTexts.emplace_back( TextureCombo{logs, rndWnd, fancyFont, texts[duels::TextUseBonus], BlackColor, 
							TexturePosition{ TextsLeftMargin, 7*SQR_SIZE+SQR_SIZE/2, false, true} } );
	inputTexts.emplace_back( TextureCombo{logs, rndWnd, fancyFont, texts[duels::TextZoneSpecific], BlackColor, 
							TexturePosition{ TextsLeftMargin, 8*SQR_SIZE+SQR_SIZE/2, false, true} } );
}