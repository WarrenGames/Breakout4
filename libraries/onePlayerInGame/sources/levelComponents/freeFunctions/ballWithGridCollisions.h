#ifndef BALL_WITH_GRID_COLLISION_H
#define BALL_WITH_GRID_COLLISION_H

struct LevelComponents;
struct Offset;
struct BallThings;
struct PlayerData;
struct BrickData;

namespace gridCol{

void collideBallWithBricksMatrix(LevelComponents& comp, const Offset& brickCoord, BallThings& ball, PlayerData& playerData);

void collideWithGenericBrick(LevelComponents& comp, BrickData& brickData, PlayerData& playerData);

void collideWithRichBrick(LevelComponents& comp, const Offset& brickCoord, PlayerData& playerData);

void collideWithLeftRichBrick(LevelComponents& comp, const Offset& brickCoord, int brickValue, PlayerData& playerData);

void collideWithRightRichBrick(LevelComponents& comp, const Offset& brickCoord, int brickValue, PlayerData& playerData);

void destroyRichBrick(LevelComponents& comp, const Offset& brickCoord);

void collisionWithBonusCoinBrick(LevelComponents& comp, BrickData& brickData, PlayerData& playerData);

void collideWithGiftBrick(LevelComponents& comp, BrickData& brickData, PlayerData& playerData, const Offset& brickCoord);

void collisionWithTenPointsBrick(LevelComponents& comp, BrickData& brickData, BallThings& ball, PlayerData& playerData);

int getPointsFrom10PtsBrickProperty(int brickProperty);

void tenPointsBrickDestruction(PlayerData& playerData, int addToScore, int bigBonusIfAny);

void stackBrickMatrixModification(LevelComponents& comp, const Offset& brickCoord, const PlayerData& playerData);

}

#endif //BALL_WITH_GRID_COLLISION_H