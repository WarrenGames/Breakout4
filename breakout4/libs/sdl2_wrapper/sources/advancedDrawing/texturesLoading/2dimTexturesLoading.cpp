#include "advancedDrawing/texturesLoading/2dimTexturesLoading.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include <sstream>

Matrix2DTexturesLoading::Matrix2DTexturesLoading():
	isLoadingPerfect{true}
{
	
}

Matrix2DTexturesLoading::Matrix2DTexturesLoading(const Coord2D& size):
	textures{size},
	isLoadingPerfect{true}
{
	
}

Matrix2DTexturesLoading::Matrix2DTexturesLoading(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Coord2D& size, const std::string& fileBase, const std::string& separator):
	textures{size},
	isLoadingPerfect{true}
{
	loadAllTextures(logs,rndWnd, fileBase, separator);
}

Matrix2DTexturesLoading::Matrix2DTexturesLoading(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Coord2D& size, const std::string& listFileName):
	textures{size},
	isLoadingPerfect{true}
{
	lookUpListFile(logs, rndWnd, listFileName);
}

bool Matrix2DTexturesLoading::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

std::size_t Matrix2DTexturesLoading::width() const
{
	return textures.width();
}

std::size_t Matrix2DTexturesLoading::height() const
{
	return textures.height();
}

std::size_t Matrix2DTexturesLoading::size() const
{
	return textures.size();
}

void Matrix2DTexturesLoading::resize(const Coord2D& size)
{
	textures.resize(size);
}

const sdl2::TextureLoader& Matrix2DTexturesLoading::operator()(const Coord2D& coords) const
{
	return textures(coords);
}

sdl2::TextureLoader& Matrix2DTexturesLoading::operator()(const Coord2D& coords)
{
	return textures(coords);
}

const sdl2::TextureLoader& Matrix2DTexturesLoading::operator()(std::size_t width, std::size_t height) const
{
	return textures(width, height);
}

sdl2::TextureLoader& Matrix2DTexturesLoading::operator()(std::size_t width, std::size_t height)
{
	return textures(width, height);
}

void Matrix2DTexturesLoading::loadAllTextures(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& fileBase, const std::string& separator)
{
	for( std::size_t height{0} ; height < textures.height() ; ++height )
	{
		for( std::size_t width{0} ; width < textures.width() ; ++width )
		{
			loadSingleTexture(logs, rndWnd, Coord2D{width, height}, fileBase, separator);
		}
	}
}

void Matrix2DTexturesLoading::loadSingleTexture(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Coord2D& size, const std::string& fileBase, const std::string& separator)
{
	if( sdl2::TextureLoader tload{ logs, rndWnd, fileBase + std::to_string( size.height ) + separator + std::to_string( size.width ) + ".png"} )
	{
		textures(size) = std::move( tload );
	}
	else{
		isLoadingPerfect = false;
	}
}

void Matrix2DTexturesLoading::lookUpListFile(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& listFileName)
{
	if( std::ifstream listFile{ listFileName } )
	{
		std::string fileLine;
		Coord2D coords;
		std::string texturePath;
		while( std::getline(listFile, fileLine) )
		{
			std::istringstream lineStream{ fileLine };
			if( lineStream >> coords.height >> coords.width >> texturePath )
			{
				loadSingleTexture(logs, rndWnd, coords, texturePath);
			}
			else{
				isLoadingPerfect = false;
				logs.error.wrReadErrorMessage(listFileName, "read height, width and texture path of '" + listFileName + "' 2dim textures file.");
			}
		}
	}
	else{
		isLoadingPerfect = false;
		logs.error.wrFileOpeningError(listFileName, "load a 2 dimension matrix of textures.");
	}
}

void Matrix2DTexturesLoading::loadSingleTexture(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Coord2D& coords, const std::string& texturePath)
{
	if( coords.width < textures.width() )
	{
		if( coords.height < textures.height() )
		{
			if( ! textures(coords) )
			{
				if( sdl2::TextureLoader texture{logs, rndWnd, texturePath} )
				{
					textures(coords) = std::move( texture );
				
				}
				else{
					isLoadingPerfect = false;
					logs.error.wrRessourceCreationError("texture of 2 dimensions Matrix", "the texture '" + texturePath + "' doesn't exist.");
				}
			}
			else{
				isLoadingPerfect = false;
				logs.error.wrRessourceCreationError("texture of 2 dimensions Matrix", 
						texturePath + " texture at coord2D(" + std::to_string( coords.width ) + ", " + std::to_string( coords.height ) + " already exists.");
			}
		}
		else{
			isLoadingPerfect = false;
			logs.error.wrRessourceCreationError("texture of 2 dimensions Matrix", "the width is outside boundaries ( " + std::to_string( coords.width ) + " )");
		}
	}
	else{
		isLoadingPerfect = false;
		logs.error.wrRessourceCreationError("texture of 2 dimensions Matrix", "the height is outside boundaries ( " + std::to_string( coords.height ) + " )");
	}
}