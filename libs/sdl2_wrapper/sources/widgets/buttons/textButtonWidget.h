#ifndef H_TEXT_BUTTON
#define H_TEXT_BUTTON

#include "texturing/texturesCombo.h"
#include <string>

struct AppLogFiles;
namespace sdl2{ class RendererWindow; class Font; }
struct Offset;
struct SDL_Color;

class TextButton
{
private:
	TextureCombo selectedTexture;
	TextureCombo awayTexture;
	bool clicked;
	bool hovered;

public:
	explicit TextButton(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& text, const SDL_Color& selected, const SDL_Color& off, 
						const TexturePosition& pos);
	explicit TextButton(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& text, const SDL_Color& selected, const SDL_Color& off, 
						int xpos, int ypos, bool isCenteredOnPos);

	~TextButton() = default;
	TextButton( const TextButton& ) = delete;
	TextButton& operator=(const TextButton& ) = delete;
	TextButton( TextButton&& ) = default;
	TextButton& operator= ( TextButton&& ) = default;
	
	operator bool() const;
	void updateButton(int mouse_x_pos, int mouse_y_pos, bool leftButtonState);
	void updateButton(const Offset& mousePosition, bool leftButtonState);
	void drawButton(sdl2::RendererWindow& rndWnd) const;
	bool buttonClicked() const;
};

#endif // H_TEXT_BUTTON
