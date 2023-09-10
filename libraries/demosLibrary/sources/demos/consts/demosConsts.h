#ifndef DEMOS_LIB_CONSTANTS_H
#define DEMOS_LIB_CONSTANTS_H

#include <cstddef>

namespace demos{
	constexpr std::size_t DefaultReservedDataForRecording = 8000000;
	
	constexpr std::size_t QuitEventReservedSize = 1;
	
	enum{	GameHasPlayerInputs, 
			GameIsRecording, 
			GameIsDemo,
			GameDemoEnumMax
	};
	
	constexpr unsigned QuitEventFunc = 0;
	
	constexpr int NotAssignedTag = -1;

	constexpr char InputDataStr[] = "inputs data";
	constexpr char QuitLevelEventStr[] = "quit level event";
	constexpr char TraceCrossPositionStr[] = "trace cross position";
	constexpr char RacketPositionStr[] = "racket position";
	constexpr char BallPositionStr[] = "ball position";
	constexpr char BrickDestructionStr[] = "brick destruction";
	constexpr char SoundEventStr[] = "sound event data";
	constexpr char PinguinsPositionDataStr[] = "pinguins position data";
	constexpr char PinguinsDirectionDataStr[] = "pinguins direction data";
	constexpr char PinguinsCreateAndDestroyStr[] = "pinguins creation and destruction data";
	constexpr char PinguinsQuackSound[] = "pinguins quack sounds data";

}

#endif //DEMOS_LIB_CONSTANTS_H