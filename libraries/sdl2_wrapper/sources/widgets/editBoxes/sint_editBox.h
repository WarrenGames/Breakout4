#ifndef SIGNED_INT_EDIT_BOX_H
#define SIGNED_INT_EDIT_BOX_H

#include "widgets/editBoxes/subObjects/boxEvents.h"
#include "widgets/editBoxes/subObjects/boxRectDisplay.h"
#include "widgets/editBoxes/subObjects/cursorDrawing.h"
#include "widgets/editBoxes/subObjects/boxContentDisplay.h"
#include <string>
#include <functional>

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }
struct SDL_Rect;

class SintEditBox
{
private:
	BoxEvents events;
	BoxRectDisplaying boxRect;
	BoxCursor cursor;
	BoxContentDisplay content;
	
	std::string stringOfSint;
	std::reference_wrapper<int> SintValue;
	bool hasStringChanged;

public:
	explicit SintEditBox(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& boxSize, unsigned int fontSize, int& refValue);
	~SintEditBox() = default;
	
	SintEditBox( const SintEditBox& ) = delete;
	SintEditBox& operator= ( const SintEditBox& ) = delete;
	
	SintEditBox( SintEditBox&& ) = default;
	SintEditBox& operator= ( SintEditBox&& ) = default;
	
	void drawBoxWithoutFocus(sdl2::RendererWindow& rndWnd) const;
	void catchUserFocus(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Offset& mousePos, bool mouseButton);
	int getCurrentValue() const;
	void changeReference(AppLogFiles& logs, int& newRef, sdl2::RendererWindow& rndWnd);
	bool isMouseOverBox(const Offset& mousePos) const;
	void updateGraphics(AppLogFiles& logs, sdl2::RendererWindow& rndWnd);
	
private:
	void addFigure(const std::string& figure);
	void deleteLastFigure();
	void recordEntry(bool& quitEdition);
	void appendNewFigureToSintString();
	void appendMinusToSintString();
	void quitSintEdition(bool& quitEdition);
	void drawEverything(sdl2::RendererWindow& rndWnd);
	void updateString();
	
};

#endif //SIGNED_INT_EDIT_BOX_H