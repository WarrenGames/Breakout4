#include "duels/zones/metalStrings/subObjects/globalSpecificObject.h"
#include "types/essentialsStruct.h"
#include "rectCollisions/objMoveWRectCollide.h"

duels::MetalStrings::MetalStrings(Essentials& essentials, const sdl2::Font& arial, duels::LevelOptions& levelOptions):
	zonesCommon{essentials, arial, std::vector<Offset>{Offset{SQR_SIZE*6, SQR_SIZE*6},Offset{SQR_SIZE*14, SQR_SIZE*9} }, levelOptions},
	stringDrawer{essentials, DuelsDataFilePath},
	inWayBarriers{essentials, std::vector<Offset>{{9*SQR_SIZE, metalStrings::TopBarY_Back}, {10*SQR_SIZE, metalStrings::BottomBarY_Back}} },
	bricks{essentials},
	switchData{bricks},
	steamPipe{essentials, Offset{SQR_SIZE, SQR_SIZE*2} }
{
	
}

duels::MetalStrings::operator bool() const
{
	return zonesCommon.wasLoadingPerfect() && stringDrawer && steamPipe;
}

void duels::MetalStrings::update(Essentials& essentials, const sdl2::Font& arial, duels::LevelOptions& levelOptions, bool& quitZone)
{
	zonesCommon.update(bricks.levelGrid, levelOptions, quitZone, 
		{ 	metalStrings::isBlueRacketLeftNotBlockedByBarrier(zonesCommon.players.rackets[duels::PlayerBlue].getRacketRect(),
																inWayBarriers.getRect(duels::PlayerRed)), 
			metalStrings::isRedRacketLeftNotBlockedByBarrier(zonesCommon.players.rackets[duels::PlayerRed].getRacketRect(),
																inWayBarriers.getRect(duels::PlayerBlue)) },
		{ 	metalStrings::isBlueRacketRightNotBlockedByBarrier(zonesCommon.players.rackets[duels::PlayerBlue].getRacketRect(),
																inWayBarriers.getRect(duels::PlayerRed)), 
			metalStrings::isRedRacketRightNotBlockedByBarrier(zonesCommon.players.rackets[duels::PlayerRed].getRacketRect(),
																inWayBarriers.getRect(duels::PlayerBlue)) }, 
			{ false, false} );
	zonesCommon.resetScoresTextures(essentials.logs, essentials.rndWnd, arial, levelOptions);
	stringDrawer.updateAnimation();
	activateBarriersWithInputs();
	updateTopBarrier();
	updateBottomBarrier();
	switchData.updateAnimation();
	checkBarriersPositions(duels::PlayerBlue, 
							inWayBarriers.getBarrierPosition(duels::PlayerBlue).y <= metalStrings::TopBarY_Forth, 
							inWayBarriers.getBarrierPosition(duels::PlayerBlue).y >= metalStrings::TopBarY_Back);
	checkBarriersPositions(duels::PlayerRed, 
							inWayBarriers.getBarrierPosition(duels::PlayerRed).y >= metalStrings::BottomBarY_Forth,
							inWayBarriers.getBarrierPosition(duels::PlayerRed).y <= metalStrings::BottomBarY_Back);
	testBarrierWithBallsAndCoinsCollisions();
	makeTopBarrierRegressDueToRacketInWay();
	makeBottomBarrierRegressDueToRacketInWay();
	steamPipe.update();
}

void duels::MetalStrings::drawEverything(Essentials& essentials)
{
	steamPipe.drawPipe(essentials);
	steamPipe.drawSteamSamples(essentials);
	bricks.drawZone(essentials, switchData);
	stringDrawer.drawAllStrings(essentials);
	zonesCommon.drawEverything(essentials.rndWnd);
	inWayBarriers.drawBarriers(essentials);
}

