#include "contexts/onePlayerGame/inputConfig/staticGraphics.h"
#include "types/essentialsStruct.h"
#include "texts/textLoader.h"
#include "advancedDrawing/interfaceGeneratorLanguage/elementsLoadingFunctions/texturesComponent.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include <algorithm>

constexpr char CONST_GUI_SCRIPT[] = "onePlayerInputConsts.txt";
constexpr char ASK_GUI_SCRIPT[] = "onePlayerInputAsk.txt";

onePlGame::StaticGraphics::StaticGraphics(Essentials& essentials, const sdl2::Font& fancyFont, const TextsBlocks& languageTexts):
	screenBackground{essentials.logs, essentials.rndWnd, {0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT}, BLUE_COL, WHITE_COL, GRAD_TEX_ON_Y}
{
	igl::texture::openScriptFile(essentials.logs, essentials.rndWnd, fancyFont, languageTexts, alwaysDrawnTextures, path::getInterfaceScript(CONST_GUI_SCRIPT), SQR_SIZE);
	igl::texture::openScriptFile(essentials.logs, essentials.rndWnd, fancyFont, languageTexts, askInputTextures, path::getInterfaceScript(ASK_GUI_SCRIPT), SQR_SIZE);
}

onePlGame::StaticGraphics::operator bool() const
{
	return std::all_of(std::cbegin(alwaysDrawnTextures), std::cend(alwaysDrawnTextures), [](auto const &tex){ return tex.texture.wasLoadingPerfect(); }) 
		&& std::all_of(std::cbegin(askInputTextures), std::cend(askInputTextures), [](auto const &tex){ return tex.texture.wasLoadingPerfect(); } )
		&& screenBackground;
}

void onePlGame::StaticGraphics::drawEverything(Essentials& essentials) const
{
	screenBackground.draw(essentials.rndWnd);
	for( auto const &tex : alwaysDrawnTextures )
	{
		tex.draw(essentials.rndWnd);
	}
}

void onePlGame::StaticGraphics::drawInputArrayLines(Essentials& essentials) const
{
	essentials.rndWnd.drawRect(WHITE_COL, SDL_Rect{SQR_SIZE*1, SQR_SIZE*3, SQR_SIZE*6, SQR_SIZE*7});
	essentials.rndWnd.drawRect(WHITE_COL, SDL_Rect{SQR_SIZE*7, SQR_SIZE*3, SQR_SIZE*6, SQR_SIZE*7});
	essentials.rndWnd.drawRect(WHITE_COL, SDL_Rect{SQR_SIZE*13, SQR_SIZE*3, SQR_SIZE*6, SQR_SIZE*7});
	essentials.rndWnd.drawRect(WHITE_COL, SDL_Rect{SQR_SIZE*7, SQR_SIZE*2, SQR_SIZE*6, SQR_SIZE});
	essentials.rndWnd.drawRect(WHITE_COL, SDL_Rect{SQR_SIZE*13, SQR_SIZE*2, SQR_SIZE*6, SQR_SIZE});
}