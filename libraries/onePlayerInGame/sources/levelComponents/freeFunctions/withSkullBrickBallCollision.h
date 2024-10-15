#ifndef WITH_SKULL_BRICK_BALL_COLLISION_H
#define WITH_SKULL_BRICK_BALL_COLLISION_H

struct LevelComponents;
struct Offset;
struct PlayerData;

namespace hellCol{

	void collideWithHellBricks(LevelComponents& comp, const Offset& brickCoord, bool isBallPowerful, PlayerData& playerData);

	void collideWithSkullHellBrick(LevelComponents& comp, const Offset& brickCoord, bool isBallPowerful, PlayerData& playerData, unsigned soundEnum, unsigned groupTag);

	void collideWithLavaStoneBrick(LevelComponents& comp, unsigned soundEnum, unsigned groupTag);
}

#endif //WITH_SKULL_BRICK_BALL_COLLISION_H