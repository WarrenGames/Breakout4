#ifndef DUELS_HALLOWEEN_PLAYER_WITH_PUMPKIN_COLLISIONS_H
#define DUELS_HALLOWEEN_PLAYER_WITH_PUMPKIN_COLLISIONS_H

struct PlayersThings;
namespace duels{ class ScoreDraw; struct LevelOptions; }
struct PumpkinCombo;
class BatObject;

namespace halloween{

void collisionRacketAndPumpkin(PlayersThings& playersThings, duels::ScoreDraw& scoreDraw, unsigned playerType, PumpkinCombo& pumpkin, duels::LevelOptions& levelOptions
								, BatObject& bat);

void collideWithRedPumpkin(duels::ScoreDraw& scoreDraw, unsigned playerType, PumpkinCombo& pumpkin, duels::LevelOptions& levelOptions, BatObject& bat);

void collideWithGrayPumpkin(PlayersThings& playersThings, unsigned playerType, PumpkinCombo& pumpkin, BatObject& bat);

void collideWithBluePumpkin(duels::ScoreDraw& scoreDraw, unsigned playerType, PumpkinCombo& pumpkin, duels::LevelOptions& levelOptions, BatObject& bat);

void collideWithYellowPumpkin(PlayersThings& playersThings, unsigned playerType, PumpkinCombo& pumpkin, BatObject& bat);

}

#endif //DUELS_HALLOWEEN_PLAYER_WITH_PUMPKIN_COLLISIONS_H