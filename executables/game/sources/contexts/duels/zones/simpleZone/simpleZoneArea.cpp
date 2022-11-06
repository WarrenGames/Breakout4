#include "contexts/duels/zones/simpleZone/simpleZoneArea.h"
#include "logging/logsStruct.h"
#include "texturing/texturePosition.h"
#include "contexts/duels/zones/allZonesConfig.h"
#include "consts/sdlColors.h"
#include "contexts/duels/duelsConstexpr.h"

duels::SimpleZone::SimpleZone(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& arial, unsigned pointsToPlay):
	isLoadingPerfect{true},
	levelGrid{GameSquaresWidth, GameSquaresHeight},
	ballsAndCoinsSpawn{ Offset{ SQR_SIZE*2, GameScreenHeight/2}, Offset{ GameScreenWidth/2, GameScreenHeight/2}, Offset{ GameScreenWidth-SQR_SIZE*2, GameScreenHeight/2} },
	blueRim{logs, rndWnd, duels::BlueRimTexturePath},
	redRim{logs, rndWnd, duels::RedRimTexturePath},
	brick{logs, rndWnd, "textures/sprites/bricks/bricksCluster_game.png"},
	textBackground{logs, rndWnd, BlackColor, SQR_SIZE*2, SQR_SIZE, TexturePosition{ GameScreenWidth/2, GameScreenHeight/2, true, true} },
	remainingPoints{logs, rndWnd, arial, std::to_string( pointsToPlay ), WhiteColor, TexturePosition{GameScreenWidth/2, GameScreenHeight/2, true, true} }
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
				case duels::GridId_BlueRim:
					blueRim.draw(rndWnd, static_cast<int>(x) * SQR_SIZE, static_cast<int>(y) * SQR_SIZE);
					break;
				case duels::GridId_RedRim:
					redRim.draw(rndWnd, static_cast<int>(x) * SQR_SIZE, static_cast<int>(y) * SQR_SIZE);
					break;
				case duels::GridId_X4_Brick:
					brick.draw(rndWnd, static_cast<int>(x) * SQR_SIZE, static_cast<int>(y) * SQR_SIZE);
					break;
			}
		}
	}
}