#ifndef MINI_SCREEN_GUI_H
#define MINI_SCREEN_GUI_H

#include "text/sdl2ttf_font.h"
#include "texturing/texturesCombo.h"
#include <vector>

class TextsBlocks;
class RendererWindow;
struct AppLogFiles;

class MiniScreen
{
private:
	sdl2::Font fancyFont;
	std::vector< TextureCombo > textsTextures;
	TextureCombo bricksBackground;
	
public:
	explicit MiniScreen(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const TextsBlocks& texts, int squareSize, int screenWidth, int screenHeight);
	~MiniScreen() = default;
	MiniScreen( const MiniScreen& ) = delete;
	MiniScreen& operator= ( const MiniScreen& ) = delete;
	MiniScreen( MiniScreen&& ) = default;
	MiniScreen& operator= ( MiniScreen&& ) = default;
	
	operator bool () const;
	
	void drawAll(sdl2::RendererWindow& rndWnd) const;
	
private:
	void loadTextsTextures(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const TextsBlocks& texts, int screenWidth, int screenHeight);
	void setTexturesCoordinates(int squareSize);
	void drawTextsTextures(sdl2::RendererWindow& rndWnd) const;
	void logErrorsIfAny(AppLogFiles& logs);
};

#endif //MINI_SCREEN_GUI_H