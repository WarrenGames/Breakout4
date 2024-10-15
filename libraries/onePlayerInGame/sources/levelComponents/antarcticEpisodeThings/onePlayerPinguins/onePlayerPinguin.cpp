#include "levelComponents/antarcticEpisodeThings/onePlayerPinguins/onePlayerPinguin.h"
#include "levelComponents/antarcticEpisodeThings/onePlayerPinguins/pinguinsDataLoader.h"
#include "rectCollisions/brickGridCollisions.h"
#include "types/brickData.h"
#include "levelComponents/balls/ballsThings.h"
#include "soundSystem/soundsPlayer.h"
#include "rectCollisions/monsterCollisionsWithRect.h"
#include "rectCollisions/colObjMvCenterAndPosWithColRect.h"
#include "rectCollisions/activeWithStaticObjectCollision.h"
#include "levelComponents/demosObjects/antarcticDemoPackage.h"
#include "consts/constexprScreen.h"
#include "consts/singlePlayerDemoConsts.h"
#include "consts/onePlayerSounds.h"
#include <cassert>
#include <algorithm>

OnePlayerPinguin::OnePlayerPinguin(onePlGame::PinguinsDataLoader& dataLoader):
	tagNumber{0},
	collisionRect{ SQR_SIZE / 2, 10 * SQR_SIZE / 64, SQR_SIZE, SQR_SIZE * 2 - 20 * SQR_SIZE / 64 },
	neededHitsToRevokePinguin{10},
	hasMovedSince{true},
	isLoadingPerfect{true}
{
	for( auto &data : dataLoader )
	{
		pinguins.emplace_back( std::move( data ) );
	}
}

std::vector< PinguinBehaviorData >::const_iterator OnePlayerPinguin::begin() const
{
	return pinguins.cbegin();
}

std::vector< PinguinBehaviorData >::const_iterator OnePlayerPinguin::end() const
{
	return pinguins.cend();
}

std::size_t OnePlayerPinguin::size() const
{
	return pinguins.size();
}

void OnePlayerPinguin::activeOnePinguin(demos::DemoAntarcticPackage& antarcticPackage)
{
	if( antarcticPackage.demoKind == demos::GameHasPlayerInputs || antarcticPackage.demoKind == demos::GameIsRecording )
	{
		if( false == pinguins.empty() )
		{
			auto iter = std::find_if(pinguins.begin(), pinguins.end(), [](auto &ping){return PinguinIsInactive == ping.getState(); } );
			if( iter != std::end(pinguins) )
			{
				iter->activePinguin(tagNumber);
				recordPinguinCreationOrDestruction(antarcticPackage, true, *iter);
				++tagNumber;
			}
		}
	}
}

void OnePlayerPinguin::updateMove(demos::DemoAntarcticPackage& antarcticPackage)
{
	if( antarcticPackage.demoKind == demos::GameHasPlayerInputs || antarcticPackage.demoKind == demos::GameIsRecording )
	{
		if( moveTime.hasTimeElapsed( std::chrono::milliseconds{10} ) )
		{
			if( false == pinguins.empty() )
			{
				for( auto &ping : pinguins )
				{
					if( PinguinIsInactive != ping.getState() )
					{
						ping.movePinguin();
						recordPinguinMove(antarcticPackage, ping);
					}
				}
			}
			moveTime.joinTimePoints();
			hasMovedSince = true;
		}
	}
	else if( antarcticPackage.demoKind == demos::GameIsDemo )
	{
		placePinguinIfAny(antarcticPackage);
	}
}

void OnePlayerPinguin::updateAnim()
{
	if( false == pinguins.empty() )
	{
		for( auto &ping : pinguins )
		{
			if( PinguinIsInactive != ping.getState() )
			{
				ping.animPinguin();
			}
		}
	}
}

void OnePlayerPinguin::updateCollisions(const MatrixTemp2D<BrickData>& grid, const SDL_Rect& racketRect, demos::DemoAntarcticPackage& antarcticPackage)
{
	if( hasMovedSince )
	{
		browseForCollisions(collisionRect, grid);
		collisionWithRacket(racketRect, antarcticPackage);
		hasMovedSince = false;
	}
}

