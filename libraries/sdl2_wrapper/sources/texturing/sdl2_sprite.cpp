#include "texturing/sdl2_sprite.h"
#include "texturing/rendererWindow.h"
#include "texturing/textureLoader.h"
#include "texturing/texturePosition.h"

sdl2::Sprite::Sprite():
	texture{ nullptr },
	destRect{ 0, 0, 0, 0 },
	srcRect{ 0, 0, 0, 0 }
{
	
}

sdl2::Sprite::Sprite( const sdl2::TextureLoader& loader):
	texture{ &loader.texture },
	destRect{ 0, 0, 0, 0 },
	srcRect{ 0, 0, 0, 0 }
{
	resetDimensions();
	resetSourceRect();
}

sdl2::Sprite::Sprite( const sdl2::TextureLoader& loader, int xpos, int ypos):
	texture{ &loader.texture },
	destRect{ xpos, ypos, 0, 0 },
	srcRect{ 0, 0, 0, 0 }
{
	resetDimensions();
	resetSourceRect();
}

sdl2::Sprite::Sprite( const sdl2::TextureLoader& loader, int xpos, bool on_x_centered, int ypos, bool on_y_centered):
	texture{ &loader.texture },
	destRect{ xpos, ypos, 0, 0 },
	srcRect{ 0, 0, 0, 0 }
{
	if( *texture )
	{
		resetDimensions();
		resetSourceRect();
		setXPos(xpos, on_x_centered);
		setYPos(ypos, on_y_centered);
	}
}

sdl2::Sprite::Sprite( const sdl2::TextureLoader& loader, const TexturePosition& pos):
	texture{ &loader.texture },
	destRect{ pos.position.x, pos.position.y, 0, 0 },
	srcRect{ 0, 0, 0, 0 }
{
	if( *texture )
	{
		resetDimensions();
		resetSourceRect();
		setXPos(pos.position.x, pos.on_x_centered);
		setYPos(pos.position.y, pos.on_y_centered);
	}
}

sdl2::Sprite& sdl2::Sprite::operator=( const sdl2::TextureLoader& loader )
{
	texture = &loader.texture;
	resetDimensions();
	resetSourceRect();
	return *this;
}

sdl2::Sprite::operator bool() const
{
	if( texture )
	{
		return texture->get() != nullptr;
	}
	else{
		return false;
	}
}

bool sdl2::Sprite::isTextureLoaded() const
{
	return texture->get() != nullptr;
}

void sdl2::Sprite::draw(sdl2::RendererWindow& rndWnd, int xpos, int ypos)
{
	destRect.x = xpos;
	destRect.y = ypos;
	SDL_RenderCopy(rndWnd.getRend(), texture->get(), &srcRect, &destRect);
}

void sdl2::Sprite::draw(sdl2::RendererWindow& rndWnd, const Offset& pos)
{
	destRect.x = pos.x;
	destRect.y = pos.y;
	SDL_RenderCopy(rndWnd.getRend(), texture->get(), &srcRect, &destRect);
}

void sdl2::Sprite::drawToCenter(sdl2::RendererWindow& rndWnd, int xpos, int ypos)
{
	center_on_x(xpos);
	center_on_y(ypos);
	SDL_RenderCopy(rndWnd.getRend(), texture->get(), &srcRect, &destRect);
}

void sdl2::Sprite::drawToCenter(sdl2::RendererWindow& rndWnd, const Offset& pos)
{
	center_on_x(pos.x);
	center_on_y(pos.y);
	SDL_RenderCopy(rndWnd.getRend(), texture->get(), &srcRect, &destRect);
}

void sdl2::Sprite::setDefaultCoord(int xpos, int ypos)
{
	destRect.x = xpos;
	destRect.y = ypos;
}

void sdl2::Sprite::draw(sdl2::RendererWindow& rndWnd) const
{
	SDL_RenderCopy(rndWnd.getRend(), texture->get(), &srcRect, &destRect);
}

void sdl2::Sprite::drawWithGivenRect(sdl2::RendererWindow& rndWnd, const SDL_Rect& givenRect) const
{
	SDL_RenderCopy(rndWnd.getRend(), texture->get(), &srcRect, &givenRect);
}

