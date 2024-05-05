#ifndef H_ENTITY_EXPLO
#define H_ENTITY_EXPLO

#include "advancedDrawing/texturesDrawing/constAnimationDrawing.h"
#include <string>

struct ExplosionChunk;
namespace sdl2{ class RendererWindow; }

class EntityExplosion
{
private:
	ConstAnimDraw sprites;
	unsigned frameSpacing;
	unsigned largerFrame;
		
public:
	explicit EntityExplosion(const ExplosionChunk& singleExplosion);
	~EntityExplosion() = default;
	EntityExplosion( const EntityExplosion& ) = delete;
	EntityExplosion& operator=( const EntityExplosion& ) = delete;
	EntityExplosion( EntityExplosion&& ) = default;
	EntityExplosion& operator= ( EntityExplosion&& ) = default;

	unsigned getFrameNumber() const;
	unsigned getExplosionDelayImg() const;
	unsigned getZenith() const;
	void drawExplosion(sdl2::RendererWindow& rndWnd, unsigned frameNumber, int posx, int posy);
	void drawExplosion(sdl2::RendererWindow& rndWnd, unsigned frameNumber, const Offset& position);
};


#endif // H_ENTITY_EXPLO
