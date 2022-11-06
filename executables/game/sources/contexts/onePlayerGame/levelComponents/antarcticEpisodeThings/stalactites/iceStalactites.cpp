#include "contexts/onePlayerGame/levelComponents/antarcticEpisodeThings//stalactites/iceStalactites.h"
#include "crossLevel/playerData.h"
#include "contexts/onePlayerGame/levelComponents/onePlayerRacket/onePlayerRacket.h"
#include "contexts/gameCommon/rectCollisions/rectLoader.h"
#include "contexts/gameCommon/stalactites/stalactitesDrawer.h"
#include "generic/sounds/soundHandler.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include "consts/onePlayerLevelConsts.h"
#include "contexts/gameCommon/stalactites/stalactitesConsts.h"
#include <fstream>
#include <string>
#include <sstream>
#include <bitset>
#include <cassert>

IceStalactitesElements::IceStalactitesElements(Essentials& essentials, const PlayerData& playerData):
	decal(SQR_SIZE / 4),
	freezeDurations{essentials, freezes::OnePlayerFilePath, onePlGame::SkillLevelMax },
	isLoadingPerfect{true}
{
	setDecalValues();
	loadStalactitesConfig(essentials, playerData);
	logEverythingWentFine(essentials, playerData);
}

bool IceStalactitesElements::wasLoadingPerfect() const
{
	return isLoadingPerfect && freezeDurations;
}

void IceStalactitesElements::updateStalactites(const StalactitesDrawer& drawer, const RectLoader& rects)
{
	for( auto &stal : elements )
	{
		switch( stal.commonData.getState() )
		{
			case stalactites::StateStatic:
				stal.startRumble();
				break;
			case stalactites::StateRumble:
				stal.commonData.startFallingIfRumbleEnds();
				break;
			case stalactites::StateFalling:
				stal.discardFallingIfOffscreen(	rects.getRect( stal.commonData.getDirection() ),
												drawer.getWidth(stal.commonData.getDirection() ), 
												drawer.getHeight(stal.commonData.getDirection() ) );
				break;
			case stalactites::StateOut:
				stal.resetToWaitingState(	rects.getRect(stal.commonData.getDirection() ),
											drawer.getWidth(stal.commonData.getDirection() ), 
											drawer.getHeight(stal.commonData.getDirection() ) );
				break;
			default:
				assert( false && "Error: wrong stalactite state !" );
				break;
		}
	}
}

void IceStalactitesElements::updateStalactitesTimers()
{
	updateRumble();
	updateFall();
}

void IceStalactitesElements::testCollisionsWithRacket(OnePlayerRacket& playerRacket, const StalactitesDrawer& drawer, const RectLoader& rects, const PlayerData& playerData, 
														const SoundHandler& sounds)
{
	assert( playerData.skillLevel < freezeDurations.size() );
	for( auto &stal : elements )
	{
		if( stal.commonData.doesCollideWithRacket(playerRacket.rect, 
									Offset{ drawer.getWidth(stal.commonData.getDirection() ),
									drawer.getHeight(stal.commonData.getDirection() ) }, 
									rects.getRect(stal.commonData.getDirection() ) ) )
		{
			
			if( playerRacket.data.canBeFreezed() && stalactites::StateFalling == stal.commonData.getState() )
			{
				sounds.playSound(onePlGame::SoundImpactWithDamage);
				stal.resetToStart();
				playerRacket.data.startFreeze( std::chrono::milliseconds{freezeDurations.getDuration(playerData.skillLevel) } );
			}
		}
	}
}

std::vector< OnePlayerStalactiteData >::const_iterator IceStalactitesElements::begin() const
{
	return elements.cbegin();
}

std::vector< OnePlayerStalactiteData >::const_iterator IceStalactitesElements::end() const
{
	return elements.cend();
}

void IceStalactitesElements::setDecalValues()
{
	for( std::size_t i{0} ; i < decal.size() ; ++i )
	{
		if( i >= decal.size() / 4 && i < decal.size() * 3 / 4 )
		{
			decal[i] = -1;
		}
		else{
			decal[i] = 1;
		}
	}
}

void IceStalactitesElements::loadStalactitesConfig(Essentials& essentials, const PlayerData& playerData)
{
	if( std::ifstream stalactiteFile{ playerData.getElementsFilePath() } )
	{
		unsigned lineNum{1};
		std::string fileLine;
		while( std::getline(stalactiteFile, fileLine) )
		{
			std::istringstream lineStream{fileLine};
			loadSingleStalactite(essentials, playerData, lineStream, lineNum);
			lineNum++;
		}
	}
	else{
		essentials.logs.error << "Error: couldn't load '" << playerData.getElementsFilePath() << "' file in order to load stalactites data.\n";
		isLoadingPerfect = false;
	}
}

void IceStalactitesElements::loadSingleStalactite(Essentials& essentials, const PlayerData& playerData, std::istringstream& lineStream, unsigned lineNum)
{
	unsigned totalWaitTime{0};
	unsigned randomTime{0};
	AccurCoords squareUintPos;
	unsigned skillUint{0};
	unsigned pauseTime{0};
	if( lineStream >> skillUint >> squareUintPos.x >> squareUintPos.y >> totalWaitTime >> randomTime >> pauseTime )
	{
		std::bitset<onePlGame::SkillLevelMax> skillBitset{skillUint};
		if( skillBitset[playerData.skillLevel] )
		{
			elements.emplace_back( OnePlayerStalactiteData{totalWaitTime, randomTime, pauseTime, 
						Offset{	static_cast<int>( squareUintPos.x * SQR_SIZE ), 
								static_cast<int>( squareUintPos.y * SQR_SIZE ) } } );
		}
	}
	else{
		essentials.logs.error << "Error: loading stalactite element for one player game failed at line #" << lineNum << " \n";
		isLoadingPerfect = false;
	}
}

void IceStalactitesElements::logEverythingWentFine(Essentials& essentials, const PlayerData& playerData) const
{
	if( isLoadingPerfect )
	{
		essentials.logs.error << ">> " << elements.size() << " stalactites total were loaded for one player game with ";
		switch( playerData.skillLevel )
		{
			case onePlGame::SkillLevelEasy:
				essentials.logs.error << " easy skill.";
				break;
			case onePlGame::SkillLevelIntermediate:
				essentials.logs.error << " intermediate skill.";
				break;
			case onePlGame::SkillLevelHard:
				essentials.logs.error << " hard skill.";
				break;
		}
		essentials.logs.error.flushLog();
	}
}

void IceStalactitesElements::updateRumble()
{
	if( rumbleDelay.hasTimeElapsed( std::chrono::milliseconds{stalactites::RumbleAnimDelay} ) )
	{
		for( auto &stal : elements )
		{
			stal.commonData.rumble( decal );
		}
		rumbleDelay.joinTimePoints();
	}
}

void IceStalactitesElements::updateFall()
{
	if( moveDelay.hasTimeElapsed( std::chrono::milliseconds{stalactites::FallSpeedDelay} ) )
	{
		for( auto &stal : elements )
		{
			stal.commonData.makeFalling();
		}
		moveDelay.joinTimePoints();
	}
}