void sdl2::Sprite::drawWithTwoRect(sdl2::RendererWindow& rndWnd, const SDL_Rect& newSrcRect, const SDL_Rect& newDestRect) const
{
	SDL_RenderCopy(rndWnd.getRend(), texture->get(), &newSrcRect, &newDestRect);
}

int sdl2::Sprite::width() const
{
	return destRect.w;
}

int sdl2::Sprite::height() const
{
	return destRect.h;
}

int sdl2::Sprite::x_pos() const
{
	return destRect.x;
}

int sdl2::Sprite::y_pos() const
{
	return destRect.y;
}

const SDL_Rect& sdl2::Sprite::getDrawRect() const
{
	return destRect;
}

SDL_Rect& sdl2::Sprite::getDrawRect()
{
	return destRect;
}

const SDL_Rect& sdl2::Sprite::getSrcRect() const
{
	return srcRect;
}

SDL_Rect& sdl2::Sprite::getSrcRect()
{
	return srcRect;
}

void sdl2::Sprite::center_on_x(int xpos)
{
	destRect.x = xpos - destRect.w / 2;
}

void sdl2::Sprite::center_on_y(int ypos)
{
	destRect.y = ypos - destRect.h / 2;
}

void sdl2::Sprite::setXPos(int xpos)
{
	destRect.x = xpos;
}

void sdl2::Sprite::setYPos(int ypos)
{
	destRect.y = ypos;
}

void sdl2::Sprite::setXPos(int xpos, bool centered)
{
	if( centered )
	{
		destRect.x = xpos - destRect.w / 2;
	}
	else{
		destRect.x = xpos;
	}
}

void sdl2::Sprite::setYPos(int ypos, bool centered)
{
	if( centered )
	{
		destRect.y = ypos - destRect.h / 2;
	}
	else{
		destRect.y = ypos;
	}
}
	

void sdl2::Sprite::setTexturePosition(const Offset& pos, bool centered_on_x, bool centered_on_y)
{
	setXPos(pos.x, centered_on_x);
	setYPos(pos.y, centered_on_y);
}

void sdl2::Sprite::setTexturePosition(const TexturePosition& pos)
{
	setXPos(pos.position.x, pos.on_x_centered);
	setYPos(pos.position.y, pos.on_y_centered);
}

void sdl2::Sprite::setTexture(const sdl2::TextureLoader& loader)
{
	texture = &(loader.texture);
}

void sdl2::Sprite::multiplyWidth(double widthMulti)
{
	if( widthMulti != 0 )
	{
		resetDimensions();
		destRect.w = static_cast<int>( widthMulti * destRect.w);
	}
}

void sdl2::Sprite::multiplyHeight(double heightMulti)
{
	if( heightMulti != 0 )
	{
		resetDimensions();
		destRect.h = static_cast<int>( heightMulti * destRect.h);
	}
}

void sdl2::Sprite::multiplyBoth(double multi)
{
	if( multi != 0 )
	{
		resetDimensions();
		destRect.w = static_cast<int>( multi * destRect.w);
		destRect.h = static_cast<int>( multi * destRect.h);
	}
}

void sdl2::Sprite::resetDimensions()
{
	if( *texture )
	{
		if( texture->get() )
		{
			SDL_QueryTexture(texture->get(), nullptr, nullptr, &destRect.w, &destRect.h);
		}
	}
}

void sdl2::Sprite::setWidth(int newValue)
{
	destRect.w = newValue;
}

void sdl2::Sprite::setHeight(int newValue)
{
	destRect.h = newValue;
}

void sdl2::Sprite::resetSourceRect()
{
	if( texture )
	{
		if( texture->get() )
		{
			SDL_QueryTexture(texture->get(), nullptr, nullptr, &srcRect.w, &srcRect.h);
			srcRect.x = 0;//This is not the position on the screen of the sprite, but the position of the texture clip
			srcRect.y = 0;//This is not the position on the screen of the sprite, but the position of the texture clip
		}
	}
}

void sdl2::Sprite::removeReferenceToTexture()
{
	texture = nullptr;
}

bool sdl2::loadedWithSuccess(const sdl2::Sprite& texture)
{
	return texture;
}

bool sdl2::loadingFailed(const sdl2::Sprite& texture)
{
	return false == texture;
}