void OnePlayerPinguin::browseForCollisions(const SDL_Rect& collisionRect, const MatrixTemp2D<BrickData>& grid)
{
	if( false == pinguins.empty() )
	{
		for( auto &ping : pinguins )
		{
			if( PinguinIsActive == ping.getState() || PinguinStartMindPlayer == ping.getState() )
			{
				ping.getDrawingData().bounceOffScreenEdges(SQR_SIZE, collisionRect);
				bool wasThereACollision{false};
				testGridCollisions(grid, ping.getDrawingData().move, SpriteSize{collisionRect.w, collisionRect.h}, wasThereACollision );
				resetPinguinDirectionIfCollision(ping, wasThereACollision);
				
			}
		}
	}
}

void OnePlayerPinguin::resetPinguinDirectionIfCollision(PinguinBehaviorData& pinguin, bool wasThereCol)
{
	if( wasThereCol )
	{
		pinguin.getDrawingData().setDirection();
	}
}

void OnePlayerPinguin::collisionWithRacket(const SDL_Rect& racketRect, demos::DemoAntarcticPackage& antarcticPackage)
{
	if( false == pinguins.empty() )
	{
		for( auto &ping : pinguins )
		{
			if( PinguinIsActive == ping.getState() || PinguinStartMindPlayer == ping.getState() )
			{
				ping.resetRacketCollisionBooleans(racketRect, collisionRect );
				ping.makeBounceWithRacket(racketRect, collisionRect, antarcticPackage );
			}
		}
	}
}

void OnePlayerPinguin::makePinguinsQuack(const SDL_Rect& racketRect, bool playerLeftState, bool playerRightState, const SoundPlayer& soundPlayer, 
											demos::DemoAntarcticPackage& antarcticPackage)
{
	for( auto &ping : pinguins )
	{
		ping.makePinguinQuack(racketRect, collisionRect, playerLeftState, playerRightState, soundPlayer, antarcticPackage);
	}
}

void OnePlayerPinguin::withBallBouncing(BallThings& ballThings)
{
	assert( ballThings.monstersCollisionIsEffective.size() == pinguins.size() );
	for( std::size_t i{0} ; i < pinguins.size() ; ++i )
	{
		if( ( pinguins[i].getState() == PinguinIsActive || pinguins[i].getState() == PinguinStartMindPlayer ) 
			&& ballThings.monstersCollisionIsEffective[i] 
			&& collision::objMvAndSingleColRect::doCollide(ballThings.move, ballThings.getTexSize(), pinguins[i].getDrawingData().move, collisionRect, CollisionInterval) )
		{
			ballThings.monstersCollisionIsEffective[i] = false;
			collision::objMvAndSingleColRect::processBouncing(ballThings.move, pinguins[i].getDrawingData().move, collisionRect);
			pinguins[i].getDrawingData().setDirection();
		}
	}
}

void OnePlayerPinguin::resetBallBouncing(BallThings& ballThings)
{
	assert( ballThings.monstersCollisionIsEffective.size() == pinguins.size() );
	if( ballThings.canTestMonstersCollision )
	{
		for( std::size_t i{0} ; i < pinguins.size() ; ++i )
		{
			if( ( pinguins[i].getState() == PinguinIsActive || pinguins[i].getState() == PinguinStartMindPlayer ) 
				&& false == collision::objMvAndSingleColRect::doCollide(ballThings.move, ballThings.getTexSize(), pinguins[i].getDrawingData().move, collisionRect, 
									CollisionInterval + SQR_SIZE / 16 ) )
			{
				ballThings.monstersCollisionIsEffective[i] = true;
			}
		}
		ballThings.canTestMonstersCollision = false;
	}
}

bool OnePlayerPinguin::atLeastOnePinguinOnRacketLeft(const SDL_Rect& racketRect) const
{
	return std::any_of( std::cbegin(pinguins), std::cend(pinguins), 
		[&racketRect, this](const auto &ping)
		{ 
			if( ping.getState() == PinguinIsActive || ping.getState() == PinguinStartMindPlayer )
			{
				return collision::monsterIsOnLeftOfRacket(racketRect, collisionRect, ping.getDrawingData().move.getOffsetPosition(), CollisionInterval ); 
			}
			else{
				return false;
			}
		}
	);
}

bool OnePlayerPinguin::atLeastOnePinguinOnRacketRight(const SDL_Rect& racketRect) const
{
	return std::any_of( std::cbegin(pinguins), std::cend(pinguins),
		[&racketRect, this](const auto &ping)
		{ 
			if( ping.getState() == PinguinIsActive || ping.getState() == PinguinStartMindPlayer )
			{
				return collision::monsterIsOnRightOfRacket(racketRect, collisionRect, ping.getDrawingData().move.getOffsetPosition(), CollisionInterval );
			}
			else{
				return false;
			}
		}
		);
}

