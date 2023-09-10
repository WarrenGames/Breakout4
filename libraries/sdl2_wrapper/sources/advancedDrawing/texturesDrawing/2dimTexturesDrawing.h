#ifndef TWO_DIMENSIONS_TEXTURES_DRAWING_H
#define TWO_DIMENSIONS_TEXTURES_DRAWING_H

#include "texturing/sdl2_sprite.h"
#include "matrices/matrix2D.h"

class Matrix2DTexturesLoading;
namespace sdl2{ class RendererWindow; }
struct Coord2D;

class Matrix2DTexturesDrawing
{
private:
	MatrixTemp2D< sdl2::Sprite > sprites;
	
public:
	explicit Matrix2DTexturesDrawing( const Coord2D& size );
	explicit Matrix2DTexturesDrawing( const Matrix2DTexturesLoading& loadedTextures );
	~Matrix2DTexturesDrawing() = default;
	Matrix2DTexturesDrawing( const Matrix2DTexturesDrawing& ) = delete;
	Matrix2DTexturesDrawing& operator= ( const Matrix2DTexturesDrawing& ) = delete;
	Matrix2DTexturesDrawing( Matrix2DTexturesDrawing&& ) = default;
	Matrix2DTexturesDrawing& operator= ( Matrix2DTexturesDrawing&& ) = default;
	
	void resetTextures(const Matrix2DTexturesLoading& loadedTextures);
	
	void draw(sdl2::RendererWindow& rndWnd, const Coord2D& coords) const;
	void draw(sdl2::RendererWindow& rndWnd, const Coord2D& coords, int xpos, int ypos);
	void draw(sdl2::RendererWindow& rndWnd, const Coord2D& coords, const Offset& position);
	void drawToCenter(sdl2::RendererWindow& rndWnd, const Coord2D& coords, int xpos, int ypos);
	void drawToCenter(sdl2::RendererWindow& rndWnd, const Coord2D& coords, const Offset& position);
	void drawToCenter(sdl2::RendererWindow& rndWnd, std::size_t width, std::size_t height, int xpos, int ypos);
	
	sdl2::Sprite& operator() ( const Coord2D& coords);
	const sdl2::Sprite& operator() ( const Coord2D& coords) const;
	sdl2::Sprite& operator() (std::size_t width, std::size_t height);
	const sdl2::Sprite& operator() (std::size_t width, std::size_t height) const;
	
	std::size_t width() const;
	std::size_t height() const;
};

#endif //TWO_DIMENSIONS_TEXTURES_DRAWING_H