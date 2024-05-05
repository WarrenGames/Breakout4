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
	void setAllCoordinates(const TexturePosition& position);
	void draw(sdl2::RendererWindow& rndWnd, std::size_t spriteIndex) const;
	void draw(sdl2::RendererWindow& rndWnd, const Offset& position, std::size_t spriteIndex);
	void draw(sdl2::RendererWindow& rndWnd, int xpos, int ypos, std::size_t spriteIndex);
	void drawToCenter(sdl2::RendererWindow& rndWnd, const Offset& centerPosition, std::size_t spriteIndex);
	void drawToCenter(sdl2::RendererWindow& rndWnd, int xpos, int ypos, std::size_t spriteIndex);
	
	const sdl2::Sprite& operator[](size_t spriteIndex) const;
	sdl2::Sprite& operator[](size_t spriteIndex);
	size_t size() const;
	int width(size_t spriteIndex) const;
	int height(size_t spriteIndex) const;
	
	std::vector< sdl2::Sprite >::const_iterator begin() const;
	std::vector< sdl2::Sprite >::const_iterator end() const;
	std::vector< sdl2::Sprite >::iterator begin();
	std::vector< sdl2::Sprite >::iterator end();
};

#endif //CONST_ANIMATION_DRAWING_H