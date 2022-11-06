#include "contexts/onePlayerGame/levelComponents/hellEpisodeThings/hellSkulls/configuration/skullFileData.h"
#include "consts/hellConsts.h"

SkullFileData::SkullFileData():
	id{ hell::IdSkull },
	skillBits{0},
	startingPos{ 0, 0},
	startingDirection{ 0, 0},
	initialSpeed{1},
	canThrowFireBalls{false},
	canSeekYellowBall{false},
	totalWaitTime{ 10000 },
	randomInterval{ 4000 },
	seedAdd{ 0 }
{
	
}

