#ifndef HEADER_SAVES_EDITOR_INTERFACE_H
#define HEADER_SAVES_EDITOR_INTERFACE_H

#include "wx/panel.h"
#include "wx/textctrl.h"
#include "wx/stattext.h"
#include <vector>

class wxNotebook;
class TextsBlocks;
struct GameSlotData;

class HeaderInterface
{
private:
	wxPanel *panel;
	std::vector< wxTextCtrl* > count;
	std::vector< wxStaticText* > headerTexts;

public:
	explicit HeaderInterface(wxNotebook* notebook, const TextsBlocks& texts);
	~HeaderInterface() = default;
	HeaderInterface( const HeaderInterface& ) = delete;
	HeaderInterface& operator= ( const HeaderInterface& ) = delete;
	HeaderInterface( HeaderInterface&& ) = default;
	HeaderInterface& operator= ( HeaderInterface&& ) = default;
	
	void setTextCtrlDataFromGameSlot(const GameSlotData& slot);
	void copyTextCtrlToSlot(std::size_t index, const std::string& itemDescription, std::string& text) const;
	void eraseTextCtrlContent(std::size_t index);
	void appendTextToWidget(const std::string& text, std::size_t widgetIndex);
	
private:
	void createInterface(const TextsBlocks& texts);
};

#endif //HEADER_SAVES_EDITOR_INTERFACE_H