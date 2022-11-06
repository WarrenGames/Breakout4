#include "contexts/onePlayerGame/levelComponents/hellEpisodeThings/hellPackage.h"
#include "types/essentialsStruct.h"
#include "contexts/gameCommon/explosions/allExplosions.h"
#include "generic/fileSystem/fileProcessing/templateLogging.h"
#include "generic/sounds/soundHandler.h"

onePlGame::HellPackage::HellPackage(Essentials& essentials, const PlayerData& playerData):
	fireBallsPaths{essentials.logs},
	fireBallGlobal{essentials, playerData, fireBallsPaths},
	hellSkullGlobal{essentials, playerData, fireBallsPaths}
{
	logLoadingStatus(essentials.logs.warning, "fire ball paths", fireBallsPaths);
	logLoadingStatus(essentials.logs.warning, "fire ball global", fireBallGlobal);
	logLoadingStatus(essentials.logs.warning, "hell skull global", hellSkullGlobal);
}

onePlGame::HellPackage::operator bool() const
{
	return fireBallsPaths.wasLoadingPerfect()
		&& fireBallGlobal.wasLoadingPerfect()
		&& hellSkullGlobal.wasLoadingPerfect();
}

void onePlGame::HellPackage::update(spriteMove::ObjectMoving& ballMove, OnePlayerRacket& racket, const AllExplosions& explosions, const TextureCombo& ballTexture, const SoundHandler& sounds)
{
	fireBallGlobal.updateFireBalls(racket, sounds);
	hellSkullGlobal.update(ballMove, racket, explosions, ballTexture, sounds);
}

void onePlGame::HellPackage::drawEverything(Essentials& essentials, AllExplosions& explosions)
{
	fireBallGlobal.drawFireBalls(essentials);
	hellSkullGlobal.drawHellSkulls(essentials, explosions);
	hellSkullGlobal.drawFireBalls(essentials, fireBallGlobal.getDrawer() );
}

void onePlGame::HellPackage::addPendingSkull()
{
	hellSkullGlobal.addPendingSkull();
}