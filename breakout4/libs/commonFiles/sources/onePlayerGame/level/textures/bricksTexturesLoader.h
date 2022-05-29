#ifndef BRICKS_TEXTURES_LOADER_H
#define BRICKS_TEXTURES_LOADER_H

#include "advancedDrawing/texturesLoading/fileTexturesList.h"
#include "texturing/textureLoader.h"

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }

struct BricksTexturesLoader
{
	TexturesFilesList generic;
	TexturesFilesList rich;
	sdl2::TextureLoader bonusBrick;
	TexturesFilesList giftBricks;
	TexturesFilesList tenPtsBricks;
	TexturesFilesList hardBricks;
	sdl2::TextureLoader iceCubeBrick;
	sdl2::TextureLoader pinguinBrick;
	sdl2::TextureLoader skullBrick;
	TexturesFilesList lavaStoneBricks;
	
	explicit BricksTexturesLoader(AppLogFiles& logs, sdl2::RendererWindow& rndWnd);
	~BricksTexturesLoader() = default;
	BricksTexturesLoader( const BricksTexturesLoader& ) = delete;
	BricksTexturesLoader& operator= ( const BricksTexturesLoader& ) = delete;
	BricksTexturesLoader( BricksTexturesLoader&& ) = default;
	BricksTexturesLoader& operator= ( BricksTexturesLoader&& ) = default;
	
	operator bool() const;
};

#endif //BRICKS_TEXTURES_LOADER_H