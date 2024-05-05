#include "explosions/entityExplosion.h"
#include "explosions/explosionLoader.h"

EntityExplosion::EntityExplosion(const ExplosionChunk& singleExplosion):
	sprites{ singleExplosion.textures },
	frameSpacing{ singleExplosion.frameDuration },
	largerFrame{ singleExplosion.zenithImage }
{
	
}

unsigned EntityExplosion::getFrameNumber() const
{
	return static_cast<unsigned>( sprites.size() );
}

unsigned int EntityExplosion::getExplosionDelayImg() const
{
	return frameSpacing;
}

unsigned EntityExplosion::getZenith() const
{
	return largerFrame;
}

void EntityExplosion::drawExplosion(sdl2::RendererWindow& rndWnd, unsigned frameNumber, int posx, int posy)
{
	if( frameNumber < sprites.size() )
	{
		sprites.drawToCenter(rndWnd, posx, posy, frameNumber);
	}
}

void EntityExplosion::drawExplosion(sdl2::RendererWindow& rndWnd, unsigned frameNumber, const Offset& position)
{
	if( frameNumber < sprites.size() )
	{
		sprites.drawToCenter(rndWnd, position, frameNumber);
	}
}