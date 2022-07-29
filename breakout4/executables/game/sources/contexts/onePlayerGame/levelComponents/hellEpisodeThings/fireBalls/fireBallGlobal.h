#ifndef ONE_PLAYER_FIRE_BALL_GLOBAL_OBJECT_H
#define ONE_PLAYER_FIRE_BALL_GLOBAL_OBJECT_H

#include "contexts/onePlayerGame/levelComponents/hellEpisodeThings/fireBalls/configuration/fireBallDataLoader.h"
#include "contexts/gameCommon/fireBall/fireBallDrawer.h"
#include "contexts/onePlayerGame/levelComponents/hellEpisodeThings/fireBalls/inGame/bottomScreenFireBallsPack.h"

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
	void updateFireBalls(OnePlayerRacket& racket, const SoundHandler& sounds);
	
	FireBallDrawer& getDrawer();
};

}

#endif //ONE_PLAYER_FIRE_BALL_GLOBAL_OBJECT_H