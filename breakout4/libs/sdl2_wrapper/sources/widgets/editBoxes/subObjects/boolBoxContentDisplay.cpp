#include "widgets/editBoxes/subObjects/boolBoxContentDisplay.h"
#include "logging/logsStruct.h"
#include "texturing/texturePosition.h"
#include "widgets/editBoxes/subObjects/editBoxes_consts.h"

constexpr SDL_Color GREEN_COL = { 0, 255, 0, 255 };
constexpr SDL_Color RED_COL = { 255, 0, 0, 255 };

BoolBoxContentDisplay::BoolBoxContentDisplay(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned fontSize, const SDL_Rect& boxRect):
	arialFont{logs.error, BOXES_ARIALFONTPATH, fontSize},
	trueTextTexture{ logs, rndWnd, arialFont, "true", GREEN_COL, TexturePosition{Offset{boxRect.x + boxRect.w / 2, boxRect.y + boxRect.h / 2}, true, true } }, 
	falseTextTexture{ logs, rndWnd, arialFont, "false", RED_COL, TexturePosition{Offset{boxRect.x + boxRect.w / 2, boxRect.y + boxRect.h / 2}, true, true} }
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