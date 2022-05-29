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
		case BRICKS::HELL_BR::SKULL_BRICK:
			hellCol::collideWithSkullHellBrick(comp, brickCoord, isBallPowerful, playerData);
			break;
		case BRICKS::HELL_BR::LAVA_STONE_1:
			hellCol::collideWithLavaStoneBrick(comp);
			break;
		case BRICKS::HELL_BR::LAVA_STONE_2:
			hellCol::collideWithLavaStoneBrick(comp);
			break;
		case BRICKS::HELL_BR::LAVA_STONE_3:
			hellCol::collideWithLavaStoneBrick(comp);
			break;
	}
}

void hellCol::collideWithSkullHellBrick(LevelComponents& comp, const Offset& brickCoord, bool isBallPowerful, PlayerData& playerData)
{
	if( isBallPowerful )
	{
		comp.sounds.playSound(onePlGame::SND_IMPACT_W_DAMAGE);
		comp.grid(brickCoord.x, brickCoord.y).index = BRICKS::INDEX::NO_BRICK;
		playerData.score += 600;
	}
	else{
		comp.monsterTrigger.setTriggerFlag(Hell_skull_monster_trigger, true);
		//comp.monsters.startOneNotBusySkullActivity();
	}
}

void hellCol::collideWithLavaStoneBrick(LevelComponents& comp)
{
	comp.sounds.playSound(onePlGame::SND_COL_BALL_W_BACKGRND);
}