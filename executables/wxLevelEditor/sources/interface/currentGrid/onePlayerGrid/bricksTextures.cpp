#include "interface/currentGrid/onePlayerGrid/bricksTextures.h"
#include "interface/currentGrid/onePlayerGrid/brickData.h"
#include "customTypes/positionTypes.h"
#include "consts/onePlayerGridConsts.h"
#include "consts/constexprScreen.h"
#include "fileSystem/fileSystem.h"
#include "wx/dc.h"
#include "wx/textctrl.h"
#include <fstream>
#include <algorithm>
#include <cassert>

OnePBricksTextures::OnePBricksTextures(wxTextCtrl *logWindow):
	isLoadingPerfect{true}
{
	if( logWindow )
	{
		loadAllTextures(*logWindow);
	}
}

bool OnePBricksTextures::wasLoadingPerfect() const
{
	for( auto const &pack : bricksTextures )
	{
		for( auto const &image : pack )
		{
			if( false == wxImageLoadedWithSuccess(image) )
			{
				return false;
			}
		}
	}
	return true;
}

void OnePBricksTextures::drawSingleBrick(wxDC& drawContext, const BrickData& brickData, const Offset& position) const
{
	if( brickData.index > 0 )
	{
		if( brickData.index <= bricksTextures.size() )
		{
			if( brickData.property < bricksTextures[brickData.index - 1 ].size() )
			{
				drawContext.DrawBitmap(bricksTextures[brickData.index - 1][brickData.property], position.x, position.y, true);
			}
			else{
				drawErrorCase(drawContext, position);
			}
		}
		else{
			drawErrorCase(drawContext, position);
		}
	}
}

std::size_t OnePBricksTextures::getCategorySize(const BrickData& brickData) const
{
	assert( brickData.index > 0 );
	assert( brickData.index <= bricksTextures.size() );
	return bricksTextures[brickData.index - 1].size();
}

std::size_t OnePBricksTextures::getSize() const
{
	return bricksTextures.size();
}

void OnePBricksTextures::loadAllTextures(wxTextCtrl& logWindow)
{
	if( std::ifstream packsFile{ bricks::GridEditorTexturesEnumFilePath } )
	{
		std::string fileLine;
		while( std::getline( packsFile, fileLine ) )
		{
			bricksTextures.emplace_back( std::vector< wxImage >{} );
			loadTexturesPack( bricks::TexturesPacksFilesDirectory + fileLine, bricksTextures.back(), logWindow );
		}
	}
	else{
		logWindow << "Error: couldn't open '" << bricks::GridEditorTexturesEnumFilePath << "' textures enum list file.\n";
		isLoadingPerfect = false;
	}
}

void OnePBricksTextures::loadTexturesPack(const std::string& texturesEnumFilePath, std::vector< wxImage >& texturePack, wxTextCtrl& logWindow)
{
	if( std::ifstream texturesEnumFile{ texturesEnumFilePath } )
	{
		std::string fileLine;
		while( std::getline( texturesEnumFile, fileLine ) )
		{
			if( fs::exists( fileLine ) )
			{
				texturePack.emplace_back( wxImage{ fileLine.c_str(), wxBITMAP_TYPE_PNG } );
			}
			else{
				logWindow << "Error: that texture file doesn't exists.\n";
			}
		}
	}
	else{
		logWindow << "Error: couldn't open textures enum file with path: '" << texturesEnumFilePath << "' .\n";
	}
}

void OnePBricksTextures::drawErrorCase(wxDC& drawContext, const Offset& position) const
{
	drawContext.DrawCircle( position.x + SQR_SIZE / 2, position.y + SQR_SIZE / 2, SQR_SIZE / 2 );
}

bool wxImageLoadedWithSuccess(const wxImage& image)
{
	return image.IsOk();
}