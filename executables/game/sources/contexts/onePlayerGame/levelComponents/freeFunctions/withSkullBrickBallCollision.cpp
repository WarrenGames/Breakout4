#include "contexts/onePlayerGame/levelComponents/freeFunctions/withSkullBrickBallCollision.h"
#include "contexts/onePlayerGame/levelComponents/global/globalGameObject.h"
#include "crossLevel/playerData.h"
#include "customTypes/positionTypes.h"
#include "consts/onePlayerGridConsts.h"
#include "consts/onePlayerLevelConsts.h"

void hellCol::collideWithHellBricks(LevelComponents& comp, const Offset& brickCoord, bool isBallPowerful, PlayerData& playerData)
{
	switch( comp.grid(brickCoord.x, brickCoord.y).property )
	{
		case bricks::hellBricks::SkullBrick:
			hellCol::collideWithSkullHellBrick(comp, brickCoord, isBallPowerful, playerData);
			break;
		case bricks::hellBricks::LavaStone1:
			hellCol::collideWithLavaStoneBrick(comp);
			break;
		case bricks::hellBricks::LavaStone2:
			hellCol::collideWithLavaStoneBrick(comp);
			break;
		case bricks::hellBricks::LavaStone3:
			hellCol::collideWithLavaStoneBrick(comp);
			break;
	}
}

void hellCol::collideWithSkullHellBrick(LevelComponents& comp, const Offset& brickCoord, bool isBallPowerful, PlayerData& playerData)
{
	if( isBallPowerful )
	{
		comp.sounds.playSound(onePlGame::SoundImpactWithDamage);
		comp.grid(brickCoord.x, brickCoord.y).index = bricks::index::NoBrick;
		playerData.score += 600;
	}
	else{
		comp.monsterTrigger.setTriggerFlag(Hell_skull_monster_trigger, true);
		//comp.monsters.startOneNotBusySkullActivity();
	}
}

void hellCol::collideWithLavaStoneBrick(LevelComponents& comp)
{
	comp.sounds.playSound(onePlGame::SoundBallWBgCollision);
}