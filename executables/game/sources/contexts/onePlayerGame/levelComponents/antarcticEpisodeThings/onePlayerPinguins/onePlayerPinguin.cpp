#include "contexts/onePlayerGame/levelComponents/antarcticEpisodeThings/onePlayerPinguins/onePlayerPinguin.h"
#include "contexts/gameCommon/rectCollisions/brickGridCollisions.h"
#include "types/brickData.h"
#include "types/essentialsStruct.h"
#include "crossLevel/playerData.h"
#include "contexts/onePlayerGame/levelComponents/balls/ballsThings.h"
#include "generic/sounds/soundHandler.h"
#include "contexts/gameCommon/rectCollisions/monsterCollisionsWithRect.h"
#include "contexts/gameCommon/rectCollisions/processBouncing.h"
#include "contexts/gameCommon/pinguins/pinguinConsts.h"
#include "consts/constexprScreen.h"
#include "consts/onePlayerLevelConsts.h"
#include <sstream>
#include <string>
#include <cassert>
#include <algorithm>

constexpr char PinguinRevokeFile[] = "data/levels/1player/options/pinguinRevoke.cfg";

OnePlayerPinguin::OnePlayerPinguin(Essentials& essentials, const PlayerData& playerData):
	
	collisionRect{ SQR_SIZE / 2, 10 * SQR_SIZE / 64, SQR_SIZE, SQR_SIZE * 2 - 20 * SQR_SIZE / 64 },
	neededHitsToRevokePinguin{10},
	hasMovedSince{true},
	isLoadingPerfect{true}
{
	loadDataFile(essentials.logs, playerData.getMonstersFilePath() );
	loadNeededHitsData(essentials.logs, playerData.skillLevel);
}

std::vector< PinguinBehaviorData >::const_iterator OnePlayerPinguin::begin() const
{
	return pinguins.cbegin();
}

std::vector< PinguinBehaviorData >::const_iterator OnePlayerPinguin::end() const
{
	return pinguins.cend();
}

bool OnePlayerPinguin::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

void OnePlayerPinguin::loadDataFile(AppLogFiles& logs, const std::string& levelDataFilePath)
{
	if( std::ifstream dataFile{ levelDataFilePath } )
	{
		std::string fileLine;
		unsigned lineIndex{0};
		while( std::getline( dataFile, fileLine ) )
		{
			std::istringstream lineStream{fileLine};
			readSingleLine(logs, levelDataFilePath, lineStream, lineIndex);
		}
	}
	else{
		logs.error << "Error: couldn't open '" << levelDataFilePath << "' data file.\n";
		isLoadingPerfect = false;
	}
}

void OnePlayerPinguin::readSingleLine(AppLogFiles& logs, const std::string& levelDataFilePath, std::istringstream& lineStream, unsigned lineIndex)
{
	if( lineStream >> lineIndex )
	{
		switch( lineIndex )
		{
			case pinguin::fileIndex::NewPinguin:
				loadPinguinData(logs, levelDataFilePath, lineStream);
				break;
			default:
				logs.error << "Error: unknown 'line index' in '" << levelDataFilePath << "' file: " << lineIndex << " .\n";
				isLoadingPerfect = false;
				break;
		}
	}
	else{
		logs.error << "Error: couldn't read index in '" << levelDataFilePath << "' file.\n";
		isLoadingPerfect = false;
	}
}

void OnePlayerPinguin::loadPinguinData(AppLogFiles& logs, const std::string& levelDataFilePath, std::istringstream& lineStream)
{
	Offset startPos;
	Offset dirVectors;
	double speed;
	if( lineStream >> startPos.x >> startPos.y >> dirVectors.x >> dirVectors.y >> speed )
	{
		pinguins.emplace_back( PinguinBehaviorData{ AccurCoords{static_cast<double>(startPos.x * SQR_SIZE), 
																static_cast<double>(startPos.y * SQR_SIZE) }, 
																speed, 
																dirVectors } );
	}
	else{
		logs.error << "Error: while loading pinguin data in '" << levelDataFilePath << "' file.\n";
		isLoadingPerfect = false;
	}
}

void OnePlayerPinguin::loadNeededHitsData(AppLogFiles& logs, unsigned skillLevel)
{
	if( std::ifstream pinguinTolerance{PinguinRevokeFile} )
	{
		std::vector<unsigned> hits(onePlGame::SkillLevelMax);
		for( auto &number : hits )
		{
			if( !( pinguinTolerance >> number ) )
			{
				isLoadingPerfect = false;
				logs.error << "Error: reading data in '" << PinguinRevokeFile << "' file failed (probably there not enough data; " 
						 << onePlGame::SkillLevelMax << " of them are needed.\n";
			}
		}
		assert( static_cast<unsigned>(skillLevel) < hits.size() );
		neededHitsToRevokePinguin = hits[skillLevel];
		logs.error << "Hits needed: " << neededHitsToRevokePinguin << " .\n";
		
	}
	else{
		isLoadingPerfect = false;
		logs.error << "Error: couldn't load '" << PinguinRevokeFile << "' in order to load data relative to pinguin tolerance.\n";
	}
}

std::size_t OnePlayerPinguin::size() const
{
	return pinguins.size();
}

