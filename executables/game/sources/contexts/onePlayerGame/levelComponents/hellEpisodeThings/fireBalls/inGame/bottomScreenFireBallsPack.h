#ifndef ONE_PLAYER_BOTTOM_SCREEN_FIRE_BALLS_PACKAGE_H
#define ONE_PLAYER_BOTTOM_SCREEN_FIRE_BALLS_PACKAGE_H

#include "contexts/onePlayerGame/levelComponents/hellEpisodeThings/fireBalls/inGame/fireBallElement.h"
#include <vector>
#include <memory>

struct AppLogFiles;
struct PlayerData;
class SoundHandler;
struct OnePlayerRacket;

namespace onePlGame{
	class FireBallDataLoader;
	struct FireBallsPaths;

class BottomScrFireBalls
{
private:
	std::vector< std::unique_ptr< FireBallElement > > data;
	AccurateTimeDelay moveDelay;

public:
	explicit BottomScrFireBalls(AppLogFiles& logs, const PlayerData& playerData, const FireBallDataLoader& dataLoader, const FireBallsPaths& paths);
	~BottomScrFireBalls() = default;
	BottomScrFireBalls( const BottomScrFireBalls& ) = delete;
	BottomScrFireBalls& operator= ( const BottomScrFireBalls& ) = delete;
	BottomScrFireBalls( BottomScrFireBalls&& ) = default;
	BottomScrFireBalls& operator= ( BottomScrFireBalls&& ) = default;
	
	void populateVector(AppLogFiles& logs, const PlayerData& playerData, const FireBallDataLoader& dataLoader, const FireBallsPaths& paths);
	
	std::vector< std::unique_ptr< FireBallElement > >::const_iterator begin() const;
	std::vector< std::unique_ptr< FireBallElement > >::const_iterator end() const;
	
	void update(OnePlayerRacket& racket, const SoundHandler& sounds);
	void startActivity(const SoundHandler& sounds);
};

}

#endif //ONE_PLAYER_BOTTOM_SCREEN_FIRE_BALLS_PACKAGE_H