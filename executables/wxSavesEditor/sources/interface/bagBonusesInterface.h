#ifndef BAG_BONUSES_INTERFACE_PANEL_H
#define BAG_BONUSES_INTERFACE_PANEL_H

#include "wx/scrolwin.h"
#include "wx/textctrl.h"
#include "wx/stattext.h"
#include <vector>

class wxNotebook;
class TextsBlocks;
struct GameSlotData;

class BagBonusesInterface
{
private:
	wxScrolledWindow* window;
	std::vector< wxTextCtrl* > bonusesCount;
	std::vector< wxStaticText* > bonusesTexts;
	
public:
	explicit BagBonusesInterface(wxNotebook* notebook, const TextsBlocks& texts);
	~BagBonusesInterface() = default;
	BagBonusesInterface( const BagBonusesInterface& ) = delete;
	BagBonusesInterface& operator= ( const BagBonusesInterface& ) = delete;
	BagBonusesInterface( BagBonusesInterface&& ) = default;
	BagBonusesInterface& operator= ( BagBonusesInterface&& ) = default;
	
	void eraseWeaponItemsTextCtrlContent();
	void setTextCtrlFromGameSlot(const GameSlotData& gameSlotData);
	void copyTextCtrlToSlot(GameSlotData& gameSlotData) const;
	
private:
	void createInterface(const TextsBlocks& texts);
};

#endif //BAG_BONUSES_INTERFACE_PANEL_H