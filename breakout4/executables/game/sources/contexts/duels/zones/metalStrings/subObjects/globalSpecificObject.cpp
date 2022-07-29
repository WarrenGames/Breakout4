#include "contexts/duels/zones/metalStrings/subObjects/globalSpecificObject.h"
#include "types/essentialsStruct.h"
#include "contexts/duels/instructions/objMoveWRectCollide.h"

duels::MetalStrings::MetalStrings(Essentials& essentials, const sdl2::Font& arial, duels::LevelOptions& levelOptions):
	zonesCommon{essentials, arial, std::vector<Offset>{Offset{SQR_SIZE*6, SQR_SIZE*6},Offset{SQR_SIZE*14, SQR_SIZE*9} }, levelOptions},
	stringDrawer{essentials, DUELS_DATA_FILE_PATH},
	inWayBarriers{essentials, std::vector<Offset>{{9*SQR_SIZE, metalStrings::TOP_BARR_Y_BACK}, {10*SQR_SIZE, metalStrings::BOTTOM_BARR_Y_BACK}} },
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
		{ 	metalStrings::isBlueRacketLeftNotBlockedByBarrier(zonesCommon.players.rackets[duels::PLAYER_BLUE].getRacketRect(),
																inWayBarriers.getRect(duels::PLAYER_RED)), 
			metalStrings::isRedRacketLeftNotBlockedByBarrier(zonesCommon.players.rackets[duels::PLAYER_RED].getRacketRect(),
																inWayBarriers.getRect(duels::PLAYER_BLUE)) },
		{ 	metalStrings::isBlueRacketRightNotBlockedByBarrier(zonesCommon.players.rackets[duels::PLAYER_BLUE].getRacketRect(),
																inWayBarriers.getRect(duels::PLAYER_RED)), 
			metalStrings::isRedRacketRightNotBlockedByBarrier(zonesCommon.players.rackets[duels::PLAYER_RED].getRacketRect(),
																inWayBarriers.getRect(duels::PLAYER_BLUE)) }, 
			{ false, false} );
	zonesCommon.resetScoresTextures(essentials.logs, essentials.rndWnd, arial, levelOptions);
	stringDrawer.updateAnimation();
	activateBarriersWithInputs();
	updateTopBarrier();
	updateBottomBarrier();
	switchData.updateAnimation();
	checkBarriersPositions(duels::PLAYER_BLUE, 
							inWayBarriers.getBarrierPosition(duels::PLAYER_BLUE).y <= metalStrings::TOP_BARR_Y_FORTH, 
							inWayBarriers.getBarrierPosition(duels::PLAYER_BLUE).y >= metalStrings::TOP_BARR_Y_BACK);
	checkBarriersPositions(duels::PLAYER_RED, 
							inWayBarriers.getBarrierPosition(duels::PLAYER_RED).y >= metalStrings::BOTTOM_BARR_Y_FORTH,
							inWayBarriers.getBarrierPosition(duels::PLAYER_RED).y <= metalStrings::BOTTOM_BARR_Y_BACK);
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
	for( unsigned player{0} ; player < duels::PLAYER_MAX ; ++player )
	{
		if( zonesCommon.players.playersInputs.getInputState(player, duels::INP_SPE_ZONE) 
			&& barriersData.barrierMoveType[player] == metalStrings::DIR_STOP 
			&& barriersData.forthBarriersPosition[player] != inWayBarriers.getBarrierPosition(player).y )
		{
			for( unsigned switchNum{0} ; switchNum < switchData.size() ; ++switchNum )
			{
				if( switchData.isPlayerOnSwitch(switchNum, zonesCommon.players.rackets[player].getRacketRect() ) )
				{
					moveBarrier(player, metalStrings::DIR_FORWARD);
					switchData.setSwitchsState(switchNum, metalStrings::DIR_FORWARD);
				}
			}
			zonesCommon.players.playersInputs.setInputState(player, duels::INP_SPE_ZONE);
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
	switch( barriersData.barrierMoveType[duels::PLAYER_BLUE] )
	{
		case metalStrings::DIR_FORWARD:
			moveUpBarrier(duels::PLAYER_BLUE);
			break;
		case metalStrings::DIR_REGRESS:
			moveDownBarrier(duels::PLAYER_BLUE);
			break;
		case metalStrings::DIR_STOP:
			stringDrawer.setBarrierActivity(duels::PLAYER_BLUE, metalStrings::DIR_STOP);
			break;
	}
}

void duels::MetalStrings::updateBottomBarrier()
{
	switch( barriersData.barrierMoveType[duels::PLAYER_RED] )
	{
		case metalStrings::DIR_FORWARD:
			moveDownBarrier(duels::PLAYER_RED);
			break;
		case metalStrings::DIR_REGRESS:
			moveUpBarrier(duels::PLAYER_RED);
			break;
		case metalStrings::DIR_STOP:
			stringDrawer.setBarrierActivity(duels::PLAYER_RED, metalStrings::DIR_STOP);
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
	if( barrierPrevent && barriersData.barrierMoveType[playerNum] == metalStrings::DIR_FORWARD )
	{
		barriersData.barrierMoveType[playerNum] = metalStrings::DIR_STOP;
		stringDrawer.setBarrierActivity(playerNum, metalStrings::DIR_STOP);
		barriersData.stopBeforeRegressDelay[playerNum].joinTimePoints();
	}
	else if( barrierPrevent && barriersData.barrierMoveType[playerNum] == metalStrings::DIR_STOP 
			&& barriersData.stopBeforeRegressDelay[playerNum].hasTimeElapsed( std::chrono::milliseconds{4000} ) )
	{
		barriersData.barrierMoveType[playerNum] = metalStrings::DIR_REGRESS;
		switchData.setPlayerSwitchState(playerNum, metalStrings::DIR_REGRESS);
		stringDrawer.setBarrierActivity(playerNum, metalStrings::DIR_REGRESS);
	}
	else if( barrierInInitialPosition && barriersData.barrierMoveType[playerNum] == metalStrings::DIR_REGRESS )
	{
		barriersData.barrierMoveType[playerNum] = metalStrings::DIR_STOP;
		stringDrawer.setBarrierActivity(playerNum, metalStrings::DIR_STOP);
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
	if( inWayBarriers.getBarrierPosition(duels::PLAYER_BLUE).y 
		== zonesCommon.players.rackets[duels::PLAYER_RED].getRacketRect().y 
		+ zonesCommon.players.rackets[duels::PLAYER_RED].getRacketRect().h 
		&& metalStrings::isRacketInWayOfBarrier(zonesCommon.players.rackets[duels::PLAYER_RED].getRacketRect(), inWayBarriers.getRect(duels::PLAYER_BLUE) ) )
	{
		moveBarrier(duels::PLAYER_BLUE, metalStrings::DIR_REGRESS);
		switchData.setSwitchsState(0, metalStrings::DIR_REGRESS);
	}
}

void duels::MetalStrings::makeBottomBarrierRegressDueToRacketInWay()
{
	if( inWayBarriers.getBarrierPosition(duels::PLAYER_RED).y
		+ inWayBarriers.getRect(duels::PLAYER_RED).h
		== zonesCommon.players.rackets[duels::PLAYER_BLUE].getRacketRect().y
		&& metalStrings::isRacketInWayOfBarrier(zonesCommon.players.rackets[duels::PLAYER_BLUE].getRacketRect(), inWayBarriers.getRect(duels::PLAYER_RED) ) )
	{
		moveBarrier(duels::PLAYER_RED, metalStrings::DIR_REGRESS);
		switchData.setSwitchsState(1, metalStrings::DIR_REGRESS);
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
