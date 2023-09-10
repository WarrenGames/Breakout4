#include "widgets/buttons/textButtonWidget.h"
#include "logging/logsStruct.h"
#include "text/sdl2ttf_font.h"
#include "texturing/rendererWindow.h"
#include "texturing/texturePosition.h"
#include "customTypes/positionTypes.h"

TextButton::TextButton(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& text, const SDL_Color& selected, const SDL_Color& offColor,
						const TexturePosition& pos):
	selectedTexture{ logs, rndWnd, font, text, selected, pos},
	awayTexture{ logs, rndWnd, font, text, offColor, pos },
	clicked{ false },
	hovered{ false }
{
	
}

TextButton::TextButton(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& text, const SDL_Color& selected, const SDL_Color& offColor, 
						int xpos, int ypos, bool isCenteredOnPos):
	selectedTexture{ logs, rndWnd, font, text, selected, TexturePosition{ Offset{xpos, ypos}, isCenteredOnPos } },
	awayTexture{ logs, rndWnd, font, text, offColor, TexturePosition{ Offset{xpos, ypos}, isCenteredOnPos } },
	clicked{ false },
	hovered{ false }
{
	
}

TextButton::operator bool() const
{
	return selectedTexture.texture && awayTexture.texture;
}

void TextButton::updateButton(int mouse_x_pos, int mouse_y_pos, bool leftButtonState)
{
	if( mouse_x_pos >= selectedTexture.sprite.x_pos() 
		&& mouse_x_pos < selectedTexture.sprite.x_pos() + selectedTexture.sprite.width() 
		&& mouse_y_pos >= selectedTexture.sprite.y_pos() 
		&& mouse_y_pos < selectedTexture.sprite.y_pos() + selectedTexture.sprite.height() )
	{
		hovered = true;
		if( leftButtonState )
		{
			clicked = true;
		}
		else{
			clicked = false;
		}
	}
	else{
		hovered = false;
		clicked = false;
	}
}

void TextButton::updateButton(const Offset& mousePosition, bool leftButtonState)
{
	updateButton(mousePosition.x, mousePosition.y, leftButtonState);
}

void TextButton::drawButton(sdl2::RendererWindow& rndWnd) const
{
	if( hovered && selectedTexture.texture )
	{
		selectedTexture.draw(rndWnd);
	}
	else if( false == hovered && awayTexture.texture )
	{
		awayTexture.draw(rndWnd);
	}
}

bool TextButton::buttonClicked() const
{
	return clicked;
}
