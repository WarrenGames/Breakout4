#ifndef CL_HIGHLIGHT_BUTTON_H
#define CL_HIGHLIGHT_BUTTON_H

#include "texturing/texturesCombo.h"
#include <string>

struct AppLogFiles;
namespace sdl2{ class RendererWindow; class Font; }
struct SDL_Color;
struct Offset;

class HighLightButton
{
private:
	TextureCombo highlightTexture;
	TextureCombo textTexture;
	std::string text;
	bool clicked_;
	bool hovered_;
	
public:
	explicit HighLightButton(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& text, const SDL_Color& textCol, 
								const SDL_Rect& square, const SDL_Color& squareCol);
	HighLightButton(const HighLightButton& ) = delete;
	HighLightButton& operator= (const HighLightButton& ) = delete;
	~HighLightButton() = default;
	HighLightButton( HighLightButton&& ) = default;
	HighLightButton& operator= ( HighLightButton&& ) = default;
	
	void drawButton(sdl2::RendererWindow& rndWnd) const;
	const std::string& getText();
	void updateButton(int mouse_posx, int mouse_posy, bool mouseButtonState);
	void updateButton(const Offset& mousePosition, bool mouseButtonState);
	void changeText(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& newText, const SDL_Color& txtCol);
	bool buttonClicked() const;
};

#endif//CL_HIGHLIGHT_BUTTON_H