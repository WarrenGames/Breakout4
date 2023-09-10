#include "levelComponents/freeFunctions/withSkullBrickBallCollision.h"
#include "levelComponents/global/globalGameObject.h"
#include "levelComponents/freeFunctions/ballWithGridCollisions.h"
#include "crossLevel/playerData.h"
#include "customTypes/positionTypes.h"
#include "consts/onePlayerGridConsts.h"
#include "consts/onePlayerLevelConsts.h"

void hellCol::collideWithHellBricks(LevelComponents& comp, const Offset& brickCoord, bool isBallPowerful, PlayerData& playerData)
{
	switch( comp.grid(brickCoord.x, brickCoord.y).property )
	{
		case bricks::hellBricks::SkullBrick:
			hellCol::collideWithSkullHellBrick(comp, brickCoord, isBallPowerful, playerData, onePlGame::SoundImpactWithDamage);
			break;
		case bricks::hellBricks::LavaStone1:
			hellCol::collideWithLavaStoneBrick(comp, onePlGame::SoundBallWBgCollision);
			break;
		case bricks::hellBricks::LavaStone2:
			hellCol::collideWithLavaStoneBrick(comp, onePlGame::SoundBallWBgCollision);
			break;
		case bricks::hellBricks::LavaStone3:
			hellCol::collideWithLavaStoneBrick(comp, onePlGame::SoundBallWBgCollision);
			break;
	}
}

void hellCol::collideWithSkullHellBrick(LevelComponents& comp, const Offset& brickCoord, bool isBallPowerful, PlayerData& playerData, unsigned soundEnum)
{
	if( isBallPowerful )
	{
		comp.sounds.playSound(soundEnum);
		comp.soundsStack.emplaceElement(demos::SoundStackData{comp.demosTimeDelay.getCurrentElapsedMicrosecondsTime(), soundEnum} );
		comp.grid(brickCoord.x, brickCoord.y).index = bricks::index::NoBrick;
		playerData.score += 600;
		gridCol::stackBrickMatrixModification(comp, brickCoord, playerData);
	}
	else{
		comp.monsterTrigger.setTriggerFlag(Hell_skull_monster_trigger, true);
	}
}

void hellCol::collideWithLavaStoneBrick(LevelComponents& comp, unsigned soundEnum)
{
	comp.sounds.playSound(soundEnum);
	comp.soundsStack.emplaceElement(demos::SoundStackData{ comp.demosTimeDelay.getCurrentElapsedMicrosecondsTime(), soundEnum} );
}