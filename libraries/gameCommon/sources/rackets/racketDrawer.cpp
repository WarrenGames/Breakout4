#include "rackets/racketDrawer.h"
#include "texturing/rendererWindow.h"
#include "logging/logsStruct.h"
#include "consts/duelsConstexpr.h"
#include <cassert>
#include <algorithm>

RacketDrawer::RacketDrawer(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned playerType):
	isLoadingPerfect{ true }
{
	loadRacket(logs, rndWnd, playerType);
	fillWidthData(logs);
	browseTexturesForErrors();
}

bool RacketDrawer::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

void RacketDrawer::browseTexturesForErrors()
{
	isLoadingPerfect = std::all_of(racketTextures.cbegin(), racketTextures.cend(), 
										[]( auto const& texture){ return texture.texture.wasLoadingPerfect(); } );
}

void RacketDrawer::loadRacket(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned playerType)
{
	switch( playerType )
	{
		case RacketIsBlue:
			loadRacketTextures(logs, rndWnd, "blue");
			break;
		case RacketIsRed:
			loadRacketTextures(logs, rndWnd, "red");
			break;
		case RacketIsGreen:
			loadRacketTextures(logs, rndWnd, "green");
			break;
		case FrozenBlueRacket:
			loadFrozenBlueRacket(logs, rndWnd);
			break;
		default:
			assert( "Wrong racket enum" && false );
			break;
	}
}

void RacketDrawer::loadFrozenBlueRacket(AppLogFiles& logs, sdl2::RendererWindow& rndWnd)
{
	for( std::size_t i{0} ; i < duels::RacketMax ; ++i )
	{
		racketTextures.emplace_back( TextureCombo{logs, rndWnd, "textures/sprites/rackets/frozen_blue_racket_" + std::to_string(i) + ".png"} );
	}
}

void RacketDrawer::loadRacketTextures(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& textureSuffix)
{
	for( std::size_t i{0} ; i < duels::RacketMax ; ++i )
	{
		racketTextures.emplace_back(TextureCombo{logs, rndWnd, "textures/sprites/rackets/racket_" + textureSuffix + "_" + std::to_string(i) + ".png"} );
	}
}

void RacketDrawer::fillWidthData(AppLogFiles& logs)
{
	if( racketTextures.size() > 0 )
	{
		for( const auto &tex : racketTextures )
		{
			racketWidth.emplace_back(tex.sprite.width() );
		}
	}
	else{
		logs.error << "Error: there is a wrong number of loaded rackets textures for the duels: " << racketTextures.size() << " .\n";
		isLoadingPerfect = false;
	}
}

int RacketDrawer::getWidth(std::size_t index) const
{
	if( index < racketWidth.size() )
	{
		if( racketTextures[index].texture )
		{
			return racketWidth[index];
		}
	}
	return 0;
}

int RacketDrawer::getHeight(std::size_t index) const
{
	if( index < racketTextures.size() )
	{
		if( racketTextures[index].texture )
		{
			return racketTextures[index].sprite.height();
		}
	}
	return 0;
}

void RacketDrawer::drawRacket(sdl2::RendererWindow& rndWnd, std::size_t racketSize, const Offset& racketPos)
{
	assert( racketSize < racketTextures.size() );
	racketTextures[racketSize].draw(rndWnd, racketPos.x, racketPos.y);
}