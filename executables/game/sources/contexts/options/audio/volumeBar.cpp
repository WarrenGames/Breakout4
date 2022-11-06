#include "contexts/options/audio/volumeBar.h"
#include "texturing/rendererWindow.h"
#include "types/essentialsStruct.h"
#include "texturing/loadSDL2.h"
#include "customTypes/positionTypes.h"
#include <fstream>

VolumeBar::VolumeBar(Essentials& essentials, const SDL_Rect& rect, const SDL_Color& lcol, const SDL_Color& rcol, const Offset& boundValues, int startValue):
	soundVolume{startValue},
	minimum{boundValues.x},
	maximum{boundValues.y},
	gradient{ essentials.logs, essentials.rndWnd, rect, lcol, rcol, GradientTextureOnX },
	cursor{ essentials.logs, essentials.rndWnd, "textures/gameGUI/optionsSprites/volumeCursor.png" }
{
	if( cursor && gradient )
	{
		cursor.sprite.setXPos(gradient.sprite.width() * soundVolume / maximum, + gradient.sprite.x_pos() - cursor.sprite.width() / 2);
		cursor.sprite.setYPos(gradient.sprite.y_pos() + gradient.sprite.height() / 2 - cursor.sprite.height() / 2 );
	}
}

void VolumeBar::drawAll(sdl2::RendererWindow& rndWnd) const
{
	drawBar(rndWnd);
	drawCursor(rndWnd);
}

void VolumeBar::drawBar(sdl2::RendererWindow& rndWnd) const
{
	if( gradient )
		gradient.draw(rndWnd);
}

void VolumeBar::drawCursor(sdl2::RendererWindow& rndWnd) const
{
	if( cursor )
		cursor.draw(rndWnd);
}

void VolumeBar::changeVolumeLevel(const Offset& mousePosition, bool buttonState)
{
	if( mousePosition.x >= gradient.sprite.x_pos() 
		&& mousePosition.x < gradient.sprite.x_pos() + gradient.sprite.width() 
		&& mousePosition.y >= gradient.sprite.y_pos() && mousePosition.y < gradient.sprite.y_pos() + gradient.sprite.height() 
		&& buttonState )
	{
		soundVolume = maximum * (mousePosition.x - gradient.sprite.x_pos() ) / gradient.sprite.width();
		setCursorPos();
	}
}

int VolumeBar::getVolume() const
{
	return soundVolume;
}

void VolumeBar::setVolume(int newValue)
{
	if( newValue < maximum )
	{
		soundVolume = newValue;
	}
	setCursorPos();
}

void VolumeBar::setCursorPos()
{
	cursor.sprite.setXPos( gradient.sprite.width() * soundVolume / maximum + gradient.sprite.x_pos() - cursor.sprite.width() / 2 );
}