#ifndef ONE_PLAYER_HELL_SKULL_GLOBAL_H
#define ONE_PLAYER_HELL_SKULL_GLOBAL_H

#include "levelComponents/hellEpisodeThings/hellSkulls/configuration/hellSkullDataLoader.h"
#include "levelComponents/hellEpisodeThings/hellSkulls/inGame/hellSkullPack.h"
#include "hellSkulls/skullDrawer.h"

struct Essentials;
struct PlayerData;
class FireBallDrawer;
class AllExplosions;
struct OnePlayerRacket;
class SoundPlayer;

namespace onePlGame{

struct FireBallsPaths;

class HellSkullGlobal
{
private:
	HellSkullDataLoader dataLoader;
	HellSkullPack skullPack;
	HellSkullDrawer drawer;
	unsigned triggersNumber;

public:
	explicit HellSkullGlobal(Essentials& essentials, const PlayerData& playerData, const FireBallsPaths& fireBallsPaths);
	~HellSkullGlobal() = default;
	HellSkullGlobal( const HellSkullGlobal& ) = delete;
	HellSkullGlobal& operator= ( const HellSkullGlobal& ) = delete;
	HellSkullGlobal( HellSkullGlobal&& ) = default;
	HellSkullGlobal& operator= ( HellSkullGlobal&& ) = default;
	
	bool wasLoadingPerfect() const;
	void addPendingSkull();
	void update(spriteMove::ObjectMoving& ballMove, OnePlayerRacket& racket, const AllExplosions& explosions, const TextureCombo& ballTexture, const SoundPlayer& soundPlayer);
	void drawHellSkulls(Essentials& essentials, AllExplosions& explosions);
	void drawFireBalls(Essentials& essentials, FireBallDrawer& fireBallDrawer);
	void activateSkullIfAny();
};

}

#endif //ONE_PLAYER_HELL_SKULL_GLOBAL_H