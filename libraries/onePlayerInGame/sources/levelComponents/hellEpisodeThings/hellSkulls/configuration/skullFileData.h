#ifndef SKULL_FILE_DATA_H
#define SKULL_FILE_DATA_H

#include "customTypes/positionTypes.h"

struct SkullFileData
{
	unsigned id;
	unsigned skillBits; //std::bitset< onePlGame::SkillLevelMax >
	Offset startingPos;
	Offset startingDirection;
	double initialSpeed;
	bool canThrowFireBalls;
	bool canSeekYellowBall;
	int totalWaitTime;
	int randomInterval;
	unsigned seedAdd;
	
	SkullFileData();
	~SkullFileData() = default;
	SkullFileData( const SkullFileData& ) = delete;
	SkullFileData& operator= ( const SkullFileData& ) = delete;
	SkullFileData( SkullFileData&& ) = default;
	SkullFileData& operator= ( SkullFileData&& ) = default;
};

#endif //SKULL_FILE_DATA_H