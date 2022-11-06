#ifndef GAME_OBJECTS_INTERFACE_H
#define GAME_OBJECTS_INTERFACE_H

#include "wx/textctrl.h"
#include "wx/stattext.h"
#include "wx/panel.h"
#include <vector>

class wxNotebook;
class TextsBlocks;
struct GameSlotData;

class GameObjectsInterface
{
private:
	wxPanel *panel;
	std::vector< wxTextCtrl* > count;
	std::vector< wxStaticText* > objectsTexts;

public:
	explicit GameObjectsInterface(wxNotebook* notebook, const TextsBlocks& texts);
	~GameObjectsInterface() = default;
	GameObjectsInterface( const GameObjectsInterface& ) = delete;
	GameObjectsInterface& operator= ( const GameObjectsInterface& ) = delete;
	GameObjectsInterface( GameObjectsInterface&& ) = default;
	GameObjectsInterface& operator= ( GameObjectsInterface&& ) = default;
	
	
	void eraseTextCtrlContent();
	void setTextCtrlData(const GameSlotData& gameSlotData);
	void checkTextCtrl(GameSlotData& gameSlotData) const;
	void setValue(std::size_t textCtrlIndex, unsigned enumValue, unsigned maxValue);
	void setValue(std::size_t textCtrlIndex, int enumValue, int minValue, int maxValue);

private:
	void createInterface(const TextsBlocks& texts);
	void setSizeSlotData(std::size_t& valueToSet, wxTextCtrl *textCtrl) const;
	void setSlotData(unsigned& valueToSet, wxTextCtrl *textCtrl) const;
	void setSlotData(int& valueToSet, wxTextCtrl *textCtrl) const;
	void setSlotData(double& valueToSet, wxTextCtrl *textCtrl) const;
	void throwNullTextCtrlPtrException() const;
};

#endif //GAME_OBJECTS_INTERFACE_H