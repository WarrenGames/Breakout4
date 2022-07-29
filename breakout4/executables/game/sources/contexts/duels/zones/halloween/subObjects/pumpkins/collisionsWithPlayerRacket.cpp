#include "contexts/duels/zones/halloween/subObjects/pumpkins/collisionsWithPlayerRacket.h"
#include "contexts/gameCommon/halloween/pumpkins/pumpkinCombo.h"
#include "contexts/duels/inGameObjects/global/playersThings.h"
#include "contexts/duels/inGameObjects/gameElements/duelsTypes.h"
#include "types/spriteSize.h"
#include "contexts/gameCommon/halloween/bat/batFactory.h"
#include "contexts/duels/instructions/positionCheck.h"
#include "consts/constexprScreen.h"
#include "contexts/gameCommon/halloween/pumpkins/pumpkinConsts.h"
#include "contexts/gameCommon/halloween/bat/batConsts.h"
#include <cassert>

void halloween::collisionRacketAndPumpkin(PlayersThings& playersThings, duels::ScoreDraw& scoreDraw, unsigned playerType, PumpkinCombo& pumpkin, duels::LevelOptions& levelOptions
											, BatObject& bat)
{
	assert( playerType < duels::PLAYER_MAX );
	if( doesMoveObjectCollideWithRect(pumpkin.move, SpriteSize{SQR_SIZE, SQR_SIZE}, playersThings.rackets[playerType].getRacketRect()) && pumpkin.isEffective )
	{
		pumpkin.isEffective = false;
		switch( pumpkin.color )
		{
			case PUMPK_RED:
				halloween::collideWithRedPumpkin(scoreDraw, playerType, pumpkin, levelOptions, bat);
				break;
			case PUMPK_GRAY:
				halloween::collideWithGrayPumpkin(playersThings, playerType, pumpkin, bat);
				break;
			case PUMPK_BLUE:
				halloween::collideWithBluePumpkin(scoreDraw, playerType, pumpkin, levelOptions, bat);
				break;
			case PUMPK_YELLOW:
				halloween::collideWithYellowPumpkin(playersThings, playerType, pumpkin, bat);
				break;
		}
	}
}

void halloween::collideWithRedPumpkin(duels::ScoreDraw& scoreDraw, unsigned playerType, PumpkinCombo& pumpkin, duels::LevelOptions& levelOptions, BatObject& bat)
{
	levelOptions.playersScores[playerType] -= 1;
	scoreDraw.setUpdateFlag();
	
	if( pumpkin.isFromBat )
		bat.changeFace(bat::FACE_HAPPY);
}

void halloween::collideWithGrayPumpkin(PlayersThings& playersThings, unsigned playerType, PumpkinCombo& pumpkin, BatObject& bat)
{
	if( playersThings.rackets[playerType].canBeFreeze() )
	{
		playersThings.rackets[playerType].freezeRacket();
		if( pumpkin.isFromBat )
			bat.changeFace(bat::FACE_HAPPY);
	}
}

void halloween::collideWithBluePumpkin(duels::ScoreDraw& scoreDraw, unsigned playerType, PumpkinCombo& pumpkin, duels::LevelOptions& levelOptions, BatObject& bat)
{
	levelOptions.playersScores[playerType] += 1;
	scoreDraw.setUpdateFlag();
	if( pumpkin.isFromBat )
		bat.changeFace(bat::FACE_DISAPOINTED);			
}

void halloween::collideWithYellowPumpkin(PlayersThings& playersThings, unsigned playerType, PumpkinCombo& pumpkin, BatObject& bat)
{
	if( playersThings.rackets[playerType].canBeSlowedDown() )
	{
		playersThings.rackets[playerType].changeSpeed(-1);
		playersThings.racketsSpeedGradients[playerType].setNewCounterValue( static_cast<unsigned int>(playersThings.rackets[playerType].getSpeed()-duels::RACKET_MIN_SPEED ) );
		if( pumpkin.isFromBat )
			bat.changeFace(bat::FACE_HAPPY);
	}
}