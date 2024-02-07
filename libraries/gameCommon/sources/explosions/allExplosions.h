#ifndef H_EXPLOSIONS
#define H_EXPLOSIONS

#include "explosions/entityExplosion.h"

class ExplosionsLoader;
namespace sdl2{ class RendererWindow; }

class AllExplosions
{
private:
	std::vector < EntityExplosion > explosionsTextures;

public:
	explicit AllExplosions(const ExplosionsLoader& explosionLoader);
	~AllExplosions() = default;
	AllExplosions( AllExplosions const& ) = delete;
	AllExplosions& operator= (AllExplosions const& ) = delete;
	AllExplosions( AllExplosions&& ) = default;
	AllExplosions& operator= ( AllExplosions&& ) = default;
		
	unsigned getExplosionFrameNumber(unsigned explosionIndex) const;
	unsigned getExplosionDelay(unsigned explosionIndex) const;
	unsigned getFrameZenith(unsigned explosionIndex) const;
	unsigned getAllExplosionsNumber() const;
	void drawFrame(sdl2::RendererWindow& rndWnd, int posX, int posY, unsigned explosionIndex, unsigned frameNumber);
	void drawFrame(sdl2::RendererWindow& rndWnd, const Offset& position, unsigned explosionIndex, unsigned frameNumber);
	
	
};

#endif //H_EXPLOSIONS
