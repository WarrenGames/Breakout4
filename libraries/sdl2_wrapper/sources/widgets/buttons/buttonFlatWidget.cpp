#include "widgets/buttons/buttonFlatWidget.h"
#include "logging/logsStruct.h"
#include "texturing/texturePosition.h"
#include "customTypes/positionTypes.h"

ButtonFlat::ButtonFlat(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& texturePath, int xpos, int ypos):
	texture{ logs, rndWnd, texturePath, TexturePosition{Offset{xpos, ypos} } },
	clicked{false},
	hovered{false}
{

}

ButtonFlat::ButtonFlat(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& texturePath, int xpos, int ypos, bool centered):
	texture{ logs, rndWnd, texturePath, TexturePosition{Offset{xpos, ypos}, centered } },
	clicked{false},
	hovered{false}
{

}

ButtonFlat::operator bool() const
{
	return texture.texture;
}

void ButtonFlat::updateButton(const Offset& mousePosition, bool mouseButtonState)
{
	if( mousePosition.x >= texture.sprite.x_pos() 
	&& mousePosition.x < texture.sprite.x_pos() + texture.sprite.width() 
	&& mousePosition.y >= texture.sprite.y_pos() 
	&& mousePosition.y < texture.sprite.y_pos() + texture.sprite.height() )
	{
		if( mouseButtonState == true)
		{
			clicked = true;
		}
		else{
			clicked = false;
		}
		hovered = true;
	}
	else{
		clicked = false;
		hovered = false;
	}
}

void ButtonFlat::drawButton(sdl2::RendererWindow& rndWnd) const
{
	texture.draw(rndWnd);
}

bool ButtonFlat::buttonClicked() const
{
	return clicked;
}

bool ButtonFlat::buttonHovered() const
{
	return hovered;
}