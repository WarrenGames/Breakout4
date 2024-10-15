#ifndef SCREEN_GRAPHICS_H
#define SCREEN_GRAPHICS_H

#include "texturing/verticalGradientTexture.h"
#include "duels/inGameObjects/playerInputs/inputsTypes.h"
#include "texturing/texturesCombo.h"
#include "duels/inGameObjects/playerInputs/inputsConsts.h"
#include <vector>

struct AppLogFiles;
namespace sdl2{ class RendererWindow; class Font; }
class TextsBlocks;

class DuelsInpCfgGraphics
{
private:
	TextureCombo screenBackground;
	TextureCombo screenTitle;
	TextureCombo deviceText;
	std::vector< TextureCombo > inputTexts;

public:
	DuelsInpCfgGraphics(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, const TextsBlocks& texts);
	~DuelsInpCfgGraphics() = default;
	DuelsInpCfgGraphics( const DuelsInpCfgGraphics& ) = delete;
	DuelsInpCfgGraphics& operator= ( const DuelsInpCfgGraphics& ) = delete;
	DuelsInpCfgGraphics( DuelsInpCfgGraphics&& ) = default;
	DuelsInpCfgGraphics& operator= ( DuelsInpCfgGraphics&& ) = default;
	
	void drawEverything(sdl2::RendererWindow& rndWnd) const;
	
private:
	void drawInputTexts(sdl2::RendererWindow& rndWnd) const;
	void populateInputTextsVector(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, const TextsBlocks& texts);
};

#endif //SCREEN_GRAPHICS_H