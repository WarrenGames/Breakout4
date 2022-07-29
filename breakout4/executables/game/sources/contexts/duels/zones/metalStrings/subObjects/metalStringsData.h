#ifndef METAL_STRINGS_DRAWER_H
#define METAL_STRINGS_DRAWER_H

#include "customTypes/positionTypes.h"

namespace metalStrings{

struct StringData
{
	const Offset texturePosition;
	unsigned textureIndex;
	unsigned orientation;//enum{ ORIENT_HORIZ, ORIENT_VERT, ORIENT_MAX };
	const unsigned forwardDirection;//enum{ DIR_TO_RIGHT, DIR_TO_LEFT, DIR_HORIZ_STOP }; ou enum{ DIR_TO_SOUTH, DIR_TO_NORTH, DIR_VERT_STOP };
	const unsigned backwardDirection;
	unsigned currentDirection;//enum{ DIR_FORWARD, DIR_REGRESS, DIR_STOP };
	
	explicit StringData(const Offset& position, unsigned stringOrientation, unsigned forwardDir, unsigned backwardDir);
	void updateAnimation();
	void reverseAnimation();
	void forwardAnimation();
	
	void startDirection(unsigned direction);
};

}
#endif //METAL_STRINGS_DRAWER_H