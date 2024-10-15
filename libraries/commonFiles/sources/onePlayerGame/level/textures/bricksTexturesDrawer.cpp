#include "onePlayerGame/level/textures/bricksTexturesDrawer.h"
#include "onePlayerGame/level/textures/bricksTexturesLoader.h"
#include "texturing/rendererWindow.h"
#include "types/brickData.h"
#include "consts/onePlayerGridConsts.h"
#include <algorithm>
#include <cassert>

OnePBricksTextures::OnePBricksTextures(const BricksTexturesLoader& texturesLoader)
{
	linkSpritesToLoadedTextures(texturesLoader);
}

void OnePBricksTextures::linkSpritesToLoadedTextures(const BricksTexturesLoader& texturesLoader)
{
	if( texturesLoader.bricksTextures.empty() == false )
	{
		for( auto const &package : texturesLoader.bricksTextures )
		{
			sprites.emplace_back( ConstAnimDraw{ package } );
		}
	}
}

void OnePBricksTextures::drawSingleBrick(sdl2::RendererWindow& rndWnd, const BrickData& brickData, const Offset& position)
{
	if( brickData.index > 0 )
	{
		if( brickData.index <= sprites.size() )
		{
			if( brickData.property < sprites[brickData.index - 1].size() )
			{
				sprites[brickData.index - 1].draw(rndWnd, position, brickData.property);
			}
			else{
				assert( false && "Error: brick property data is too high !" );
			}
		}
		else{
			assert( false && "Error: brick index data is too high !" );
		}
	}
}
