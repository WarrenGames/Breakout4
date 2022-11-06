#ifndef RECT_STREAMS_H
#define RECT_STREAMS_H

#include <iostream>

struct SDL_Rect;
struct Coord2D;
struct Coord3D;
struct TexturePosition;

std::ostream& operator<< (std::ostream& in, const SDL_Rect& rect);

std::ostream& operator<< (std::ostream& in, const Coord2D& coordinates);

std::ostream& operator<< (std::ostream& in, const Coord3D& coordinates);

std::ostream& operator<< (std::ostream& in, const TexturePosition& position);

#endif //RECT_STREAMS_H