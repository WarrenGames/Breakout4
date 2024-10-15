#include "widgets/editBoxes/subObjects/boxContentDisplay.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include "texturing/texturePosition.h"
#include "widgets/editBoxes/subObjects/editBoxes_consts.h"

BoxContentDisplay::BoxContentDisplay(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, int fontSize, const std::string& valueInText):
	arialFont{logs.error, BoxesArialFontPath, fontSize},
	currentValue{ logs, rndWnd, arialFont, valueInText, BoxesEditBoxBlack, TexturePosition{} }
{

}


void BoxContentDisplay::makeTextTextureFromString(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& valueInText, bool& canChange)
{
	if( canChange && arialFont )
	{
		if( false == valueInText.empty() )
		{
			currentValue.texture.loadBlendedText(logs, rndWnd, arialFont, valueInText, BoxesEditBoxBlack);
			setRectDimensions();
		}
		canChange = false;
	}
}

void BoxContentDisplay::setRectDimensions()
{
	if( currentValue.texture )
	{
		currentValue.catchTexture();
		currentValue.sprite.resetDimensions();
		currentValue.sprite.resetSourceRect();
	}
}

void BoxContentDisplay::drawCurrentValueWithFocus(sdl2::RendererWindow& rndWnd, const SDL_Rect& boxRect, const std::string& valueInText)
{
	if( currentValue.texture && false == valueInText.empty() )
	{
		currentValue.sprite.setXPos(boxRect.x + BoxesMarginSize * 2);
		currentValue.sprite.setYPos(boxRect.y + boxRect.h / 2 - currentValue.sprite.height() / 2 );
		currentValue.draw(rndWnd);
	}
}

void BoxContentDisplay::drawCurrentValueWithoutFocus(sdl2::RendererWindow& rndWnd) const
{
	if( currentValue.texture )
	{
		currentValue.draw(rndWnd);
	}
}

void BoxContentDisplay::updateContentWhileLosingFocus(const SDL_Rect& boxRect)
{
	setRectDimensions();
	currentValue.sprite.setXPos( boxRect.x + boxRect.w - BoxesMarginSize * 2 - currentValue.sprite.width() );
	currentValue.sprite.setYPos( boxRect.y + boxRect.h / 2 - currentValue.sprite.height() / 2 );
}

const SDL_Rect& BoxContentDisplay::getContentRect() const
{
	return currentValue.sprite.getDrawRect();
}