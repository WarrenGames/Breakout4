#ifndef SPRITE_MOVE_LIB_MOVE_INFOS_H
#define SPRITE_MOVE_LIB_MOVE_INFOS_H

#include "customTypes/positionTypes.h"
#include <chrono>

namespace spriteMove{
	
struct MoveInfo
{
	Offset vectors;
	Offset finalPos;
	double speed;
	std::chrono::milliseconds wait;
};

}

#endif //SPRITE_MOVE_LIB_MOVE_INFOS_H