void duels::MetalStrings::activateBarriersWithInputs()
{
	for( unsigned player{0} ; player < duels::PlayerMax ; ++player )
	{
		if( zonesCommon.players.playersInputs.getInputState(player, duels::InputZoneSpecific) 
			&& barriersData.barrierMoveType[player] == metalStrings::DirectionStop 
			&& barriersData.forthBarriersPosition[player] != inWayBarriers.getBarrierPosition(player).y )
		{
			for( unsigned switchNum{0} ; switchNum < switchData.size() ; ++switchNum )
			{
				if( switchData.isPlayerOnSwitch(switchNum, zonesCommon.players.rackets[player].getRacketRect() ) )
				{
					moveBarrier(player, metalStrings::DirectionForward);
					switchData.setSwitchsState(switchNum, metalStrings::DirectionForward);
				}
			}
			zonesCommon.players.playersInputs.setInputState(player, duels::InputZoneSpecific);
		}
	}
}

void duels::MetalStrings::moveBarrier(unsigned playerNum, unsigned directionType)
{
	stringDrawer.setBarrierActivity(playerNum, directionType);
	barriersData.barrierMoveType[playerNum] = directionType;
}

void duels::MetalStrings::updateTopBarrier()
{
	switch( barriersData.barrierMoveType[duels::PlayerBlue] )
	{
		case metalStrings::DirectionForward:
			moveUpBarrier(duels::PlayerBlue);
			break;
		case metalStrings::DirectionRegress:
			moveDownBarrier(duels::PlayerBlue);
			break;
		case metalStrings::DirectionStop:
			stringDrawer.setBarrierActivity(duels::PlayerBlue, metalStrings::DirectionStop);
			break;
	}
}

void duels::MetalStrings::updateBottomBarrier()
{
	switch( barriersData.barrierMoveType[duels::PlayerRed] )
	{
		case metalStrings::DirectionForward:
			moveDownBarrier(duels::PlayerRed);
			break;
		case metalStrings::DirectionRegress:
			moveUpBarrier(duels::PlayerRed);
			break;
		case metalStrings::DirectionStop:
			stringDrawer.setBarrierActivity(duels::PlayerRed, metalStrings::DirectionStop);
			break;
	}
}

void duels::MetalStrings::moveUpBarrier(std::size_t playerNum)
{
	if( barriersData.moveDelay[playerNum].hasTimeElapsed( std::chrono::milliseconds{10} ) )
	{
		inWayBarriers.moveUpBarrier(playerNum);
		barriersData.moveDelay[playerNum].joinTimePoints();
	}
}

void duels::MetalStrings::moveDownBarrier(std::size_t playerNum)
{
	if( barriersData.moveDelay[playerNum].hasTimeElapsed( std::chrono::milliseconds{10} ) )
	{
		inWayBarriers.moveDownBarrier(playerNum);
		barriersData.moveDelay[playerNum].joinTimePoints();
	}
}

void duels::MetalStrings::checkBarriersPositions(std::size_t playerNum, bool barrierPrevent, bool barrierInInitialPosition)
{
	if( barrierPrevent && barriersData.barrierMoveType[playerNum] == metalStrings::DirectionForward )
	{
		barriersData.barrierMoveType[playerNum] = metalStrings::DirectionStop;
		stringDrawer.setBarrierActivity(playerNum, metalStrings::DirectionStop);
		barriersData.stopBeforeRegressDelay[playerNum].joinTimePoints();
	}
	else if( barrierPrevent && barriersData.barrierMoveType[playerNum] == metalStrings::DirectionStop 
			&& barriersData.stopBeforeRegressDelay[playerNum].hasTimeElapsed( std::chrono::milliseconds{4000} ) )
	{
		barriersData.barrierMoveType[playerNum] = metalStrings::DirectionRegress;
		switchData.setPlayerSwitchState(playerNum, metalStrings::DirectionRegress);
		stringDrawer.setBarrierActivity(playerNum, metalStrings::DirectionRegress);
	}
	else if( barrierInInitialPosition && barriersData.barrierMoveType[playerNum] == metalStrings::DirectionRegress )
	{
		barriersData.barrierMoveType[playerNum] = metalStrings::DirectionStop;
		stringDrawer.setBarrierActivity(playerNum, metalStrings::DirectionStop);
	}
}

