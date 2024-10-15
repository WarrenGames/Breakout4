#include "texturing/horizontalGradientTexture.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include "customTypes/positionTypes.h"
#include <cassert>

sdl2::HorizontalGradient::HorizontalGradient(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned startValue, unsigned valueMax, const SDL_Rect& newRect, 
										const SDL_Color& leftColor, const SDL_Color& rightColor, bool fromLeftCount):
	gradient{ logs, rndWnd, newRect, leftColor, rightColor, GradientTextureOnX },
	boundingBox{newRect},
	selectRect{0, 0, newRect.w, newRect.h},
	destRect{newRect},
	counterMaxValue{ static_cast<int>(valueMax) },
	fromLeftToRightGrad{fromLeftCount},
	isLoadingPerfect{true}
{
	assert( valueMax != 0 );
	setNewCounterValue(static_cast<int>(startValue) );
}

sdl2::HorizontalGradient::operator bool() const
{
	return wasLoadingPerfect();
}

bool sdl2::HorizontalGradient::wasLoadingPerfect() const
{
	if( gradient )
		return true;
	else
		return false;
}

void sdl2::HorizontalGradient::draw(sdl2::RendererWindow& rndWnd) const
{
	gradient.sprite.drawWithTwoRect(rndWnd, selectRect, destRect);
}

void sdl2::HorizontalGradient::setNewCounterValue(int newValue)
{
	assert( newValue >= 0 && newValue <= counterMaxValue );
	
	if( fromLeftToRightGrad )
		setWithLeftAsOrigin(newValue);
	else
		setWithRightAsOrigin(newValue);
}

void sdl2::HorizontalGradient::setMaxValue(int newMaxValue)
{
	counterMaxValue = newMaxValue;
}

void sdl2::HorizontalGradient::setWithLeftAsOrigin(int newValue)
{
	selectRect.w = newValue * boundingBox.w / counterMaxValue;
	destRect.w = selectRect.w;
}

void sdl2::HorizontalGradient::setWithRightAsOrigin(int newValue)
{
	selectRect.x = boundingBox.w - newValue * boundingBox.w / counterMaxValue;
	selectRect.w = newValue * boundingBox.w / counterMaxValue;
	
	destRect.x = boundingBox.x + boundingBox.w - selectRect.w;
	destRect.w = selectRect.w;
}