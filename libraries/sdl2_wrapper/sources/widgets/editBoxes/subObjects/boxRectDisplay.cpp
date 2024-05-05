#include "widgets/editBoxes/subObjects/boxRectDisplay.h"
#include "texturing/rendererWindow.h"
#include "logging/logsStruct.h"
#include "wrappers/rectStream.h"
#include "widgets/editBoxes/subObjects/editBoxes_consts.h"
#include <cassert>

BoxRectDisplaying::BoxRectDisplaying(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& boxSize):
	mainRect{boxSize}
{
	assert(boxSize.w >= 32 && boxSize.h >= 16);
	sdl2::SurfacePtr activeWindowSurf{ SDL_CreateRGBSurface(0, boxSize.w, boxSize.h, 32, 0, 0, 0, 0) };
	
	SDL_Rect rectBlack{BoxesMarginSize, BoxesMarginSize, boxSize.w - BoxesMarginSize, boxSize.h - BoxesMarginSize},
			 editRect{BoxesMarginSize, BoxesMarginSize, boxSize.w - BoxesMarginSize*2, boxSize.h - BoxesMarginSize*2};
	
	if( activeWindowSurf ){
		SDL_FillRect( activeWindowSurf.get(), nullptr, SDL_MapRGBA(activeWindowSurf->format , BoxesEditBoxBlack.r, BoxesEditBoxBlack.g, BoxesEditBoxBlack.b, BoxesEditBoxBlack.a));
		SDL_FillRect( activeWindowSurf.get(), &rectBlack, SDL_MapRGBA(activeWindowSurf->format , BoxesEditBoxWhite.r, BoxesEditBoxWhite.g, BoxesEditBoxWhite.b, BoxesEditBoxWhite.a));
		SDL_FillRect( activeWindowSurf.get(), &editRect, SDL_MapRGBA(activeWindowSurf->format, BoxesActiveEditBox.r, BoxesActiveEditBox.g, BoxesActiveEditBox.b, BoxesActiveEditBox.a));
		activeWindow.reset( SDL_CreateTextureFromSurface(rndWnd.getRend(), activeWindowSurf.get() ) );
	}
	else{
		logs.error.wrRessourceCreationError("SDL_Surface for box widget", SDL_GetError() );
	}
	
	sdl2::SurfacePtr offWindowSurf{ SDL_CreateRGBSurface(0, boxSize.w, boxSize.h, 32, 0, 0, 0, 0) };
	if( offWindowSurf ){
		SDL_FillRect( offWindowSurf.get(), nullptr, SDL_MapRGBA(offWindowSurf->format , BoxesEditBoxBlack.r, BoxesEditBoxBlack.g, BoxesEditBoxBlack.b, BoxesEditBoxBlack.a));
		SDL_FillRect( offWindowSurf.get(), &rectBlack, SDL_MapRGBA(offWindowSurf->format , BoxesEditBoxWhite.r, BoxesEditBoxWhite.g, BoxesEditBoxWhite.b, BoxesEditBoxWhite.a));
		SDL_FillRect( offWindowSurf.get(), &editRect, SDL_MapRGBA(offWindowSurf->format, BoxesOffEditBox.r, BoxesOffEditBox.g, BoxesOffEditBox.b, BoxesOffEditBox.a));
		offWindow.reset( SDL_CreateTextureFromSurface(rndWnd.getRend(), offWindowSurf.get() ) );
	}
	else{
		logs.error.wrRessourceCreationError("SDL_Surface for box widget", SDL_GetError() );
	}
}

void BoxRectDisplaying::drawActiveWindow(sdl2::RendererWindow& rndWnd) const
{
	SDL_RenderCopy(rndWnd.getRend(), activeWindow.get(), nullptr, &mainRect);
}

void BoxRectDisplaying::drawOffWindow(sdl2::RendererWindow& rndWnd) const
{
	SDL_RenderCopy(rndWnd.getRend(), offWindow.get(), nullptr, &mainRect);
}

const SDL_Rect& BoxRectDisplaying::getMainRect() const
{
	return mainRect;
}

bool BoxRectDisplaying::isOffsetInsideRect(const Offset& offset) const
{
	return offset.x >= mainRect.x && offset.x < mainRect.x + mainRect.w 
		&& offset.y >= mainRect.y && offset.y < mainRect.y + mainRect.h;
}