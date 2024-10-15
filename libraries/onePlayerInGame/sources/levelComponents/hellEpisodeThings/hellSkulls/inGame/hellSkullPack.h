#ifndef ONE_PLAYER_GAME_HELL_SKULL_PACK_H
#define ONE_PLAYER_GAME_HELL_SKULL_PACK_H

#include "levelComponents/hellEpisodeThings/hellSkulls/inGame/hellSkullElement.h"
#include <vector>
#include <memory>

struct AppLogFiles;
struct PlayerData;
struct TextureCombo;
struct OnePlayerRacket;
class SoundPlayer;

namespace onePlGame{

struct FireBallsPaths;
class HellSkullDataLoader;

class HellSkullPack
{
private:
	std::vector< std::unique_ptr< HellSkullElement > > hellSkulls;
	AccurateTimeDelay moveDelay;
	bool isLoadingPerfect;
	
public:
	explicit HellSkullPack(AppLogFiles& logs, const PlayerData& playerData, const FireBallsPaths& fireBallsPaths, const HellSkullDataLoader& dataLoader);
	~HellSkullPack() = default;
	HellSkullPack( const HellSkullPack& ) = delete;
	HellSkullPack& operator= ( const HellSkullPack& ) = delete;
	HellSkullPack( HellSkullPack&& ) = default;
	HellSkullPack& operator= ( HellSkullPack&& ) = default;
	
	void populateVector(AppLogFiles& logs, const PlayerData& playerData, const FireBallsPaths& fireBallsPaths, const HellSkullDataLoader& dataLoader);
	
	bool wasLoadingPerfect() const;
	void updateSkulls(const HellSkullDrawer& skullDrawer, const spriteMove::ObjectMoving& ballMove, const AllExplosions& explosions, const SoundPlayer& soundPlayer);
	void withBallCollision(const HellSkullDrawer& skullDrawer, spriteMove::ObjectMoving& ballMove, const TextureCombo& ballTexture);
	void fireBallCollisionWithRacket(OnePlayerRacket& racket, const SoundPlayer& soundPlayer);
	void moveSkulls();
	
	std::size_t size() const;
	std::vector< std::unique_ptr< onePlGame::HellSkullElement > >::const_iterator begin() const;
	std::vector< std::unique_ptr< onePlGame::HellSkullElement > >::const_iterator end() const;
	std::unique_ptr< onePlGame::HellSkullElement >& operator[](std::size_t index);
};

}

#endif //ONE_PLAYER_GAME_HELL_SKULL_PACK_H