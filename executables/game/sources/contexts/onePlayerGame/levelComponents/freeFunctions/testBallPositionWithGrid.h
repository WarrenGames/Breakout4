#ifndef TEST_BALL_POSITION_WITH_GRID_H
#define TEST_BALL_POSITION_WITH_GRID_H

struct LevelComponents;
struct BallThings;
struct PlayerData;
struct Offset;

namespace ballCol{
	bool isThereAnElementInGrid(LevelComponents& comp, const Offset& coords);
	
	void testLeftCollision(LevelComponents& comp, BallThings& ball, PlayerData& playerData);
	void testRightCollision(LevelComponents& comp, BallThings& ball, PlayerData& playerData);
	void testTopCollision(LevelComponents& comp, BallThings& ball, PlayerData& playerData);
	void testBottomCollision(LevelComponents& comp, BallThings& ball, PlayerData& playerData);
	
	void testTopLeftCollision(LevelComponents& comp, BallThings& ball, PlayerData& playerData);
	void testTopRightCollision(LevelComponents& comp, BallThings& ball, PlayerData& playerData);
	void testBottomLeftCollision(LevelComponents& comp, BallThings& ball, PlayerData& playerData);
	void testBottomRightCollision(LevelComponents& comp, BallThings& ball, PlayerData& playerData);
	
	void testScreenLeftCollision(LevelComponents& comp, BallThings& ball);
	void testScreenRightCollision(LevelComponents& comp, BallThings& ball);
	void testScreenTopCollision(LevelComponents& comp, BallThings& ball);
	void testScreenBottomtCollision(LevelComponents& comp, BallThings& ball);
	
	Offset getBrickCoordinates(const Offset& ballToGridPosition, const Offset& ballRelativeBrickPos);
	
	void appendCornerBallModifications(LevelComponents& comp, PlayerData& playerData, const Offset& newBallDir, const Offset& brickCoord);
}

#endif //TEST_BALL_POSITION_WITH_GRID_H