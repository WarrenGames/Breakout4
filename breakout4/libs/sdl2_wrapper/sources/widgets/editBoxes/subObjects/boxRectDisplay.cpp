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
	
	SDL_Rect rectBlack{MARGIN_SIZE, MARGIN_SIZE, boxSize.w - MARGIN_SIZE, boxSize.h - MARGIN_SIZE},
			 editRect{MARGIN_SIZE, MARGIN_SIZE, boxSize.w - MARGIN_SIZE*2, boxSize.h - MARGIN_SIZE*2};
	
	if( activeWindowSurf ){
		SDL_FillRect( activeWindowSurf.get(), nullptr, SDL_MapRGBA(activeWindowSurf->format , ED_BOX_BLACK.r, ED_BOX_BLACK.g, ED_BOX_BLACK.b, ED_BOX_BLACK.a));
		SDL_FillRect( activeWindowSurf.get(), &rectBlack, SDL_MapRGBA(activeWindowSurf->format , ED_BOX_WHITE.r, ED_BOX_WHITE.g, ED_BOX_WHITE.b, ED_BOX_WHITE.a));
		SDL_FillRect( activeWindowSurf.get(), &editRect, SDL_MapRGBA(activeWindowSurf->format, ACTIVE_ED_BOX.r, ACTIVE_ED_BOX.g, ACTIVE_ED_BOX.b, ACTIVE_ED_BOX.a));
		activeWindow.reset( SDL_CreateTextureFromSurface(rndWnd.getRend(), activeWindowSurf.get() ) );
	}
	else{
		logs.error.wrRessourceCreationError("SDL_Surface for box widget", SDL_GetError() );
	}
	
	sdl2::SurfacePtr offWindowSurf{ SDL_CreateRGBSurface(0, boxSize.w, boxSize.h, 32, 0, 0, 0, 0) };
	if( offWindowSurf ){
		SDL_FillRect( offWindowSurf.get(), nullptr, SDL_MapRGBA(offWindowSurf->format , ED_BOX_BLACK.r, ED_BOX_BLACK.g, ED_BOX_BLACK.b, ED_BOX_BLACK.a));
		SDL_FillRect( offWindowSurf.get(), &rectBlack, SDL_MapRGBA(offWindowSurf->format , ED_BOX_WHITE.r, ED_BOX_WHITE.g, ED_BOX_WHITE.b, ED_BOX_WHITE.a));
		SDL_FillRect( offWindowSurf.get(), &editRect, SDL_MapRGBA(offWindowSurf->format, OFF_BOX.r, OFF_BOX.g, OFF_BOX.b, OFF_BOX.a));
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