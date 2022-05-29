#ifndef DUELS_SPECIFIC_HALLOWEEN_ELEMENTS_H
#define DUELS_SPECIFIC_HALLOWEEN_ELEMENTS_H

#include "texturing/texturesCombo.h"
#include "contexts/gameCommon/halloween/pumpkins/pumpkinConsts.h"
#include "widgets/editBoxes/uint_editBox.h"
#include "widgets/editBoxes/bool_editBox.h"
#include "widgets/buttons/textButtonWidget.h"
#include <iosfwd>
#include <array>
#include <vector>

struct AppLogFiles;
class TextsBlocks;
struct HalloweenConfig;

struct HalloweenSpecElements
{
	std::array< const TextureCombo, PUMPK_MAX > pumpkins;
	std::vector< UintEditBox > editBoxes;
	std::array< const TextureCombo, PUMPK_MAX > explanationsAboutPumpkins;
	BoolEditBox displayWallpaperBooleanBox;
	BoolEditBox displayDaytimeWallpaper;
	const TextureCombo wallpaperDisplayInfo;
	const TextureCombo wallpaperThemeIsDaytime;
	TextureCombo title;
	TextButton quitBtn;
	
	HalloweenSpecElements(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const TextsBlocks& langTexts, const sdl2::Font& arial, HalloweenConfig& halloweenConfig);
	void createEditBoxes(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, HalloweenConfig& halloweenConfig);
	void centerPumpkinsTextures();
	
	void boxesValueEditing(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Offset& mousePosition, bool mouseButtonState);
	void catchWallpaperBoolBoxFocus(const Offset& mousePosition, bool mouseButtonState);
	
	void drawEverything(sdl2::RendererWindow& rndWnd) const;
	void drawPumpkins(sdl2::RendererWindow& rndWnd) const;
	void drawEditBoxes(sdl2::RendererWindow& rndWnd) const;
	
	void drawExplanationTexts(sdl2::RendererWindow& rndWnd) const;
};

#endif //DUELS_SPECIFIC_HALLOWEEN_ELEMENTS_H