void OnePlayerPinguin::makePinguinsBounceWithRims(const SDL_Rect& rimRect, const SoundPlayer& soundPlayer)
{
	for( auto &pinguin : pinguins )
	{
		pinguin.makeBounceWithRimRect(rimRect, collisionRect, soundPlayer );
	}
}

void OnePlayerPinguin::setPinguinPathWithMouse(const Offset& mousePosition, bool mouseButtonState)
{
	for( auto &ping : pinguins )
	{
		ping.setPinguinPathWithMouse(mousePosition, mouseButtonState);
	}
}

void OnePlayerPinguin::playRecordedQuackSounds(demos::DemoAntarcticPackage& antarcticPackage, const SoundPlayer& soundPlayer)
{
	if( antarcticPackage.demoKind == demos::GameIsDemo )
	{
		while( antarcticPackage.pinguinsQuacks.getCommandsNumber() > 0 && antarcticPackage.pinguinsQuacks.hasLastTimeElapsed() )
		{
			soundPlayer.playSoundOnGroup( antarcticPackage.pinguinsQuacks.getLastElement().soundEnum, onePlGame::GroupTagEnemy);
			antarcticPackage.pinguinsQuacks.pop_back();
		}
	}
}

void OnePlayerPinguin::tryToMindPlayer(const SDL_Rect& racketRect)
{
	if( mindPlayerTime.hasTimeElapsed( std::chrono::milliseconds{1000} ) )
	{
		for( auto &ping : pinguins )
		{
			if( ping.isPinguinInsideScreen( collisionRect ) )
			{
				ping.startMindPlayer(racketRect, collisionRect );
			}
		}
		mindPlayerTime.joinTimePoints();
	}
}

void OnePlayerPinguin::revokePinguinIfHitEnough(demos::DemoAntarcticPackage& antarcticPackage)
{
	if( antarcticPackage.demoKind == demos::GameHasPlayerInputs || antarcticPackage.demoKind == demos::GameIsRecording )
	{
		for( auto &ping : pinguins )
		{
			if( ( ping.getState() == PinguinIsActive || ping.getState() == PinguinStartMindPlayer ) && ping.doesPinguinLeaveIfAny(neededHitsToRevokePinguin) )
			{
				recordPinguinCreationOrDestruction(antarcticPackage, false, ping);
			}
		}
	}
}

void OnePlayerPinguin::forcePinguinsToStayBesideRacket(const SDL_Rect& racketRect)
{
	for( auto &ping : pinguins )
	{
		ping.makeStayOnRacketLevelIfMindPlayer(racketRect);
	}
}

void OnePlayerPinguin::recordPinguinCreationOrDestruction(demos::DemoAntarcticPackage& antarcticPackage, bool action, const PinguinBehaviorData& ping) const
{
	if( antarcticPackage.demoKind == demos::GameIsRecording )
	{
		if( antarcticPackage.pinguinsCreateAndDestroy.getCommandsNumber() + 1 < antarcticPackage.pinguinsCreateAndDestroy.getCapacity() )
		{
			antarcticPackage.pinguinsCreateAndDestroy.emplaceElement(demos::ActionData{ 
			std::chrono::microseconds{ static_cast<long int>(antarcticPackage.pinguinsCreateAndDestroy.getElapsedMicroSecondsTime() ) },
			ping.getTagNumber(), action} );
		}
		else{
			antarcticPackage.pinguinsCreateAndDestroy.setSizeNotSufficientFlag();
		}
	}
}

void OnePlayerPinguin::recordPinguinMove(demos::DemoAntarcticPackage& antarcticPackage, const PinguinBehaviorData& ping)
{
	if( ping.getState() != PinguinIsInactive && antarcticPackage.demoKind == demos::GameIsRecording )
	{
		if( antarcticPackage.pinguinsPositions.getCommandsNumber() == 0 )
		{
			antarcticPackage.pinguinsPositions.emplaceElement(demos::TaggedPositionStackData{
				std::chrono::microseconds{ static_cast<long int>( antarcticPackage.pinguinsPositions.getElapsedMicroSecondsTime() ) }, 
				ping.getDrawingData().move.get_x_position(), ping.getDrawingData().move.get_y_position(), ping.getTagNumber() } );
		}
		else if( antarcticPackage.pinguinsPositions.getCommandsNumber() + 1 < antarcticPackage.pinguinsPositions.getCapacity() 
				&& antarcticPackage.pinguinsPositions.getCommandsNumber() > 0 ) 
		{
			if( ! ( antarcticPackage.pinguinsPositions.getLastElement().position.x == ping.getDrawingData().move.get_x_position()
				&& antarcticPackage.pinguinsPositions.getLastElement().position.y == ping.getDrawingData().move.get_y_position() ) )
			{
				antarcticPackage.pinguinsPositions.emplaceElement(demos::TaggedPositionStackData{
					std::chrono::microseconds{ static_cast<long int>( antarcticPackage.pinguinsPositions.getElapsedMicroSecondsTime() ) }, 
					ping.getDrawingData().move.get_x_position(), ping.getDrawingData().move.get_y_position(), ping.getTagNumber() } );
			}
		}
		else{
			antarcticPackage.pinguinsPositions.setSizeNotSufficientFlag();
		}
	}
}

