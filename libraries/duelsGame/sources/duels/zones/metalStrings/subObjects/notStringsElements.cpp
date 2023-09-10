#include "duels/zones/metalStrings/subObjects/notStringsElements.h"
#include "duels/zones/metalStrings/subObjects/switchsData.h"
#include "types/essentialsStruct.h"
#include "duels/zones/allZonesConfig.h"
#include "consts/duelsConstexpr.h"
#include "duels/zones/metalStrings/subObjects/consts.h"
#include <cassert>

metalStrings::LevelBricks::LevelBricks(Essentials& essentials):
	levelGrid{GameSquaresWidth, GameSquaresHeight},
	blueRim{essentials.logs, essentials.rndWnd, duels::BlueRimTexturePath},
	redRim{essentials.logs, essentials.rndWnd, duels::RedRimTexturePath},
	brick{essentials.logs, essentials.rndWnd, "textures/sprites/bricks/bricksCluster_game.png"},
	isLoadingPerfect{true}
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
				case duels::GridId_BlueRim:
					blueRim.draw(essentials.rndWnd, static_cast<int>(x) * SQR_SIZE, static_cast<int>(y) * SQR_SIZE);
					break;
				case duels::GridId_RedRim:
					redRim.draw(essentials.rndWnd, static_cast<int>(x) * SQR_SIZE, static_cast<int>(y) * SQR_SIZE);
					break;
				case duels::GridId_X4_Brick:
					brick.draw(essentials.rndWnd, static_cast<int>(x) * SQR_SIZE, static_cast<int>(y) * SQR_SIZE);
					break;
				case duels::GridId_Button:
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
			assert( switchs[i].animFrame < switchsTextures.size() );
			switchsTextures[ switchs[i].animFrame ].draw(essentials.rndWnd, static_cast<int>(x) * SQR_SIZE, static_cast<int>(y) * SQR_SIZE );
		}
	}
}

void metalStrings::LevelBricks::loadSwitchsTextures(Essentials& essentials)
{
	for( std::size_t i{0} ; i < metalStrings::SwitchsTexturesNumber ; ++i )
	{
		switchsTextures.emplace_back( TextureCombo{essentials.logs, essentials.rndWnd, "textures/sprites/switchs/quakeSwitch_" + std::to_string(i) + ".png"} );
	}
}
