#ifndef SPRITE_TYPE_H
#define SPRITE_TYPE_H

struct SpriteSize
{
	int w;
	int h;
	
	SpriteSize();
	constexpr SpriteSize(int width, int height):w{width},h{height}{}
	SpriteSize( const SpriteSize& ) = default;
	SpriteSize& operator= ( const SpriteSize& ) = default;
};

#endif //SPRITE_TYPE_H