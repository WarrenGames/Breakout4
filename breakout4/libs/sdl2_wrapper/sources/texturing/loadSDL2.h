#ifndef LOAD_SDL2_H
#define LOAD_SDL2_H

#include "wrappers/sdl2_ptr.h"
#include <string>

struct AppLogFiles;
namespace sdl2{ class RendererWindow; class Font; class TextureLoader; class Sprite; }
struct SDL_Color;

SDL_Texture* makeHorizontalGradient(sdl2::RendererWindow& rndWnd, int w, int h, const SDL_Color& startColor, const SDL_Color& endColor);

void drawHorizontalGradient(sdl2::SurfacePtr& surf, int startx, int endx, const SDL_Color& startColor, const SDL_Color& endColor);

void drawVerticalGradient(sdl2::SurfacePtr& surf, int starty, int endy, const SDL_Color& topColor, const SDL_Color& bottomColor);

//void resetSimpleTexture(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, sdl2::TextureLoader& texture, sdl2::Sprite& sprite, const std::string& text, const SDL_Color& col);

#endif //LOAD_SDL2_H
