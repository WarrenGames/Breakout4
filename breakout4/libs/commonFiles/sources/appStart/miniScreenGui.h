#ifndef MINI_SCREEN_GUI_H
#define MINI_SCREEN_GUI_H

#include "text/sdl2ttf_font.h"
#include "texturing/texturesCombo.h"

class TextsBlocks;
class RendererWindow;
struct AppLogFiles;

class MiniScreen
{
private:
	bool isLoadingPerfect;
	const sdl2::Font fancyFont;
	const TextureCombo f1_fullScreenTxt;
	const TextureCombo f5_windowedTxt;
	const TextureCombo betaVersion;
	const TextureCombo bricksBackground;
	
public:
	explicit MiniScreen(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const TextsBlocks& texts, int squareSize, int screenWidth, int screenHeight);
	~MiniScreen() = default;
	MiniScreen( const MiniScreen& ) = delete;
	MiniScreen& operator= ( const MiniScreen& ) = delete;
	MiniScreen( MiniScreen&& ) = default;
	MiniScreen& operator= ( MiniScreen&& ) = default;
	
	operator bool () const;
	
	void drawAll(sdl2::RendererWindow& rndWnd) const;
};

#endif //MINI_SCREEN_GUI_H