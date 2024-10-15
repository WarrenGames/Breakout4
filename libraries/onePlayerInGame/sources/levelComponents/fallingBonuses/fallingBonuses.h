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
class OnePlayerRimsSystem;
class InfoBar;
class SoundPlayer;
struct BrickData;
template< typename T > class MatrixTemp2D;

constexpr double FallBonusesSpeed = 2;

struct FallingBonusData
{
	std::size_t bonusType;
	spriteMove::ObjectMoving objectMove;
	
	explicit FallingBonusData(std::size_t bonusIndex, const AccurCoords& startCoords, double newSpeed, const Offset& newDirVectors);
	~FallingBonusData() = default;
	FallingBonusData( const FallingBonusData& ) = delete;
	FallingBonusData& operator= ( const FallingBonusData& ) = delete;
	FallingBonusData( FallingBonusData&& ) = default;
	FallingBonusData& operator= ( FallingBonusData&& ) = default;
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
	
	void detectCollisionWithRacket(PlayerData& playerData, OnePlayerRacket& racket, OnePlayerRimsSystem& rims, InfoBar& infoBar, const SoundPlayer& soundPlayer);

private:
	void applyBonusModificationToPlayer(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData, OnePlayerRacket& racket, OnePlayerRimsSystem& rims, const SoundPlayer& soundPlayer);
	void improveBall(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData, const SoundPlayer& soundPlayer);
	void speedUpRacket(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData, const SoundPlayer& soundPlayer);
	void speedDownRacket(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData, OnePlayerRacket& racket, const SoundPlayer& soundPlayer);
	void enlargeRims(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData, const SoundPlayer& soundPlayer);
	void shrinkRims(std::unique_ptr< FallingBonusData >& bonus, OnePlayerRimsSystem& rims, const SoundPlayer& soundPlayer);
	void enlargeRacket(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData, const SoundPlayer& soundPlayer);
	void shrinkRacket(std::unique_ptr< FallingBonusData >& bonus, OnePlayerRacket& racket, const SoundPlayer& soundPlayer);
	void addOneLife(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData, const SoundPlayer& soundPlayer);
	void glueRacket(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData);
};

#endif //FALLING_BONUSES_DATA_H