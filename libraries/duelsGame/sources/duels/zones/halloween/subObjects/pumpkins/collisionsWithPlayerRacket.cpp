#include "duels/zones/halloween/subObjects/pumpkins/collisionsWithPlayerRacket.h"
#include "halloween/pumpkins/pumpkinCombo.h"
#include "duels/inGameObjects/global/playersThings.h"
#include "duels/inGameObjects/gameElements/duelsLevelOptions.h"
#include "types/spriteSize.h"
#include "halloween/bat/batFactory.h"
#include "rectCollisions/positionCheck.h"
#include "consts/constexprScreen.h"
#include "halloween/pumpkins/pumpkinConsts.h"
#include "halloween/bat/batConsts.h"
#include <cassert>

void halloween::collisionRacketAndPumpkin(PlayersThings& playersThings, duels::ScoreDraw& scoreDraw, unsigned playerType, PumpkinCombo& pumpkin, duels::LevelOptions& levelOptions
											, BatObject& bat)
{
	assert( playerType < duels::PlayerMax );
	if( doesMoveObjectCollideWithRect(pumpkin.move, SpriteSize{SQR_SIZE, SQR_SIZE}, playersThings.rackets[playerType].getRacketRect()) && pumpkin.isEffective )
	{
		pumpkin.isEffective = false;
		switch( pumpkin.color )
		{
			case PumpkinColorRed:
				halloween::collideWithRedPumpkin(scoreDraw, playerType, pumpkin, levelOptions, bat);
				break;
			case PumpkinColorGray:
				halloween::collideWithGrayPumpkin(playersThings, playerType, pumpkin, bat);
				break;
			case PumpkinColorBlue:
				halloween::collideWithBluePumpkin(scoreDraw, playerType, pumpkin, levelOptions, bat);
				break;
			case PumpkinColorYellow:
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
		bat.changeFace(bat::FaceHappy);
}

void halloween::collideWithGrayPumpkin(PlayersThings& playersThings, unsigned playerType, PumpkinCombo& pumpkin, BatObject& bat)
{
	if( playersThings.rackets[playerType].canBeFreeze() )
	{
		playersThings.rackets[playerType].freezeRacket();
		if( pumpkin.isFromBat )
			bat.changeFace(bat::FaceHappy);
	}
}

void halloween::collideWithBluePumpkin(duels::ScoreDraw& scoreDraw, unsigned playerType, PumpkinCombo& pumpkin, duels::LevelOptions& levelOptions, BatObject& bat)
{
	levelOptions.playersScores[playerType] += 1;
	scoreDraw.setUpdateFlag();
	if( pumpkin.isFromBat )
		bat.changeFace(bat::FaceDisapointed);			
}

void halloween::collideWithYellowPumpkin(PlayersThings& playersThings, unsigned playerType, PumpkinCombo& pumpkin, BatObject& bat)
{
	if( playersThings.rackets[playerType].canBeSlowedDown() )
	{
		playersThings.rackets[playerType].changeSpeed(-1);
		playersThings.racketsSpeedGradients[playerType].setNewCounterValue( static_cast<int>(playersThings.rackets[playerType].getSpeed()-duels::RacketMinimumSpeed ) );
		if( pumpkin.isFromBat )
			bat.changeFace(bat::FaceHappy);
	}
}