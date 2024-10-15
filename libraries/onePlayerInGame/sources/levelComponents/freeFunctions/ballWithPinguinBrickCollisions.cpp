#include "levelComponents/freeFunctions/ballWithPinguinBrickCollisions.h"
#include "levelComponents/global/globalGameObject.h"
#include "levelComponents/freeFunctions/ballWithGridCollisions.h"
#include "crossLevel/playerData.h"
#include "customTypes/positionTypes.h"
#include "consts/onePlayerGridConsts.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/onePlayerSounds.h"

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
		comp.gameSoundSystem.soundSystem.soundPlayer.playSoundOnGroup(onePlGame::SoundImpactWithDamage, onePlGame::GroupTagNewCoin);
		comp.soundsStack.emplaceElement(demos::SoundStackData{comp.demosTimeDelay.getCurrentElapsedMicrosecondsTime(), onePlGame::SoundImpactWithDamage, onePlGame::GroupTagNewCoin} );
		comp.grid(brickCoord.x, brickCoord.y).index = bricks::index::NoBrick;
		playerData.score += 400;
		gridCol::stackBrickMatrixModification(comp, brickCoord, playerData);
	}
	else{
		comp.gameSoundSystem.soundSystem.soundPlayer.playSoundOnGroup(onePlGame::SoundQuack, onePlGame::GroupTagEnemy);
		comp.soundsStack.emplaceElement(demos::SoundStackData{comp.demosTimeDelay.getCurrentElapsedMicrosecondsTime(), onePlGame::SoundQuack, onePlGame::GroupTagEnemy} );
		comp.monsterTrigger.setTriggerFlag(Pinguin_monster_trigger, true);
	}
}

void iceCol::collideWithIceCube(LevelComponents& comp)
{
	comp.gameSoundSystem.soundSystem.soundPlayer.playSoundOnGroup(onePlGame::SoundBallWBgCollision, onePlGame::GroupTagRacketWithBallCollision);
	comp.soundsStack.emplaceElement(demos::SoundStackData{comp.demosTimeDelay.getCurrentElapsedMicrosecondsTime(), onePlGame::SoundBallWBgCollision, onePlGame::GroupTagRacketWithBallCollision} );
}