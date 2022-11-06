#include "contexts/duels/zones/halloween/subObjects/pumpkins/playersSpecialPumpkins.h"
#include "contexts/gameCommon/halloween/pumpkins/pumpkinDrawer.h"
#include "contexts/duels/inGameObjects/global/playersThings.h"
#include "types/essentialsStruct.h"
#include "customTypes/positionTypes.h"
#include "contexts/duels/inGameObjects/gameElements/duelsTypes.h"
#include "contexts/duels/zones/halloween/subObjects/pumpkins/collisionsWithPlayerRacket.h"
#include <fstream>

constexpr char PumpkinsPositionFilePath[] = "data/levels/duels/halloweenPumpkinsPos.lvl";
constexpr std::size_t SpecialPumpkinsCount = 6;

SpecialPumpkins::SpecialPumpkins(Essentials& essentials):
	lastSpecialBonusDelay(duels::PlayerMax),
	pumpkinsData{duels::PlayerMax, SpecialPumpkinsCount},
	specialPumpkins{duels::PlayerMax, SpecialPumpkinsCount},
	havePumpkinsMovedSince{true}
{
	populateSpecialBonusPumpkinsVector(essentials);
}

void SpecialPumpkins::activateSpecialBonus(const duels::LevelOptions& levelOptions, unsigned playerNum)
{
	if( lastSpecialBonusDelay[playerNum].hasTimeElapsed(  std::chrono::milliseconds{levelOptions.halloween.secondsSinceLastSpecialBonus * 1000} ) )
	{
		resetSpecialPumpkinsPositions(playerNum);
		traceSpecialPumpkins(playerNum);
		lastSpecialBonusDelay[playerNum].joinTimePoints();
	}
}

void SpecialPumpkins::update(PlayersThings& playersThings, duels::LevelOptions& levelOptions, BatObject& badBat)
{
	movePumpkins();
	disableStaledPumpkins();
	browsePumpkinsForCollision(playersThings, levelOptions, badBat);
}

void SpecialPumpkins::drawPumpkins(Essentials& essentials, PumpkinDrawer& drawer)
{
	for( auto const &pumpkin : specialPumpkins )
	{
		if( pumpkin.isEffective )
		{
			drawer.drawPumpkin(essentials, pumpkin);
		}
	}
}

bool SpecialPumpkins::canActivateSpecialBonus(unsigned playerNum)
{
	assert( playerNum < duels::PlayerMax );
	for( std::size_t i{0} ; i < specialPumpkins.height() ; ++i )
	{
		if( specialPumpkins(playerNum, i).isPumpkinInsideOfScreen(SQR_SIZE, SQR_SIZE) && specialPumpkins(playerNum, i).isEffective )
			return false;
	}
	return true;
}

void SpecialPumpkins::populateSpecialBonusPumpkinsVector(Essentials& essentials)
{
	if( std::ifstream pumpkPosFile{PumpkinsPositionFilePath} )
	{
		Offset pumpkinPosition{0, 0};
		Offset pumpkinDestination{0, 0};
		readPumpkinsPositionsData(essentials, pumpkPosFile, pumpkinPosition, pumpkinDestination);
	}
	else{
		essentials.logs.error << "Error: couldn't open '" << PumpkinsPositionFilePath << "' file in order to read the pumpkins position.\n";
	}
}

void SpecialPumpkins::readPumpkinsPositionsData(Essentials& essentials, std::ifstream& pumpkPosFile, Offset& pumpkinPosition, Offset& pumpkinDestination)
{
	double speed{0};
	for( std::size_t player{0} ; player < duels::PlayerMax ; ++player )
	{
		for( std::size_t i{0} ; i < SpecialPumpkinsCount ; ++i )
		{
			if( pumpkPosFile >> pumpkinPosition.x >> pumpkinPosition.y >> pumpkinDestination.x >> pumpkinDestination.y >> speed )
			{
				pumpkinsData(player, i).origin = pumpkinPosition;
				pumpkinsData(player, i).destination = pumpkinDestination;
				pumpkinsData(player, i).pumpkinSpeed = speed;
			}
			else{
				essentials.logs.error << "Error: couldn't read data in '" << PumpkinsPositionFilePath << "' file for the player #" << player + 1 
									<< " and pumpkin position number " << i << " .\n"; 
			}
		}
	}
}

void SpecialPumpkins::resetSpecialPumpkinsPositions(unsigned playerNum)
{
	if( pumpkinsData.width() == duels::PlayerMax && pumpkinsData.height() == SpecialPumpkinsCount 
		&& specialPumpkins.width() == duels::PlayerMax && specialPumpkins.height() == SpecialPumpkinsCount )
	{
		for( std::size_t i{0} ; i < SpecialPumpkinsCount ; ++i )
		{
			specialPumpkins(playerNum, i).move.setPosition( Offset{ pumpkinsData(playerNum,i).origin.x * SQR_SIZE, pumpkinsData(playerNum, i).origin.y * SQR_SIZE } );
			specialPumpkins(playerNum, i).move.setBothVectors( computeDiff( pumpkinsData(playerNum, i).origin, pumpkinsData(playerNum, i).destination ) );
			specialPumpkins(playerNum, i).move.setSpeed( pumpkinsData(playerNum, i).pumpkinSpeed );
			specialPumpkins(playerNum, i).move.adjust_x_speed();
			specialPumpkins(playerNum, i).move.adjust_y_speed();
		}
	}
}

void SpecialPumpkins::traceSpecialPumpkins(unsigned playerNum)
{
	for( std::size_t i{0} ; i < specialPumpkins.height() ; ++i )
	{
		specialPumpkins(playerNum, i).isEffective = true;
	}
}

void SpecialPumpkins::movePumpkins()
{
	if( moveDelay.hasTimeElapsed( std::chrono::milliseconds{10} ) )
	{
		for( auto &pumpkin : specialPumpkins )
		{
			if( pumpkin.isEffective )
				pumpkin.move.moveObject();
		}
		havePumpkinsMovedSince = true;
		moveDelay.joinTimePoints();
	}
}

void SpecialPumpkins::disableStaledPumpkins()
{
	if( havePumpkinsMovedSince )
	{
		for( std::size_t i{0} ; i < specialPumpkins.height() ; ++i )
		{
			if( specialPumpkins(duels::PlayerBlue, i).move.get_y_position() < -SQR_SIZE )
			{
				specialPumpkins(duels::PlayerBlue, i).isEffective = false;
			}
			if( specialPumpkins(duels::PlayerRed, i).move.get_y_position() >= GameScreenHeight + SQR_SIZE )
			{
				specialPumpkins(duels::PlayerRed, i).isEffective = false;
			}
		}
		havePumpkinsMovedSince = false;
	}
}

void SpecialPumpkins::browsePumpkinsForCollision(PlayersThings& playersThings, duels::LevelOptions& levelOptions, BatObject& badBat)
{
	for( unsigned playerNum{0} ; playerNum < duels::PlayerMax ; ++playerNum )
	{
		for( auto &pumpkin : specialPumpkins )
		{
			halloween::collisionRacketAndPumpkin(playersThings, playersThings.scoresDrawing[playerNum], playerNum, pumpkin, levelOptions, badBat);
		}
	}
}