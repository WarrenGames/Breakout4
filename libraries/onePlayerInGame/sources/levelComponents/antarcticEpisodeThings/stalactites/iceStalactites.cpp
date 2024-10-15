#include "levelComponents/antarcticEpisodeThings//stalactites/iceStalactites.h"
#include "crossLevel/playerData.h"
#include "types/essentialsStruct.h"
#include "levelComponents/onePlayerRacket/onePlayerRacket.h"
#include "rectCollisions/rectLoader.h"
#include "stalactites/stalactitesDrawer.h"
#include "soundSystem/soundsPlayer.h"
#include "stalactites/stalactitesConsts.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/onePlayerSounds.h"
#include <cassert>

IceStalactitesElements::IceStalactitesElements(Essentials& essentials, std::vector< OnePlayerStalactiteData >& loadedData):
	elements{ std::move( loadedData ) },
	decal(SQR_SIZE / 4),
	freezeDurations{essentials, freezes::OnePlayerFilePath, onePlGame::SkillLevelMax }
{
	setDecalValues();
}

bool IceStalactitesElements::wasLoadingPerfect() const
{
	return freezeDurations;
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
														const SoundPlayer& soundPlayer)
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
				soundPlayer.playSoundOnGroup(onePlGame::SoundImpactWithDamage, onePlGame::GroupTagNewCoin);
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