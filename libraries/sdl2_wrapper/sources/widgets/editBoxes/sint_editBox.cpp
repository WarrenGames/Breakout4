#include "widgets/editBoxes/sint_editBox.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include "customTypes/positionTypes.h"
#include "widgets/editBoxes/subObjects/editBoxes_consts.h"
#include <sstream>

SintEditBox::SintEditBox(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& boxSize, unsigned int fontSize, int& refValue):
	events{},
	boxRect{logs, rndWnd, boxSize},
	cursor{logs, rndWnd, boxSize},
	content{logs, rndWnd, fontSize, std::to_string(refValue)},
	stringOfSint{std::to_string(refValue)},
	SintValue{std::ref(refValue)},
	hasStringChanged{true}
{
	updateGraphics(logs, rndWnd);
}

void SintEditBox::drawBoxWithoutFocus(sdl2::RendererWindow& rndWnd) const
{
	boxRect.drawOffWindow(rndWnd);
	content.drawCurrentValueWithoutFocus(rndWnd);
}

void SintEditBox::catchUserFocus(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Offset& mousePos, bool mouseButton)
{
	if( mouseButton && isUserMouseInBox(boxRect.getMainRect(), mousePos ) )
	{
		bool quitEdition{false};
		while(!quitEdition)
		{
			cursor.blinkCursor();
			events.updateEvents(quitEdition);
			appendNewFigureToSintString();
			appendMinusToSintString();
			recordEntry(quitEdition);
			deleteLastFigure();
			quitSintEdition(quitEdition);
			content.makeTextTextureFromString(logs, rndWnd, stringOfSint, hasStringChanged);
			drawEverything(rndWnd);
		}
		content.updateContentWhileLosingFocus(boxRect.getMainRect());
		events.resetAllKeys();
		events.setMouseLeftButtonToFalse();
	}
}

int SintEditBox::getCurrentValue() const
{
	return SintValue;
}

void SintEditBox::addFigure(const std::string& figure)
{
	stringOfSint += figure;
	hasStringChanged = true;
}

void SintEditBox::deleteLastFigure()
{
	if( events.getSpecificKey(BoxEventBackspace) && false == stringOfSint.empty() )
	{
		stringOfSint.pop_back();
		hasStringChanged = true;
		events.setSpecificKeyToFalse(BoxEventBackspace);
	}
}

void SintEditBox::recordEntry(bool& quitEdition)
{
	if( events.getSpecificKey(BoxEventReturn) && false == stringOfSint.empty() && !isOnlyMinusCharInSintString(stringOfSint) )
	{
		quitEdition = true;
		hasStringChanged = true;
		std::istringstream valueStream{stringOfSint};
		valueStream >> SintValue;
		events.setSpecificKeyToFalse(BoxEventReturn);
	}
}

void SintEditBox::appendNewFigureToSintString()
{
	for( unsigned i{0} ; i < BoxEventMax ; ++i )
	{
		if( events.getNumbersState(i) && stringOfSint.size() < BoxesCharSizeMax )
		{
			addFigure( std::to_string(i) );
			events.setNumberKeyToFalse(i);
		}
	}
}

void SintEditBox::appendMinusToSintString()
{
	if( stringOfSint.empty() && events.getSpecificKey(BoxEventMinus) )
	{
		addFigure("-");
		events.setSpecificKeyToFalse(BoxEventMinus);
	}
}

void SintEditBox::quitSintEdition(bool& quitEdition)
{
	if( false == isOnlyMinusCharInSintString(stringOfSint) && !stringOfSint.empty() 
		&& ( ( false == isUserMouseInBox(boxRect.getMainRect(), events.getMousePosition() ) && events.getMouseLeftButtonState() ) || events.getSpecificKey(BoxEventEscape) ) )
	{
		quitEdition = true;
		events.setSpecificKeyToFalse(BoxEventEscape);
		events.setMouseLeftButtonToFalse();
	}
}

void SintEditBox::drawEverything(sdl2::RendererWindow& rndWnd)
{
	boxRect.drawActiveWindow(rndWnd);
	content.drawCurrentValueWithFocus(rndWnd, boxRect.getMainRect(), stringOfSint);
	cursor.drawCursor(rndWnd, Offset{content.getContentRect().x + content.getContentRect().w, content.getContentRect().y + content.getContentRect().h / 2} );
	rndWnd.displayRenderer();
	SDL_Delay(10);
}

void SintEditBox::updateString()
{
	stringOfSint = std::to_string(SintValue);
	hasStringChanged = true;
	std::istringstream stream{stringOfSint};
	stream >> SintValue;
}

void SintEditBox::changeReference(AppLogFiles& logs, int& newRef, sdl2::RendererWindow& rndWnd)
{
	SintValue = std::ref(newRef);
	updateString();
	content.makeTextTextureFromString(logs, rndWnd, stringOfSint, hasStringChanged);
	content.updateContentWhileLosingFocus(boxRect.getMainRect());
}

void SintEditBox::updateGraphics(AppLogFiles& logs, sdl2::RendererWindow& rndWnd)
{
	updateString();
	content.makeTextTextureFromString(logs, rndWnd, stringOfSint, hasStringChanged);
	content.updateContentWhileLosingFocus(boxRect.getMainRect());
}

bool SintEditBox::isMouseOverBox(const Offset& mousePos) const
{
	return boxRect.isOffsetInsideRect(mousePos);
}