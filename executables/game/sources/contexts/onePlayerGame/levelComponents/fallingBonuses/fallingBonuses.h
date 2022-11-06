#ifndef FALLING_BONUSES_DATA_H
#define FALLING_BONUSES_DATA_H

#include "spriteMove/objectMove.h"
#include "texturing/texturesCombo.h"
#include "time/accurateTime.h"
#include "consts/onePlayerGridConsts.h"
#include <vector>

struct Essentials;
struct PlayerData;
struct OnePlayerRacket;
struct BallThings;
class OnePlayerRims;
class InfoBar;
class SoundHandler;
struct BrickData;
template< typename T > class MatrixTemp2D;

constexpr double FallBonusesSpeed = 2;

struct FallingBonusData
{
	std::size_t bonusType;
	spriteMove::ObjectMoving objectMove;
	
	explicit FallingBonusData(std::size_t bonusIndex, const AccurCoords& startCoords, double newSpeed, const Offset& newDirVectors);
};

class FallingBonuses
{
private:
	bool isLoadingPerfect;
	bool haveBonusesMoved;
	std::vector< TextureCombo > bonusesTextures;
	std::vector< std::unique_ptr<FallingBonusData> > bonusesData;
	AccurateTimeDelay moveBonuses;

public:
	explicit FallingBonuses(Essentials& essentials);
	~FallingBonuses() = default;
	FallingBonuses( const FallingBonuses& ) = delete;
	FallingBonuses& operator= ( const FallingBonuses& ) = delete;
	FallingBonuses( FallingBonuses&& ) = default;
	FallingBonuses& operator= ( FallingBonuses&& ) = default;

private:
	void checkEverythingIsLoaded(Essentials& essentials);
	void loadTexture(Essentials& essentials, const std::string& texturePath);

public:
	void reserveGiftBricksData(const MatrixTemp2D< BrickData >& levelMatrix);
	operator bool () const;
	void drawBonuses(Essentials& essentials);
	void update();
	void addNewFallingBonus(std::size_t bonusIndex, const AccurCoords& startCoords, double newSpeed, const Offset& newDirVectors);
	
	void detectCollisionWithRacket(PlayerData& playerData, OnePlayerRacket& racket, OnePlayerRims& rims, InfoBar& infoBar, const SoundHandler& sounds);

private:
	void applyBonusModificationToPlayer(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData, OnePlayerRacket& racket, OnePlayerRims& rims, const SoundHandler& sounds);
	void improveBall(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData, const SoundHandler& sounds);
	void speedUpRacket(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData, const SoundHandler& sounds);
	void speedDownRacket(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData, OnePlayerRacket& racket, const SoundHandler& sounds);
	void enlargeRims(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData, const SoundHandler& sounds);
	void shrinkRims(std::unique_ptr< FallingBonusData >& bonus, OnePlayerRims& rims, const SoundHandler& sounds);
	void enlargeRacket(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData, const SoundHandler& sounds);
	void shrinkRacket(std::unique_ptr< FallingBonusData >& bonus, OnePlayerRacket& racket, const SoundHandler& sounds);
	void addOneLife(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData, const SoundHandler& sounds);
	void glueRacket(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData);
};

#endif //FALLING_BONUSES_DATA_H