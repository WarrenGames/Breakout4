#ifndef METAL_STRINGS_DRAWER_H
#define METAL_STRINGS_DRAWER_H

#include "customTypes/positionTypes.h"

namespace metalStrings{

struct StringData
{
	const Offset texturePosition;
	unsigned textureIndex;
	unsigned orientation;//enum{ OrientationHorizontal, OrientationVertical, OrientationMax };
	const unsigned forwardDirection;//enum{ DirectionToRight, DirectionToLeft, DirectionHorizontalStop }; ou enum{ DirectionToSouth, DirectionToNorth, DirectionVerticalStop };
	const unsigned backwardDirection;
	unsigned currentDirection;//enum{ DirectionForward, DirectionRegress, DirectionStop };
	
	explicit StringData(const Offset& position, unsigned stringOrientation, unsigned forwardDir, unsigned backwardDir);
	void updateAnimation();
	void reverseAnimation();
	void forwardAnimation();
	
	void startDirection(unsigned direction);
};

}
#endif //METAL_STRINGS_DRAWER_H