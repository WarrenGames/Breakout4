#ifndef ONE_PLAYER_FIRE_BALL_ELEMENT_H
#define ONE_PLAYER_FIRE_BALL_ELEMENT_H

#include "contexts/gameCommon/fireBall/fireBallDrawData.h"
#include "spriteMove/spriteMoveData.h"
#include "spriteMove/starType.h"
#include "contexts/gameCommon/time/intervalAndRandomTimeHappening.h"
#include "consts/onePlayerLevelConsts.h"

namespace spriteMove{ struct VectorsGroup; }
struct FireBallFileData;
class SoundHandler;
struct OnePlayerRacket;

namespace onePlGame{

struct FireBallElement
{
	const Offset startPosition;
	FireBallDrawData drawData;
	spriteMove::MovementThings move;
	spriteMove::StarTypeThings starThings;
	IntervalAndRandom randomInterval;
	bool isActive;
	bool globalTimeHasRewind;
	
	explicit FireBallElement(const spriteMove::VectorsGroup& path, const FireBallFileData& fileData);
	~FireBallElement() = default;
	FireBallElement( const FireBallElement& ) = delete;
	FireBallElement& operator= ( const FireBallElement& ) = delete;
	FireBallElement( FireBallElement&& ) = default;
	FireBallElement& operator= ( FireBallElement&& ) = default;
	
	void update();
	void updateWithRacket(OnePlayerRacket& racket, const SoundHandler& sounds);
	void startActivity(const SoundHandler& sounds);
	void moveFireBall();
	void resetPositionIfNeeded();
};

}

#endif //ONE_PLAYER_FIRE_BALL_ELEMENT_H