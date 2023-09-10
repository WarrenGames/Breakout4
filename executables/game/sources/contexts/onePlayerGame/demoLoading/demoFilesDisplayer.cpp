#include "contexts/onePlayerGame/demoLoading/demoFilesDisplayer.h"
#include "types/essentialsStruct.h"
#include "text/sdl2ttf_font.h"
#include "texturing/texturePosition.h"
#include "consts/constexprScreen.h"
#include "consts/fontsConsts.h"
#include "consts/sdlColors.h"
#include <cassert>

constexpr char DemoDirPath[] = "data/demos/";

demosLoading::DemoFilesDisplayer::DemoFilesDisplayer(Essentials& essentials, const sdl2::Font& font):
	currentPage{ 0 }
{
	openDictionaryFile(essentials, font);
}

void demosLoading::DemoFilesDisplayer::openDictionaryFile(Essentials& essentials, const sdl2::Font& font)
{
	if( std::ifstream dictionaryFile{demosLoading::DemoDictionnaryFile} )
	{
		std::string fileLine;
		while( std::getline(dictionaryFile, fileLine) )
		{
			manageVectorSize();
			addTextButtons(essentials, fileLine, font);
		}
	}
	else{
		essentials.logs.error << "Error: couldn't open '" << demosLoading::DemoDictionnaryFile << "' file in order to load the demo files.\n";
	}
}

void demosLoading::DemoFilesDisplayer::manageVectorSize()
{
	if( demoData.empty() )
	{
		demoData.emplace_back( std::vector< DemoInfosData >() );
	}
	else{
		if( demoData.back().size() == EntriesPerPage )
		{
			demoData.emplace_back( std::vector< DemoInfosData >() );
		}
	}
}

void demosLoading::DemoFilesDisplayer::addTextButtons(Essentials& essentials, const std::string& fileLine, const sdl2::Font& font)
{
	demoData.back().emplace_back( TextButton{essentials.logs, essentials.rndWnd, font, fileLine, WhiteColor, MediumGrayColor, 
									TexturePosition{ GameScreenWidth / 2, ( static_cast<int>(demoData.back().size() ) + 3 ) * SQR_SIZE, true, true} },
									fs::path{ DemoDirPath + fileLine } );
}

void demosLoading::DemoFilesDisplayer::seeNextPage()
{
	if( currentPage + 1 < demoData.size() )
	{
		currentPage++;
	}
}

void demosLoading::DemoFilesDisplayer::seePreviousPage()
{
	if( currentPage > 0 )
	{
		currentPage--;
	}
}

void demosLoading::DemoFilesDisplayer::updateActiveButtons(const Offset& mousePosition, bool mouseLeftButtonState)
{
	if( demoData.empty() == false )
	{
		assert( currentPage < demoData.size() );
		for( auto &data : demoData[currentPage] )
		{
			data.button.updateButton(mousePosition, mouseLeftButtonState);
		}
	}
}

void demosLoading::DemoFilesDisplayer::drawCurrentPage(Essentials& essentials) const
{
	if( demoData.empty() == false )
	{
		assert( currentPage < demoData.size() );
		for( auto const &data : demoData[currentPage] )
		{
			data.button.drawButton(essentials.rndWnd);
		}
	}
}