#include "wrappers/rectStream.h"
#include "matrices/matrixStructs.h"
#include "texturing/texturePosition.h"
#include "SDL_rect.h"

std::ostream& operator<< (std::ostream& in, const SDL_Rect& rect)
{
	return in << "rect( " << rect.x << ", " << rect.y << ", " << rect.w << ", " << rect.h << ")"; 
}

std::ostream& operator<< (std::ostream& in, const Coord2D& coordinates)
{
	return in << "coords x,y,z( " << coordinates.width << " ; " << coordinates.height << " ).";
}

std::ostream& operator<< (std::ostream& in, const Coord3D& coordinates)
{
	return in << "coords x,y,z( " << coordinates.width << " ; " << coordinates.height << " ; " << coordinates.depth << " ).";
}

std::ostream& operator<< (std::ostream& in, const TexturePosition& position)
{
	return in << "xpos = " << position.position.x << " ypos = " << position.position.y << " on x centered: " << position.on_x_centered << " on y centered: " << position.on_y_centered;
}