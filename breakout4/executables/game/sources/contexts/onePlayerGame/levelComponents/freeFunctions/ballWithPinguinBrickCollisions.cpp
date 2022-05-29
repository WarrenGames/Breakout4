#include "contexts/onePlayerGame/levelComponents/freeFunctions/ballWithPinguinBrickCollisions.h"
#include "contexts/onePlayerGame/levelComponents/global/globalGameObject.h"
#include "crossLevel/playerData.h"
#include "customTypes/positionTypes.h"
#include "consts/onePlayerGridConsts.h"
#include "consts/onePlayerLevelConsts.h"

void iceCol::collideWithIceBricks(LevelComponents& comp, const Offset& brickCoord, bool isBallPowerful, PlayerData& playerData)
{
	switch( comp.grid(brickCoord.x, brickCoord.y).property )
	{
		case BRICKS::ICE_BR::ICE_CUBE:
			iceCol::collideWithIceCube(comp);
			break;
		case BRICKS::ICE_BR::PINGUIN_BRICK:
			iceCol::collideWithPinguinBrick(comp, brickCoord, isBallPowerful, playerData);
			break;
	}
}

void iceCol::collideWithPinguinBrick(LevelComponents& comp, const Offset& brickCoord, bool isBallPowerful, PlayerData& playerData)
{
	if( isBallPowerful )
	{
		comp.sounds.playSound(onePlGame::SND_IMPACT_W_DAMAGE);
		comp.grid(brickCoord.x, brickCoord.y).index = BRICKS::INDEX::NO_BRICK;
		playerData.score += 400;
	}
	else{
		comp.sounds.playSound(onePlGame::SND_QUACK);
		comp.monsterTrigger.setTriggerFlag(Pinguin_monster_trigger, true);
	}
}

void iceCol::collideWithIceCube(const LevelComponents& comp)
{
	comp.sounds.playSound(onePlGame::SND_COL_BALL_W_BACKGRND);
}