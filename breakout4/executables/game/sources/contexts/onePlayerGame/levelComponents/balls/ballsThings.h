#ifndef BALLS_THINGS_H
#define BALLS_THINGS_H

#include "spriteMove/objectMove.h"
#include "texturing/texturesCombo.h"
#include "time/accurateTime.h"
#include "types/spriteSize.h"
#include "matrices/matrix2D.h"
#include "consts/onePlayerGridConsts.h"
#include "contexts/onePlayerGame/levelComponents/balls/ballSpeedsOptions.h"

namespace sdl2{ class RendererWindow; }
class SoundHandler;
class OnePlayerRims;

struct BallThings
{
	bool isLoadingPerfect;
	bool isMainBallActive;
	bool canDetectCollisionSince;
	bool canTestRimCollisions;
	bool canTestMonstersCollision;
	bool isBallPowerful;
	bool canTestRacketCollideBox;
	std::vector< bool > monstersCollisionIsEffective;
	spriteMove::ObjectMoving move;
	AccurateTimeDelay moveBallDelay;
	AccurateTimeDelay accelerateBallDelay;
	TextureCombo texture;
	Offset gridRelPos;
	BallSpeeds speeds;

	explicit BallThings(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, std::size_t monstersNumber);
	~BallThings() = default;
	BallThings( const BallThings& ) = delete;
	BallThings& operator= ( const BallThings& ) = delete;
	BallThings( BallThings&& ) = default;
	BallThings& operator= ( BallThings&& ) = default;
	
	operator bool() const;
	
	void drawMainBall(sdl2::RendererWindow& rndWnd);
	void moveMainBall();
	void setGridRelativePosition();
	
	void handleBallWithRacketCollision(const SDL_Rect& racketRect, unsigned& glueLevel, const SoundHandler& sounds);
	
	void resetBetweenRacketAndBallCollisionPossibility(const SDL_Rect& racketRect);
	void setEnlargedRacketRect(SDL_Rect& enlargedRacketRect, int interval);
	bool isThereCollisionBetweenRects(const SDL_Rect& racketRect/* can be enlarged one for reseting collide*/, const SDL_Rect& ballRect);
	
	void detectCollisionBetweenBallAndRacket(const SDL_Rect& racketRect, unsigned& glueLevel, const SoundHandler& sounds);
	void determineBallBounceWithRacket(const SDL_Rect& racketRect, const SoundHandler& sounds);
	void bounceMakeBallGoesUpward(const SDL_Rect& racketRect, const SoundHandler& sounds);
	
	void accelerateSpeed(unsigned skillLevel);
	
	void testCollisionWithRims(const OnePlayerRims& rims, const SoundHandler& sounds);
	
	SpriteSize getTexSize() const;
};

#endif //BALLS_THINGS_H