#ifndef SPRITE_MOVE_LIB_CREATE_PATHS_DATA_H
#define SPRITE_MOVE_LIB_CREATE_PATHS_DATA_H

#include <cstdlib>

struct Offset;

namespace spriteMove{
	
	struct MovementThings;
	class Movements;
	struct VectorsGroup;

	void createPathData(spriteMove::MovementThings& moveThing, const spriteMove::Movements& movements, std::size_t moveNumber, Offset startPosition);
	
	void createPathData(spriteMove::MovementThings& moveThing, const spriteMove::VectorsGroup& path, Offset startPosition);
}

#endif //SPRITE_MOVE_LIB_CREATE_PATHS_DATA_H