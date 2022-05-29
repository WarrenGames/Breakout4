#include "contexts/duels/zones/halloween/subObjects/halloweenArea.h"
#include "types/essentialsStruct.h"
#include "contexts/duels/inGameObjects/gameElements/duelsTypes.h"
#include "texturing/texturePosition.h"
#include "contexts/duels/zones/allZonesConfig.h"
#include "consts/sdlColors.h"
#include "contexts/duels/duelsConstexpr.h"

constexpr std::size_t MUSHROOMS_NUMBER = 3;

duels::HalloweenArea::HalloweenArea(Essentials& essentials, const sdl2::Font& arial, unsigned pointsToPlay):
	isLoadingPerfect{true},
	levelGrid{GAME_SQUARES_WIDTH, GAME_SQUARES_HEIGHT},
	ballsAndCoinsSpawn{ Offset{ SQR_SIZE*2, GAME_SCREEN_HEIGHT/2}, Offset{ GAME_SCREEN_WIDTH/2, GAME_SCREEN_HEIGHT/2}, Offset{ GAME_SCREEN_WIDTH-SQR_SIZE*2, GAME_SCREEN_HEIGHT/2} },
	blueRim{essentials.logs, essentials.rndWnd, duels::BLUE_RIM_TEXTURE_PATH},
	redRim{essentials.logs, essentials.rndWnd, duels::RED_RIM_TEXTURE_PATH},
	brick{essentials.logs, essentials.rndWnd, "textures/sprites/bricks/bricksCluster_game.png"},
	pot{essentials.logs, essentials.rndWnd, "textures/gameZones/halloween/pot.png"},
	textBackground{essentials.logs, essentials.rndWnd, BLACK_COL, SQR_SIZE*2, SQR_SIZE, TexturePosition{GAME_SCREEN_WIDTH/2, GAME_SCREEN_HEIGHT/2, true, true} },
	remainingPoints{essentials.logs, essentials.rndWnd, arial, std::to_string( pointsToPlay ), WHITE_COL, TexturePosition{GAME_SCREEN_WIDTH/2, GAME_SCREEN_HEIGHT/2, true, true} }
{
	loadMushrooms(essentials);
	setMushroomsPositions();
	if( !( duels::loadLevelGridIsSuccess(essentials.logs, levelGrid, "halloween.lvl") && blueRim.texture && redRim.texture && brick.texture && pot.texture && textBackground.texture && remainingPoints.texture) )
		isLoadingPerfect = false;
}

void duels::HalloweenArea::loadMushrooms(Essentials& essentials)
{
	for( std::size_t i{0} ; i < MUSHROOMS_NUMBER ; ++i )
	{
		mushrooms.emplace_back( TextureCombo{essentials.logs, essentials.rndWnd, "textures/gameZones/halloween/mushroom" + std::to_string(i + 1) + ".png"} );
	}
}

void duels::HalloweenArea::setMushroomsPositions()
{
	mushrooms[0].resetSpritePosition(TexturePosition{ SQR_SIZE/2, GAME_SCREEN_HEIGHT - SQR_SIZE - mushrooms[0].sprite.height(), true, false});
	mushrooms[1].resetSpritePosition(TexturePosition{GAME_SCREEN_WIDTH - SQR_SIZE, GAME_SCREEN_HEIGHT - SQR_SIZE - mushrooms[1].sprite.height(), true, false});
	mushrooms[2].resetSpritePosition(TexturePosition{SQR_SIZE + SQR_SIZE / 2, GAME_SCREEN_HEIGHT - SQR_SIZE - mushrooms[2].sprite.height() , true, false});
}

void duels::HalloweenArea::drawZone(sdl2::RendererWindow& rndWnd)
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
				case duels::GRID_ID_POT_TEXTURE:
					pot.draw(rndWnd, static_cast<int>(x) * SQR_SIZE, static_cast<int>(y) * SQR_SIZE);
					break;
					
			}
		}
	}
}

void duels::HalloweenArea::drawMushrooms(sdl2::RendererWindow& rndWnd, const duels::LevelOptions& levelOptions) const
{
	if( false == levelOptions.halloween.canDisplayWallpaper )
	{
		for( auto const &mushroom : mushrooms )
		{
			mushroom.draw(rndWnd);
		}
	}
}
	