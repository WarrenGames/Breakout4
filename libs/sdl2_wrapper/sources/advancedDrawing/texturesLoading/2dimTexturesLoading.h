#ifndef MATRIX_2_DIMENSIONS_TEXTURES_LOADING_H
#define MATRIX_2_DIMENSIONS_TEXTURES_LOADING_H

#include "texturing/textureLoader.h"
#include "matrices/matrix2D.h"
#include <string>

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }
struct Coord2D;

class Matrix2DTexturesLoading
{	
private:
	MatrixTemp2D< sdl2::TextureLoader > textures;
	bool isLoadingPerfect;
	
public:
	explicit Matrix2DTexturesLoading();
	explicit Matrix2DTexturesLoading(const Coord2D& size);
	explicit Matrix2DTexturesLoading(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Coord2D& size, const std::string& fileBase, const std::string& separator);
	explicit Matrix2DTexturesLoading(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Coord2D& size, const std::string& listFileName);
	~Matrix2DTexturesLoading() = default;
	Matrix2DTexturesLoading( const Matrix2DTexturesLoading& ) = delete;
	Matrix2DTexturesLoading& operator= ( const Matrix2DTexturesLoading& ) = delete;
	Matrix2DTexturesLoading( Matrix2DTexturesLoading&& ) = default;
	Matrix2DTexturesLoading& operator= ( Matrix2DTexturesLoading&& ) = default;
	
	bool wasLoadingPerfect() const;
	std::size_t width() const;
	std::size_t height() const;
	std::size_t size() const;
	void resize(const Coord2D& size);
	const sdl2::TextureLoader& operator()(const Coord2D& coords) const;
	sdl2::TextureLoader& operator()(const Coord2D& coords);
	const sdl2::TextureLoader& operator()(std::size_t width, std::size_t height) const;
	sdl2::TextureLoader& operator()(std::size_t width, std::size_t height);
	
	void loadAllTextures(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& fileBase, const std::string& separator);
	void loadSingleTexture(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Coord2D& size, const std::string& fileBase, const std::string& separator);
	void lookUpListFile(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& listFileName);
	void loadSingleTexture(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Coord2D& coords, const std::string& texturePath);
};

#endif //MATRIX_2_DIMENSIONS_TEXTURES_LOADING_H