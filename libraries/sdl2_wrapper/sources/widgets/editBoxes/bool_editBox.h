#ifndef BOOL_EDIT_BOX_H
#define BOOL_EDIT_BOX_H

#include "widgets/editBoxes/subObjects/boxRectDisplay.h"
#include "widgets/editBoxes/subObjects/boolBoxContentDisplay.h"

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }
struct SDL_Rect;
struct Offset;

class BoolEditBox
{
private:
	BoxRectDisplaying boxRect;
	BoolBoxContentDisplay boxContent;
	bool *boolValue;
	
public:
	explicit BoolEditBox(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& boxSize, unsigned int fontSize);
	explicit BoolEditBox(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& boxSize, unsigned int fontSize, bool& ref);
	~BoolEditBox() = default;
	BoolEditBox(BoolEditBox& ) = delete;
	BoolEditBox& operator= (BoolEditBox& ) = delete;
	
	BoolEditBox(BoolEditBox&& ) = default;
	BoolEditBox& operator= ( BoolEditBox&& ) = default;
	
	void drawBox(sdl2::RendererWindow& rndWnd) const;
	void catchUserFocus(const Offset& mousePosition, bool mouseButton);
	void changeReference(bool& newRef);
	bool isMouseOverBox(const Offset& mousePos) const;
	
private:
	void drawText(sdl2::RendererWindow& rndWnd) const;
	void invertBooleanValue();
};

#endif //BOOL_EDIT_BOX_H