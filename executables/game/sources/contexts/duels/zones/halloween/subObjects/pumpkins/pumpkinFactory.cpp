#include "contexts/duels/zones/halloween/subObjects/pumpkins/pumpkinFactory.h"
#include "contexts/gameCommon/halloween/pumpkins/pumpkinDrawer.h"
#include "contexts/gameCommon/halloween/bat/batFactory.h"
#include "contexts/duels/instructions/positionCheck.h"
#include "contexts/duels/inGameObjects/gameElements/duelsTypes.h"
#include "contexts/duels/inGameObjects/global/playersThings.h"
#include "contexts/duels/zones/halloween/subObjects/pumpkins/collisionsWithPlayerRacket.h"
#include "types/essentialsStruct.h"
#include "contexts/gameCommon/halloween/pumpkins/pumpkinConsts.h"
#include "consts/constexprScreen.h"
#include "contexts/duels/duelsConstexpr.h"
#include <fstream>
#include <cassert>
#include <algorithm>

PumpkinFactory::PumpkinFactory(const HalloweenConfig& halloweenCfg):
	pumpkins{
		PumpkinCombo{true},
		PumpkinCombo{true},
		PumpkinCombo{false},
		PumpkinCombo{false}
	},
	randomDirections{-SQR_SIZE, SQR_SIZE, 0},
	arePotPumpkinsRedirected{false}
{
	createBonusPicker(halloweenCfg);
}

void PumpkinFactory::update(BatObject& badBat, PlayersThings& playersThings, duels::LevelOptions& levelOptions, const PumpkinDrawer& drawer)
{
	makePumpkinsFollowBat(badBat, drawer);
	disableOutOfScreenFromBatPumpkin(drawer);
	movePumpkins();
	redirectPotPumpkins();
	makeBatDropPumpkins(badBat);
	browseRacketsAndPumpkinsForCollision(playersThings, levelOptions, badBat);
}

void PumpkinFactory::drawPumpkins(Essentials& essentials, PumpkinDrawer& drawer)
{
	for( auto const &pumpkin : pumpkins )
	{
		drawSinglePumpkin(essentials, drawer, pumpkin);
	}
}

bool PumpkinFactory::canStartActivity() const
{
	return std::all_of(pumpkins.cbegin(), pumpkins.cend(), [](auto pumpkin){return pumpkin.direction == PumpkinStuck;} );
}

void PumpkinFactory::startPumpkinActivity()
{
	arePotPumpkinsRedirected = false;
	hangPumpkinToBadBat(pumpkins[0], PumpkinFollowBatOnLeft);
	hangPumpkinToBadBat(pumpkins[1], PumpkinFollowBatOnRight);
	setPumpkinIntoPot(pumpkins[2], Offset{ SQR_SIZE*7, SQR_SIZE*5});
	setPumpkinIntoPot(pumpkins[3], Offset{ SQR_SIZE*13 , SQR_SIZE*5});
}

void PumpkinFactory::makePumpkinsFollowBat(const BatObject& badBat, const PumpkinDrawer& drawer)
{
	if( pumpkins[0].direction == PumpkinFollowBatOnLeft )
	{
		pumpkins[0].move.setPosition(Offset{static_cast<int>(badBat.getBatPosition().x) - drawer.getTextureWidth(pumpkins[0].color) / 2, 
											static_cast<int>(badBat.getBatPosition().y) - badBat.getFaceHeight() / 2 + 88} );
	}
	if( pumpkins[1].direction == PumpkinFollowBatOnRight )
	{
		pumpkins[1].move.setPosition(Offset{static_cast<int>(badBat.getBatPosition().x) + drawer.getTextureWidth(pumpkins[1].color) / 2, 
											static_cast<int>(badBat.getBatPosition().y) - badBat.getFaceHeight() / 2 + 88} );
	}
}

void PumpkinFactory::drawSinglePumpkin(Essentials& essentials, PumpkinDrawer& drawer, const PumpkinCombo& pumpkin)
{
	assert( pumpkin.color < PumpkinColorMax );
	if( pumpkin.isEffective )
	{
		drawer.drawPumpkin(essentials, pumpkin);
	}
}

void PumpkinFactory::disableOutOfScreenFromBatPumpkin(const PumpkinDrawer& drawer)
{
	for( auto &pumpkin : pumpkins )
	{
		if( false == pumpkin.isPumpkinInsideOfScreen( drawer.getTextureWidth(pumpkin.color), drawer.getTextureHeight(pumpkin.color) ) && pumpkin.direction >= PumpkinDropFromBat )
		{
			pumpkin.direction = PumpkinStuck;
		}
	}
}

