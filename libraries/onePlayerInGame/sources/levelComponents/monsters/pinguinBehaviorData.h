#ifndef PINGUIN_BEHAVIOR_DATA_H
#define PINGUIN_BEHAVIOR_DATA_H

#include "pinguins/pinguinDrawData.h"
#include "consts/constexprScreen.h"
#include "matrices/matrix2D.h"

struct SDL_Rect;
class SoundPlayer;
namespace demos{ struct DemoAntarcticPackage; }

enum{ PinguinIsActive, PinguinIsLeaving, PinguinIsInactive, PinguinStartMindPlayer };

constexpr int CollisionInterval = SQR_SIZE / 16;

class PinguinBehaviorData
{
private:
	PinguinDrawData drawingData;
	unsigned anger;
	unsigned state;
	unsigned tagNumber;
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
	unsigned getTagNumber() const;
	bool doesPinguinLeaveIfAny(unsigned hitTimesThreshold);
	
	void activePinguin(int newTagNumber);
	void movePinguin();
	void animPinguin();
	
	void resetRacketCollisionBooleans(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect);
	void makeBounceWithRacket(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect, demos::DemoAntarcticPackage& antarcticPackage);
	void recordPinguinDirection(demos::DemoAntarcticPackage& antarcticPackage) const;
	void makeBounceVertically(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect);
	void bounceFromRacketTop(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect);
	void bounceFromRacketBottom(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect);
	void makeBounceHorizontally(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect);
	void bounceFromRacketLeft();
	void bounceFromRacketRight();
	
	void makePinguinQuack(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect, bool playerLeftState, bool playerRightState, const SoundPlayer& soundPlayer, 
							demos::DemoAntarcticPackage& antarcticPackage);
	void quackFromItsLeft(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect, bool playerRightState, const SoundPlayer& soundPlayer, demos::DemoAntarcticPackage& antarcticPackage);
	void quackFromItsRight(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect, bool playerLeftState, const SoundPlayer& soundPlayer, demos::DemoAntarcticPackage& antarcticPackage);
	
	void makeBounceWithRimRect(const SDL_Rect& rimRect, const SDL_Rect& pinguinRect, const SoundPlayer& soundPlayer);

	void setPinguinPathWithMouse(const Offset& mousePosition, bool mouseButtonState);
	
	void startMindPlayer(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect);
	
	bool isPinguinNearXRacketCoordinates(const SDL_Rect& racketRect, const SDL_Rect& pinguinRect, int interval) const;
	bool isPinguinOnSameLevelAsRacket() const;
	void makeStayOnRacketLevelIfMindPlayer(const SDL_Rect& racketRect);
	
	bool isPinguinInsideScreen(const SDL_Rect& pinguinRect) const;
	
	void emplaceQuackSoundToStack(demos::DemoAntarcticPackage& antarcticPackage) const;
};

#endif //PINGUIN_BEHAVIOR_DATA_H