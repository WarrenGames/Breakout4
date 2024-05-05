#ifndef VERTICAL_GRADIENT_TEXTURE_H
#define VERTICAL_GRADIENT_TEXTURE_H

#include "texturing/texturesCombo.h"

struct AppLogFiles;

namespace sdl2{
	class RendererWindow;

class VerticalGradient
{
private:
	TextureCombo gradient;
	SDL_Rect boundingBox;
	SDL_Rect selectRect;
	SDL_Rect destRect;
	int counterMaxValue;
	bool fromBottomToTopGrad;
	
public:
	VerticalGradient(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned startValue, unsigned valueMax, const SDL_Rect& newRect, const SDL_Color& topColor, const SDL_Color& bottomColor, 
						bool fromBottomCount);
	~VerticalGradient() = default;
	
	VerticalGradient( const VerticalGradient& ) = delete;
	VerticalGradient& operator= ( const VerticalGradient& ) = delete;
	VerticalGradient( VerticalGradient&& ) = default;
	VerticalGradient& operator= ( VerticalGradient&& ) = default;
	
	operator bool () const;
	
	bool wasLoadingPerfect() const;
	
	void draw(sdl2::RendererWindow& rndWnd) const;
	void setNewCounterValue(int newValue);
	void setWithBottomAsOrigin(int newValue);
	void setWithTopAsOrigin(int newValue);
};

}

#endif //VERTICAL_GRADIENT_TEXTURE_H