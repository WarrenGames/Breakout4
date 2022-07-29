#include "contexts/duels/zones/metalStrings/subObjects/notStringsElements.h"
#include "contexts/duels/zones/metalStrings/subObjects/switchsData.h"
#include "types/essentialsStruct.h"
#include "contexts/duels/zones/allZonesConfig.h"
#include "contexts/duels/duelsConstexpr.h"
#include "contexts/duels/zones/metalStrings/subObjects/consts.h"

metalStrings::LevelBricks::LevelBricks(Essentials& essentials):
	isLoadingPerfect{true},
	levelGrid{GAME_SQUARES_WIDTH, GAME_SQUARES_HEIGHT},
	blueRim{essentials.logs, essentials.rndWnd, duels::BLUE_RIM_TEXTURE_PATH},
	redRim{essentials.logs, essentials.rndWnd, duels::RED_RIM_TEXTURE_PATH},
	brick{essentials.logs, essentials.rndWnd, "textures/sprites/bricks/bricksCluster_game.png"}
{	
	loadSwitchsTextures(essentials);
	
	if( !( duels::loadLevelGridIsSuccess(essentials.logs, levelGrid, "metalStringsSqr1.lvl") && blueRim.texture && redRim.texture && brick.texture ) )
		isLoadingPerfect = false;
}

void metalStrings::LevelBricks::drawZone(Essentials& essentials, const SwitchsData& switchs)
{
	for( std::size_t x{0} ; x < levelGrid.width() ; ++x )
	{
		for( std::size_t y{0} ; y < levelGrid.height() ; ++y )
		{
			switch( levelGrid(x, y).index )
			{
				case duels::GRID_ID_BLUERIM:
					blueRim.draw(essentials.rndWnd, static_cast<int>(x) * SQR_SIZE, static_cast<int>(y) * SQR_SIZE);
					break;
				case duels::GRID_ID_REDRIM:
					redRim.draw(essentials.rndWnd, static_cast<int>(x) * SQR_SIZE, static_cast<int>(y) * SQR_SIZE);
					break;
				case duels::GRID_ID_X4:
					brick.draw(essentials.rndWnd, static_cast<int>(x) * SQR_SIZE, static_cast<int>(y) * SQR_SIZE);
					break;
				case duels::GRID_ID_BUTTON:
					drawSwitch(essentials, switchs, x, y);
					break;
			}
		}
	}
}

void metalStrings::LevelBricks::drawSwitch(Essentials& essentials, const SwitchsData& switchs, std::size_t x, std::size_t y)
{
	for( std::size_t i{0} ; i < switchs.size() ; ++i )
	{
		if( switchs[i].coords.width == x && switchs[i].coords.height == y )
		{
			switchsTextures[ switchs[i].animFrame ].draw(essentials.rndWnd, static_cast<int>(x) * SQR_SIZE, static_cast<int>(y) * SQR_SIZE );
		}
	}
}

void metalStrings::LevelBricks::loadSwitchsTextures(Essentials& essentials)
{
	for( std::size_t i{0} ; i < metalStrings::SWITCHS_TEX_NUM ; ++i )
	{
		switchsTextures.emplace_back( TextureCombo{essentials.logs, essentials.rndWnd, "textures/sprites/switchs/quakeSwitch_" + std::to_string(i) + ".png"} );
	}
}
