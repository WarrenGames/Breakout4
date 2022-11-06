#include "matrices/matrixStructs.h"

Coord2D::Coord2D():
	width{0},
	height{0}
{
	
}

Coord2D::Coord2D(std::size_t w, std::size_t h):
	width{w},
	height{h}
{

}

Coord3D::Coord3D():
	width{0},
	height{0},
	depth{0}
{
	
}

Coord3D::Coord3D(std::size_t w, std::size_t h, std::size_t d):
	width{w},
	height{h},
	depth{d}
{
	
}