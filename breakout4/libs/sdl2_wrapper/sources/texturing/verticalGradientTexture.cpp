#include "texturing/verticalGradientTexture.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include "texturing/loadSDL2.h"
#include "customTypes/positionTypes.h"
#include "wrappers/rectStream.h"
#include <cassert>

sdl2::VerticalGradient::VerticalGradient(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned startValue, unsigned valueMax, const SDL_Rect& newRect, const SDL_Color& topCol, 
									const SDL_Color& bottomCol, bool fromBottom):
	isLoadingPerfect{true},
	fromBottomToTopGrad{fromBottom},
	counterMaxValue{static_cast<int>(valueMax)},
	gradient{logs, rndWnd, newRect, topCol, bottomCol, GRAD_TEX_ON_Y},
	boundingBox{newRect},
	selectRect{0, 0, newRect.w, newRect.h},
	destRect{newRect}
{
	assert( valueMax != 0 );
	setNewCounterValue(startValue);
}

sdl2::VerticalGradient::operator bool () const
{
	if( gradient )
		return true;
	else
		return false;
}

bool sdl2::VerticalGradient::wasLoadingPerfect() const
{
	if( gradient )
		return true;
	else
		return false;
}

void sdl2::VerticalGradient::draw(sdl2::RendererWindow& rndWnd) const
{
	gradient.sprite.drawWithTwoRect(rndWnd, selectRect, destRect);
}

void sdl2::VerticalGradient::setNewCounterValue(int newValue)
{
	assert( newValue >= 0 && newValue <= counterMaxValue );
	
	if( fromBottomToTopGrad )
		setWithBottomAsOrigin(newValue);
	else
		setWithTopAsOrigin(newValue);
}

void sdl2::VerticalGradient::setWithBottomAsOrigin(int newValue)
{
	selectRect.y = boundingBox.h - newValue * boundingBox.h / counterMaxValue;
	selectRect.h = newValue * boundingBox.h / counterMaxValue;
	
	destRect.y = boundingBox.y + boundingBox.h - selectRect.h;
	destRect.h = selectRect.h;
}

void sdl2::VerticalGradient::setWithTopAsOrigin(int newValue)
{
	selectRect.h = newValue * boundingBox.h / counterMaxValue;
	
	destRect.h = selectRect.h;
}