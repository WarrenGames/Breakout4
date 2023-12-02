#ifndef DUELS_COINS_MAIN_H
#define DUELS_COINS_MAIN_H

#include "advancedDrawing/texturesLoading/fileTexturesList.h"
#include "advancedDrawing/texturesDrawing/constAnimationDrawing.h"
#include "duels/inGameObjects/bonusCoins/bonusCoin.h"
#include "duels/inGameObjects/gameElements/collisionBools.h"
#include "duels/inGameObjects/gameElements/duelsLevelOptions.h"
#include "duels/inGameObjects/gameElements/spawnsData.h"
#include "random/randomGenerator.h"
#include "time/accurateTime.h"

template<typename T> class MatrixTemp2D;
struct BrickData;
class SoundPlayer;

namespace duels{
	class BallsThings;
	struct ComboBallData;

class CoinsThings
{
	friend class GlobalObject;
	 
private:
	std::vector< duels::ComboCoinData > coinsData;
	TexturesFilesList coinTextures;
	ConstAnimDraw coinSprites;
	AccurateTimeDelay coinsAnimation;
	AccurateTimeDelay coinsMove;
	CollisionBools collisionBools;
	duels::SpawnsData spawns;

public:
	explicit CoinsThings(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::vector< Offset >& spawnsCoord, const duels::LevelOptions& levelOptions);
	~CoinsThings() = default;
	CoinsThings( const CoinsThings& ) = delete;
	CoinsThings& operator= ( const CoinsThings& ) = delete;
	CoinsThings( CoinsThings&& ) = default;
	CoinsThings& operator= ( CoinsThings&& ) = default;
	
	bool wasLoadingPerfect() const;
	
	void update(const MatrixTemp2D<BrickData>& levelGrid, BallsThings& balls, IntRandomGenerator& randomGen, const SoundPlayer& soundPlayer);
	void animateCoins();
	void moveCoins();
	void testCoinAndScreenRimsCollision();
	void disableCoinIfOutsideOfScreen();
	void checkCollisionWithGrid(const MatrixTemp2D<BrickData>& levelGrid);
	
	unsigned getEffectiveCoinCount() const;
	std::size_t getFirstFreeCoinIndex() const;
	bool isAnyCoinOverSpawnPoint(const Offset& spawnPoint) const;
	void createNewCoinIfPossible(BallsThings& balls, IntRandomGenerator& randomGen, const SoundPlayer& soundPlayer);
	void setCanCreateCoin();
	
	void drawBonusCoins(sdl2::RendererWindow& rndWnd);
	
	void checkCollisionWithRect(const SDL_Rect& externObjectRect, std::vector< bool >& canCollide);
};

}

#endif //DUELS_COINS_MAIN_H