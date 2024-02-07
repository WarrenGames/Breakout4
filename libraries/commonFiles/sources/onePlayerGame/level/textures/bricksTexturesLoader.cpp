#include "onePlayerGame/level/textures/bricksTexturesLoader.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include "fileSystem/fileSystem.h"
#include <string>
#include <fstream>
#include <algorithm>

constexpr char OnePlayerTexturesPacksFile[] = "data/textures/texturesPacksConfigurations/gamePackList.txt";
constexpr char TexturesPackDir[] = "data/textures";

BricksTexturesLoader::BricksTexturesLoader(AppLogFiles& logs, sdl2::RendererWindow& rndWnd)
{
	loadTextures(logs, rndWnd);
}

BricksTexturesLoader::operator bool() const
{
	if( bricksTextures.empty() )
	{
		return false;
	}
	else{
		return std::all_of( std::cbegin( bricksTextures ), std::cend( bricksTextures ), [](auto const& list){ return list.wasLoadingPerfect(); } );
	}
}

void BricksTexturesLoader::loadTextures(AppLogFiles& logs, sdl2::RendererWindow& rndWnd)
{
	if( std::ifstream texturesPacksFile{ OnePlayerTexturesPacksFile } )
	{
		std::string fileLine;
		while( std::getline( texturesPacksFile, fileLine ) )
		{
			if( fileLine[0] != '#' )
			{
				fs::path packFullPath{ TexturesPackDir };
				packFullPath /= fileLine;
				bricksTextures.emplace_back( TexturesFilesList{ logs, rndWnd, packFullPath.string() } );
			}
		}
	}
	else{
		logs.error << "Error: couldn't open '" << OnePlayerTexturesPacksFile << "' textures packs file for one player game.\n";
	}
}