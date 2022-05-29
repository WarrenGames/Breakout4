#include "contexts/duels/zones/simpleZone/simpleZoneArea.h"
#include "logging/logsStruct.h"
#include "texturing/texturePosition.h"
#include "contexts/duels/zones/allZonesConfig.h"
#include "consts/sdlColors.h"
#include "contexts/duels/duelsConstexpr.h"

duels::SimpleZone::SimpleZone(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& arial, unsigned pointsToPlay):
	isLoadingPerfect{true},
	levelGrid{GAME_SQUARES_WIDTH, GAME_SQUARES_HEIGHT},
	ballsAndCoinsSpawn{ Offset{ SQR_SIZE*2, GAME_SCREEN_HEIGHT/2}, Offset{ GAME_SCREEN_WIDTH/2, GAME_SCREEN_HEIGHT/2}, Offset{ GAME_SCREEN_WIDTH-SQR_SIZE*2, GAME_SCREEN_HEIGHT/2} },
	blueRim{logs, rndWnd, duels::BLUE_RIM_TEXTURE_PATH},
	redRim{logs, rndWnd, duels::RED_RIM_TEXTURE_PATH},
	brick{logs, rndWnd, "textures/sprites/bricks/bricksCluster_game.png"},
	textBackground{logs, rndWnd, BLACK_COL, SQR_SIZE*2, SQR_SIZE, TexturePosition{ GAME_SCREEN_WIDTH/2, GAME_SCREEN_HEIGHT/2, true, true} },
	remainingPoints{logs, rndWnd, arial, std::to_string( pointsToPlay ), WHITE_COL, TexturePosition{GAME_SCREEN_WIDTH/2, GAME_SCREEN_HEIGHT/2, true, true} }
{
	if( !( duels::loadLevelGridIsSuccess(logs, levelGrid, "simple.lvl") 
		&& blueRim.texture && redRim.texture && brick.texture && textBackground.texture && remainingPoints.texture ) )
		isLoadingPerfect = false;
}

void duels::SimpleZone::drawZone(sdl2::RendererWindow& rndWnd)
{
	for( std::size_t x{0} ; x < levelGrid.width() ; ++x )
	{
		for( std::size_t y{0} ; y < levelGrid.height() ; ++y )
		{
			switch( levelGrid(x, y).index )
			{
				case duels::GRID_ID_BLUERIM:
					blueRim.draw(rndWnd, static_cast<int>(x) * SQR_SIZE, static_cast<int>(y) * SQR_SIZE);
					break;
				case duels::GRID_ID_REDRIM:
					redRim.draw(rndWnd, static_cast<int>(x) * SQR_SIZE, static_cast<int>(y) * SQR_SIZE);
					break;
				case duels::GRID_ID_X4:
					brick.draw(rndWnd, static_cast<int>(x) * SQR_SIZE, static_cast<int>(y) * SQR_SIZE);
					break;
			}
		}
	}
}