#include "advancedDrawing/texturesDrawing/3dimTexturesDrawing.h"
#include "advancedDrawing/texturesLoading/3dimTexturesLoading.h"
#include "texturing/rendererWindow.h"

Matrix3DTexturesDrawing::Matrix3DTexturesDrawing(const Coord3D& size):
	sprites{size}
{
	
}

Matrix3DTexturesDrawing::Matrix3DTexturesDrawing( const Matrix3DTexturesLoading& loadedTextures ):
	sprites{ loadedTextures.width(), loadedTextures.height(), loadedTextures.depth() }
{
	resetTextures(loadedTextures);
}

void Matrix3DTexturesDrawing::resetTextures(const Matrix3DTexturesLoading& loadedTextures)
{
	if( loadedTextures.wasLoadingPerfect() && loadedTextures.size() > 0 )
	{
		for( std::size_t depth{0} ; depth < loadedTextures.depth() ; ++depth )
		{
			for( std::size_t height{0} ; height < loadedTextures.height() ; ++height )
			{
				for( std::size_t width{0} ; width < loadedTextures.width() ; ++width )
				{
					sprites(width, height, depth) = loadedTextures.getLoadedTexture(Coord3D{width, height, depth} );
				}
			}
		}
	}
}

void Matrix3DTexturesDrawing::draw(sdl2::RendererWindow& rndWnd, const Coord3D& coords) const
{
	sprites(coords).draw(rndWnd);
}

void Matrix3DTexturesDrawing::draw(sdl2::RendererWindow& rndWnd, const Coord3D& coords, int xpos, int ypos)
{
	sprites(coords).draw(rndWnd, xpos, ypos);
}

void Matrix3DTexturesDrawing::draw(sdl2::RendererWindow& rndWnd, const Coord3D& coords, const Offset& position)
{
	sprites(coords).draw(rndWnd, position);
}

void Matrix3DTexturesDrawing::drawToCenter(sdl2::RendererWindow& rndWnd, const Coord3D& coords, int xpos, int ypos)
{
	sprites(coords).drawToCenter(rndWnd, xpos, ypos);
}

void Matrix3DTexturesDrawing::drawToCenter(sdl2::RendererWindow& rndWnd, const Coord3D& coords, const Offset& position)
{
	sprites(coords).drawToCenter(rndWnd, position);
}

sdl2::Sprite& Matrix3DTexturesDrawing::operator() ( const Coord3D& coords)
{
	return sprites(coords);
}

const sdl2::Sprite& Matrix3DTexturesDrawing::operator() ( const Coord3D& coords) const
{
	return sprites(coords);
}

std::size_t Matrix3DTexturesDrawing::width() const
{
	return sprites.width();
}

std::size_t Matrix3DTexturesDrawing::height() const
{
	return sprites.height();
}

std::size_t Matrix3DTexturesDrawing::depth() const
{
	return sprites.depth();
}