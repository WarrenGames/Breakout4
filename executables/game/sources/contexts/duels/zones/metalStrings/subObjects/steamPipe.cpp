#include "contexts/duels/zones/metalStrings/subObjects/steamPipe.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "consts/constexprScreen.h"
#include <algorithm>

constexpr std::size_t SteamFramesNumber = 24;

SteamPipe::SteamPipe(Essentials& essentials, const Offset& pipePosition):
	isLoadingPerfect{true},
	steamPipe{essentials.logs, essentials.rndWnd, "textures/gameZones/factory/backgrounds/pipe_0.png", TexturePosition{pipePosition} },
	steamSamples(4)
{
	loadSteamAnimation(essentials);
	if( false == steamPipe.texture )
	{
		isLoadingPerfect = false;
	}
}

SteamPipe::operator bool() const
{
	return isLoadingPerfect;
}

void SteamPipe::update()
{
	animateSteamClouds();
	moveSteamClouds();
	revokeOutdoorsClouds();
	createNewSteamCloud();
}

void SteamPipe::drawPipe(Essentials& essentials) const
{
	steamPipe.draw(essentials.rndWnd);
}

void SteamPipe::drawSteamSamples(Essentials& essentials)
{
	for( auto const &sample : steamSamples )
	{
		if( sample )
		{
			steamAnim[sample->frameNum].drawToCenter(essentials.rndWnd, sample->moveSample.get_x_position(), sample->moveSample.get_y_position() );
		}
	}
}

void SteamPipe::loadSteamAnimation(Essentials& essentials)
{
	for( std::size_t i{0} ; i < SteamFramesNumber ; ++i )
	{
		TextureCombo texture{essentials.logs, essentials.rndWnd, "textures/gameZones/factory/steamAnim/steam_" + std::to_string(i) + ".png"};
		if( texture.texture )
		{
			steamAnim.emplace_back( std::move(texture) );
		}
		else{
			isLoadingPerfect = false;
		}
	}
}

void SteamPipe::animateSteamClouds()
{
	if( steamAnimDelay.hasTimeElapsed( std::chrono::milliseconds{110} ) )
	{
		for( auto &sample : steamSamples )
		{
			if( sample )
			{
				sample->anim( steamAnim.size(), false );
			}
		}
		steamAnimDelay.joinTimePoints();
	}
}

void SteamPipe::moveSteamClouds()
{
	for( auto &sample : steamSamples )
	{
		if( sample )
		{
			sample->move(10);
		}
	}
}

void SteamPipe::revokeOutdoorsClouds()
{
	for( auto &sample : steamSamples )
	{
		if( sample )
		{
			if( sample->moveSample.get_y_position() <= -SQR_SIZE )
			{
				sample.reset();
			}
		}
	}
}

void SteamPipe::createNewSteamCloud()
{
	if( createDelay.hasTimeElapsed( std::chrono::milliseconds{5000} ) )
	{
		const auto iter = std::find(steamSamples.begin(), steamSamples.end(), nullptr );
		if( iter != std::end( steamSamples ) )
		{
			iter->reset( new SteamSample{AccurCoords{static_cast<double>(steamPipe.sprite.x_pos()) + 108, static_cast<double>(steamPipe.sprite.y_pos()) + 130}, 1, Offset{ 0, -1} } );
		}
		createDelay.joinTimePoints();
	}
}