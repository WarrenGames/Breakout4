#ifndef BALL_WITH_PINGUIN_BRICK_COLLISION_H
#define BALL_WITH_PINGUIN_BRICK_COLLISION_H

struct LevelComponents;
struct Offset;
struct PlayerData;
class MonstersPack;

namespace iceCol{

void collideWithIceBricks(LevelComponents& comp, const Offset& brickCoord, bool isBallPowerful, PlayerData& playerData);
	
void collideWithPinguinBrick(LevelComponents& comp, const Offset& brickCoord, bool isBallPowerful, PlayerData& playerData);

void collideWithIceCube(const LevelComponents& comp);

}

#endif //BALL_WITH_PINGUIN_BRICK_COLLISION_H