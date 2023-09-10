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
};

struct Coord2D
{
	std::size_t width;
	std::size_t height;
	
	Coord2D();
	Coord2D(std::size_t w, std::size_t h);
};

#endif //TEMPLATE_MATRIX_STRUCTS_H