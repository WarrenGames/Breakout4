#ifndef DEMOS_LOAD_AND_SAVE_STACK_SQUARE_SIZE_LEGACY_H
#define DEMOS_LOAD_AND_SAVE_STACK_SQUARE_SIZE_LEGACY_H

namespace demos{ 
	template<typename T>class Stack; 
	struct PositionStackData; 
	struct TaggedPositionStackData;
}

void transformPositionStackWithLegacy(demos::Stack< demos::PositionStackData >& stack, int squareSizeAtSaving);

void transformPositionStackWithLegacy(demos::Stack< demos::TaggedPositionStackData >& stack, int squareSizeAtSaving);

#endif //DEMOS_LOAD_AND_SAVE_STACK_SQUARE_SIZE_LEGACY_H