#include "levelComponents/hellEpisodeThings/fireBalls/configuration/fireBallFileData.h"
#include "consts/hellConsts.h"

FireBallFileData::FireBallFileData():
	id{ hell::IdLava },
	behaviorId{ 0 },
	skillBits{ 0 },
	sqrSizeRelativePos{ -2 },
	totalWaitTime{ 10000 },
	randomTimeInterval{ 1000 },
	seedAdd{ 0 }
{
	
}