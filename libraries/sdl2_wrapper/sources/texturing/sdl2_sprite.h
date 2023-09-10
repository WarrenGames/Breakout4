#ifndef SDL2_SPRITE_TEXTURE_H
#define SDL2_SPRITE_TEXTURE_H

#include "wrappers/sdl2_ptr.h"

struct TexturePosition;
struct Offset;

namespace sdl2{
	class RendererWindow;
	class TextureLoader;
	
class Sprite
{
private:
	const sdl2::TexturePtr* texture;
	SDL_Rect destRect;
	SDL_Rect srcRect;

public:
	explicit Sprite();
	explicit Sprite( const sdl2::TextureLoader& loader);
	explicit Sprite( const sdl2::TextureLoader& loader, int xpos, int ypos);
	explicit Sprite( const sdl2::TextureLoader& loader, int xpos, bool on_x_centered, int ypos, bool on_y_centered);
	explicit Sprite( const sdl2::TextureLoader& loader, const TexturePosition& pos);
	Sprite& operator= ( const sdl2::TextureLoader& loader);
	
	~Sprite() = default;
	Sprite( const Sprite& ) = default;
	Sprite& operator= ( const Sprite& ) = default;
	Sprite( Sprite&& ) = default;
	Sprite& operator= ( Sprite&& ) = default;
	
	operator bool () const;
	
	bool isTextureLoaded() const;
	void draw( sdl2::RendererWindow& rndWnd, int xpos, int ypos);
	void draw( sdl2::RendererWindow& rndWnd, const Offset& pos);
	void drawToCenter( sdl2::RendererWindow& rndWnd, int xpos, int ypos);
	void drawToCenter( sdl2::RendererWindow& rndWnd, const Offset& pos);
	void setDefaultCoord(int xpos, int ypos);
	void draw( sdl2::RendererWindow& rndWnd) const;
	void drawWithGivenRect(sdl2::RendererWindow& rndWnd, const SDL_Rect& givenRect) const;
	void drawWithTwoRect(sdl2::RendererWindow& rndWnd, const SDL_Rect& newSrcRect, const SDL_Rect& newDestRect) const;
	int width() const;
	int height() const;
	int x_pos() const;
	int y_pos() const;
	const SDL_Rect& getDrawRect() const;
	SDL_Rect& getDrawRect();
	const SDL_Rect& getSrcRect() const;
	SDL_Rect& getSrcRect();
	void center_on_x(int xpos);
	void center_on_y(int ypos);
	void setXPos(int xpos);
	void setYPos(int ypos);
	void setXPos(int xpos, bool centered);
	void setYPos(int ypos, bool centered);
	void setTexturePosition(const Offset& pos, bool centered_on_x, bool centered_on_y);
	void setTexturePosition(const TexturePosition& pos);
	void setTexture(const sdl2::TextureLoader& loader);
	
	void multiplyWidth(double widthMulti);
	void multiplyHeight(double heightMulti);
	void multiplyBoth(double multi);
	void resetDimensions();
	void setWidth(int newValue);
	void setHeight(int newValue);
	
	void resetSourceRect();
	void removeReferenceToTexture();
};

bool loadedWithSuccess(const sdl2::Sprite& texture);

bool loadingFailed(const sdl2::Sprite& texture);

}

#endif //SDL2_SPRITE_TEXTURE_H