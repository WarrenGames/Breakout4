#include "widgets/editBoxes/bool_editBox.h"
#include "widgets/editBoxes/subObjects/boxEvents.h"
#include "logging/logsStruct.h"

BoolEditBox::BoolEditBox(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& boxSize, int fontSize):
	boxRect{logs, rndWnd, boxSize},
	boxContent{logs, rndWnd, fontSize, boxSize},
	boolValue{nullptr}
{
	
}
	

BoolEditBox::BoolEditBox(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& boxSize, int fontSize, bool& boolRef):
	boxRect{logs, rndWnd, boxSize},
	boxContent{logs, rndWnd, fontSize, boxSize},
	boolValue{&boolRef}
{
	
}

void BoolEditBox::drawBox(sdl2::RendererWindow& rndWnd) const
{
	boxRect.drawOffWindow(rndWnd);
	drawText(rndWnd);
}

void BoolEditBox::drawText(sdl2::RendererWindow& rndWnd) const
{
	if( boolValue )
	{
		if( *boolValue )
			boxContent.drawTrue(rndWnd);
		else
			boxContent.drawFalse(rndWnd);
	}
}

void BoolEditBox::invertBooleanValue()
{
	if( boolValue )
		*boolValue = !(*boolValue);
}

void BoolEditBox::catchUserFocus(const Offset& mousePosition, bool mouseButton)
{
	if( mouseButton && isUserMouseInBox(boxRect.getMainRect(), mousePosition) )
	{
		invertBooleanValue();
	}
}

void BoolEditBox::changeReference(bool& newRef)
{
	boolValue = &newRef;
}

bool BoolEditBox::isMouseOverBox(const Offset& mousePos) const
{
	return boxRect.isOffsetInsideRect(mousePos);
}