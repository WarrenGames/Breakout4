#ifndef H_3TEXTURES_BUTTON
#define H_3TEXTURES_BUTTON

#include "texturing/texturesCombo.h"
#include <vector>
#include <array>
#include <string>

struct AppLogFiles;
struct TexturePosition;
namespace sdl2{ class RendererWindow; class Font; }
struct SDL_Color;

enum{ Texture3ButtonOff, Texture3ButtonHovered, Texture3ButtonClick, T3BTN_MAX};

class T3_Button
{
private:
	std::vector< TextureCombo > textures;
	unsigned buttonState;

public:
	explicit T3_Button(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::array<const std::string, T3BTN_MAX>& texturesPaths, const TexturePosition& pos);
	explicit T3_Button(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& text, const SDL_Color& offText, 
						const SDL_Color& selectText, const SDL_Color& backgrnd, const TexturePosition& pos);
	T3_Button( const T3_Button& ) = delete;
	T3_Button& operator= ( const T3_Button& ) = delete;
	T3_Button( T3_Button&&  ) = default;
	T3_Button& operator= ( T3_Button&& ) = default;

	void updateButton(const Offset& mousePosition, bool mouseButtonState);
	void drawButton(sdl2::RendererWindow& rndWnd) const;
	bool buttonClicked() const;
	
private:
	void createTexturesWithPath(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::array< const std::string, T3BTN_MAX>& paths, const TexturePosition& pos);
	void createTexturesWithFont(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& text, const SDL_Color& offText, 
								const SDL_Color& selectText, const SDL_Color& backgrnd, const TexturePosition& pos);
};

#endif //H_3TEXTURES_BUTTON
