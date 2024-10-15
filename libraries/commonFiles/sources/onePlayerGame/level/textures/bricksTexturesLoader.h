#ifndef BRICKS_TEXTURES_LOADER_H
#define BRICKS_TEXTURES_LOADER_H

#include "advancedDrawing/texturesLoading/fileTexturesList.h"
#include <vector>

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }

struct BricksTexturesLoader
{
	std::vector< TexturesFilesList > bricksTextures;
	
	explicit BricksTexturesLoader(AppLogFiles& logs, sdl2::RendererWindow& rndWnd);
	~BricksTexturesLoader() = default;
	BricksTexturesLoader( const BricksTexturesLoader& ) = delete;
	BricksTexturesLoader& operator= ( const BricksTexturesLoader& ) = delete;
	BricksTexturesLoader( BricksTexturesLoader&& ) = default;
	BricksTexturesLoader& operator= ( BricksTexturesLoader&& ) = default;
	
	operator bool() const;
	
	void loadTextures(AppLogFiles& logs, sdl2::RendererWindow& rndWnd);
};

#endif //BRICKS_TEXTURES_LOADER_H