#ifndef ONE_PLAYER_FIRE_BALL_PATHS_H
#define ONE_PLAYER_FIRE_BALL_PATHS_H

#include "contexts/gameCommon/movements/pathsLoader.h"

struct AppLogFiles;

namespace onePlGame{

struct FireBallsPaths
{
	PathsLoader paths;
	bool isLoadingPerfect;
	
	explicit FireBallsPaths(AppLogFiles& logs);
	~FireBallsPaths() = default;
	FireBallsPaths( const FireBallsPaths& ) = delete;
	FireBallsPaths& operator= ( const FireBallsPaths& ) = delete;
	FireBallsPaths( FireBallsPaths&& ) = default;
	FireBallsPaths& operator= ( FireBallsPaths&& ) = default;
	
	bool wasLoadingPerfect() const;
};

}

#endif //ONE_PLAYER_FIRE_BALL_PATHS_H