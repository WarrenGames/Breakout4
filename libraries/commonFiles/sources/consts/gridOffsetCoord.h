#ifndef GRID_OFFSET_COORD_CONSTS_H
#define GRID_OFFSET_COORD_CONSTS_H

#include "customTypes/positionTypes.h"

namespace position{

constexpr Offset Top = { 0, -1 };
constexpr Offset Bottom = { 0, 1 };
constexpr Offset Left = { -1, 0 };
constexpr Offset Right = { 1, 0 };

constexpr Offset TopLeft	 =  { -1, -1 };
constexpr Offset TopRight	= {  1, -1 };
constexpr Offset BottomLeft  =  { -1, 1 };
constexpr Offset BottomRight =  {  1, 1 };

}

#endif //GRID_OFFSET_COORD_CONSTS_H