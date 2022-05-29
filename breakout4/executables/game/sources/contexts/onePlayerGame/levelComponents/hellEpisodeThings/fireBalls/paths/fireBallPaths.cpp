#include "contexts/onePlayerGame/levelComponents/hellEpisodeThings/fireBalls/paths/fireBallPaths.h"
#include "logging/logsStruct.h"
#include "consts/hellConsts.h"

constexpr char FireBallsPathsEnum[] = "data/paths/fireBallsOnePlayerEnum.txt";

onePlGame::FireBallsPaths::FireBallsPaths(AppLogFiles& logs):
	paths{ logs, FireBallsPathsEnum },
	isLoadingPerfect{ true }
{
	if( paths.size() != hell::FB_PATH_MAX )
	{
		logs.error << "Error: the number of loaded paths is not good: " << paths.size() << " paths loaded, and " << hell::FB_PATH_MAX << " expected.\n";
		isLoadingPerfect = false;
	}
}

bool onePlGame::FireBallsPaths::wasLoadingPerfect() const
{
	return paths.wasLoadingPerfect() && isLoadingPerfect;
}