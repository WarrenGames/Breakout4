#include "appStart/miniScreenGui.h"
#include "logging/logsStruct.h"
#include "texts/textLoader.h"
#include "texturing/texturePosition.h"
#include "consts/fontsConsts.h"
#include "consts/sdlColors.h"

MiniScreen::MiniScreen(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const TextsBlocks& texts, int squareSize, int screenWidth, int screenHeight):
	isLoadingPerfect{true},
	fancyFont{logs.error, FANCYFONTPATH, FONT_MEDIUM_PTSIZE},
	f1_fullScreenTxt{ logs, rndWnd, fancyFont, texts[0], WHITE_COL, TexturePosition{Offset{squareSize, squareSize*2}, false, true} },
	f5_windowedTxt{ logs, rndWnd, fancyFont, texts[1] + " (" + std::to_string(screenWidth) + " x " + std::to_string(screenHeight) 
					+ ") ", WHITE_COL, TexturePosition{Offset{squareSize, squareSize*4}, false, true} },
	betaVersion{ logs, rndWnd, fancyFont, texts[2], RED_COL, TexturePosition{Offset{squareSize, squareSize*5}, false, true} },
	bricksBackground{ logs, rndWnd, "textures/wallpapers/miniScreenBg.png", TexturePosition{} }
{
	if( !( fancyFont && f1_fullScreenTxt.texture && f5_windowedTxt.texture && bricksBackground.texture ) )
	{
		isLoadingPerfect = false;
		logs.error.wrSimpleMessage("Error: the loading of the 'mini screen' gui has failed.");
	}
}

MiniScreen::operator bool() const
{
	return fancyFont && f1_fullScreenTxt.texture && f5_windowedTxt.texture && bricksBackground.texture;
}

void MiniScreen::drawAll(sdl2::RendererWindow& rndWnd) const
{
	bricksBackground.draw(rndWnd);
	f1_fullScreenTxt.draw(rndWnd);
	f5_windowedTxt.draw(rndWnd);
	betaVersion.draw(rndWnd);
}