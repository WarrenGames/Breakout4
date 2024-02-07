#include "explosions/allExplosions.h"
#include "explosions/explosionLoader.h"
#include <cassert>

AllExplosions::AllExplosions(const ExplosionsLoader& explosionLoader)
{
	for( unsigned i{0} ; i < explosionLoader.size() ; ++i )
	{
		explosionsTextures.emplace_back( EntityExplosion{explosionLoader[i]} );
	}
}

unsigned AllExplosions::getExplosionFrameNumber(unsigned explosionIndex) const
{
	assert( explosionIndex < explosionsTextures.size() );
	return explosionsTextures[explosionIndex].getFrameNumber();
}

unsigned int AllExplosions::getExplosionDelay(unsigned explosionIndex) const
{
	assert( explosionIndex < explosionsTextures.size() );
	return explosionsTextures[explosionIndex].getExplosionDelayImg();
}

unsigned AllExplosions::getFrameZenith(unsigned explosionIndex) const
{
	assert( explosionIndex < explosionsTextures.size() );
	return explosionsTextures[explosionIndex].getZenith();
}

unsigned AllExplosions::getAllExplosionsNumber() const
{
	return static_cast<unsigned>( explosionsTextures.size() );
}

void AllExplosions::drawFrame(sdl2::RendererWindow& rndWnd, int xpos, int ypos, unsigned explosionIndex, unsigned frameNumber)
{
	assert( explosionIndex < explosionsTextures.size() );
	assert( frameNumber < explosionsTextures[explosionIndex].getFrameNumber() );
	explosionsTextures[explosionIndex].drawExplosion(rndWnd, frameNumber, xpos, ypos);
}

void AllExplosions::drawFrame(sdl2::RendererWindow& rndWnd, const Offset& position, unsigned explosionIndex, unsigned frameNumber)
{
	assert( explosionIndex < explosionsTextures.size() );
	assert( frameNumber < explosionsTextures[explosionIndex].getFrameNumber() );
	explosionsTextures[explosionIndex].drawExplosion(rndWnd, frameNumber, position);
}