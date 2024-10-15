#include "widgets/editBoxes/uint_editBox.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include "customTypes/positionTypes.h"
#include "widgets/editBoxes/subObjects/editBoxes_consts.h"
#include <sstream>

UintEditBox::UintEditBox(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& boxSize, int fontSize, unsigned& refValue):
	events{},
	boxRect{logs, rndWnd, boxSize},
	cursor{logs, rndWnd, boxSize},
	content{logs, rndWnd, fontSize, std::to_string(refValue)},
	stringOfUint{std::to_string(refValue)},
	uintValue{std::ref(refValue)},
	hasStringChanged{true}
{
	updateGraphics(logs, rndWnd);
}

void UintEditBox::drawBoxWithoutFocus(sdl2::RendererWindow& rndWnd) const
{
	boxRect.drawOffWindow(rndWnd);
	content.drawCurrentValueWithoutFocus(rndWnd);
}

void UintEditBox::catchUserFocus(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Offset& mousePos, bool mouseButton)
{
	if( mouseButton && isUserMouseInBox(boxRect.getMainRect(), mousePos ) )
	{
		bool quitEdition{false};
		while( false == quitEdition)
		{
			cursor.blinkCursor();
			events.updateEvents(quitEdition);
			appendNewFigureToUintString();
			recordEntry(quitEdition);
			deleteLastFigure();
			quitUintEdition(quitEdition);
			content.makeTextTextureFromString(logs, rndWnd, stringOfUint, hasStringChanged);
			drawEverything(rndWnd);
		}
		content.updateContentWhileLosingFocus(boxRect.getMainRect());
		events.resetAllKeys();
		events.setMouseLeftButtonToFalse();
	}
}

unsigned UintEditBox::getCurrentValue() const
{
	return uintValue;
}

void UintEditBox::addFigure(const std::string& figure)
{
	stringOfUint += figure;
	hasStringChanged = true;
}

void UintEditBox::deleteLastFigure()
{
	if( events.getSpecificKey(BoxEventBackspace) && false == stringOfUint.empty() )
	{
		stringOfUint.pop_back();
		hasStringChanged = true;
		events.setSpecificKeyToFalse(BoxEventBackspace);
	}
}

void UintEditBox::recordEntry(bool& quitEdition)
{
	if( events.getSpecificKey(BoxEventReturn) && false == stringOfUint.empty() )
	{
		quitEdition = true;
		hasStringChanged = true;
		std::istringstream valueStream{stringOfUint};
		valueStream >> uintValue;
		events.setSpecificKeyToFalse(BoxEventReturn);
	}
}

void UintEditBox::appendNewFigureToUintString()
{
	for( unsigned i{0} ; i < BoxEventMax ; ++i )
	{
		if( events.getNumbersState(i) && stringOfUint.size() < BoxesCharSizeMax )
		{
			addFigure( std::to_string(i) );
			events.setNumberKeyToFalse(i);
		}
	}
}

void UintEditBox::quitUintEdition(bool& quitEdition)
{
	if( false == stringOfUint.empty() 
	&& ( ( false == isUserMouseInBox(boxRect.getMainRect(), events.getMousePosition() ) && events.getMouseLeftButtonState() ) 
	|| events.getSpecificKey(BoxEventEscape) ) )
	{
		quitEdition = true;
		events.setSpecificKeyToFalse(BoxEventEscape);
		events.setMouseLeftButtonToFalse();
	}
}

void UintEditBox::drawEverything(sdl2::RendererWindow& rndWnd)
{
	boxRect.drawActiveWindow(rndWnd);
	content.drawCurrentValueWithFocus(rndWnd, boxRect.getMainRect(), stringOfUint);
	cursor.drawCursor(rndWnd, Offset{content.getContentRect().x + content.getContentRect().w, content.getContentRect().y + content.getContentRect().h / 2} );
	rndWnd.displayRenderer();
	SDL_Delay(10);
}

void UintEditBox::updateString()
{
	stringOfUint = std::to_string(uintValue);
	hasStringChanged = true;
	std::istringstream stream{stringOfUint};
	stream >> uintValue;
}

void UintEditBox::changeReference(AppLogFiles& logs, unsigned& newRef, sdl2::RendererWindow& rndWnd)
{
	uintValue = std::ref(newRef);
	updateString();
	content.makeTextTextureFromString(logs, rndWnd, stringOfUint, hasStringChanged);
	content.updateContentWhileLosingFocus(boxRect.getMainRect());
}

bool UintEditBox::isMouseOverBox(const Offset& mousePosition) const
{
	return boxRect.isOffsetInsideRect(mousePosition);
}

void UintEditBox::updateGraphics(AppLogFiles& logs, sdl2::RendererWindow& rndWnd)
{
	updateString();
	content.makeTextTextureFromString(logs, rndWnd, stringOfUint, hasStringChanged);
	content.updateContentWhileLosingFocus(boxRect.getMainRect());
}