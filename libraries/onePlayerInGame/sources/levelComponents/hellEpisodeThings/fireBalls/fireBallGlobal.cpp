#include "levelComponents/hellEpisodeThings/fireBalls/fireBallGlobal.h"
#include "types/essentialsStruct.h"
#include "crossLevel/playerData.h"
#include "generic/fileSystem/fileProcessing/templateLogging.h"
#include "soundSystem/soundsPlayer.h"
#include "levelComponents/hellEpisodeThings/fireBalls/paths/fireBallPaths.h"

onePlGame::FireBallGlobal::FireBallGlobal(Essentials& essentials, const PlayerData& playerData, const FireBallsPaths& fireBallsPaths):
	fireBallLoader{essentials, playerData},
	fireBallDrawer{essentials},
	bottomFireBalls{ essentials.logs, playerData, fireBallLoader, fireBallsPaths }
{
	logLoadingStatus(essentials.logs.warning, "fire ball loader", fireBallLoader);
	logLoadingStatus(essentials.logs.warning, "fire ball drawer", fireBallDrawer);
}

bool onePlGame::FireBallGlobal::wasLoadingPerfect() const
{
	return fireBallLoader.wasLoadingPerfect()
		&& fireBallDrawer.wasLoadingPerfect();
}

void onePlGame::FireBallGlobal::drawFireBalls(Essentials& essentials)
{
	for( auto const &element : bottomFireBalls )
	{
		if( element )
		{
			if( element->isActive )
			{
				fireBallDrawer.drawFireBall(essentials, element->drawData, element->move.moveSprite, element->starThings );
			}
		}
	}
}

void onePlGame::FireBallGlobal::updateFireBalls(OnePlayerRacket& racket, const SoundPlayer& soundPlayer)
{
	bottomFireBalls.update(racket, soundPlayer);
	bottomFireBalls.startActivity(soundPlayer);
}

FireBallDrawer& onePlGame::FireBallGlobal::getDrawer()
{
	return fireBallDrawer;
}