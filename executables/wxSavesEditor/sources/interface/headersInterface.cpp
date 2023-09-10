#include "interface/headersInterface.h"
#include "gameSlots/gameSlotData.h"
#include "texts/textLoader.h"
#include "wx/notebook.h"
#include "consts/consts.h"

HeaderInterface::HeaderInterface(wxNotebook* notebook, const TextsBlocks& texts):
	panel{ new wxPanel{ notebook, wxID_ANY, wxPoint{ -1, -1}, wxSize{ -1, -1} } }
{
	createInterface( texts );
	notebook->AddPage( panel, "Game save headers" );
}

void HeaderInterface::createInterface(const TextsBlocks& texts)
{
	wxPoint textPt{ 0, 0 };
	wxPoint textCtrlPt{ 0, 0 };
	
	for( std::size_t i{0} ; i < texts.size() ; ++i )
	{
		textPt.x = HeaderLeftMargin;
		textPt.y = 96 + 48 * i;
		textCtrlPt.x = HeaderRightMargin;
		textCtrlPt.y = 96 + 48 * i;
		headerTexts.emplace_back( new wxStaticText{ panel, wxID_ANY, wxString{texts[i]}, textPt} );
		count.emplace_back( new wxTextCtrl{ panel, wxID_ANY, "string", textCtrlPt, wxSize{TextCtrlBigWidth, TextCtrlHeight} } );
	}
}

void HeaderInterface::setTextCtrl(const GameSlotData& slot)
{
	eraseTextCtrlContent(HeaderCampaignAndDate);
	eraseTextCtrlContent(HeaderScoreAndCoin);
	appendTextToWidget(slot.campaignAndDateInfos, HeaderCampaignAndDate);
	appendTextToWidget(slot.scoreAndCoinsInfos, HeaderScoreAndCoin);
}

void HeaderInterface::eraseTextCtrlContent(std::size_t index)
{
	assert( index < count.size() );
	
	if( false == count[index]->IsEmpty() )
	{
		count[index]->Clear();
	}
}

void HeaderInterface::appendTextToWidget(const std::string& text, std::size_t widgetIndex)
{
	assert( widgetIndex < count.size() );
	if( false == text.empty() )
	{
		*( count[widgetIndex] ) << text;
	}
}

void HeaderInterface::checkTextCtrl(std::size_t index, const std::string& itemDescription, std::string& text) const
{
	assert( index < count.size() );
	if( count[index]->IsEmpty() )
	{
		throw std::runtime_error{itemDescription + " is empty, data is not valid."};
	}
	text = count[index]->GetLineText(0).ToStdString();
}