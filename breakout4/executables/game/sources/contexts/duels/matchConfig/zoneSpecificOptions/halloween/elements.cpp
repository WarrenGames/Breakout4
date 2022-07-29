#include "contexts/duels/matchConfig/zoneSpecificOptions/halloween/elements.h"
#include "contexts/duels/zones/halloween/subObjects/halloweenConfig.h"
#include "texturing/texturePosition.h"
#include "texts/textLoader.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/fontsConsts.h"
#include "contexts/duels/matchConfig/zoneSpecificOptions/halloween/languageTexts.h"
#include <cassert>

HalloweenSpecElements::HalloweenSpecElements(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const TextsBlocks& langTexts, const sdl2::Font& arial, HalloweenConfig& halloweenConfig):
	displayWallpaperBooleanBox{logs, rndWnd, SDL_Rect{SQR_SIZE*3, SQR_SIZE*11, SQR_SIZE*3, SQR_SIZE}, FONT_BIG_PTSIZE, halloweenConfig.canDisplayWallpaper},
	displayDaytimeWallpaper{logs, rndWnd, SDL_Rect{SQR_SIZE*3, SQR_SIZE*13, SQR_SIZE*3, SQR_SIZE}, FONT_BIG_PTSIZE, halloweenConfig.wallpaperIsDaytime},
	wallpaperDisplayInfo{logs, rndWnd, arial, langTexts[language::halloween::DRAW_WALLPAPER], WHITE_COL, TexturePosition{SQR_SIZE*7, SQR_SIZE*11 + SQR_SIZE / 2, false, true} },
	wallpaperThemeIsDaytime{logs, rndWnd, arial, langTexts[language::halloween::WALLPAPER_THEME], WHITE_COL, TexturePosition{SQR_SIZE*7, SQR_SIZE*13 + SQR_SIZE/2, false, true} }, 
	title{logs, rndWnd, arial, langTexts[language::halloween::PUMPKIN_GRANULARITY], WHITE_COL, TexturePosition{GAME_SCREEN_WIDTH/2, SQR_SIZE, true, true} },
	quitBtn{logs, rndWnd, arial, langTexts[language::halloween::QUIT_SCREEN], WHITE_COL, MEDIUM_GRAY_COL, GAME_SCREEN_WIDTH - SQR_SIZE*3, SQR_SIZE*2, true}
{
	createEditBoxes(logs, rndWnd, halloweenConfig);
	createPumpkinsTextures(logs, rndWnd);
	createExplanationsAboutPumpkins(logs, rndWnd, langTexts, arial);
}

void HalloweenSpecElements::createEditBoxes(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, HalloweenConfig& halloweenConfig)
{
	if( halloweenConfig )
	{
		for( std::size_t i{0} ; i < halloweenConfig.pumpkinsSeed.size() ; ++i )
		{
			editBoxes.emplace_back(UintEditBox{logs, rndWnd, {SQR_SIZE*3, SQR_SIZE*3 + SQR_SIZE*2*static_cast<int>(i), SQR_SIZE*3, SQR_SIZE}, 
													FONT_BIG_PTSIZE, halloweenConfig.pumpkinsSeed[i]});
		}
	}
}

void HalloweenSpecElements::boxesValueEditing(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Offset& mousePosition, bool mouseButtonState)
{
	for( auto &box : editBoxes )
		box.catchUserFocus(logs, rndWnd, mousePosition, mouseButtonState);
}

void HalloweenSpecElements::catchWallpaperBoolBoxFocus(const Offset& mousePosition, bool mouseButtonState)
{
	displayWallpaperBooleanBox.catchUserFocus(mousePosition, mouseButtonState);
	displayDaytimeWallpaper.catchUserFocus(mousePosition, mouseButtonState);
}

void HalloweenSpecElements::drawEverything(sdl2::RendererWindow& rndWnd) const
{
	drawPumpkins(rndWnd);
	drawExplanationTexts(rndWnd);
	drawEditBoxes(rndWnd);
	title.draw(rndWnd);
	displayWallpaperBooleanBox.drawBox(rndWnd);
	displayDaytimeWallpaper.drawBox(rndWnd);
	wallpaperDisplayInfo.draw(rndWnd);
	wallpaperThemeIsDaytime.draw(rndWnd);
	quitBtn.drawButton(rndWnd);
}

void HalloweenSpecElements::drawPumpkins(sdl2::RendererWindow& rndWnd) const
{
	for( auto const &pumpkin : pumpkins )
		pumpkin.draw(rndWnd);
}

void HalloweenSpecElements::drawEditBoxes(sdl2::RendererWindow& rndWnd) const
{
	for( auto &box : editBoxes )
		box.drawBoxWithoutFocus(rndWnd);
}

void HalloweenSpecElements::drawExplanationTexts(sdl2::RendererWindow& rndWnd) const
{
	for( auto const &text : explanationsAboutPumpkins )
		text.draw(rndWnd);
}

void HalloweenSpecElements::createPumpkinsTextures(AppLogFiles& logs, sdl2::RendererWindow& rndWnd)
{
	pumpkins.emplace_back( TextureCombo{logs, rndWnd, "textures/gameZones/halloween/pumpkinRed.png", TexturePosition{SQR_SIZE, SQR_SIZE * 3 + SQR_SIZE / 2, true, true} } );
	pumpkins.emplace_back( TextureCombo{logs, rndWnd, "textures/gameZones/halloween/pumpkinGray.png", TexturePosition{SQR_SIZE, SQR_SIZE * 5 + SQR_SIZE / 2,true, true} } );
	pumpkins.emplace_back( TextureCombo{logs, rndWnd, "textures/gameZones/halloween/pumpkinBlue.png", TexturePosition{SQR_SIZE, SQR_SIZE * 7 + SQR_SIZE / 2, true, true} } );
	pumpkins.emplace_back( TextureCombo{logs, rndWnd, "textures/gameZones/halloween/pumpkinYellow.png", TexturePosition{SQR_SIZE, SQR_SIZE * 9 + SQR_SIZE / 2, true, true} } );
}

void HalloweenSpecElements::createExplanationsAboutPumpkins(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const TextsBlocks& langTexts, const sdl2::Font& arial)
{
	explanationsAboutPumpkins.emplace_back( TextureCombo{logs, rndWnd, arial, langTexts[language::halloween::RED_PUMPKIN], WHITE_COL, 
															TexturePosition{SQR_SIZE * 7, SQR_SIZE * 3 + SQR_SIZE / 2, false, true} } );
	explanationsAboutPumpkins.emplace_back( TextureCombo{logs, rndWnd, arial, langTexts[language::halloween::GRAY_PUMPKIN], WHITE_COL, 
															TexturePosition{SQR_SIZE * 7, SQR_SIZE * 5 + SQR_SIZE / 2, false, true} } );
	explanationsAboutPumpkins.emplace_back( TextureCombo{logs, rndWnd, arial, langTexts[language::halloween::BLUE_PUMPKIN], WHITE_COL, 
															TexturePosition{SQR_SIZE * 7, SQR_SIZE * 7 + SQR_SIZE / 2, false, true} } );
	explanationsAboutPumpkins.emplace_back( TextureCombo{logs, rndWnd, arial, langTexts[language::halloween::YELLOW_PUMPKIN], WHITE_COL, 
															TexturePosition{SQR_SIZE * 7, SQR_SIZE * 9 + SQR_SIZE / 2, false, true} } );
}
