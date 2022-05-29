#ifndef CONST_ANIMATION_DRAWING_H
#define CONST_ANIMATION_DRAWING_H

#include "texturing/sdl2_sprite.h"
#include <vector>

class TexturesFilesList;
struct Offset;

class ConstAnimDraw
{
private:
	std::vector< sdl2::Sprite > sprites;
	
public:
	explicit ConstAnimDraw() = default;
	explicit ConstAnimDraw(const TexturesFilesList& loadedTextures);
	~ConstAnimDraw() = default;
	ConstAnimDraw( const ConstAnimDraw& ) = delete;
	ConstAnimDraw& operator= ( const ConstAnimDraw& ) = delete;
	ConstAnimDraw( ConstAnimDraw&& ) = default;
	ConstAnimDraw& operator= ( ConstAnimDraw&& ) = default;
	ConstAnimDraw& operator= ( const TexturesFilesList& loadedTextures );
	
	void setAllCoordinates(const Offset& position);
	void draw(sdl2::RendererWindow& rndWnd, unsigned spriteIndex) const;
	void draw(sdl2::RendererWindow& rndWnd, const Offset& position, unsigned spriteIndex);
	void draw(sdl2::RendererWindow& rndWnd, int xpos, int ypos, unsigned spriteIndex);
	void drawToCenter(sdl2::RendererWindow& rndWnd, const Offset& centerPosition, unsigned spriteIndex);
	void drawToCenter(sdl2::RendererWindow& rndWnd, int xpos, int ypos, unsigned spriteIndex);
	
	const sdl2::Sprite& operator[](unsigned spriteIndex) const;
	sdl2::Sprite& operator[](unsigned spriteIndex);
	unsigned size() const;
	int width(unsigned spriteIndex) const;
	int height(unsigned spriteIndex) const;
	
	std::vector< sdl2::Sprite >::const_iterator begin() const;
	std::vector< sdl2::Sprite >::const_iterator end() const;
};

#endif //CONST_ANIMATION_DRAWING_H