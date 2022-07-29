#include "contexts/duels/matchConfig/graphics/zoneChoiceGraphics.h"
#include "types/essentialsStruct.h"
#include "texts/textLoader.h"
#include "texturing/texturePosition.h"
#include "contexts/duels/inGameObjects/gameElements/duelsTypes.h"
#include "contexts/duels/duelsConstexpr.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include <cassert>

ZoneChoiceGraphics::ZoneChoiceGraphics(Essentials& essentials, const sdl2::Font& fancyFont, const TextsBlocks& langTexts, duels::LevelOptions& levelOptions):
	grad{essentials.logs, essentials.rndWnd, SDL_Rect{ 0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT}, RED_COL, YELLOW_COL, GRAD_TEX_ON_Y},
	vignettes{essentials.logs, essentials.rndWnd},
	spin{essentials.logs, essentials.rndWnd},
	panelsTextures{ essentials.logs, essentials.rndWnd},
	colors{ BLUE_COL, RED_COL },
	playersStrings{langTexts[duels::MATCH_CFG_TXT_BLUE_PLAYER], langTexts[duels::MATCH_CFG_TXT_RED_PLAYER]},
	scoresTexts( duels::PLAYER_MAX ),
	spinsCoordinates{ Offset{ SQR_SIZE * 12, SQR_SIZE * 8}, Offset{0, SQR_SIZE * 2}, Offset{ SQR_SIZE * 7, SQR_SIZE * 2} },
	canChangeScoreGraphics{true}
{
	changeScoreGraphics(essentials, fancyFont, levelOptions);
}

void ZoneChoiceGraphics::drawEverything(Essentials& essentials, std::size_t panelIndex)
{
	grad.draw(essentials.rndWnd);
	vignettes.drawVignettes(essentials.rndWnd);
	drawSpins(essentials);
	panelsTextures.drawPanel(essentials.rndWnd, panelIndex);
	drawPlayerThings(essentials);
}

void ZoneChoiceGraphics::drawPlayerThings(Essentials& essentials) const
{
	for( unsigned player{0} ; player < duels::PLAYER_MAX ; ++player )
	{
		scoresTexts[player].draw(essentials.rndWnd);
	}
}

void ZoneChoiceGraphics::changeScoreGraphics(Essentials& essentials, const sdl2::Font& fancyFont, duels::LevelOptions& levelOptions)
{
	if( canChangeScoreGraphics )
	{
		for( unsigned player{0} ; player < duels::PLAYER_MAX ; ++player )
		{
			scoresTexts[player].texture.loadBlendedText(essentials.logs, essentials.rndWnd, fancyFont, playersStrings[player] + " : " + std::to_string(levelOptions.playersScores[player]), 
												colors[player]);
			scoresTexts[player].resetSpritePosition(TexturePosition{SQR_SIZE * 5 * ( static_cast<int>(player) * 2 + 1), GAME_SCREEN_HEIGHT - SQR_SIZE*3, true, true});
		}
		canChangeScoreGraphics = false;
	}
}

void ZoneChoiceGraphics::setScoreUpdateFlag()
{
	canChangeScoreGraphics = true;
}

void ZoneChoiceGraphics::drawSpins(Essentials& essentials)
{
	for( auto const &offset : spinsCoordinates )
	{
		spin.drawSpin(essentials.rndWnd, offset);
	}
}

bool ZoneChoiceGraphics::isSpinClicked(std::size_t spinNumber, const Offset& mousePosition, bool mouseButtonState) const
{
	assert( spinNumber < spinsCoordinates.size() );
	return mouseButtonState 
		&& mousePosition.x >= spinsCoordinates[spinNumber].x 
		&& mousePosition.x < spinsCoordinates[spinNumber].x + SQR_SIZE
		&& mousePosition.y >= spinsCoordinates[spinNumber].y
		&& mousePosition.y < spinsCoordinates[spinNumber].y + SQR_SIZE;
}