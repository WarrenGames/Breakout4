#ifndef CURSOR_DRAWING_H
#define CURSOR_DRAWING_H

#include "texturing/texturesCombo.h"
#include "time/accurateTime.h"

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }
struct SDL_Rect;
struct Offset;

class BoxCursor
{
private:
	TextureCombo cursor;
	AccurateTimeDelay timeCursor;
	bool canCursorBeBlit;

public:
	explicit BoxCursor(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& boxSize);
	~BoxCursor() = default;
	BoxCursor( const BoxCursor& ) = delete;
	BoxCursor& operator= ( const BoxCursor& ) = delete;
	BoxCursor( BoxCursor&& ) = default;
	BoxCursor& operator= ( BoxCursor&& ) = default;
	
	void blinkCursor();
	void drawCursor(sdl2::RendererWindow& rndWnd, const Offset& cursorPosition);
};

#endif //CURSOR_DRAWING_H