#include "interface/gameObjectsInterface.h"
#include "gameSlots/gameSlotData.h"
#include "texts/textLoader.h"
#include "wx/notebook.h"
#include "consts/consts.h"
#include "consts/onePlayerLevelConsts.h"
#include <cassert>

GameObjectsInterface::GameObjectsInterface(wxNotebook* notebook, const TextsBlocks& texts):
	panel{ new wxPanel{ notebook, wxID_ANY, wxPoint{ -1, -1}, wxSize{ -1, -1} } }
{
	createInterface( texts );
	notebook->AddPage( panel, "Game objects" );
}

void GameObjectsInterface::createInterface(const TextsBlocks& texts)
{
	wxPoint textPt{ 0, 0 };
	wxPoint textCtrlPt{ 0, 0 };
	
	for( std::size_t i{0} ; i < texts.size() && i < IndexMax ; ++i )
	{
		textPt.x = BonusesLeftMargin + ColumnWidth * ( i % ColumnsNumber );
		textPt.y = 96 + 48 * ( i / ColumnsNumber );
		textCtrlPt.x = BonusesRightMargin + ColumnWidth * ( i % ColumnsNumber );
		textCtrlPt.y = 96 + 48 * ( i / ColumnsNumber );
		objectsTexts.emplace_back( new wxStaticText{ panel, wxID_ANY, wxString{texts[i]}, textPt} );
		count.emplace_back( new wxTextCtrl{ panel, wxID_ANY, "0", textCtrlPt, wxSize{TextCtrlWidth, TextCtrlHeight} } );
	}
}

void GameObjectsInterface::eraseTextCtrlContent()
{
	for( auto &widget : count )
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

void GameObjectsInterface::setTextCtrlDataFromGameSlot(const GameSlotData& gameSlotData)
{
	eraseTextCtrlContent();
	*(count[IndexCampaignType])		<< static_cast<int>( gameSlotData.campaignType );
	*(count[IndexLevelCursor])		<< static_cast<int>( gameSlotData.levelCursor );
	*(count[IndexSkillLevel])		<< static_cast<int>( gameSlotData.skillLevel );
	*(count[IndexPlayerLives]) 		<< static_cast<int>( gameSlotData.playerLives );
	*(count[IndexRacketSpeed])		<< std::to_string( gameSlotData.racketSpeed );
	*(count[IndexRacketSize])		<< static_cast<int>( gameSlotData.racketSize );
	*(count[IndexScore])			<< static_cast<int>( gameSlotData.score );
	*(count[IndexBonusCoinNumber])	<< static_cast<int>( gameSlotData.bonusCoinNumber );
	*(count[IndexRimState])			<< static_cast<int>( gameSlotData.rimsStartState );
	
}

void GameObjectsInterface::setValue(std::size_t textCtrlIndex, unsigned enumValue, unsigned maxValue)
{
	assert( textCtrlIndex < count.size() );
	assert( enumValue < maxValue );
	if( false == count[textCtrlIndex]->IsEmpty() )
	{
		count[textCtrlIndex]->Clear();
	}
	*(count[textCtrlIndex]) << static_cast<int>(enumValue);
}

void GameObjectsInterface::setValue(std::size_t textCtrlIndex, int enumValue, int minValue, int maxValue)
{
	assert( textCtrlIndex < count.size() );
	assert( enumValue >= minValue && enumValue < maxValue );
	if( false == count[textCtrlIndex]->IsEmpty() )
	{
		count[textCtrlIndex]->Clear();
	}
	*count[textCtrlIndex] << enumValue;
}

void GameObjectsInterface::copyTextCtrlToSlot(GameSlotData& gameSlotData) const
{
	setSlotData(gameSlotData.campaignType, count[IndexCampaignType] );
	setSizeSlotData( gameSlotData.levelCursor, count[IndexLevelCursor] );
	setSlotData( gameSlotData.skillLevel, count[IndexSkillLevel] );
	setSlotData( gameSlotData.playerLives, count[IndexPlayerLives] );
	setSlotData( gameSlotData.racketSpeed, count[IndexRacketSpeed] );
	setSlotData( gameSlotData.racketSize, count[IndexRacketSize] );
	setSlotData( gameSlotData.score, count[IndexScore] );
	setSlotData( gameSlotData.bonusCoinNumber, count[IndexBonusCoinNumber] );
	setSlotData( gameSlotData.rimsStartState, count[IndexRimState] );
}

void GameObjectsInterface::setSlotData(unsigned& valueToSet, wxTextCtrl *textCtrl) const
{
	if( false == textCtrl->IsEmpty() )
	{
		valueToSet = std::stoul( textCtrl->GetLineText(0).ToStdString() );
	}
	else{
		throwNullTextCtrlPtrException();
	}
}

void GameObjectsInterface::setSizeSlotData(std::size_t& valueToSet, wxTextCtrl *textCtrl) const
{
	if( false == textCtrl->IsEmpty() )
	{
		valueToSet = std::stoul( textCtrl->GetLineText(0).ToStdString() );
	}
	else{
		throwNullTextCtrlPtrException();
	}
}

void GameObjectsInterface::setSlotData(int& valueToSet, wxTextCtrl *textCtrl) const
{
	if( false == textCtrl->IsEmpty() )
	{
		valueToSet = std::stoul( textCtrl->GetLineText(0).ToStdString() );
	}
	else{
		throwNullTextCtrlPtrException();
	}
}

void GameObjectsInterface::setSlotData(double& valueToSet, wxTextCtrl *textCtrl) const
{
	if( false == textCtrl->IsEmpty() )
	{
		valueToSet = std::stoul( textCtrl->GetLineText(0).ToStdString() );
	}
	else{
		throwNullTextCtrlPtrException();
	}
}	

void GameObjectsInterface::throwNullTextCtrlPtrException() const
{
	throw std::runtime_error{ "wxTextCtrl of is empty." };
}
