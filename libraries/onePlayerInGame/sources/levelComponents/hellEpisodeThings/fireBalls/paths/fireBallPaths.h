#ifndef ONE_PLAYER_FIRE_BALL_PATHS_H
#define ONE_PLAYER_FIRE_BALL_PATHS_H

#include "spriteMove/movements.h"

struct AppLogFiles;

namespace onePlGame{

struct FireBallsPaths
{
	spriteMove::Movements paths;
	bool isLoadingPerfect;
	
	explicit FireBallsPaths();
	explicit FireBallsPaths(AppLogFiles& logs);
	~FireBallsPaths() = default;
	FireBallsPaths( const FireBallsPaths& ) = delete;
	FireBallsPaths& operator= ( const FireBallsPaths& ) = delete;
	FireBallsPaths( FireBallsPaths&& ) = default;
	FireBallsPaths& operator= ( FireBallsPaths&& ) = default;
	
	bool wasLoadingPerfect() const;
	
	void openMainFile(AppLogFiles& logs, const std::string& mainFilePath);
	void addPathFromFile(AppLogFiles& logs, const std::string& pathFile);
};

}

#endif //ONE_PLAYER_FIRE_BALL_PATHS_H