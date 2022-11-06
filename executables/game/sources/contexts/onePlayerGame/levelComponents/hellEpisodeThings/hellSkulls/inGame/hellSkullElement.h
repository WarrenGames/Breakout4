#ifndef ONE_PLAYER_GAME_HELL_SKULL_ELEMENT_H
#define ONE_PLAYER_GAME_HELL_SKULL_ELEMENT_H

#include "contexts/onePlayerGame/levelComponents/hellEpisodeThings/hellSkulls/inGame/hellSkullActivity.h"
#include "contexts/gameCommon/hellSkulls/skullData.h"
#include "contexts/gameCommon/fireBall/fireBallDrawData.h"
#include "contexts/gameCommon/time/intervalAndRandomTimeHappening.h"
#include "spriteMove/spriteMoveData.h"
#include "spriteMove/movements.h"
#include "spriteMove/starType.h"

struct SkullFileData;
class HellSkullDrawer;
class AllExplosions;
struct TextureCombo;
class SoundHandler;
struct OnePlayerRacket;

namespace onePlGame{

struct FireBallsPaths;
	
struct HellSkullElement
{
	SkullData skullData;
	spriteMove::VectorsGroup toLeftFireBall;
	spriteMove::VectorsGroup toRightFireBall;
	FireBallDrawData fireBallDrawData;
	spriteMove::MovementThings fireBallMove;
	spriteMove::StarTypeThings fireBallStarThings;
	IntervalAndRandom randomInterval;
	SkullActivity activity;
	AccurateTimeDelay rushDelay;

	explicit HellSkullElement(const onePlGame::FireBallsPaths& fireBallPaths, const SkullFileData& fileData);
	~HellSkullElement() = default;
	HellSkullElement( const HellSkullElement& ) = delete;
	HellSkullElement& operator= ( const HellSkullElement& ) = delete;
	HellSkullElement( HellSkullElement&& ) = default;
	HellSkullElement& operator= ( HellSkullElement&& ) = default;

	void resetPositionAndInitialDirection(const SkullFileData& fileData);
	void update(const HellSkullDrawer& skullDrawer, const spriteMove::ObjectMoving& ballMove, const AllExplosions& explosions, const SoundHandler& sounds);
	void updateExplosion(const AllExplosions& explosions);
	void screenBounce(const HellSkullDrawer& skullDrawer);
	void fireBallSkullScreenBounce(const HellSkullDrawer& skullDrawer);
	void toBallRushingSkullScreenBounce(const HellSkullDrawer& skullDrawer);
	void bounceAgainScreenLeft(const HellSkullDrawer& skullDrawer);
	void bounceAgainScreenRight(const HellSkullDrawer& skullDrawer);
	void bounceAgainInfosBar(const HellSkullDrawer& skullDrawer);
	void bounceAgainScreenBottom(const HellSkullDrawer& skullDrawer);
	void moveSkull();
	void moveFireBall();
	void nextJob(const SoundHandler& sounds);
	void throwFireBall(const SoundHandler& sounds);
	void rushToPlayerBall();
	void chooseThrowSide();
	bool isSkullInsideScreen() const;
	void handleRush(const spriteMove::ObjectMoving& ballMove);
	void collisionWithBall(const HellSkullDrawer& skullDrawer, spriteMove::ObjectMoving& ballMove, const TextureCombo& ballTexture);
	void fireBallCollisionWithRacket(OnePlayerRacket& racket, const SoundHandler& sounds);
	void accelerateBall(spriteMove::ObjectMoving& ballMove);
	void setSkullToExplosion();
	void watchFireBallMoveEnd();
};

}

#endif //ONE_PLAYER_GAME_HELL_SKULL_ELEMENT_H