#ifndef VOLUMEBAR_H
#define VOLUMEBAR_H

#include "texturing/texturesCombo.h"

struct Offset;
namespace sdl2{ class RendererWindow; }
struct Essentials;

class VolumeBar
{
private:
	int soundVolume;
	int minimum;
	int maximum;
	TextureCombo gradient;
	TextureCombo cursor;

public:
	explicit VolumeBar(Essentials& essentials, const SDL_Rect& rect, const SDL_Color& lcol, const SDL_Color& rcol, const Offset& boundValues, int startValue);
	~VolumeBar() = default;
	VolumeBar( const VolumeBar& ) = delete;
	VolumeBar& operator= (const VolumeBar& ) = delete;
	VolumeBar( VolumeBar&& ) = default;
	VolumeBar& operator= ( VolumeBar&& ) = default;
	
	void drawAll(sdl2::RendererWindow& rndWnd) const;
	void drawBar(sdl2::RendererWindow& rndWnd) const;
	void drawCursor(sdl2::RendererWindow& rndWnd) const;
	void changeVolumeLevel(const Offset& mousePosition, bool buttonState);
	int getVolume() const;
	void setVolume(int newValue);
	void setCursorPos();
};

#endif//VOLUMEBAR_H