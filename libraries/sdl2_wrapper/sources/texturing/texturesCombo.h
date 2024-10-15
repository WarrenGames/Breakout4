#ifndef INTERFACE_GENERATOR_LANGUAGE_TEXTURES_COMBO_H
#define INTERFACE_GENERATOR_LANGUAGE_TEXTURES_COMBO_H

#include "texturing/textureLoader.h"
#include "texturing/sdl2_sprite.h"
#include "fileSystem/fileSystem.h"
#include <string>

struct AppLogFiles;
namespace sdl2{ class RendererWindow; class Font; }
struct Offset;
struct TexturePosition;

struct TextureCombo
{
	sdl2::TextureLoader texture;
	sdl2::Sprite sprite;
	
	TextureCombo();
	
	TextureCombo(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& texturePath, const TexturePosition& pos);
	TextureCombo(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& texturePath);
	
	TextureCombo(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Color& color, int squareWidth, int squareHeight);
	TextureCombo(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Color& color, int squareWidth, int squareHeight, const TexturePosition& pos);
	
	TextureCombo(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& text, const SDL_Color& color, const TexturePosition& pos);
	TextureCombo(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& text, const SDL_Color& txtCol, const SDL_Color& roundCol, 
							const TexturePosition& pos);
	
	TextureCombo(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& rect, const SDL_Color& startColor, const SDL_Color& endColor, unsigned axis);
	TextureCombo(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& rect, const SDL_Color& startColor, const SDL_Color& endColor, unsigned axis,
							const TexturePosition& pos);
	TextureCombo( sdl2::TextureLoader&& textureLoader );
	~TextureCombo() = default;
	TextureCombo( const TextureCombo& ) = delete;
	TextureCombo& operator= ( const TextureCombo& ) = delete;
	TextureCombo( TextureCombo&& );
	TextureCombo& operator= ( TextureCombo&& );
	
	operator bool() const;
	
	void draw(sdl2::RendererWindow& rndWnd) const;
	void draw(sdl2::RendererWindow& rndWnd, const Offset& pos);
	void draw(sdl2::RendererWindow& rndWnd, int xpos, int ypos);
	void drawToCenter(sdl2::RendererWindow& rndWnd, int xpos, int ypos);
	void resetSpritePosition(const TexturePosition& pos);
	void catchTexture();
};

#endif //INTERFACE_GENERATOR_LANGUAGE_TEXTURES_COMBO_H