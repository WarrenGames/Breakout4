#include "texturing/texturesCombo.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include "text/sdl2ttf_font.h"
#include "texturing/texturePosition.h"

TextureCombo::TextureCombo():
	texture{},
	sprite{ texture }
{
	
}

TextureCombo::TextureCombo(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& texturePath, const TexturePosition& pos):
	texture{ logs, rndWnd, texturePath },
	sprite{ texture, pos }
{
	
}

TextureCombo::TextureCombo(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const std::string& texturePath):
	texture{ logs, rndWnd, texturePath },
	sprite{ texture, TexturePosition{ Offset{ 0, 0}, false, false } }
{
	
}

TextureCombo::TextureCombo(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Color& color, int squareWidth, int squareHeight):
	texture{ logs, rndWnd, color, squareWidth, squareHeight},
	sprite{ texture, TexturePosition{} }
{
	
}

TextureCombo::TextureCombo(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Color& color, int squareWidth, int squareHeight, const TexturePosition& pos):
	texture{ logs, rndWnd, color, squareWidth, squareHeight },
	sprite{ texture, pos }
{
	
}

TextureCombo::TextureCombo(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& text, const SDL_Color& color, const TexturePosition& pos):
	texture{ logs, rndWnd, font, text, color },
	sprite{ texture, pos }
{
	
}

TextureCombo::TextureCombo(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& font, const std::string& text, const SDL_Color& txtCol, const SDL_Color& roundCol, const TexturePosition& pos):
	texture{ logs, rndWnd, font, text, txtCol, roundCol },
	sprite{ texture, pos }
{
	
}

TextureCombo::TextureCombo(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& rect, const SDL_Color& startColor, const SDL_Color& endColor, unsigned axis):
	texture{ logs, rndWnd, rect, startColor, endColor, axis },
	sprite{ texture, TexturePosition{rect.x, rect.y} }
{
	
}

TextureCombo::TextureCombo(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& rect, const SDL_Color& startColor, const SDL_Color& endColor, unsigned axis,
							const TexturePosition& pos):
	texture{ logs, rndWnd, rect, startColor, endColor, axis },
	sprite{ texture, pos }
{
	
}

TextureCombo::TextureCombo( sdl2::TextureLoader&& textureLoader ):
	texture{ std::move( textureLoader ) },
	sprite{ texture }
{
	
}

TextureCombo::TextureCombo(TextureCombo&& toMove):
	texture{ std::move( toMove.texture ) },
	sprite{ std::move( toMove.sprite ) }
{
	sprite.setTexture(texture);
}

TextureCombo& TextureCombo::operator= (TextureCombo&& toMove)
{
	texture = std::move( toMove.texture );
	sprite = std::move( toMove.sprite );
	sprite.setTexture(texture);
	return *this;
}

TextureCombo::operator bool() const
{
	return texture;
}

void TextureCombo::draw(sdl2::RendererWindow& rndWnd) const
{
	sprite.draw(rndWnd);
}

void TextureCombo::draw(sdl2::RendererWindow& rndWnd, const Offset& pos)
{
	sprite.draw(rndWnd, pos);
}

void TextureCombo::draw(sdl2::RendererWindow& rndWnd, int xpos, int ypos)
{
	sprite.draw(rndWnd, xpos, ypos);
}

void TextureCombo::drawToCenter(sdl2::RendererWindow& rndWnd, int xpos, int ypos)
{
	sprite.drawToCenter(rndWnd, xpos, ypos);
}

void TextureCombo::resetSpritePosition(const TexturePosition& pos)
{
	sprite.setTexture(texture);
	sprite.resetDimensions();
	sprite.resetSourceRect();
	sprite.setTexturePosition(pos);
}

void TextureCombo::catchTexture()
{
	sprite.setTexture(texture);
}