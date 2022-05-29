#ifndef ONE_PLAYER_FIRE_BALL_ELEMENT_H
#define ONE_PLAYER_FIRE_BALL_ELEMENT_H

#include "contexts/gameCommon/fireBall/fireBallDrawData.h"
#include "contexts/gameCommon/fireBall/fireBallPathData.h"
#include "contexts/gameCommon/movements/objectMove.h"
#include "contexts/gameCommon/time/intervalAndRandomTimeHappening.h"
#include "consts/onePlayerLevelConsts.h"
#include <bitset>

class PathData;
struct FireBallFileData;
class SoundHandler;
struct OnePlayerRacket;

namespace onePlGame{

struct FireBallElement
{
	FireBallDrawData drawData;
	FireBallPathData pathData;
	ObjectMoving move;
	IntervalAndRandom randomInterval;
	bool isActive;
	bool globalTimeHasRewind;
	
	explicit FireBallElement(const PathData& path, const FireBallFileData& fileData);
	~FireBallElement() = default;
	FireBallElement( const FireBallElement& ) = delete;
	FireBallElement& operator= ( const FireBallElement& ) = delete;
	FireBallElement( FireBallElement&& ) = default;
	FireBallElement& operator= ( FireBallElement&& ) = default;
	
	void update();
	void updateWithRacket(OnePlayerRacket& racket, const SoundHandler& sounds);
	void startActivity(const SoundHandler& sounds);
	void moveFireBall();
};

}

#endif //ONE_PLAYER_FIRE_BALL_ELEMENT_H