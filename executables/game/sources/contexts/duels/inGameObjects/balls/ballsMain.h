#ifndef DUELS_BALLS_MAIN_H
#define DUELS_BALLS_MAIN_H

#include "contexts/duels/inGameObjects/balls/duelBall.h"
#include "texturing/texturesCombo.h"
#include "time/accurateTime.h"
#include "contexts/duels/inGameObjects/gameElements/duelsTypes.h"
#include "contexts/duels/inGameObjects/gameElements/collisionBools.h"
#include "contexts/duels/inGameObjects/gameElements/spawnsData.h"
#include "contexts/duels/duelsConstexpr.h"
#include <vector>

struct AppLogFiles;
class IntRandomGenerator;
class SoundHandler;
template<typename T> class MatrixTemp2D;
struct BrickData;

namespace duels{

	class CoinsThings;
	struct ComboCoinData;
	class ScoreDraw;

class BallsThings
{
	friend class GlobalObject;
	
private:	
	std::vector< duels::ComboBallData > ballsData;
	TextureCombo ballTexture;
	AccurateTimeDelay ballsMove;
	AccurateTimeDelay ballsSpeedIncr;
	CollisionBools collisionBools;
	bool canCheckForScores;
	duels::SpawnsData spawns;

public:
	explicit BallsThings(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::vector< Offset >& spawnsCoord, const duels::LevelOptions& levelOptions);
	~BallsThings() = default;
	BallsThings( const BallsThings& ) = delete;
	BallsThings& operator= ( const BallsThings& ) = delete;
	BallsThings( BallsThings&& ) = default;
	BallsThings& operator= ( BallsThings&& ) = default;
	
	bool wasLoadingPerfect() const;
	
	void update(const MatrixTemp2D<BrickData>& levelGrid, duels::LevelOptions& levelOptions, CoinsThings& coins, IntRandomGenerator& randomGen, const SoundHandler& commonSounds,
				std::vector< duels::ScoreDraw >& scoreDrawing, unsigned& givenPoints);
	void moveBalls();
	void accelarateBallsSpeed();
	void testBallAndScreenRimsCollision();
	void checkBallsPositionsForScore(std::vector< int >& playersScores, std::vector< duels::ScoreDraw >& scoreDrawing, unsigned& givenPoints);
	void giveBluePlayerAPoint(int& bluePlayerScore, duels::ScoreDraw& blueScore, unsigned& givenPoints);//If a ball leaves the screen to the north
	void giveRedPlayerAPoint(int& redPlayerScore, duels::ScoreDraw& redScore, unsigned& givenPoints);//If a ball leaves the screen to the south
	void disableCoinIfOutsideScreen();
	
	void checkCollisionWithGrid(const MatrixTemp2D<BrickData>& levelGrid, const SoundHandler& commonSounds);
	
	unsigned getEffectiveBallsCount() const;
	std::size_t getFirstFreeBallIndex() const;
	bool isAnyBallOverSpawnPoint(const Offset& spawnPoint) const;
	void createNewBallIfPossible(CoinsThings& coins, IntRandomGenerator& randomGen);
	void setCanCreateBall();
	
	void drawBalls(sdl2::RendererWindow& rndWnd);
	
	void checkCollisionWithRect(const SDL_Rect& externObjectRect, std::vector< bool >& canCollide);
	
	void playSoundIfCollision(const SoundHandler& sounds, bool wasThereCol);
};

}

#endif //DUELS_BALLS_MAIN_H