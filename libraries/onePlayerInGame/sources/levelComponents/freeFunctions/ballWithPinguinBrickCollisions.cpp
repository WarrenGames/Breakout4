#include "levelComponents/freeFunctions/ballWithPinguinBrickCollisions.h"
#include "levelComponents/global/globalGameObject.h"
#include "levelComponents/freeFunctions/ballWithGridCollisions.h"
#include "crossLevel/playerData.h"
#include "customTypes/positionTypes.h"
#include "consts/onePlayerGridConsts.h"
#include "consts/onePlayerLevelConsts.h"

void iceCol::collideWithIceBricks(LevelComponents& comp, const Offset& brickCoord, bool isBallPowerful, PlayerData& playerData)
{
	switch( comp.grid(brickCoord.x, brickCoord.y).property )
	{
		case bricks::iceBricks::IceCube:
			iceCol::collideWithIceCube(comp);
			break;
		case bricks::iceBricks::PinguinBrickTexturePath:
			iceCol::collideWithPinguinBrick(comp, brickCoord, isBallPowerful, playerData);
			break;
	}
}

void iceCol::collideWithPinguinBrick(LevelComponents& comp, const Offset& brickCoord, bool isBallPowerful, PlayerData& playerData)
{
	if( isBallPowerful )
	{
		comp.sounds.playSound(onePlGame::SoundImpactWithDamage);
		comp.soundsStack.emplaceElement(demos::SoundStackData{comp.demosTimeDelay.getCurrentElapsedMicrosecondsTime(), onePlGame::SoundImpactWithDamage} );
		comp.grid(brickCoord.x, brickCoord.y).index = bricks::index::NoBrick;
		playerData.score += 400;
		gridCol::stackBrickMatrixModification(comp, brickCoord, playerData);
	}
	else{
		comp.sounds.playSound(onePlGame::SoundQuack);
		comp.soundsStack.emplaceElement(demos::SoundStackData{comp.demosTimeDelay.getCurrentElapsedMicrosecondsTime(), onePlGame::SoundQuack} );
		comp.monsterTrigger.setTriggerFlag(Pinguin_monster_trigger, true);
	}
}

void iceCol::collideWithIceCube(LevelComponents& comp)
{
	comp.sounds.playSound(onePlGame::SoundBallWBgCollision);
	comp.soundsStack.emplaceElement(demos::SoundStackData{comp.demosTimeDelay.getCurrentElapsedMicrosecondsTime(), onePlGame::SoundBallWBgCollision} );
}