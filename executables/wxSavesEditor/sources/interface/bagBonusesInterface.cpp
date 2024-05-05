#include "interface/bagBonusesInterface.h"
#include "gameSlots/gameSlotData.h"
#include "texts/textLoader.h"
#include "wx/notebook.h"
#include "consts/consts.h"
#include <cassert>

BagBonusesInterface::BagBonusesInterface(wxNotebook* notebook, const TextsBlocks& texts):
	window{ new wxScrolledWindow{ notebook, wxID_ANY, wxPoint{ -1, -1}, wxSize{ -1, -1}, wxVSCROLL, wxString{"bag bonuses panel"} } }
{
	createInterface(texts);
	notebook->AddPage( window, "Bag bonuses" );
}

void BagBonusesInterface::createInterface(const TextsBlocks& texts)
{
	wxPoint textPt{ 0, 0 };
	wxPoint textCtrlPt{ 0, 0 };
	
	for( std::size_t i{0} ; i < texts.size() ; ++i )
	{
		textPt.x = BonusesLeftMargin + ColumnWidth * ( i % ColumnsNumber );
		textPt.y = 96 + 48 * ( i / ColumnsNumber );
		textCtrlPt.x = BonusesRightMargin + ColumnWidth * ( i % ColumnsNumber );
		textCtrlPt.y = 96 + 48 * ( i / ColumnsNumber );
		bonusesTexts.emplace_back( new wxStaticText{ window, wxID_ANY, wxString{texts[i]}, textPt} );
		bonusesCount.emplace_back( new wxTextCtrl{ window, wxID_ANY, "0", textCtrlPt, wxSize{TextCtrlWidth, TextCtrlHeight} } );
	}
}

void BagBonusesInterface::eraseWeaponItemsTextCtrlContent()
{
	for( auto &widget : bonusesCount )
	{
		if( widget )
		{
			if( false == widget->IsEmpty() )
			{
				widget->Clear();
			}
		}
	}
}

void BagBonusesInterface::setTextCtrlFromGameSlot(const GameSlotData& gameSlotData)
{
	eraseWeaponItemsTextCtrlContent();
	assert( gameSlotData.bonusesInBag.size() == bonusesCount.size() );
	for( std::size_t i{0} ; i < gameSlotData.bonusesInBag.size() && i < bonusesCount.size() ; ++i )
	{
		*(bonusesCount[i]) << static_cast<int>( gameSlotData.bonusesInBag[i] );
	}
}

void BagBonusesInterface::copyTextCtrlToSlot(GameSlotData& gameSlotData) const
{
	for( std::size_t i{0} ; i < gameSlotData.bonusesInBag.size() && i < bonusesCount.size() ; ++i )
	{
		if( false == bonusesCount[i]->IsEmpty() )
		{
			gameSlotData.bonusesInBag[i] = std::stoul( bonusesCount[i]->GetLineText(0).ToStdString() );
		}
		else{
			throw std::runtime_error{"bonusesInBag item (wxTextCtrl) number " + std::to_string(i) + " is empty."};
		}
	}
}