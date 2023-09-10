#include "widgets/buttons/3TexturesButtonWidget.h"
#include "logging/logsStruct.h"
#include "text/sdl2ttf_font.h"
#include "texturing/rendererWindow.h"
#include "texturing/texturePosition.h"
#include <cassert>

T3_Button::T3_Button(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::array<const std::string, T3BTN_MAX>& texturesPaths, const TexturePosition& pos):
	buttonState{Texture3ButtonOff}
{
	createTexturesWithPath(logs, rndWnd, texturesPaths, pos);
}

T3_Button::T3_Button(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& text,
					 const SDL_Color& offText, const SDL_Color& selectText, const SDL_Color& backgrnd, const TexturePosition& pos):
	buttonState{Texture3ButtonOff}
{
	createTexturesWithFont(logs, rndWnd, font, text, offText, selectText, backgrnd, pos);
}

void T3_Button::updateButton(const Offset& mousePosition, bool mouseButtonState)
{
	if( mousePosition.x >= textures[0].sprite.x_pos() 
		&& mousePosition.x < textures[0].sprite.x_pos() + textures[0].sprite.width()
		&& mousePosition.y >= textures[0].sprite.y_pos() 
		&& mousePosition.y < textures[0].sprite.y_pos() + textures[0].sprite.height() )
	{
		if( mouseButtonState )
		{
			buttonState = Texture3ButtonClick;
		}
		else{
			buttonState = Texture3ButtonHovered;
		}
	}
	else{
		buttonState = Texture3ButtonOff;
	}
}

void T3_Button::drawButton(sdl2::RendererWindow& rndWnd) const
{
	assert( buttonState < textures.size() );
	textures[buttonState].draw(rndWnd);
}

bool T3_Button::buttonClicked() const
{
	return buttonState == Texture3ButtonClick;
}

void T3_Button::createTexturesWithPath(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::array< const std::string, T3BTN_MAX>& paths, const TexturePosition& pos)
{
	for( unsigned i{0} ; i < T3BTN_MAX ; ++i )
	{
		textures.emplace_back( TextureCombo{logs, rndWnd, paths[i], pos } );
	}
}

void T3_Button::createTexturesWithFont(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& text, const SDL_Color& offText, 
								const SDL_Color& selectText, const SDL_Color& backgrnd, const TexturePosition& pos)
{
	textures.emplace_back( TextureCombo{logs, rndWnd, font, text, offText, backgrnd, pos} );
	textures.emplace_back( TextureCombo{logs, rndWnd, font, text, selectText, backgrnd, pos} );
	textures.emplace_back( TextureCombo{logs, rndWnd, font, text, selectText, backgrnd, pos} );
}
