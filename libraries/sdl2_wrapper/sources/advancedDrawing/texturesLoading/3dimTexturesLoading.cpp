#include "advancedDrawing/texturesLoading/3dimTexturesLoading.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include <sstream>

Matrix3DTexturesLoading::Matrix3DTexturesLoading():
	isLoadingPerfect{true}
{
	
}

Matrix3DTexturesLoading::Matrix3DTexturesLoading(const Coord3D& matSize):
	textures{matSize},
	isLoadingPerfect{true}
{
	
}

Matrix3DTexturesLoading::Matrix3DTexturesLoading(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Coord3D& matSize, const std::string& filePath):
	textures{matSize},
	isLoadingPerfect{true}
{
	lookUpListFile(logs, rndWnd, filePath);
}

bool Matrix3DTexturesLoading::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

std::size_t Matrix3DTexturesLoading::width() const
{
	return textures.width();
}

std::size_t Matrix3DTexturesLoading::height() const
{
	return textures.height();
}

std::size_t Matrix3DTexturesLoading::depth() const
{
	return textures.depth();
}

std::size_t Matrix3DTexturesLoading::size() const
{
	return textures.size();
}

const sdl2::TextureLoader& Matrix3DTexturesLoading::getLoadedTexture(const Coord3D& coords) const
{
	return textures(coords);
}

void Matrix3DTexturesLoading::lookUpListFile(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& filePath)
{
	if( std::ifstream texturesListFile{ filePath } )
	{
		std::string fileLine;
		while( std::getline( texturesListFile, fileLine ) )
		{
			std::istringstream lineStream{ fileLine };
			readLineAndLoadTexture(logs, rndWnd, lineStream, filePath);
		}
	}
	else{
		logs.error.wrFileOpeningError(filePath, "load 3dim textures matrix");
	}
}

void Matrix3DTexturesLoading::readLineAndLoadTexture(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, std::istringstream& lineStream, const std::string& filePath)
{
	Coord3D coord;
	std::string texturePath;
	if( lineStream >> coord.depth >> coord.height >> coord.width >> texturePath )
	{
		checkDimensionBeforeLoading(logs, rndWnd, coord, texturePath);
	}
	else{
		logs.error.wrReadErrorMessage(filePath, "3d coords and texture path");
	}
}

void Matrix3DTexturesLoading::checkTexturePresenceBeforeLoading(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Coord3D& coord, const std::string& texturePath)
{
	if( false == textures(coord) )
	{
		if( sdl2::TextureLoader tload{logs, rndWnd, texturePath} )
		{
			textures(coord) = std::move( tload );
		}
		else{
			isLoadingPerfect = false;
			logs.error.wrRessourceCreationError("texture of 3 dimensions Matrix", "the texture '" + texturePath + "' doesn't exist.");
		}
	}
	else{
		isLoadingPerfect = false;
		logs.error.wrRessourceCreationError("sdl2::TextureLoader " + texturePath, "the ressource is present already");
		logs.error << "  ressource coordinates: width( " << coord.width << " ), height( " << coord.height << " ), depth( " << coord.depth << " ).\n";
	}
}

void Matrix3DTexturesLoading::checkDimensionBeforeLoading(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Coord3D& coords, const std::string& texturePath)
{
	if( coords.width < textures.width() )
	{
		if( coords.height < textures.height() )
		{
			if( coords.depth < textures.depth() )
			{
				checkTexturePresenceBeforeLoading(logs, rndWnd, coords, texturePath);
			}
			else{
				isLoadingPerfect = false;
				logs.error.wrRessourceCreationError("texture of 3 dimensions Matrix", "the depth is outside boundaries ( " + std::to_string( coords.depth ) + " )");
			}
		}
		else
		{
			isLoadingPerfect = false;
			logs.error.wrRessourceCreationError("texture of 3 dimensions Matrix", "the height is outside boundaries ( " + std::to_string( coords.height ) + " )");
		}
	}
	else{
		isLoadingPerfect = false;
		logs.error.wrRessourceCreationError("texture of 3 dimensions Matrix", "the width is outside boundaries ( " + std::to_string( coords.width ) + " )");
	}
}