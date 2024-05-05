#ifndef BOX_DISPLAY_H
#define BOX_DISPLAY_H

#include "wrappers/sdl2_ptr.h"

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }
struct SDL_Rect;
struct Offset;

class BoxRectDisplaying
{
private:
	sdl2::TexturePtr activeWindow;
	sdl2::TexturePtr offWindow;	
	const SDL_Rect mainRect;

public:
	explicit BoxRectDisplaying(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& boxSize);
	~BoxRectDisplaying() = default;
	BoxRectDisplaying( const BoxRectDisplaying& ) = delete;
	BoxRectDisplaying& operator= ( const BoxRectDisplaying& ) = delete;
	BoxRectDisplaying( BoxRectDisplaying&& ) = default;
	BoxRectDisplaying& operator= ( BoxRectDisplaying&& ) = default;
	
	void drawActiveWindow(sdl2::RendererWindow& rndWnd) const;
	void drawOffWindow(sdl2::RendererWindow& rndWnd) const;
	
	const SDL_Rect& getMainRect() const;
	bool isOffsetInsideRect(const Offset& offset) const;
};

#endif //BOX_DISPLAY_H