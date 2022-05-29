#include "onePlayerGame/level/textures/bricksTexturesDrawer.h"
#include "onePlayerGame/level/textures/bricksTexturesLoader.h"
#include "texturing/rendererWindow.h"
#include "types/brickData.h"
#include "consts/onePlayerGridConsts.h"
#include <algorithm>
#include <cassert>

OnePBricksTextures::OnePBricksTextures(BricksTexturesLoader& texturesLoader):
	generic{ texturesLoader.generic },
	rich{ texturesLoader.rich },
	bonusBrick{ texturesLoader.bonusBrick },
	giftBricks{ texturesLoader.giftBricks },
	tenPtsBricks{ texturesLoader.tenPtsBricks },
	hardBricks{ texturesLoader.hardBricks },
	iceCubeBrick{ texturesLoader.iceCubeBrick },
	pinguinBrick{ texturesLoader.pinguinBrick },
	skullBrick{ texturesLoader.skullBrick },
	lavaStoneBricks{ texturesLoader.lavaStoneBricks }
{
	
}

void OnePBricksTextures::drawSingleBrick(sdl2::RendererWindow& rndWnd, const BrickData& brickData, const Offset& position)
{
	switch( brickData.index )
	{
		case BRICKS::INDEX::GEN_BRICK:
			drawGeneric(rndWnd, brickData.property, position);
			break;
		case BRICKS::INDEX::RICH_BRICK:
			drawRich(rndWnd, brickData.property, position);
			break;
		case BRICKS::INDEX::BONUS_COIN:
			drawBonusCoinBrick(rndWnd, position);
			break;
		case BRICKS::INDEX::GIFT_BRICK:
			drawGiftBrick(rndWnd, brickData.property, position);
			break;
		case BRICKS::INDEX::TEN_POINTS:
			drawTenPtsBricks(rndWnd, brickData.property, position);
			break;
		case BRICKS::INDEX::SOLID:
			drawSolidBrick(rndWnd, brickData.property, position);
			break;
		case BRICKS::INDEX::ICE_BRICKS:
			drawIceBricks(rndWnd, brickData.property, position);
			break;
		case BRICKS::INDEX::HELL_BRICKS:
			drawHellBricks(rndWnd, brickData.property, position);
			break;
	}
}

void OnePBricksTextures::drawGeneric(sdl2::RendererWindow& rndWnd, unsigned brickInfo, const Offset& position)
{
	if( brickInfo < generic.size() )
		generic.draw(rndWnd, position, brickInfo);
}

void OnePBricksTextures::drawRich(sdl2::RendererWindow& rndWnd, unsigned brickInfo, const Offset& position)
{
	if( brickInfo < rich.size() )
		rich.draw(rndWnd, position, brickInfo);
}

void OnePBricksTextures::drawBonusCoinBrick(sdl2::RendererWindow& rndWnd, const Offset& position)
{
	bonusBrick.draw(rndWnd, position);
}

void OnePBricksTextures::drawGiftBrick(sdl2::RendererWindow& rndWnd, unsigned brickInfo, const Offset& position)
{
	if( brickInfo < giftBricks.size() )
		giftBricks.draw(rndWnd, position, brickInfo);
}

void OnePBricksTextures::drawTenPtsBricks(sdl2::RendererWindow& rndWnd, unsigned brickInfo, const Offset& position)
{
	if( brickInfo < tenPtsBricks.size() )
	{
		tenPtsBricks.draw(rndWnd, position, brickInfo);
	}
}

void OnePBricksTextures::drawSolidBrick(sdl2::RendererWindow& rndWnd, unsigned brickInfo, const Offset& position)
{
	if( brickInfo < hardBricks.size() )
	{
		hardBricks.draw(rndWnd, position, brickInfo);
	}
}

void OnePBricksTextures::drawIceBricks(sdl2::RendererWindow& rndWnd, unsigned brickInfo, const Offset& position)
{
	switch( brickInfo )
	{
		case BRICKS::ICE_BR::ICE_CUBE:
			drawIceCube(rndWnd, position);
			break;
		case BRICKS::ICE_BR::PINGUIN_BRICK:
			pinguinBrick.draw(rndWnd, position);
			break;
	}
}

void OnePBricksTextures::drawIceCube(sdl2::RendererWindow& rndWnd, const Offset& position)
{
	iceCubeBrick.draw(rndWnd, position);
}

void OnePBricksTextures::drawHellBricks(sdl2::RendererWindow& rndWnd, unsigned brickInfo, const Offset& position)
{
	switch( brickInfo )
	{
		case BRICKS::HELL_BR::SKULL_BRICK:
			skullBrick.draw(rndWnd, position);
			break;
		case BRICKS::HELL_BR::LAVA_STONE_1:
			drawLavaBrick(rndWnd, 0, position);
			break;
		case BRICKS::HELL_BR::LAVA_STONE_2:
			drawLavaBrick(rndWnd, 1, position);
			break;
		case BRICKS::HELL_BR::LAVA_STONE_3:
			drawLavaBrick(rndWnd, 2, position);
			break;
	}
}

void OnePBricksTextures::drawLavaBrick(sdl2::RendererWindow& rndWnd, unsigned lavaBrickIndex, const Offset& position)
{
	assert( lavaBrickIndex < lavaStoneBricks.size() );
	lavaStoneBricks[lavaBrickIndex].draw(rndWnd, position);
}