#ifndef IN_GAME_EXPLOSIONS_TEXTURES_LOADER_H
#define IN_GAME_EXPLOSIONS_TEXTURES_LOADER_H

#include "advancedDrawing/texturesLoading/fileTexturesList.h"

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }

struct ExplosionChunk
{
	TexturesFilesList textures;
	unsigned frameDuration;
	unsigned zenithImage;
	
	explicit ExplosionChunk(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned texturesNumber, const std::string& fileBase, unsigned frameDuration_, unsigned zenithImage_);
	~ExplosionChunk() = default;
	ExplosionChunk( const ExplosionChunk& ) = delete;
	ExplosionChunk& operator= ( const ExplosionChunk& ) = delete;
	ExplosionChunk( ExplosionChunk&& ) = default;
	ExplosionChunk& operator= ( ExplosionChunk&& ) = default;
};

class ExplosionsLoader
{
private:
	std::vector< ExplosionChunk > explosionsTextures;
	bool isLoadingPerfect;

public:
	explicit ExplosionsLoader();
	explicit ExplosionsLoader(AppLogFiles& logs, sdl2::RendererWindow& rndWnd);
	~ExplosionsLoader() = default;
	ExplosionsLoader( const ExplosionsLoader& ) = delete;
	ExplosionsLoader& operator= ( const ExplosionsLoader& ) = delete;
	ExplosionsLoader( ExplosionsLoader&& ) = default;
	ExplosionsLoader& operator= ( ExplosionsLoader&& ) = default;
	
	std::size_t size() const;
	const ExplosionChunk& operator[](std::size_t index) const;
	bool wasLoadingPerfect() const;
	
private:
	void openConfigFile(AppLogFiles& logs, sdl2::RendererWindow& rndWnd);
	void loadEntityExplosion(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& referenceLine);
};

#endif //IN_GAME_EXPLOSIONS_TEXTURES_LOADER_H