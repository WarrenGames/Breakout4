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

bool coords::are2DCoordsTheSame(const Coord2D& c1, const Coord2D& c2)
{
	return c1.width == c2.width && c1.height == c2.height;
}

bool coords::are3DCoordsTheSame(const Coord3D& c1, const Coord3D& c2)
{
	return c1.width == c2.width && c1.height == c2.height && c1.depth == c2.depth;
}

bool coords::isNewCoordOnTopFromSecond(const Coord2D& newCoord, const Coord2D& second)
{
	return newCoord.width == second.width && newCoord.height + 1 == second.height;
}

bool coords::isNewCoordToBottomFromSecond(const Coord2D& newCoord, const Coord2D& second)
{
	return newCoord.width == second.width && newCoord.height == second.height + 1;
}

bool coords::isNewCoordToLeftFromSecond(const Coord2D& newCoord, const Coord2D& second)
{
	return newCoord.height == second.height && newCoord.width + 1 == second.width;
}

bool coords::isNewCoordToRightFromSecond(const Coord2D& newCoord, const Coord2D& second)
{
	return newCoord.height == second.height && newCoord.width == second.width + 1;
}
