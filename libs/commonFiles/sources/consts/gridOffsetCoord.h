#ifndef GRID_OFFSET_COORD_CONSTS_H
#define GRID_OFFSET_COORD_CONSTS_H

#include "customTypes/positionTypes.h"

namespace position{

constexpr Offset TOP = { 0, -1 };
constexpr Offset BOTTOM = { 0, 1 };
constexpr Offset LEFT = { -1, 0 };
constexpr Offset RIGHT = { 1, 0 };

constexpr Offset TOP_LEFT	 =  { -1, -1 };
constexpr Offset TOP_RIGHT	= {  1, -1 };
constexpr Offset BOTTOM_LEFT  =  { -1, 1 };
constexpr Offset BOTTOM_RIGHT =  {  1, 1 };

}

#endif //GRID_OFFSET_COORD_CONSTS_H