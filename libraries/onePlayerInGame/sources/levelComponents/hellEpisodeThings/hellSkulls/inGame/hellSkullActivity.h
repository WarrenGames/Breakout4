#ifndef ONE_PLAYER_GAME_HELL_SKULL_ACTIVITY_H
#define ONE_PLAYER_GAME_HELL_SKULL_ACTIVITY_H

#include "consts/onePlayerLevelConsts.h"
#include <bitset>

struct SkullFileData;

namespace onePlGame{

struct SkullActivity
{
	std::bitset< SkillLevelMax > skillAppearence;
	unsigned pathNumber;
	unsigned nextJob;//Throw fire balls or rush to ball
	bool canThrowFireBalls;
	bool canSeekYellowBall;
	bool isSkullActive;
	bool isFireBallActive;
	bool globalTimeHasRewind;
	bool isRushing;
	bool isExploding;
	bool canCollideWithBall;
	
	explicit SkullActivity(const SkullFileData& fileData);
	~SkullActivity() = default;
	SkullActivity( const SkullActivity& ) = default;
	SkullActivity& operator= ( const SkullActivity& ) = default;
	SkullActivity( SkullActivity&& ) = default;
	SkullActivity& operator= ( SkullActivity&& ) = default;
};

}

#endif //ONE_PLAYER_GAME_HELL_SKULL_ACTIVITY_H