#ifndef ANIM_FILE_TEXTURES_LIST_LOADING_H
#define ANIM_FILE_TEXTURES_LIST_LOADING_H

#include "texturing/textureLoader.h"
#include <vector>
#include <string>

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }

struct AnimLoadData
{
	sdl2::TextureLoader tload;
	unsigned frameDuration;
	
	explicit AnimLoadData(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& texturePath, unsigned frameDuration);
	~AnimLoadData() = default;
	AnimLoadData( const AnimLoadData& ) = delete;
	AnimLoadData& operator= ( const AnimLoadData& ) = delete;
	AnimLoadData( AnimLoadData&& ) = default;
	AnimLoadData& operator= ( AnimLoadData&& ) = default;
	
	operator bool() const;
};

class AnimTextureElement
{
private:
	std::vector< AnimLoadData > loadedTextures;
	bool isLoadingPerfect;
	
public:
	explicit AnimTextureElement();
	explicit AnimTextureElement(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& listFile);
	~AnimTextureElement() = default;
	AnimTextureElement( const AnimTextureElement& ) = delete;
	AnimTextureElement& operator= ( const AnimTextureElement& ) = delete;
	AnimTextureElement( AnimTextureElement&& ) = default;
	AnimTextureElement& operator= ( AnimTextureElement&& ) = default;
	
	operator bool() const;
	bool wasLoadingPerfect() const;
	std::size_t size() const;
	
	std::vector< AnimLoadData >::const_iterator begin() const;
	std::vector< AnimLoadData >::const_iterator end() const;
	
	std::vector< AnimLoadData >::iterator begin();
	std::vector< AnimLoadData >::iterator end();
	
	void addTexture(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& textureFilePath, unsigned frameDuration);
	void readLine(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, std::istringstream& lineStream);
	void lookUpListFile(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& listFilePath);
};

class LoadedAnimTexturesList
{
private:
	std::vector< AnimTextureElement > animations;
	bool isLoadingPerfect;
	
public:
	explicit LoadedAnimTexturesList();
	~LoadedAnimTexturesList() = default;
	LoadedAnimTexturesList( const LoadedAnimTexturesList& ) = delete;
	LoadedAnimTexturesList& operator= ( const LoadedAnimTexturesList& ) = delete;
	LoadedAnimTexturesList( LoadedAnimTexturesList&& ) = default;
	LoadedAnimTexturesList& operator= ( LoadedAnimTexturesList&& ) = default;
	
	bool wasLoadingPerfect() const;
	void lookUpListFile(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& listFilePath, const std::string& refListDirectory);
	
	std::size_t size() const;
	const AnimTextureElement& operator[](std::size_t index) const;
	std::vector< AnimTextureElement >::const_iterator begin() const;
	std::vector< AnimTextureElement >::const_iterator end() const;
	
	std::vector< AnimTextureElement >::iterator begin();
	std::vector< AnimTextureElement >::iterator end();
	
	void clearData();
};

#endif //ANIM_FILE_TEXTURES_LIST_LOADING_H