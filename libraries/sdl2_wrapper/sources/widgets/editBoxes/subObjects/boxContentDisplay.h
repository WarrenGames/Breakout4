#ifndef BOX_CONTENT_DISPLAY_H
#define BOX_CONTENT_DISPLAY_H

#include "text/sdl2ttf_font.h"
#include "texturing/texturesCombo.h"
#include <string>

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }

class BoxContentDisplay
{
private:
	sdl2::Font arialFont;
	TextureCombo currentValue;

public:
	explicit BoxContentDisplay(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned int fontSize, const std::string& valueInText);
	~BoxContentDisplay() = default;
	BoxContentDisplay( const BoxContentDisplay& ) = delete;
	BoxContentDisplay& operator= ( const BoxContentDisplay& ) = delete;
	BoxContentDisplay( BoxContentDisplay&& ) = default;
	BoxContentDisplay& operator= ( BoxContentDisplay&& ) = default;
	
	void makeTextTextureFromString(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& valueInText, bool& canChange);
	void setRectDimensions();
	
	void drawCurrentValueWithFocus(sdl2::RendererWindow& rndWnd, const SDL_Rect& boxRect, const std::string& valueInText);
	void drawCurrentValueWithoutFocus(sdl2::RendererWindow& rndWnd) const;
	
	void updateContentWhileLosingFocus(const SDL_Rect& boxRect);
	
	const SDL_Rect& getContentRect() const;
};

#endif //BOX_CONTENT_DISPLAY_H