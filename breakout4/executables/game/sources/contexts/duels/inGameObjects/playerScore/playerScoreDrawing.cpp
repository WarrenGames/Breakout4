#include "contexts/duels/inGameObjects/playerScore/playerScoreDrawing.h"
#include "logging/logsStruct.h"
#include "texturing/texturePosition.h"
#include "text/sdl2ttf_font.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

constexpr int BOX_WIDTH = SQR_SIZE * 3 / 4;
constexpr int BOX_HEIGHT = SQR_SIZE / 2;

duels::ScoreDraw::ScoreDraw(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& arialFont, const Offset& centerDrawPosition, int playerScore):
	mustUpdate{ true },
	offset{ centerDrawPosition },
	backgroundSquare{ logs, rndWnd, BLACK_COL, BOX_WIDTH, BOX_HEIGHT, 
						TexturePosition{centerDrawPosition.x, centerDrawPosition.y, true, true } } 
{
	updateIfPossible(logs, rndWnd, arialFont, playerScore);
}

void duels::ScoreDraw::updateIfPossible(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& arialFont, int playerScore)
{
	if( mustUpdate )
	{
		scoreText.texture.loadBlendedText(logs, rndWnd, arialFont, std::to_string(playerScore), WHITE_COL);
		scoreText.resetSpritePosition(TexturePosition{offset, true});
		mustUpdate = false;
	}
}

void duels::ScoreDraw::setUpdateFlag()
{
	mustUpdate = true;
}

void duels::ScoreDraw::drawScore(sdl2::RendererWindow& rndWnd) const
{
	backgroundSquare.draw(rndWnd);
	scoreText.draw(rndWnd);
}