void duels::MetalStrings::testBarrierWithBallsAndCoinsCollisions()
{
	for( std::size_t barrierNum{0} ; barrierNum < inWayBarriers.size() ; ++barrierNum )
	{
		zonesCommon.balls.checkCollisionWithRect(inWayBarriers.getRect(barrierNum), barriersData.canBallCollideWithBarrier);
		zonesCommon.coins.checkCollisionWithRect(inWayBarriers.getRect(barrierNum), barriersData.canCoinCollideWithBarrier);
	}
}

void duels::MetalStrings::makeTopBarrierRegressDueToRacketInWay()
{
	if( inWayBarriers.getBarrierPosition(duels::PlayerBlue).y 
		== zonesCommon.players.rackets[duels::PlayerRed].getRacketRect().y 
		+ zonesCommon.players.rackets[duels::PlayerRed].getRacketRect().h 
		&& metalStrings::isRacketInWayOfBarrier(zonesCommon.players.rackets[duels::PlayerRed].getRacketRect(), inWayBarriers.getRect(duels::PlayerBlue) ) )
	{
		moveBarrier(duels::PlayerBlue, metalStrings::DirectionRegress);
		switchData.setSwitchsState(0, metalStrings::DirectionRegress);
	}
}

void duels::MetalStrings::makeBottomBarrierRegressDueToRacketInWay()
{
	if( inWayBarriers.getBarrierPosition(duels::PlayerRed).y
		+ inWayBarriers.getRect(duels::PlayerRed).h
		== zonesCommon.players.rackets[duels::PlayerBlue].getRacketRect().y
		&& metalStrings::isRacketInWayOfBarrier(zonesCommon.players.rackets[duels::PlayerBlue].getRacketRect(), inWayBarriers.getRect(duels::PlayerRed) ) )
	{
		moveBarrier(duels::PlayerRed, metalStrings::DirectionRegress);
		switchData.setSwitchsState(1, metalStrings::DirectionRegress);
	}
}

bool metalStrings::isRacketInWayOfBarrier(const SDL_Rect& racket, const SDL_Rect& barrier)
{
	return racket.x + racket.w >= barrier.x && racket.x < barrier.x + barrier.w;
}

bool metalStrings::isBlueRacketLeftNotBlockedByBarrier(const SDL_Rect& racket, const SDL_Rect& barrier)
{
	return ! ( racket.x < barrier.x + barrier.w && racket.x > barrier.x + barrier.w - SQR_SIZE / 2
		&& barrier.y + barrier.h > racket.y );
}

bool metalStrings::isBlueRacketRightNotBlockedByBarrier(const SDL_Rect& racket, const SDL_Rect& barrier)
{
	return ! ( racket.x + racket.w > barrier.x && racket.x + racket.w < barrier.x + SQR_SIZE / 2
		&& barrier.y + barrier.h > racket.y );
}

bool metalStrings::isRedRacketLeftNotBlockedByBarrier(const SDL_Rect& racket, const SDL_Rect& barrier)
{
	return ! ( racket.x < barrier.x + barrier.w && racket.x > barrier.x + barrier.w - SQR_SIZE / 2
		&& barrier.y < racket.y + racket.h );
}

bool metalStrings::isRedRacketRightNotBlockedByBarrier(const SDL_Rect& racket, const SDL_Rect& barrier)
{
	return ! ( racket.x + racket.w > barrier.x && racket.x + racket.w < barrier.x + SQR_SIZE / 2
		&& barrier.y < racket.y + racket.h );
}