void OnePlayerPinguin::activeOnePinguin()
{
	if( false == pinguins.empty() )
	{
		auto iter = std::find_if(pinguins.begin(), pinguins.end(), [](auto &ping){return PinguinIsInactive == ping.getState(); } );
		if( iter != std::end(pinguins) )
		{
			iter->activePinguin();
		}
	}
}

void OnePlayerPinguin::update(const MatrixTemp2D<BrickData>& grid, const SDL_Rect& racketRect, bool playerLeftState, bool playerRightState, const SoundHandler& sounds)
{
	updateMove();
	updateAnim();
	updateCollisions(grid, racketRect);
	makePinguinsQuack(racketRect, playerLeftState, playerRightState, sounds);
	tryToMindPlayer(racketRect);
	revokePinguinIfHitEnough();
	forcePinguinsToStayBesideRacket(racketRect);
	resetPinguinStatusIfOffscreen();
}

void OnePlayerPinguin::updateMove()
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
				}
			}
		}
		moveTime.joinTimePoints();
		hasMovedSince = true;
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

void OnePlayerPinguin::updateCollisions(const MatrixTemp2D<BrickData>& grid, const SDL_Rect& racketRect)
{
	if( hasMovedSince )
	{
		browseForCollisions(collisionRect, grid);
		collisionWithRacket(racketRect);
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

void OnePlayerPinguin::collisionWithRacket(const SDL_Rect& racketRect)
{
	if( false == pinguins.empty() )
	{
		for( auto &ping : pinguins )
		{
			if( PinguinIsActive == ping.getState() || PinguinStartMindPlayer == ping.getState() )
			{
				ping.resetRacketCollisionBooleans(racketRect, collisionRect );
				ping.makeBounceWithRacket(racketRect, collisionRect );
			}
		}
	}
}

void OnePlayerPinguin::makePinguinsQuack(const SDL_Rect& racketRect, bool playerLeftState, bool playerRightState, const SoundHandler& sounds)
{
	for( auto &ping : pinguins )
	{
		ping.makePinguinQuack(racketRect, collisionRect, playerLeftState, playerRightState, sounds);
	}
}

void OnePlayerPinguin::withBallBouncing(BallThings& ballThings)
{
	assert( ballThings.monstersCollisionIsEffective.size() == pinguins.size() );
	for( std::size_t i{0} ; i < pinguins.size() ; ++i )
	{
		if( ballThings.monstersCollisionIsEffective[i] && bouncing::objectsCollide( ballThings.move, ballThings.getTexSize(), pinguins[i].getDrawingData().move, 
																					SpriteSize{collisionRect.w, collisionRect.h}, 0) )
		{
			ballThings.monstersCollisionIsEffective[i] = false;
			bouncing::processElementsBouncing(ballThings.move, pinguins[i].getDrawingData().move, SpriteSize{collisionRect.w, collisionRect.h} );
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
			if( false == bouncing::objectsCollide(ballThings.move, ballThings.getTexSize(), pinguins[i].getDrawingData().move, SpriteSize{collisionRect.w, collisionRect.h}, SQR_SIZE / 8 ) )
			{
				ballThings.monstersCollisionIsEffective[i] = true;
			}
		}
		ballThings.canTestMonstersCollision = false;
	}
}

bool OnePlayerPinguin::atLeastOnePinguinOnRacketLeft(const SDL_Rect& racketRect) const
{
	return std::any_of(pinguins.cbegin(), pinguins.cend(), 
		[&racketRect, this](const auto &ping){ return collision::monsterIsOnLeftOfRacket(racketRect, collisionRect, ping.getDrawingData().move.getOffsetPosition() ); } );
}

bool OnePlayerPinguin::atLeastOnePinguinOnRacketRight(const SDL_Rect& racketRect) const
{
	return std::any_of(pinguins.cbegin(), pinguins.cend(), 
		[&racketRect, this](const auto &ping){ return collision::monsterIsOnRightOfRacket(racketRect, collisionRect, ping.getDrawingData().move.getOffsetPosition() ); } );
}

void OnePlayerPinguin::makePinguinsBounceWithRims(const SDL_Rect& rimRect, const SoundHandler& sounds)
{
	for( auto &pinguin : pinguins )
	{
		pinguin.makeBounceWithRimRect(rimRect, collisionRect, sounds );
	}
}

void OnePlayerPinguin::setPinguinPathWithMouse(const Offset& mousePosition, bool mouseButtonState)
{
	for( auto &ping : pinguins )
	{
		ping.setPinguinPathWithMouse(mousePosition, mouseButtonState);
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

void OnePlayerPinguin::revokePinguinIfHitEnough()
{
	for( auto &ping : pinguins )
	{
		ping.makePinguinLeaveIfAny(neededHitsToRevokePinguin);
	}
}

void OnePlayerPinguin::forcePinguinsToStayBesideRacket(const SDL_Rect& racketRect)
{
	for( auto &ping : pinguins )
	{
		ping.makeStayOnRacketLevelIfMindPlayer(racketRect);
	}
}

void OnePlayerPinguin::resetPinguinStatusIfOffscreen()
{
	for( auto &ping : pinguins )
	{
		if( false == ping.isPinguinInsideScreen(collisionRect ) && PinguinIsLeaving == ping.getState() )
		{
			ping.setState(PinguinIsInactive);
		}
	}
}