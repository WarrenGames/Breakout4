#ifndef DUELS_HALLOWEEN_SPECIAL_PLAYER_PUMPKINS_H
#define DUELS_HALLOWEEN_SPECIAL_PLAYER_PUMPKINS_H

#include "time/accurateTime.h"
#include "matrices/matrix2D.h"
#include "halloween/pumpkins/pumpkinCombo.h"
#include "consts/duelsConstexpr.h"
#include <iosfwd>

struct Essentials;
struct Offset;
class PumpkinDrawer;
struct PlayersThings;
class BatObject;

namespace duels{ struct LevelOptions; }
	
class SpecialPumpkins
{
private:
	AccurateTimeDelay moveDelay;
	std::vector< AccurateTimeDelay > lastSpecialBonusDelay;
	MatrixTemp2D< PumpkinMoveInfo > pumpkinsData;
	MatrixTemp2D< PumpkinCombo > specialPumpkins;
	bool havePumpkinsMovedSince;
	
public:
	explicit SpecialPumpkins(Essentials& essentials);
	~SpecialPumpkins() = default;
	SpecialPumpkins( const SpecialPumpkins& ) = delete;
	SpecialPumpkins& operator= ( const SpecialPumpkins& ) = delete;
	SpecialPumpkins( SpecialPumpkins&& ) = default;
	SpecialPumpkins& operator= ( SpecialPumpkins&& ) = default;
	
	void activateSpecialBonus(const duels::LevelOptions& levelOptions, unsigned playerNum);
	void update(PlayersThings& playersThings, duels::LevelOptions& levelOptions, BatObject& badBat);
	void drawPumpkins(Essentials& essentials, PumpkinDrawer& drawer);
	bool canActivateSpecialBonus(unsigned playerNum);
	
private:
	void populateSpecialBonusPumpkinsVector(Essentials& essentials);
	void readPumpkinsPositionsData(Essentials& essentials, std::ifstream& pumpkPosFile, Offset& pumpkinPosition, Offset& pumpkinDestination);
	
	void resetSpecialPumpkinsPositions(unsigned playerNum);
	void traceSpecialPumpkins(unsigned playerNum);
	void moveSpecialPumpkins();
	void movePumpkins();
	void disableStaledPumpkins();
	void browsePumpkinsForCollision(PlayersThings& playersThings, duels::LevelOptions& levelOptions, BatObject& badBat);
};

#endif //DUELS_HALLOWEEN_SPECIAL_PLAYER_PUMPKINS_H