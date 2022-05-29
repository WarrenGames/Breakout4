#ifndef ONE_PLAYER_GAME_HELL_SKULL_ELEMENT_H
#define ONE_PLAYER_GAME_HELL_SKULL_ELEMENT_H

#include "contexts/gameCommon/hellSkulls/skullData.h"
#include "contexts/gameCommon/fireBall/fireBallPathData.h"
#include "contexts/gameCommon/fireBall/fireBallDrawData.h"
#include "contexts/gameCommon/movements/objectMove.h"
#include "contexts/onePlayerGame/levelComponents/hellEpisodeThings/hellSkulls/inGame/hellSkullActivity.h"
#include "contexts/gameCommon/time/intervalAndRandomTimeHappening.h"

class PathData;
struct SkullFileData;
class HellSkullDrawer;
class AllExplosions;
struct TextureCombo;
class SoundHandler;
struct OnePlayerRacket;

namespace onePlGame{

struct HellSkullElement
{
	SkullData skullData;
	FireBallPathData toLeftFireBall;
	FireBallPathData toRightFireBall;
	FireBallDrawData fireBallDrawData;
	ObjectMoving fireBallMove;
	IntervalAndRandom randomInterval;
	SkullActivity activity;
	AccurateTimeDelay rushDelay;

	explicit HellSkullElement(const PathData& toLeftPath, const PathData& toRightPath, const SkullFileData& fileData);
	~HellSkullElement() = default;
	HellSkullElement( const HellSkullElement& ) = delete;
	HellSkullElement& operator= ( const HellSkullElement& ) = delete;
	HellSkullElement( HellSkullElement&& ) = default;
	HellSkullElement& operator= ( HellSkullElement&& ) = default;

	void resetPositionAndInitialDirection(const SkullFileData& fileData);
	void update(const HellSkullDrawer& skullDrawer, const ObjectMoving& ballMove, const AllExplosions& explosions, const SoundHandler& sounds);
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
	void handleRush(const ObjectMoving& ballMove);
	void collisionWithBall(const HellSkullDrawer& skullDrawer, ObjectMoving& ballMove, const TextureCombo& ballTexture);
	void fireBallCollisionWithRacket(OnePlayerRacket& racket, const SoundHandler& sounds);
	void accelerateBall(ObjectMoving& ballMove);
	void setSkullToExplosion();
};

}

#endif //ONE_PLAYER_GAME_HELL_SKULL_ELEMENT_H