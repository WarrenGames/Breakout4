#ifndef SDL2_TEXTURE_LOADER_H
#define SDL2_TEXTURE_LOADER_H

#include "wrappers/sdl2_ptr.h"
#include <string>

struct AppLogFiles;
struct SDL_Color;

enum{ 	GradientTextureOnX,
		GradientTextureOnY
};

namespace sdl2{
	class RendererWindow;
	class Font;
	
class TextureLoader
{
	friend class Sprite;

private:
	sdl2::SurfacePtr surface;
	sdl2::TexturePtr texture;
	
public:
	TextureLoader() = default;
	TextureLoader(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& texturePath);
	TextureLoader(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Color& col, int width, int height);
	TextureLoader(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& text, const SDL_Color& color);
	TextureLoader(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& text, const SDL_Color& txtCol, const SDL_Color& roundCol);
	TextureLoader(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& rect, const SDL_Color& startColor, const SDL_Color& endColor, unsigned axis);
	
	~TextureLoader() = default;
	TextureLoader( const TextureLoader& ) = delete;
	TextureLoader& operator= ( const TextureLoader& ) = delete;
	TextureLoader( TextureLoader&& ) = default;
	TextureLoader& operator= ( TextureLoader&& ) = default;
	TextureLoader(sdl2::TexturePtr&& ptr);
	TextureLoader& operator= (sdl2::TexturePtr&& ptr);
	
	operator bool() const;
	bool wasLoadingPerfect() const;
	void loadTextureFile(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& texturePath);
	void loadTextureSquare(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Color& col, int width, int height);
	void loadBlendedText(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& text, const SDL_Color& color);
	void loadShadedText(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& text, const SDL_Color& txtCol, const SDL_Color& roundCol);
	void freeSurface();
	void freeTexture();
	void freeAllRessources();
	void createGradient(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& rect, const SDL_Color& startColor, const SDL_Color& endColor, unsigned axis);
	void createTexture(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::SurfacePtr& tempSurf);
	void setDimensions(int& width, int& height) const;
	
private:
	void createSDL_Texture(AppLogFiles& logs, sdl2::RendererWindow& rndWnd);
};

}

#endif //SDL2_TEXTURE_LOADER_H