#include "texturing/loadSDL2.h"
#include "texturing/rendererWindow.h"
#include "texturing/sdl2_sprite.h"

SDL_Texture* makeHorizontalGradient(sdl2::RendererWindow& rndWnd, int w, int h, const SDL_Color& startColor, const SDL_Color& endColor)
{
	if( sdl2::SurfacePtr tempSurf{ SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0) } )
	{
		SDL_Rect RectTemp{0, 0, 1, h};
		for(int i{ 0 } ; i < w ; ++i)
		{
			RectTemp.x = i;
			SDL_FillRect(tempSurf.get(), &RectTemp, SDL_MapRGBA(tempSurf->format,
																		static_cast<Uint8>((endColor.r - startColor.r) * i / w + startColor.r),
																		static_cast<Uint8>((endColor.g - startColor.g) * i / w + startColor.g),
																		static_cast<Uint8>((endColor.b - startColor.b) * i / w + startColor.b),
																		static_cast<Uint8>((endColor.a - startColor.a) * i / w + startColor.a )) );
		}
		return SDL_CreateTextureFromSurface(rndWnd.getRend(), tempSurf.get() );
	}
	else{
		return nullptr;
	}
}

void drawHorizontalGradient(sdl2::SurfacePtr& surf, int startx, int endx, const SDL_Color& startColor, const SDL_Color& endColor)
{	
	double start = startx;
	double end = endx;
	//Compute coefficient director
	double coefDirRed = (endColor.r -startColor.r ) / (end - start);
	double coefDirGreen = (endColor.g - startColor.g ) / (end - start);
	double coefDirBlue = (endColor.b - startColor.b ) / (end - start);
	double coefDirAlpha = (endColor.a -startColor.a ) / (end - start);
	
	//Ordonnée à l'origine
	double bRed = startColor.r - coefDirRed * startx;
	double bGreen = startColor.g - coefDirGreen * startx;
	double bBlue = startColor.b - coefDirBlue * startx;
	double bAlpha = startColor.a - coefDirAlpha * startx;
	
	SDL_Rect rect{0, 0, 1, surf->h};
	
	for(int i{startx} ; i < endx ; ++i)
	{
		rect.x = i;
		SDL_FillRect(surf.get(), &rect, SDL_MapRGBA(surf->format, static_cast<Uint8>(coefDirRed * i + bRed), 
																	static_cast<Uint8>(coefDirGreen * i + bGreen),
																	static_cast<Uint8>(coefDirBlue * i + bBlue), 
																	static_cast<Uint8>(coefDirAlpha * i + bAlpha) ) );
	}
}

void drawVerticalGradient(sdl2::SurfacePtr& surf, int starty, int endy, const SDL_Color& topColor, const SDL_Color& bottomColor)
{			
	double start = starty;
	double end = endy;
	//Compute coefficient director
	double coefDirRed = (bottomColor.r - topColor.r ) / (end - start);
	double coefDirGreen = (bottomColor.g - topColor.g ) / (end - start);
	double coefDirBlue = (bottomColor.b - topColor.b ) / (end - start);
	double coefDirAlpha = (bottomColor.a - topColor.a ) / (end - start);
	
	//Ordonnée à l'origine
	double bRed = topColor.r - coefDirRed * starty;
	double bGreen = topColor.g - coefDirGreen * starty;
	double bBlue = topColor.b - coefDirBlue * starty;
	double bAlpha = topColor.a - coefDirAlpha * starty;
	
	SDL_Rect rect{0, 0, surf->w, 1};
	
	for( int i{ starty } ; i < endy ; ++i )
	{
		rect.y = i;
		SDL_FillRect(surf.get(), &rect, SDL_MapRGBA(surf->format, static_cast<Uint8>(coefDirRed * i + bRed),
																  static_cast<Uint8>(coefDirGreen * i + bGreen),
																  static_cast<Uint8>(coefDirBlue * i + bBlue),
																  static_cast<Uint8>(coefDirAlpha * i + bAlpha) ) );
	}
}
