#include "widgets/buttons/highlightButtonWidget.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include "texturing/texturePosition.h"

HighLightButton::HighLightButton(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& text, const SDL_Color& textCol, const SDL_Rect& square, 
								const SDL_Color& squareCol):
	highlightTexture{ logs, rndWnd, squareCol, square.w, square.h, TexturePosition{ Offset{ square.x, square.y} } },
	textTexture{ logs, rndWnd, font, text, textCol, TexturePosition{ Offset{ square.x + square.w / 2, square.y + square.h / 2}, true, true } },
	clicked_{ false },
	hovered_{ false }
{
	
}

void HighLightButton::drawButton(sdl2::RendererWindow& rndWnd) const
{
	if( hovered_ && highlightTexture.texture )
	{
		highlightTexture.draw(rndWnd);
	}
	if( textTexture.texture )
	{
		textTexture.draw(rndWnd);
	}
}

const std::string& HighLightButton::getText()
{
	return text;
}

void HighLightButton::updateButton(int mouse_posx, int mouse_posy, bool mouseButtonState)
{
	if( mouse_posx >= highlightTexture.sprite.x_pos() 
		&& mouse_posx < highlightTexture.sprite.x_pos() + highlightTexture.sprite.width() 
		&& mouse_posy >= highlightTexture.sprite.y_pos() 
		&& mouse_posy < highlightTexture.sprite.y_pos() + highlightTexture.sprite.height() )
	{
		hovered_ = true;
		
		if( mouseButtonState )
			clicked_ = true;
		else
			clicked_ = false;
	}
	else{
		hovered_ = false;
		clicked_ = false;
	}
}

void HighLightButton::updateButton(const Offset& mousePosition, bool mouseButtonState)
{
	updateButton(mousePosition.x, mousePosition.y, mouseButtonState);
}

void HighLightButton::changeText(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& newText, const SDL_Color& txtCol)
{
	text = newText;
	
	textTexture.texture.loadBlendedText(logs, rndWnd, font, newText, txtCol);
	
	
	if( textTexture.texture && highlightTexture.texture )
	{
		textTexture.resetSpritePosition(TexturePosition{highlightTexture.sprite.x_pos() + highlightTexture.sprite.width() / 2,
														highlightTexture.sprite.y_pos() + highlightTexture.sprite.height() / 2, true, true} );
	}
}

bool HighLightButton::buttonClicked() const
{
	return clicked_;
}