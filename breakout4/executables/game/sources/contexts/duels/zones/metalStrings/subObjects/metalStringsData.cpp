#include "contexts/duels/zones/metalStrings/subObjects/metalStringsData.h"
#include "contexts/duels/zones/metalStrings/subObjects/consts.h"
#include <cassert>

metalStrings::StringData::StringData(const Offset& position, unsigned stringOrientation, unsigned forwardDir, unsigned backwardDir):
	texturePosition{position},
	textureIndex{0},
	orientation{stringOrientation},
	forwardDirection{forwardDir},
	backwardDirection{backwardDir},
	currentDirection{metalStrings::DIR_STOP}
{
	
}

void metalStrings::StringData::updateAnimation()
{
	if( currentDirection == forwardDirection )
		forwardAnimation();
	else if( currentDirection == backwardDirection )
		reverseAnimation();
}

void metalStrings::StringData::reverseAnimation()
{
	if( textureIndex > 0 )
		textureIndex--;
	else{
		textureIndex = metalStrings::STRING_FRAMES_NUM - 1;
	}
}

void metalStrings::StringData::forwardAnimation()
{
	if( textureIndex + 1 < metalStrings::STRING_FRAMES_NUM )
		textureIndex++;
	else
		textureIndex = 0;
}

void metalStrings::StringData::startDirection(unsigned direction)
{
	assert( direction <= metalStrings::DIR_STOP );
	currentDirection = direction;
}