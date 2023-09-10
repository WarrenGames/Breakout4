#ifndef BOOL_BOX_CONTENT_DISPLAY_H
#define BOOL_BOX_CONTENT_DISPLAY_H

#include "text/sdl2ttf_font.h"
#include "texturing/texturesCombo.h"

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }

class BoolBoxContentDisplay
{
private:
	sdl2::Font arialFont;
	TextureCombo trueTextTexture;
	TextureCombo falseTextTexture;

public:
	explicit BoolBoxContentDisplay(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned fontSize, const SDL_Rect& boxRect);
	~BoolBoxContentDisplay() = default;
	BoolBoxContentDisplay( const BoolBoxContentDisplay& ) = delete;
	BoolBoxContentDisplay& operator= ( const BoolBoxContentDisplay& ) = delete;
	BoolBoxContentDisplay( BoolBoxContentDisplay&& ) = default;
	BoolBoxContentDisplay& operator= ( BoolBoxContentDisplay&& ) = default;
	
	void drawTrue(sdl2::RendererWindow& rndWnd) const;
	void drawFalse(sdl2::RendererWindow& rndWnd) const;
};

#endif //BOOL_BOX_CONTENT_DISPLAY_H