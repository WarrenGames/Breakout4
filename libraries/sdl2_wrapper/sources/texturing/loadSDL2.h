#ifndef LOAD_SDL2_H
#define LOAD_SDL2_H

#include "wrappers/sdl2_ptr.h"
#include <string>

namespace sdl2{ class RendererWindow; }
struct SDL_Color;

SDL_Texture* makeHorizontalGradient(sdl2::RendererWindow& rndWnd, int w, int h, const SDL_Color& startColor, const SDL_Color& endColor);

void drawHorizontalGradient(sdl2::SurfacePtr& surf, int startx, int endx, const SDL_Color& startColor, const SDL_Color& endColor);

void drawVerticalGradient(sdl2::SurfacePtr& surf, int starty, int endy, const SDL_Color& topColor, const SDL_Color& bottomColor);

#endif //LOAD_SDL2_H
