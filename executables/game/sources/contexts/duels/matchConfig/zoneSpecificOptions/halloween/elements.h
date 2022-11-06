#ifndef DUELS_SPECIFIC_HALLOWEEN_ELEMENTS_H
#define DUELS_SPECIFIC_HALLOWEEN_ELEMENTS_H

#include "texturing/texturesCombo.h"
#include "contexts/gameCommon/halloween/pumpkins/pumpkinConsts.h"
#include "widgets/editBoxes/uint_editBox.h"
#include "widgets/editBoxes/bool_editBox.h"
#include "widgets/buttons/textButtonWidget.h"
#include <vector>

struct AppLogFiles;
class TextsBlocks;
struct HalloweenConfig;

struct HalloweenSpecElements
{
	std::vector< TextureCombo > pumpkins;
	std::vector< UintEditBox > editBoxes;
	std::vector< TextureCombo > explanationsAboutPumpkins;
	BoolEditBox displayWallpaperBooleanBox;
	BoolEditBox displayDaytimeWallpaper;
	const TextureCombo wallpaperDisplayInfo;
	const TextureCombo wallpaperThemeIsDaytime;
	const TextureCombo title;
	TextButton quitBtn;
	
	HalloweenSpecElements(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const TextsBlocks& langTexts, const sdl2::Font& arial, HalloweenConfig& halloweenConfig);
	~HalloweenSpecElements() = default;
	HalloweenSpecElements( const HalloweenSpecElements& ) = delete;
	HalloweenSpecElements& operator= ( const HalloweenSpecElements& ) = delete;
	HalloweenSpecElements( HalloweenSpecElements&& ) = default;
	HalloweenSpecElements& operator= ( HalloweenSpecElements&& ) = default;
	
	void createEditBoxes(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, HalloweenConfig& halloweenConfig);
	void centerPumpkinsTextures();
	
	void boxesValueEditing(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Offset& mousePosition, bool mouseButtonState);
	void catchWallpaperBoolBoxFocus(const Offset& mousePosition, bool mouseButtonState);
	
	void drawEverything(sdl2::RendererWindow& rndWnd) const;
	void drawPumpkins(sdl2::RendererWindow& rndWnd) const;
	void drawEditBoxes(sdl2::RendererWindow& rndWnd) const;
	
	void drawExplanationTexts(sdl2::RendererWindow& rndWnd) const;
	
	void createPumpkinsTextures(AppLogFiles& logs, sdl2::RendererWindow& rndWnd);
	void createExplanationsAboutPumpkins(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const TextsBlocks& langTexts, const sdl2::Font& arial);
};

#endif //DUELS_SPECIFIC_HALLOWEEN_ELEMENTS_H