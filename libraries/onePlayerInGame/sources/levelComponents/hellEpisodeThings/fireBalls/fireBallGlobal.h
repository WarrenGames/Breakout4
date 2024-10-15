#ifndef ONE_PLAYER_FIRE_BALL_GLOBAL_OBJECT_H
#define ONE_PLAYER_FIRE_BALL_GLOBAL_OBJECT_H

#include "levelComponents/hellEpisodeThings/fireBalls/configuration/fireBallDataLoader.h"
#include "fireBall/fireBallDrawer.h"
#include "levelComponents/hellEpisodeThings/fireBalls/inGame/bottomScreenFireBallsPack.h"

struct Essentials;
struct PlayerData;
struct OnePlayerRacket;

namespace onePlGame{

class FireBallGlobal
{
private:
	FireBallDataLoader fireBallLoader;
	FireBallDrawer fireBallDrawer;
	BottomScrFireBalls bottomFireBalls;

public:
	explicit FireBallGlobal(Essentials& essentials, const PlayerData& playerData, const FireBallsPaths& fireBallsPaths);
	~FireBallGlobal() = default;
	FireBallGlobal( const FireBallGlobal& ) = delete;
	FireBallGlobal& operator= ( const FireBallGlobal& ) = delete;
	FireBallGlobal( FireBallGlobal&& ) = default;
	FireBallGlobal& operator= ( FireBallGlobal&& ) = default;
	
	bool wasLoadingPerfect() const;
	
	void drawFireBalls(Essentials& essentials);
	void updateFireBalls(OnePlayerRacket& racket, const SoundPlayer& soundPlayer);
	
	FireBallDrawer& getDrawer();
};

}

#endif //ONE_PLAYER_FIRE_BALL_GLOBAL_OBJECT_H