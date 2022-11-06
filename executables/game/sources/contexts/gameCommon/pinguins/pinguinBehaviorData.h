#ifndef PINGUIN_BEHAVIOR_DATA_H
#define PINGUIN_BEHAVIOR_DATA_H

#include "contexts/gameCommon/pinguins/pinguinDrawData.h"
#include "matrices/matrix2D.h"

struct SDL_Rect;
class SoundHandler;

enum{ PinguinIsActive, PinguinIsLeaving, PinguinIsInactive, PinguinStartMindPlayer };

class PinguinBehaviorData
{
private:
	PinguinDrawData drawingData;
	unsigned anger;
	unsigned state;
	bool canPinguinGoOut;
	bool canPinguinQuack;//true if racket collide (while moving) with pinguin
	bool canCollideWithRacket;//true if pinguin can reverse its move vectors (reset to true if racket is a little far from pinguin)
	bool canCollideWithRims;
	Offset startingPosition;
	Offset startingDir;
	double startingSpeed;

public:
	explicit PinguinBehaviorData(const AccurCoords& pinguinPos, double speed, const Offset& dirVectors);
	~PinguinBehaviorData() = default;
	PinguinBehaviorData( const PinguinBehaviorData& ) = delete;
	PinguinBehaviorData& operator= ( const PinguinBehaviorData& ) = delete;
	PinguinBehaviorData( PinguinBehaviorData&& ) = default;
	PinguinBehaviorData& operator= ( PinguinBehaviorData&& ) = default;
	
	unsigned getState() const;
	void setState(unsigned newState);
	unsigned getAnger() const;
	const PinguinDrawData& getDrawingData() const;
	PinguinDrawData& getDrawingData();
	void makePinguinLeaveIfAny(unsigned hitTimesThreshold);
	
	void activePinguin();
	void movePinguin();
	void animPinguin();
	
	void resetRacketCollisionBooleans(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect);
	void makeBounceWithRacket(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect);
	void makeBounceVertically(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect);
	void bounceFromRacketTop(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect);
	void bounceFromRacketBottom(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect);
	void makeBounceHorizontally(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect);
	void bounceFromRacketLeft(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect);
	void bounceFromRacketRight(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect);
	
	void makePinguinQuack(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect, bool playerLeftState, bool playerRightState, const SoundHandler& sounds);
	void quackFromItsLeft(const SDL_Rect& racketRect, bool playerRightState, const SoundHandler& sounds);
	void quackFromItsRight(const SDL_Rect& racketRect, bool playerLeftState, const SoundHandler& sounds);
	
	void makeBounceWithRimRect(const SDL_Rect& rimRect, const SDL_Rect& pinguinRect, const SoundHandler& sounds);

	void setPinguinPathWithMouse(const Offset& mousePosition, bool mouseButtonState);
	
	void startMindPlayer(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect);
	
	bool isPinguinNearXRacketCoordinates(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect, int interval) const;
	bool isPinguinOnSameLevelAsRacket() const;
	void makeStayOnRacketLevelIfMindPlayer(const SDL_Rect& racketRect);
	
	bool isPinguinInsideScreen(const SDL_Rect& pinguinRect) const;
};

#endif //PINGUIN_BEHAVIOR_DATA_H