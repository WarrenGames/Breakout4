#ifndef ONE_PLAYER_PINGUINS_H
#define ONE_PLAYER_PINGUINS_H

#include "levelComponents/monsters/pinguinBehaviorData.h"
#include "time/accurateTime.h"
#include "SDL_rect.h"
#include <vector>

namespace onePlGame{ class PinguinsDataLoader; }
template<typename T>class MatrixTemp2D;
class SoundPlayer;
struct BrickData;
struct BallThings;
namespace demos{ struct DemoAntarcticPackage; }

class OnePlayerPinguin
{
private:
	std::vector< PinguinBehaviorData > pinguins;
	AccurateTimeDelay moveTime;
	AccurateTimeDelay mindPlayerTime;
	unsigned tagNumber;
	SDL_Rect collisionRect;
	unsigned neededHitsToRevokePinguin;
	bool hasMovedSince;
	bool isLoadingPerfect;

public:
	explicit OnePlayerPinguin(onePlGame::PinguinsDataLoader& dataLoader);
	~OnePlayerPinguin() = default;
	OnePlayerPinguin( const OnePlayerPinguin& ) = delete;
	OnePlayerPinguin& operator= ( const OnePlayerPinguin& ) = delete;
	OnePlayerPinguin( OnePlayerPinguin&& ) = default;
	OnePlayerPinguin& operator= ( OnePlayerPinguin&& ) = default;
	
	std::vector< PinguinBehaviorData >::const_iterator begin() const;
	std::vector< PinguinBehaviorData >::const_iterator end() const;

	std::size_t size() const;
	void activeOnePinguin(demos::DemoAntarcticPackage& antarcticPackage);
	
	bool atLeastOnePinguinOnRacketLeft(const SDL_Rect& racketRect) const;
	bool atLeastOnePinguinOnRacketRight(const SDL_Rect& racketRect) const;
	void withBallBouncing(BallThings& ballThings);
	void resetBallBouncing(BallThings& ballThings);
	void makePinguinsBounceWithRims(const SDL_Rect& rimRect, const SoundPlayer& soundPlayer);
	void setPinguinPathWithMouse(const Offset& mousePosition, bool mouseButtonState);
	void playRecordedQuackSounds(demos::DemoAntarcticPackage& antarcticPackage, const SoundPlayer& soundPlayer);
	void updateMove(demos::DemoAntarcticPackage& antarcticPackage);
	void updateAnim();
	void updateCollisions(const MatrixTemp2D<BrickData>& grid, const SDL_Rect& racketRect, demos::DemoAntarcticPackage& antarcticPackage);
	void makePinguinsQuack(const SDL_Rect& racketRect, bool playerLeftState, bool playerRightState, const SoundPlayer& soundPlayer, demos::DemoAntarcticPackage& antarcticPackage);
	void tryToMindPlayer(const SDL_Rect& racketRect);
	void revokePinguinIfHitEnough(demos::DemoAntarcticPackage& antarcticPackage);
	void forcePinguinsToStayBesideRacket(const SDL_Rect& racketRect);
	void recordPinguinCreationOrDestruction(demos::DemoAntarcticPackage& antarcticPackage, bool action, const PinguinBehaviorData& ping) const;
	void rotatePinguinIfAny(demos::DemoAntarcticPackage& antarcticPackage);
	void createOrDestroyPinguinsWithStack(demos::DemoAntarcticPackage& antarcticPackage);
	void collisionWithPlayerRim(const SDL_Rect& rimRect);
	
private:
	void browseForCollisions(const SDL_Rect& collisionRect, const MatrixTemp2D<BrickData>& grid);
	void resetPinguinDirectionIfCollision(PinguinBehaviorData& pinguin, bool wasThereCol);
	void collisionWithRacket(const SDL_Rect& racketRect, demos::DemoAntarcticPackage& antarcticPackage);
	void recordPinguinMove(demos::DemoAntarcticPackage& antarcticPackage, const PinguinBehaviorData& ping);
	void placePinguinIfAny(demos::DemoAntarcticPackage& antarcticPackage);
};

#endif //ONE_PLAYER_PINGUINS_H