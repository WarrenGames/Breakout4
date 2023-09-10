#include "advancedDrawing/texturesLoading/fileTexturesList.h"
#include "logging/logsStruct.h"
#include <cassert>

TexturesFilesList::TexturesFilesList():
	isLoadingPerfect{ true }
{

}

TexturesFilesList::TexturesFilesList(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& listFilePath):
	isLoadingPerfect{ true }
{
	lookUpListFile(logs, rndWnd, listFilePath );
}

TexturesFilesList::TexturesFilesList(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned texturesNumber, const std::string& fileBase):
	isLoadingPerfect{ true }
{
	for( unsigned i{0} ; i < texturesNumber ; ++i )
	{
		addTexture(logs, rndWnd, fileBase + std::to_string(i) + ".png");
	}
}

bool TexturesFilesList::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

std::size_t TexturesFilesList::size() const
{
	return loadedTextures.size();
}

const sdl2::TextureLoader& TexturesFilesList::operator[](std::size_t index) const
{
	assert( index < loadedTextures.size() );
	return loadedTextures[index];
}

std::vector< sdl2::TextureLoader >::const_iterator TexturesFilesList::begin() const
{
	return loadedTextures.cbegin();
}

std::vector< sdl2::TextureLoader >::const_iterator TexturesFilesList::end() const
{
	return loadedTextures.cend();
}

std::vector< sdl2::TextureLoader >::iterator TexturesFilesList::begin()
{
	return loadedTextures.begin();
}

std::vector< sdl2::TextureLoader >::iterator TexturesFilesList::end()
{
	return loadedTextures.end();
}

void TexturesFilesList::addTexture(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& textureFilePath)
{
	if( sdl2::TextureLoader tload{ logs, rndWnd, textureFilePath } )
	{
		loadedTextures.emplace_back( std::move( tload ) );
	}
	else{
		isLoadingPerfect = false;
	}
}

void TexturesFilesList::lookUpListFile(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& listFilePath)
{
	if( std::ifstream listFile{ listFilePath } )
	{
		std::string fileLine;
		while( std::getline( listFile, fileLine ) )
		{
			addTexture(logs, rndWnd, fileLine);
		}
	}
	else{
		logs.error.wrFileOpeningError(listFilePath, "load 'TexturesFilesList' data.");
		isLoadingPerfect = false;
	}
}

void TexturesFilesList::clearData()
{
	loadedTextures.clear();
}