#ifndef FILE_TEXTURES_LIST_LOADING_H
#define FILE_TEXTURES_LIST_LOADING_H

#include "texturing/textureLoader.h"
#include <vector>

namespace sdl2{ class RendererWindow; }

struct AppLogFiles;

class TexturesFilesList
{
private:
	std::vector< sdl2::TextureLoader > loadedTextures;
	bool isLoadingPerfect;
	
public:
	explicit TexturesFilesList();
	explicit TexturesFilesList(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& listFilePath);
	explicit TexturesFilesList(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned texturesNumber, const std::string& fileBase);
	~TexturesFilesList() = default;
	TexturesFilesList( const TexturesFilesList& ) = delete;
	TexturesFilesList& operator= ( const TexturesFilesList& ) = delete;
	TexturesFilesList( TexturesFilesList&& ) = default;
	TexturesFilesList& operator= ( TexturesFilesList&& ) = default;
	
	bool wasLoadingPerfect() const;
	std::size_t size() const;
	const sdl2::TextureLoader& operator[](std::size_t index) const;
	
	std::vector< sdl2::TextureLoader >::const_iterator begin() const;
	std::vector< sdl2::TextureLoader >::const_iterator end() const;
	
	std::vector< sdl2::TextureLoader >::iterator begin();
	std::vector< sdl2::TextureLoader >::iterator end();
	
	void addTexture(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& textureFilePath);
	void lookUpListFile(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& listFilePath);
	void clearData();
};

#endif //FILE_TEXTURES_LIST_LOADING_H