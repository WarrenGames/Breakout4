#include "levelComponents/hellEpisodeThings/hellSkulls/inGame/hellSkullActivity.h"
#include "levelComponents/hellEpisodeThings/hellSkulls/configuration/skullFileData.h"
#include "consts/hellConsts.h"

onePlGame::SkullActivity::SkullActivity(const SkullFileData& fileData):
	skillAppearence{ fileData.skillBits },
	pathNumber{ hell::FireBallPathMax },
	nextJob{ hell::SkullThrowFireBall },
	canThrowFireBalls{ fileData.canThrowFireBalls },
	canSeekYellowBall{ fileData.canSeekYellowBall },
	isSkullActive{ false },
	isFireBallActive{ false },
	globalTimeHasRewind{ true },
	isRushing{ false },
	isExploding{ false },
	canCollideWithBall{ true }
{
	
}