void OnePlayerPinguin::placePinguinIfAny(demos::DemoAntarcticPackage& antarcticPackage)
{
	while( antarcticPackage.pinguinsPositions.getCommandsNumber() > 0 && antarcticPackage.pinguinsPositions.hasLastTimeElapsed() )
	{
		auto iter = std::find_if( pinguins.begin(), pinguins.end(), [&antarcticPackage](auto &ping){ 
								return ping.getTagNumber() == antarcticPackage.pinguinsPositions.getLastElement().itemTagNumber; } );
		if( iter != pinguins.end() )
		{
			iter->getDrawingData().move.setPosition( antarcticPackage.pinguinsPositions.getLastElement().position );
		}
		antarcticPackage.pinguinsPositions.pop_back();
	}
}

void OnePlayerPinguin::rotatePinguinIfAny(demos::DemoAntarcticPackage& antarcticPackage)
{
	if( antarcticPackage.demoKind == demos::GameIsDemo )
	{
		while( antarcticPackage.pinguinsDirection.getCommandsNumber() > 0 && antarcticPackage.pinguinsDirection.hasLastTimeElapsed() )
		{
			auto iter = std::find_if( pinguins.begin(), pinguins.end(), [&antarcticPackage](auto &ping){ 
								return ping.getTagNumber() == antarcticPackage.pinguinsDirection.getLastElement().itemTagNumber; } );
			if( iter != pinguins.end() )
			{
				iter->getDrawingData().direction = antarcticPackage.pinguinsDirection.getLastElement().direction;
			}
			antarcticPackage.pinguinsDirection.pop_back();
		}
	}
}

void OnePlayerPinguin::createOrDestroyPinguinsWithStack(demos::DemoAntarcticPackage& antarcticPackage)
{
	if( antarcticPackage.demoKind == demos::GameIsDemo )
	{
		while( antarcticPackage.pinguinsCreateAndDestroy.getCommandsNumber() > 0 && antarcticPackage.pinguinsCreateAndDestroy.hasLastTimeElapsed() )
		{
			if( antarcticPackage.pinguinsCreateAndDestroy.getLastElement().actionState )
			{
				auto iter = std::find_if(pinguins.begin(), pinguins.end(), [](auto const &ping){return PinguinIsInactive == ping.getState(); } );
				if( iter != std::end( pinguins ) )
				{
					iter->activePinguin( antarcticPackage.pinguinsCreateAndDestroy.getLastElement().funcEnum );
					++tagNumber;
				}
				else{
					assert( false && "Error: bad pinguin creating funcEnum with demo running." );
				}
			}
			else{
				auto iter = std::find_if(pinguins.begin(), pinguins.end(), [&antarcticPackage](auto const&ping)
										{
											return ( PinguinIsActive == ping.getState() || PinguinStartMindPlayer == ping.getState() )
											&& ping.getTagNumber() == antarcticPackage.pinguinsCreateAndDestroy.getLastElement().funcEnum; 
										} 
							);
				if( iter != std::end(pinguins) )
				{
					iter->setState(PinguinIsInactive);
				}
				else{
					//assert( false && "Error: bad pinguin destruction funcEnum with demo running." );
				}
			}
			antarcticPackage.pinguinsCreateAndDestroy.pop_back();
		}
	}
}

void OnePlayerPinguin::collisionWithPlayerRim(const SDL_Rect& rimRect)
{
	for( auto &pinguin : pinguins )
	{
		collision::activeAndStatic::processBouncing(pinguin.getDrawingData().move, collisionRect, rimRect);
		pinguin.getDrawingData().setDirection();
	}
}