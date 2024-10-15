#ifndef DUELS_GLOBAL_OBJECT_H
#define DUELS_GLOBAL_OBJECT_H

#include "duels/inGameObjects/bonusCoins/coinsMain.h"
#include "duels/inGameObjects/balls/ballsMain.h"
#include "duels/inGameObjects/global/playersThings.h"
#include "random/randomGenerator.h"
#include "generic/gameSoundSystem/gameSoundSystem.h"
#include <array>

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
	std::array< bool, duels::PlayerMax > zoneSpecificFlags;
	GameSoundSystem gameSoundSystem;
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
				const std::vector< bool >& canMoveRackToLeft, const std::vector< bool >& canMoveRackToRight,
				const std::vector< bool >& canActivateSpecialBonus);
	void drawEverything(sdl2::RendererWindow& rndWnd);
	void resetScoresTextures(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& arial, duels::LevelOptions& levelOptions);
	
	bool canConsumeZoneSpecificFlag(unsigned playerNum);
	void playZoneGreetingsSound(unsigned soundEnum, int groupTag) const;
	
private:
	void testCollisionsBetweenCoinsAndBalls();
	void testCoinToCoinCollisions();
	void testCoinToBallCollisions();
	void testBallToBallCollisions();
	
	void testCoinToRacketsCollision();
	void compareBallsPositionWithRackets();
	
	void makeBallsBounceAgainstRacket(spriteMove::ObjectMoving& ballMove, const SDL_Rect& racketRect, const Offset& sideLeftDir, const Offset& sideRightDir);
	void resetBallToRacketsCollisionStatus();
	
	void moveRackets(const std::vector< bool >& canMoveRackToLeft, const std::vector< bool >& canMoveRackToRight);
	
	void handleBonuses(duels::LevelOptions& levelOptions, const std::vector< bool >& canActivateSpecialBonus);
	void actAccordingToBonus(unsigned playerNum, duels::LevelOptions& levelOptions, bool canActivateSpecialBonus);
	
	void checkPointsToPlayInZoneAchievement(duels::LevelOptions& levelOptions, bool& quitZone);
};

}

#endif //DUELS_GLOBAL_OBJECT_H