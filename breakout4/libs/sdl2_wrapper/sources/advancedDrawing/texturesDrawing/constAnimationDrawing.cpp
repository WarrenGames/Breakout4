#include "advancedDrawing/texturesDrawing/constAnimationDrawing.h"
#include "advancedDrawing/texturesLoading/fileTexturesList.h"
#include "texturing/rendererWindow.h"
#include "customTypes/positionTypes.h"
#include <cassert>

ConstAnimDraw::ConstAnimDraw(const TexturesFilesList& loadedTextures)
{
	if( loadedTextures.wasLoadingPerfect() && loadedTextures.size() > 0 )
	{
		for( auto const &t : loadedTextures )
		{
			sprites.emplace_back( sdl2::Sprite{ t } );
		}
	}
}

ConstAnimDraw& ConstAnimDraw::operator= ( const TexturesFilesList& loadedTextures )
{
	for( auto const &t : loadedTextures )
	{
		sprites.emplace_back( sdl2::Sprite{ t } );
	}
	return *this;
}

void ConstAnimDraw::setAllCoordinates(const Offset& position)
{
	for( auto &spr : sprites )
	{
		spr.setDefaultCoord(position.x, position.y);
	}
}

void ConstAnimDraw::draw(sdl2::RendererWindow& rndWnd, unsigned spriteIndex) const
{
	assert( spriteIndex < sprites.size() );
	sprites[spriteIndex].draw(rndWnd);
}

void ConstAnimDraw::draw(sdl2::RendererWindow& rndWnd, const Offset& position, unsigned spriteIndex)
{
	assert( spriteIndex < sprites.size() );
	sprites[spriteIndex].draw(rndWnd, position);
}

void ConstAnimDraw::draw(sdl2::RendererWindow& rndWnd, int xpos, int ypos, unsigned spriteIndex)
{
	assert( spriteIndex < sprites.size() );
	sprites[spriteIndex].draw(rndWnd, xpos, ypos);
}

void ConstAnimDraw::drawToCenter(sdl2::RendererWindow& rndWnd, const Offset& centerPosition, unsigned spriteIndex)
{
	assert( spriteIndex < sprites.size() );
	sprites[spriteIndex].drawToCenter(rndWnd, centerPosition);
}

void ConstAnimDraw::drawToCenter(sdl2::RendererWindow& rndWnd, int xpos, int ypos, unsigned spriteIndex)
{
	assert( spriteIndex < sprites.size() );
	sprites[spriteIndex].drawToCenter(rndWnd, xpos, ypos);
}

unsigned ConstAnimDraw::size() const
{
	return static_cast<unsigned>( sprites.size() );
}

const sdl2::Sprite& ConstAnimDraw::operator[](unsigned spriteIndex) const
{
	assert( spriteIndex < sprites.size() );
	return sprites[spriteIndex];
}

sdl2::Sprite& ConstAnimDraw::operator[](unsigned spriteIndex)
{
	assert( spriteIndex < sprites.size() );
	return sprites[spriteIndex];
}

int ConstAnimDraw::width(unsigned spriteIndex) const
{
	assert( spriteIndex < sprites.size() );
	return sprites[spriteIndex].width();
}

int ConstAnimDraw::height(unsigned spriteIndex) const
{
	assert( spriteIndex < sprites.size() );
	return sprites[spriteIndex].height();
}

std::vector< sdl2::Sprite >::const_iterator ConstAnimDraw::begin() const
{
	return sprites.cbegin();
}

std::vector< sdl2::Sprite >::const_iterator ConstAnimDraw::end() const
{
	return sprites.cend();
}