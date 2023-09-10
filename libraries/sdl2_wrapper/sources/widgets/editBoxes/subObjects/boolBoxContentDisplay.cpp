#include "widgets/editBoxes/subObjects/boolBoxContentDisplay.h"
#include "logging/logsStruct.h"
#include "texturing/texturePosition.h"
#include "widgets/editBoxes/subObjects/editBoxes_consts.h"

constexpr SDL_Color GreenCol = { 0, 255, 0, 255 };
constexpr SDL_Color RedCol = { 255, 0, 0, 255 };

BoolBoxContentDisplay::BoolBoxContentDisplay(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned fontSize, const SDL_Rect& boxRect):
	arialFont{logs.error, BoxesArialFontPath, fontSize},
	trueTextTexture{ logs, rndWnd, arialFont, "true", GreenCol, TexturePosition{Offset{boxRect.x + boxRect.w / 2, boxRect.y + boxRect.h / 2}, true, true } }, 
	falseTextTexture{ logs, rndWnd, arialFont, "false", RedCol, TexturePosition{Offset{boxRect.x + boxRect.w / 2, boxRect.y + boxRect.h / 2}, true, true} }
{
	
}

void BoolBoxContentDisplay::drawTrue(sdl2::RendererWindow& rndWnd) const
{
	trueTextTexture.draw(rndWnd);
}

void BoolBoxContentDisplay::drawFalse(sdl2::RendererWindow& rndWnd) const
{
	falseTextTexture.draw(rndWnd);
}