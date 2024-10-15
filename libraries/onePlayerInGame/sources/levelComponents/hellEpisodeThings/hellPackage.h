#ifndef ONE_PLAYER_GAME_HELL_PACKAGE_H
#define ONE_PLAYER_GAME_HELL_PACKAGE_H

#include "levelComponents/hellEpisodeThings/fireBalls/paths/fireBallPaths.h"
#include "levelComponents/hellEpisodeThings/fireBalls/fireBallGlobal.h"
#include "levelComponents/hellEpisodeThings/hellSkulls/hellSkullGlobal.h"

struct Essentials;
struct OnePlayerRacket;
class AllExplosions;
class SoundPlayer;

namespace onePlGame{

class HellPackage
{
private:
	FireBallsPaths fireBallsPaths;
	FireBallGlobal fireBallGlobal;
	HellSkullGlobal hellSkullGlobal;

public:
	explicit HellPackage(Essentials& essentials, const PlayerData& playerData);
	~HellPackage() = default;
	HellPackage( const HellPackage& ) = delete;
	HellPackage& operator= ( const HellPackage& ) = delete;
	HellPackage( HellPackage&& ) = default;
	HellPackage& operator= ( HellPackage&& ) = default;
	
	operator bool() const;
	
	void update(spriteMove::ObjectMoving& ballMove, OnePlayerRacket& racket, const AllExplosions& explosions, const TextureCombo& ballTexture, const SoundPlayer& soundPlayer);
	void drawEverything(Essentials& essentials, AllExplosions& explosions);
	void addPendingSkull();
};

}

#endif //ONE_PLAYER_GAME_HELL_PACKAGE_H