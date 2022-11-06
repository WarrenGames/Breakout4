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
		case bricks::index::GenericBrick:
			drawGeneric(rndWnd, brickData.property, position);
			break;
		case bricks::index::RichBrick:
			drawRich(rndWnd, brickData.property, position);
			break;
		case bricks::index::BonusCoin:
			drawBonusCoinBrick(rndWnd, position);
			break;
		case bricks::index::GiftBrick:
			drawGiftBrick(rndWnd, brickData.property, position);
			break;
		case bricks::index::TenPointsBrick:
			drawTenPtsBricks(rndWnd, brickData.property, position);
			break;
		case bricks::index::SolidBrick:
			drawSolidBrick(rndWnd, brickData.property, position);
			break;
		case bricks::index::IceBrick:
			drawIceBricks(rndWnd, brickData.property, position);
			break;
		case bricks::index::HellBricks:
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
		case bricks::iceBricks::IceCube:
			drawIceCube(rndWnd, position);
			break;
		case bricks::iceBricks::PinguinBrickTexturePath:
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
		case bricks::hellBricks::SkullBrick:
			skullBrick.draw(rndWnd, position);
			break;
		case bricks::hellBricks::LavaStone1:
			drawLavaBrick(rndWnd, 0, position);
			break;
		case bricks::hellBricks::LavaStone2:
			drawLavaBrick(rndWnd, 1, position);
			break;
		case bricks::hellBricks::LavaStone3:
			drawLavaBrick(rndWnd, 2, position);
			break;
	}
}

void OnePBricksTextures::drawLavaBrick(sdl2::RendererWindow& rndWnd, unsigned lavaBrickIndex, const Offset& position)
{
	assert( lavaBrickIndex < lavaStoneBricks.size() );
	lavaStoneBricks[lavaBrickIndex].draw(rndWnd, position);
}