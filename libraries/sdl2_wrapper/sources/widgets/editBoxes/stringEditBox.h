#ifndef STD_STRING_EDIT_BOX_H
#define STD_STRING_EDIT_BOX_H

#include "widgets/editBoxes/subObjects/boxEvents.h"
#include "widgets/editBoxes/subObjects/boxRectDisplay.h"
#include "widgets/editBoxes/subObjects/cursorDrawing.h"
#include "widgets/editBoxes/subObjects/boxContentDisplay.h"
#include <string>
#include <functional>

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }
struct SDL_Rect;

class StringEditBox
{
private:
	BoxEvents events;
	BoxRectDisplaying boxRect;
	BoxCursor cursor;
	BoxContentDisplay content;
	
	unsigned strMaxSize;
	std::reference_wrapper<std::string> ref;
	bool hasStringChanged;
	
public:
	explicit StringEditBox(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& boxSize, int fontSize, std::string& obj, unsigned stringMaxSize);
	~StringEditBox() = default;
	StringEditBox( const StringEditBox& ) = delete;
	StringEditBox& operator= ( const StringEditBox& ) = delete;
	StringEditBox( StringEditBox&& ) = default;
	StringEditBox& operator= ( StringEditBox&& ) = default;
	
	void drawBoxWithoutFocus(sdl2::RendererWindow& rndWnd) const;
	void catchUserFocus(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Offset& mousePos, bool mouseButton);
	const std::string& getCurrentValue() const;
	void changeReference(AppLogFiles& logs, std::string& newRef, sdl2::RendererWindow& rndWnd);
	void updateGraphics(AppLogFiles& logs, sdl2::RendererWindow& rndWnd);
	bool isMouseOverBox(const Offset& mousePos) const;

private:
	void addFigure(const std::string& figure);
	void deleteLastFigure();
	void recordEntry(bool& quitEdition);
	void appendNewFigureToString();
	void appendLowerCaseToString();
	void appendUpperCaseToString();
	void appendSpaceBarToString();
	void appendDotToString();
	void quitStringEdition(bool& quitEdition);
	void drawEverything(sdl2::RendererWindow& rndWnd);
	void updateString();
};

#endif //STD_STRING_EDIT_BOX_H