#ifndef TEMPLATE_MATRIX_STRUCTS_H
#define TEMPLATE_MATRIX_STRUCTS_H

#include <cstddef>

struct Coord3D
{
	std::size_t width;
	std::size_t height;
	std::size_t depth;
	
	Coord3D();
	Coord3D(std::size_t w, std::size_t h, std::size_t d);
	Coord3D( const Coord3D& ) = default;
	Coord3D& operator= ( const Coord3D& ) = default;
};

struct Coord2D
{
	std::size_t width;
	std::size_t height;
	
	Coord2D();
	Coord2D(std::size_t w, std::size_t h);
	Coord2D( const Coord2D& ) = default;
	Coord2D& operator= ( const Coord2D& ) = default;
};

namespace coords{

bool are2DCoordsTheSame(const Coord2D& c1, const Coord2D& c2);

bool are3DCoordsTheSame(const Coord3D& c1, const Coord3D& c2);

bool isNewCoordOnTopFromSecond(const Coord2D& newCoord, const Coord2D& second);

bool isNewCoordToBottomFromSecond(const Coord2D& newCoord, const Coord2D& second);

bool isNewCoordToLeftFromSecond(const Coord2D& newCoord, const Coord2D& second);

bool isNewCoordToRightFromSecond(const Coord2D& newCoord, const Coord2D& second);

}

#endif //TEMPLATE_MATRIX_STRUCTS_H