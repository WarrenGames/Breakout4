#ifndef BALLS_THINGS_H
#define BALLS_THINGS_H

#include "spriteMove/objectMove.h"
#include "texturing/texturesCombo.h"
#include "time/accurateTime.h"
#include "types/spriteSize.h"
#include "matrices/matrix2D.h"
#include "consts/onePlayerGridConsts.h"
#include "levelComponents/balls/ballSpeedsOptions.h"

namespace sdl2{ class RendererWindow; }
class SoundPlayer;
class OnePlayerRimsSystem;
namespace demos{ template<typename T>class Stack; struct SoundStackData; }

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
	spriteMove::ObjectMoving move;//X and y position are the 'center' of the ball
	AccurateTimeDelay moveBallDelay;
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
	
	void handleBallWithRacketCollision(const SDL_Rect& racketRect, unsigned& glueLevel, const SoundPlayer& soundPlayer, demos::Stack< demos::SoundStackData >& soundsStack, 
												unsigned demoKind);
	
	void resetBetweenRacketAndBallCollisionPossibility(const SDL_Rect& racketRect);
	void setEnlargedRacketRect(SDL_Rect& enlargedRacketRect, int interval);
	bool isThereCollisionBetweenRects(const SDL_Rect& racketRect/* can be enlarged one for reseting collide*/, const SDL_Rect& ballRect);
	
	void detectCollisionBetweenBallAndRacket(const SDL_Rect& racketRect, unsigned& glueLevel, const SoundPlayer& soundPlayer, demos::Stack< demos::SoundStackData >& soundsStack, 
												unsigned demoKind);
	void determineBallBounceWithRacket(const SDL_Rect& racketRect, const SoundPlayer& soundPlayer, demos::Stack< demos::SoundStackData >& soundsStack, unsigned demoKind);
	void bounceMakeBallGoesUpward(const SDL_Rect& racketRect, const SoundPlayer& soundPlayer, demos::Stack< demos::SoundStackData >& soundsStack, unsigned demoKind);

	void testCollisionWithRims(const OnePlayerRimsSystem& rims, const SoundPlayer& soundPlayer);

	SpriteSize getTexSize() const;
};

void stackSoundOfBallWithRacketCollision(demos::Stack< demos::SoundStackData >& soundsStack, unsigned demoKind);

#endif //BALLS_THINGS_H