#include "contexts/gameCommon/explosions/explosionLoader.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include <sstream>
#include <algorithm>
#include <cassert>

constexpr char ExplosionConfigFilePath[] = "data/explosions/explosions";
constexpr char ExplosionTexturesDirectory[] = "textures/sprites/explosions/";

ExplosionChunk::ExplosionChunk(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned texturesNumber, const std::string& fileBase, unsigned frameDuration_, unsigned zenithImage_):
	textures{logs, rndWnd, texturesNumber, fileBase},
	frameDuration{frameDuration_},
	zenithImage{zenithImage_}
{
	
}

ExplosionsLoader::ExplosionsLoader():
	isLoadingPerfect{true}
{
	
}

ExplosionsLoader::ExplosionsLoader(AppLogFiles& logs, sdl2::RendererWindow& rndWnd):
	isLoadingPerfect{true}
{
	openConfigFile(logs, rndWnd);
}

std::size_t ExplosionsLoader::size() const
{
	return explosionsTextures.size();
}

const ExplosionChunk& ExplosionsLoader::operator[](std::size_t index) const
{
	assert( index < explosionsTextures.size() );
	return explosionsTextures[index];
}

bool ExplosionsLoader::wasLoadingPerfect() const
{
	return isLoadingPerfect && std::all_of( std::cbegin( explosionsTextures ), std::cend( explosionsTextures ), [](auto &singleExplo){ return singleExplo.textures.wasLoadingPerfect(); } );
}

void ExplosionsLoader::openConfigFile(AppLogFiles& logs, sdl2::RendererWindow& rndWnd)
{
	if( std::ifstream mainReferenceExplosionFile{ExplosionConfigFilePath} )
	{
		std::string referenceLine;
		while(std::getline(mainReferenceExplosionFile, referenceLine) )
		{
			loadEntityExplosion(logs, rndWnd, referenceLine);
		}
	}
	else
	{
		logs.error.wrFileOpeningError(ExplosionConfigFilePath, "load explosions textures");
		isLoadingPerfect = false;
	}
}

void ExplosionsLoader::loadEntityExplosion(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& referenceLine)
{
	std::string filePrefix;
	unsigned imagesNumber{0};
	unsigned zenithImage{0};
	unsigned frameDuration;
	std::istringstream fluxInput{referenceLine};

	if( fluxInput >> filePrefix >> imagesNumber >> frameDuration >> zenithImage )
	{
		explosionsTextures.emplace_back( ExplosionChunk{logs, rndWnd, imagesNumber, ExplosionTexturesDirectory + filePrefix + "_", frameDuration, zenithImage} );
	}
}
