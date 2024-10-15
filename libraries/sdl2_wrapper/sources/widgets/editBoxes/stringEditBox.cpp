#include "widgets/editBoxes/stringEditBox.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include "customTypes/positionTypes.h"
#include "widgets/editBoxes/subObjects/editBoxes_consts.h"
#include <sstream>

StringEditBox::StringEditBox(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& boxSize, int fontSize, std::string& obj, unsigned stringMaxSize):
	events{},
	boxRect{logs, rndWnd, boxSize},
	cursor{logs, rndWnd, boxSize},
	content{logs, rndWnd, fontSize, obj },
	strMaxSize{stringMaxSize},
	ref{std::ref(obj)},
	hasStringChanged{true}
{
	updateGraphics(logs, rndWnd);
}

void StringEditBox::drawBoxWithoutFocus(sdl2::RendererWindow& rndWnd) const
{
	boxRect.drawOffWindow(rndWnd);
	content.drawCurrentValueWithoutFocus(rndWnd);
}

void StringEditBox::catchUserFocus(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Offset& mousePos, bool mouseButton)
{
	if( mouseButton && isUserMouseInBox(boxRect.getMainRect(), mousePos ) )
	{
		bool quitEdition{false};
		while( false == quitEdition )
		{
			cursor.blinkCursor();
			events.updateEvents(quitEdition);
			appendNewFigureToString();
			appendLowerCaseToString();
			appendUpperCaseToString();
			appendSpaceBarToString();
			appendDotToString();
			recordEntry(quitEdition);
			deleteLastFigure();
			quitStringEdition(quitEdition);
			content.makeTextTextureFromString(logs, rndWnd, ref, hasStringChanged);
			drawEverything(rndWnd);
		}
		content.updateContentWhileLosingFocus(boxRect.getMainRect());
		events.resetAllKeys();
		events.setMouseLeftButtonToFalse();
	}
}

const std::string& StringEditBox::getCurrentValue() const
{
	return ref;
}

void StringEditBox::addFigure(const std::string& figure)
{
	ref.get() += figure;
	hasStringChanged = true;
}

void StringEditBox::deleteLastFigure()
{
	if( events.getSpecificKey(BoxEventBackspace) && false == ref.get().empty() )
	{
		ref.get().pop_back();
		hasStringChanged = true;
		events.setSpecificKeyToFalse(BoxEventBackspace);
	}
}

void StringEditBox::recordEntry(bool& quitEdition)
{
	if( events.getSpecificKey(BoxEventReturn) && false == ref.get().empty() )
	{
		quitEdition = true;
		events.setSpecificKeyToFalse(BoxEventReturn);
		
	}
}

void StringEditBox::appendNewFigureToString()
{
	for( unsigned i{0} ; i < BoxEventMax ; ++i )
	{
		if( events.getNumbersState(i) && ref.get().size() + 1 < strMaxSize )
		{
			addFigure( std::to_string(i) );
			events.setNumberKeyToFalse(i);
		}
	}
}

void StringEditBox::appendLowerCaseToString()
{
	for( char c{'a'} ; c <= 'z' ; ++c )
	{
		if( events.getLowerCaseState(c) )
		{
			ref.get() += c;
			hasStringChanged = true;
			events.setLowerCaseStateToFalse(c);
		}
	}
}

void StringEditBox::appendUpperCaseToString()
{
	for( char c{'A'} ; c <= 'Z' ; ++c )
	{
		if( events.getUpperCaseState(c) )
		{
			ref.get() += c;
			hasStringChanged = true;
			events.setUpperCaseStateToFalse(c);
		}
	}
}

void StringEditBox::appendSpaceBarToString()
{
	if( events.getSpecificKey(BoxEventSpacebar) )
	{
		ref.get() += ' ';
		hasStringChanged = true;
		events.setSpecificKeyToFalse(BoxEventSpacebar);
	}
}

void StringEditBox::appendDotToString()
{
	if( events.getSpecificKey(BoxEventDot) )
	{
		ref.get() += '.';
		hasStringChanged = true;
		events.setSpecificKeyToFalse(BoxEventDot);
	}
}

void StringEditBox::quitStringEdition(bool& quitEdition)
{
	if( false == ref.get().empty() 
	&& ( ( false == isUserMouseInBox(boxRect.getMainRect(), events.getMousePosition() ) && events.getMouseLeftButtonState() ) 
		|| events.getSpecificKey(BoxEventEscape) ) )
	{
		quitEdition = true;
		events.setSpecificKeyToFalse(BoxEventEscape);
		events.setMouseLeftButtonToFalse();
	}
}

void StringEditBox::drawEverything(sdl2::RendererWindow& rndWnd)
{
	boxRect.drawActiveWindow(rndWnd);
	content.drawCurrentValueWithFocus(rndWnd, boxRect.getMainRect(), ref.get() );
	cursor.drawCursor(rndWnd, Offset{content.getContentRect().x + content.getContentRect().w, content.getContentRect().y + content.getContentRect().h / 2} );
	rndWnd.displayRenderer();
	SDL_Delay(10);
}

void StringEditBox::changeReference(AppLogFiles& logs, std::string& newRef, sdl2::RendererWindow& rndWnd)
{
	ref = std::ref(newRef);
	content.makeTextTextureFromString(logs, rndWnd, ref, hasStringChanged);
	content.updateContentWhileLosingFocus(boxRect.getMainRect());
}

void StringEditBox::updateGraphics(AppLogFiles& logs, sdl2::RendererWindow& rndWnd)
{
	content.makeTextTextureFromString(logs, rndWnd, ref, hasStringChanged);
	content.updateContentWhileLosingFocus(boxRect.getMainRect());
}

bool StringEditBox::isMouseOverBox(const Offset& mousePos) const
{
	return boxRect.isOffsetInsideRect(mousePos);
}