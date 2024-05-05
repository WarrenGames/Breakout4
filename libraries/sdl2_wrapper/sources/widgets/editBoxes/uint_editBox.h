#ifndef UNSIGNED_INT_EDIT_BOX_H
#define UNSIGNED_INT_EDIT_BOX_H

#include "widgets/editBoxes/subObjects/boxEvents.h"
#include "widgets/editBoxes/subObjects/boxRectDisplay.h"
#include "widgets/editBoxes/subObjects/cursorDrawing.h"
#include "widgets/editBoxes/subObjects/boxContentDisplay.h"
#include <string>
#include <functional>

struct AppLogFiles;

class UintEditBox
{
private:
	BoxEvents events;
	BoxRectDisplaying boxRect;
	BoxCursor cursor;
	BoxContentDisplay content;
	
	std::string stringOfUint;
	std::reference_wrapper<unsigned> uintValue;
	bool hasStringChanged;

public:
	explicit UintEditBox(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& boxSize, unsigned int fontSize, unsigned& refValue);
	~UintEditBox() = default;
	
	UintEditBox( const UintEditBox& ) = delete;
	UintEditBox& operator= ( const UintEditBox& ) = delete;
	
	UintEditBox( UintEditBox&& ) = default;
	UintEditBox& operator= ( UintEditBox&& ) = default;
	
	void drawBoxWithoutFocus(sdl2::RendererWindow& rndWnd) const;
	void catchUserFocus(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Offset& mousePos, bool mouseButton);
	unsigned getCurrentValue() const;
	void changeReference(AppLogFiles& logs, unsigned& newRef, sdl2::RendererWindow& rndWnd);
	bool isMouseOverBox(const Offset& mousePosition) const;
	void updateGraphics(AppLogFiles& logs, sdl2::RendererWindow& rndWnd);
	
private:
	void addFigure(const std::string& figure);
	void deleteLastFigure();
	void recordEntry(bool& quitEdition);
	void appendNewFigureToUintString();
	void quitUintEdition(bool& quitEdition);
	void drawEverything(sdl2::RendererWindow& rndWnd);
	void updateString();

};

#endif //UNSIGNED_INT_EDIT_BOX_H