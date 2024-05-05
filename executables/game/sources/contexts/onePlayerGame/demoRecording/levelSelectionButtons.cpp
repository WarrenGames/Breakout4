#include "contexts/onePlayerGame/demoRecording/levelSelectionButtons.h"
#include "types/essentialsStruct.h"
#include "crossLevel/levelsInfos.h"
#include "texturing/texturePosition.h"
#include "consts/fontsConsts.h"
#include "consts/constexprScreen.h"
#include <cassert>

onePlGame::demoRecording::LevelsButtons::LevelsButtons(Essentials& essentials):
	currentPageNumber{0},
	arial{ essentials.logs.error, ArialFontPath, FontMediumPointSize}
{

}

void onePlGame::demoRecording::LevelsButtons::createButtons(Essentials& essentials, const LevelsInfos& levelsInfos)
{
	buttons.emplace_back( std::vector< TextButton >() );
	for( std::size_t i{0} ; i < levelsInfos.size() ; ++i )
	{
		if( buttons.back().size() + 1 < onePlGame::demoRecording::LevelsPerPage )
		{
			buttons.back().emplace_back( TextButton{essentials.logs, essentials.rndWnd, arial, levelsInfos.getMainLevelFileName(i), WhiteColor, MediumGrayColor, 
										TexturePosition{ GameScreenWidth * 3 / 4, SQR_SIZE * 2 + SQR_SIZE * static_cast<int>(buttons.back().size()) / 2, true, true } } );
		}
		else{
			buttons.emplace_back( std::vector< TextButton >() );
			buttons.back().emplace_back( TextButton{essentials.logs, essentials.rndWnd, arial, levelsInfos.getMainLevelFileName(i), WhiteColor, MediumGrayColor, 
										TexturePosition{ GameScreenWidth * 3 / 4, SQR_SIZE * 2 + SQR_SIZE * static_cast<int>(buttons.back().size()) / 2, true, true } } );
		}
	}
}

void onePlGame::demoRecording::LevelsButtons::nextPageIfAny()
{
	if( currentPageNumber + 1 < buttons.size() )
	{
		currentPageNumber++;
	}
}

void onePlGame::demoRecording::LevelsButtons::previousPageIfAny()
{
	if( currentPageNumber > 0 )
	{
		currentPageNumber--;
	}
}

void onePlGame::demoRecording::LevelsButtons::updateButtons(Essentials& essentials)
{
	if( buttons.empty() == false )
	{
		assert( currentPageNumber < buttons.size() );
		for( auto &btn : buttons[currentPageNumber] )
		{
			btn.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
		}
	}
}

void onePlGame::demoRecording::LevelsButtons::drawCurrentPage(Essentials& essentials) const
{
	if( buttons.empty() == false )
	{
		assert( currentPageNumber < buttons.size() );
		for( auto const &btn : buttons[currentPageNumber] )
		{
			btn.drawButton(essentials.rndWnd);
		}
	}
}

bool onePlGame::demoRecording::LevelsButtons::isButtonClicked(std::size_t buttonNum) const
{
	if( buttons.empty() == false )
	{
		for( std::size_t i{0} ; i < buttons[currentPageNumber].size() ; ++i )
		{
			if( buttonNum == currentPageNumber * LevelsPerPage + i )
			{
				return buttons[currentPageNumber][i].buttonClicked();
			}
		}
		return false;
	}
	else{
		return false;
	}
}