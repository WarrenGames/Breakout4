#include "contexts/duels/matchConfig/interface/bonusEditBoxes.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/constexprScreen.h"
#include "consts/fontsConsts.h"
#include <cassert>

duels::BonusEditBoxes::BonusEditBoxes(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, std::vector< unsigned >& bonuses)
{	
	assert( bonuses.size() == duels::DuelBonusMax );
	for( std::size_t i{0} ; i < bonuses.size() ; ++i )
	{
		boxes.emplace_back( UintEditBox{logs, rndWnd, SDL_Rect{SQR_SIZE * 3 + SQR_SIZE / 4, SQR_SIZE*static_cast<int>(i) + SQR_SIZE * 2, SQR_SIZE, SQR_SIZE/2}, 
										FontSmallPointSize, bonuses[i] } );
	}
}

void duels::BonusEditBoxes::catchUserFocus(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Offset& mousePos, bool isButtonPushed)
{
	for( auto &box : boxes )
		box.catchUserFocus(logs, rndWnd, mousePos, isButtonPushed);
}

void duels::BonusEditBoxes::drawBoxes(sdl2::RendererWindow& rndWnd) const
{
	for( auto const &box : boxes )
		box.drawBoxWithoutFocus(rndWnd);
}

int duels::BonusEditBoxes::getIndexOfBoxWithMouseOver(const Offset& mousePosition) const
{
	for( std::size_t i{0} ; i < boxes.size() ; ++i )
	{
		if( boxes[i].isMouseOverBox(mousePosition) )
			return static_cast<int>(i);
	}
	return -1;
}

void duels::BonusEditBoxes::updateGraphics(AppLogFiles& logs, sdl2::RendererWindow& rndWnd)
{
	for( auto &box : boxes )
	{
		box.updateGraphics(logs, rndWnd);
	}
}