#ifndef HORIZONTAL_GRADIENT_TEXTURE_H
#define HORIZONTAL_GRADIENT_TEXTURE_H

#include "texturing/texturesCombo.h"

struct AppLogFiles;

namespace sdl2{
	class RendererWindow;

class HorizontalGradient
{
private:
	TextureCombo gradient;
	SDL_Rect boundingBox;
	SDL_Rect selectRect;
	SDL_Rect destRect;
	int counterMaxValue;
	bool fromLeftToRightGrad;
	bool isLoadingPerfect;
	
public:
	HorizontalGradient(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned startValue, unsigned valueMax, const SDL_Rect& newRect, const SDL_Color& leftColor, 
						const SDL_Color& rightColor, bool fromLeftCount);
	~HorizontalGradient() = default;
	HorizontalGradient( const HorizontalGradient& ) = delete;
	HorizontalGradient& operator= ( const HorizontalGradient& ) = delete;
	HorizontalGradient( HorizontalGradient&& ) = default;
	HorizontalGradient& operator= ( HorizontalGradient&& ) = default;
	
	operator bool () const;
	
	bool wasLoadingPerfect() const;
	
	void draw(sdl2::RendererWindow& rndWnd) const;
	void setNewCounterValue(int newValue);
	void setMaxValue(int newMaxValue);
	
private:
	void setWithLeftAsOrigin(int newValue);
	void setWithRightAsOrigin(int newValue);
};

}

#endif //HORIZONTAL_GRADIENT_TEXTURE_H