void PumpkinFactory::makeBatDropPumpkins(const BatObject& badBat)
{
	if( badBat.getBatPosition().x >= SQR_SIZE * 7 - SQR_SIZE / 2 && badBat.getBatPosition().x < SQR_SIZE * 7 + SQR_SIZE / 2 )
	{
		dropSinglePumpkin(pumpkins[0], Offset{randomDirections.getRandomValue(), SQR_SIZE}, PumpkinDropFromBat);
	}
	if( badBat.getBatPosition().x >= SQR_SIZE * 13 - SQR_SIZE / 2 && badBat.getBatPosition().x < SQR_SIZE * 13 + SQR_SIZE / 2 )
	{
		dropSinglePumpkin(pumpkins[1], Offset{randomDirections.getRandomValue(), SQR_SIZE}, PumpkinDropFromBat);
	}
}

void PumpkinFactory::dropSinglePumpkin(PumpkinCombo& pumpkin, const Offset& newDirection, unsigned pumpkinState)
{
	pumpkin.move.setSpeed(1);
	giveObjectNewDirection(pumpkin.move, newDirection);
	pumpkin.direction = pumpkinState;
}

void PumpkinFactory::setPumpkinIntoPot(PumpkinCombo& pumpkin, const Offset& position)
{
	assert( pumpkinColorPicker.size() == duels::PlayerMax );
	pumpkin.direction = PumpkinLeavePot;
	pumpkin.color = pumpkinColorPicker[duels::PlayerRed].pickNextBonus();
	pumpkin.move.setPosition(position);
	pumpkin.move.setSpeed(1);
	pumpkin.isEffective = true;
	giveObjectNewDirection(pumpkin.move, Offset{0, -1});
}

void PumpkinFactory::hangPumpkinToBadBat(PumpkinCombo& pumpkin, unsigned newState)
{
	assert( pumpkinColorPicker.size() == duels::PlayerMax );
	pumpkin.direction = newState;
	pumpkin.isEffective = true;
	pumpkin.color = pumpkinColorPicker[duels::PlayerBlue].pickNextBonus();
	assert( pumpkin.color < PumpkinColorMax );
}

void PumpkinFactory::movePumpkins()
{
	if( moveDelay.hasTimeElapsed( std::chrono::milliseconds{10} ) )
	{
		moveBatPumpkins(pumpkins[0]);
		moveBatPumpkins(pumpkins[1]);
		movePotPumpkins(pumpkins[2]);
		movePotPumpkins(pumpkins[3]);
		moveDelay.joinTimePoints();
	}
}

void PumpkinFactory::movePotPumpkins(PumpkinCombo& pumpkin)
{
	if( pumpkin.direction == PumpkinLeavePot || pumpkin.direction == PumpkinReleasedFromPot )
	{
		pumpkin.move.moveObject();
	}
}

void PumpkinFactory::moveBatPumpkins(PumpkinCombo& pumpkin)
{
	if( pumpkin.direction == PumpkinDropFromBat )
	{
		pumpkin.move.moveObject();
	}
}

void PumpkinFactory::redirectPotPumpkins()
{
	if( false == arePotPumpkinsRedirected && pumpkins[2].move.getPosition().y <= SQR_SIZE * 3 && pumpkins[3].move.getPosition().y <= SQR_SIZE * 3 )
	{
		arePotPumpkinsRedirected = true;
		redirectSinglePotPumpkin(pumpkins[2]);
		redirectSinglePotPumpkin(pumpkins[3]);
	}
}

void PumpkinFactory::redirectSinglePotPumpkin(PumpkinCombo& pumpkin)
{
	giveObjectNewDirection(pumpkin.move, Offset{randomDirections.getRandomValue(), -SQR_SIZE} );
}

void PumpkinFactory::browseRacketsAndPumpkinsForCollision(PlayersThings& playersThings, duels::LevelOptions& levelOptions, BatObject& badBat)
{
	for( auto &pumpkin : pumpkins )
	{
		for( unsigned i{0} ; i < playersThings.rackets.size() ; ++i )
		{
			halloween::collisionRacketAndPumpkin(playersThings, playersThings.scoresDrawing[i], i, pumpkin, levelOptions, badBat);
		}
	}
}

void PumpkinFactory::createBonusPicker(const HalloweenConfig& halloweenCfg)
{
	pumpkinColorPicker.emplace_back( BonusPicker{halloweenCfg.pumpkinsSeed} );
	pumpkinColorPicker.emplace_back( BonusPicker{halloweenCfg.pumpkinsSeed} );
	
	for( auto &picker : pumpkinColorPicker )
	{
		picker.setIteratorToBegin();
	}
}