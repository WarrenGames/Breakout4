#ifndef PUMPKIN_FACTORY_H
#define PUMPKIN_FACTORY_H

#include "contexts/gameCommon/halloween/pumpkins/pumpkinCombo.h"
#include "contexts/duels/inGameObjects/bonus/bonusPicker.h"
#include "contexts/duels/zones/halloween/subObjects/halloweenConfig.h"
#include "random/randomGenerator.h"
#include "contexts/duels/zones/halloween/subObjects/pumpkins/playersSpecialPumpkins.h"
#include "time/accurateTime.h"
#include "contexts/duels/duelsConstexpr.h"
#include <array>
#include <vector>

struct Essentials;
namespace sdl2{ class RendererWindow; }
class PlayerRacket;
struct PlayersThings;
class BatObject;
namespace duels{ struct LevelOptions; class ScoreDraw; }

class PumpkinFactory
{
private:
	std::array< PumpkinCombo, 4 > pumpkins;//the two firsts pumpkinCombo are for the bat, the two lastings for the pots
	std::array< BonusPicker, duels::PLAYER_MAX > pumpkinColorPicker;
	AccurateTimeDelay moveDelay;
	IntRandomGenerator randomDirections;
	bool arePotPumpkinsRedirected;

public:
	explicit PumpkinFactory(const HalloweenConfig& halloweenCfg);
	~PumpkinFactory() = default;
	PumpkinFactory( const PumpkinFactory& ) = delete;
	PumpkinFactory& operator= ( const PumpkinFactory& ) = delete;
	PumpkinFactory( PumpkinFactory&& ) = default;
	PumpkinFactory& operator= ( PumpkinFactory&& ) = default;
	
	void update(BatObject& badBat, PlayersThings& playersThings, duels::LevelOptions& levelOptions, const PumpkinDrawer& drawer);
	void drawPumpkins(Essentials& essentials, PumpkinDrawer& drawer);
	bool canStartActivity() const;
	void startPumpkinActivity();
	
private:
	void makePumpkinsFollowBat(const BatObject& bat, const PumpkinDrawer& drawer);
	void drawSinglePumpkin(Essentials& essentials, PumpkinDrawer& drawer, const PumpkinCombo& pumpkin);
	void disableOutOfScreenFromBatPumpkin(const PumpkinDrawer& drawer);
	void makeBatDropPumpkins(const BatObject& badBat);
	void dropSinglePumpkin(PumpkinCombo& pumpkin, const Offset& newDirection, unsigned pumpkinState);
	void setPumpkinIntoPot(PumpkinCombo& pumpkin, const Offset& position);
	void hangPumpkinToBadBat(PumpkinCombo& pumpkin, unsigned newState);
	void movePumpkins();
	void movePotPumpkins(PumpkinCombo& pumpkin);
	void moveBatPumpkins(PumpkinCombo& pumpkin);
	void redirectPotPumpkins();
	void redirectSinglePotPumpkin(PumpkinCombo& pumpkin);
	void browseRacketsAndPumpkinsForCollision(PlayersThings& playersThings, duels::LevelOptions& levelOptions, BatObject& badBat);
};

#endif //PUMPKIN_FACTORY_H