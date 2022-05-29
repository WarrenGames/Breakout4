#ifndef DUELS_GLOBAL_OBJECT_H
#define DUELS_GLOBAL_OBJECT_H

#include "contexts/duels/inGameObjects/bonusCoins/coinsMain.h"
#include "contexts/duels/inGameObjects/balls/ballsMain.h"
#include "contexts/duels/inGameObjects/global/playersThings.h"
#include "random/randomGenerator.h"
#include "generic/sounds/soundHandler.h"

struct Essentials;
struct AppLogFiles;
template< typename T > class MatrixTemp2D;
struct BrickData;

namespace duels{

class GlobalObject
{
	friend class HalloweenFactory;
	friend struct MetalStrings;
	
private:
	bool isLoadingPerfect;
	duels::CoinsThings coins;
	BallsThings balls;
	PlayersThings players;
	IntRandomGenerator randomGen;
	std::array<bool, duels::PLAYER_MAX> zoneSpecificFlags;
	const SoundHandler commonSounds;
	unsigned givenPoints;

public:
	explicit GlobalObject(Essentials& essentials, const sdl2::Font& arialFont, const std::vector< Offset >& spawnsCoord, const duels::LevelOptions& levelOptions);
	~GlobalObject() = default;
	GlobalObject( const GlobalObject& ) = delete;
	GlobalObject& operator= ( const GlobalObject& ) = delete;
	GlobalObject( GlobalObject&& ) = default;
	GlobalObject& operator= ( GlobalObject&& ) = default;
	
	bool wasLoadingPerfect() const;
	
	void update(const MatrixTemp2D<BrickData>& levelGrid, duels::LevelOptions& levelOptions, bool& quitZone, 
				const std::array< bool, duels::PLAYER_MAX>& canMoveRackToLeft, const std::array<bool, duels::PLAYER_MAX>& canMoveRackToRight,
				const std::array<bool, duels::PLAYER_MAX>& canActivateSpecialBonus);
	void drawEverything(sdl2::RendererWindow& rndWnd);
	void resetScoresTextures(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& arial, duels::LevelOptions& levelOptions);
	
	bool canConsumeZoneSpecificFlag(unsigned playerNum);
	
private:
	void testCollisionsBetweenCoinsAndBalls();
	void testCoinToCoinCollisions();
	void testCoinToBallCollisions();
	void testBallToBallCollisions();
	
	void testCoinToRacketsCollision();
	void compareBallsPositionWithRacketsRects();
	void makeBallsBounceAgainstRacket(ObjectMoving& ballMove, const SDL_Rect& racketRect);
	void resetBallToRacketsCollisionStatus();
	
	void moveRackets(const std::array< bool, duels::PLAYER_MAX>& canMoveRackToLeft, const std::array< bool, duels::PLAYER_MAX>& canMoveRackToRight);
	
	void handleBonuses(duels::LevelOptions& levelOptions, const std::array<bool, duels::PLAYER_MAX>& canActivateSpecialBonus);
	void actAccordingToBonus(unsigned playerNum, duels::LevelOptions& levelOptions, bool canActivateSpecialBonus);
	
	void checkPointsToPlayInZoneAchievement(duels::LevelOptions& levelOptions, bool& quitZone);
};

}

#endif //DUELS_GLOBAL_OBJECT_H