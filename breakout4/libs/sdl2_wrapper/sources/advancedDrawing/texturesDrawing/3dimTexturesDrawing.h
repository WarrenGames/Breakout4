#ifndef THREE_DIMENSIONS_TEXTURES_DRAWING_H
#define THREE_DIMENSIONS_TEXTURES_DRAWING_H

#include "texturing/sdl2_sprite.h"
#include "matrices/matrix3D.h"

class Matrix3DTexturesLoading;
namespace sdl2{ class RendererWindow; }
struct Coord3D;

class Matrix3DTexturesDrawing
{
private:
	MatrixTemp3D< sdl2::Sprite > sprites;
	
public:
	explicit Matrix3DTexturesDrawing( const Coord3D& size );
	explicit Matrix3DTexturesDrawing( const Matrix3DTexturesLoading& loadedTextures );
	~Matrix3DTexturesDrawing() = default;
	Matrix3DTexturesDrawing( const Matrix3DTexturesDrawing& ) = delete;
	Matrix3DTexturesDrawing& operator= ( Matrix3DTexturesDrawing& ) = delete;
	Matrix3DTexturesDrawing( Matrix3DTexturesDrawing&& ) = default;
	Matrix3DTexturesDrawing& operator= ( Matrix3DTexturesDrawing&& ) = default;
	
	void resetTextures(const Matrix3DTexturesLoading& loadedTextures);
	
	void draw(sdl2::RendererWindow& rndWnd, const Coord3D& coords) const;
	void draw(sdl2::RendererWindow& rndWnd, const Coord3D& coords, int xpos, int ypos);
	void draw(sdl2::RendererWindow& rndWnd, const Coord3D& coords, const Offset& position);
	void drawToCenter(sdl2::RendererWindow& rndWnd, const Coord3D& coords, int xpos, int ypos);
	void drawToCenter(sdl2::RendererWindow& rndWnd, const Coord3D& coords, const Offset& position);
	
	sdl2::Sprite& operator() ( const Coord3D& coords);
	const sdl2::Sprite& operator() ( const Coord3D& coords) const;
	
	std::size_t width() const;
	std::size_t height() const;
	std::size_t depth() const;
};

#endif //THREE_DIMENSIONS_TEXTURES_DRAWING_H