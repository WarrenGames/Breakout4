#include "widgets/editBoxes/subObjects/cursorDrawing.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include "customTypes/positionTypes.h"
#include "widgets/editBoxes/subObjects/editBoxes_consts.h"


BoxCursor::BoxCursor(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& boxSize):
	cursor{ logs, rndWnd, BoxesEditBoxBlack, 2, boxSize.h - BoxesMarginSize * 2 },
	timeCursor{},
	canCursorBeBlit{false}
{
	
}

void BoxCursor::blinkCursor()
{
	if( timeCursor.hasTimeElapsed( std::chrono::milliseconds{BoxesCursorBlinkTime} ) )
	{
		timeCursor.joinTimePoints();
		canCursorBeBlit = !canCursorBeBlit;
	}
}

void BoxCursor::drawCursor(sdl2::RendererWindow& rndWnd, const Offset& cursorPosition)
{
	if( cursor.texture && canCursorBeBlit )
	{
		cursor.sprite.setDefaultCoord(cursorPosition.x, cursorPosition.y - cursor.sprite.height() / 2 );
		cursor.draw(rndWnd);
	}
}