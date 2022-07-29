#ifndef BONUS_EDIT_BOXES_H
#define BONUS_EDIT_BOXES_H

#include "widgets/editBoxes/uint_editBox.h"
#include "contexts/duels/duelsConstexpr.h"
#include <vector>

struct AppLogFiles;

namespace duels{

class BonusEditBoxes
{
private:
	std::vector< UintEditBox > boxes;

public:
	explicit BonusEditBoxes(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, std::vector< unsigned >& bonuses);
	~BonusEditBoxes() = default;
	BonusEditBoxes( const BonusEditBoxes& ) = delete;
	BonusEditBoxes& operator= ( const BonusEditBoxes& ) = delete;
	BonusEditBoxes( BonusEditBoxes&& ) = default;
	BonusEditBoxes& operator= ( BonusEditBoxes&& ) = default;
	
	void catchUserFocus(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Offset& mousePos, bool isButtonPushed);
	void drawBoxes(sdl2::RendererWindow& rndWnd) const;
	
	int getIndexOfBoxWithMouseOver(const Offset& mousePosition) const;
	void updateGraphics(AppLogFiles& logs, sdl2::RendererWindow& rndWnd);
};

}

#endif //BONUS_EDIT_BOXES_H