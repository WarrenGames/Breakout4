#include "contexts/options/mainMenuData.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/constexprScreen.h"
#include "consts/fontsConsts.h"
#include "consts/sdlColors.h"
#include <algorithm>
#include <cassert>

optionsMenu::MainMenu::MainMenu(Essentials& essentials):
	languagesTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::OPT_MENU_MAIN_PANEL), optionsMenu::TXT_MENUS_MAX},
	fancyFont{essentials.logs.error, FANCYFONTPATH, FONT_BIG_PTSIZE},
	title{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[optionsMenu::TXT_MAIN_MENU_TITLE], WHITE_COL, TexturePosition{GAME_SCREEN_WIDTH / 2, SQR_SIZE * 2, true, true} },
	soundImage{essentials.logs, essentials.rndWnd, "textures/gameGUI/optionsVignettes/audioVignette.png", TexturePosition{GAME_SCREEN_WIDTH / 4, SQR_SIZE * 12, true, true } },
	musicImage{essentials.logs, essentials.rndWnd, "textures/gameGUI/optionsVignettes/musicVignette.png", TexturePosition{GAME_SCREEN_WIDTH * 3 / 4, SQR_SIZE * 12, true, true } },
	categoriesTexts{
		TextButton{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[optionsMenu::TXT_LANGUAGE_MENU], GREEN_COL, WHITE_COL, GAME_SCREEN_WIDTH / 4, SQR_SIZE * 6, true},
		TextButton{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[optionsMenu::TXT_GRAPHICS_MENU], GREEN_COL, WHITE_COL, GAME_SCREEN_WIDTH * 3 / 4, SQR_SIZE * 6, true},
		TextButton{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[optionsMenu::TXT_SOUND_MENU], GREEN_COL, WHITE_COL, GAME_SCREEN_WIDTH / 4, SQR_SIZE * 12, true},
		TextButton{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[optionsMenu::TXT_MUSIC_MENU], GREEN_COL, WHITE_COL, GAME_SCREEN_WIDTH * 3 / 4, SQR_SIZE * 12, true},
		TextButton{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[optionsMenu::TXT_QUIT_MENU], GREEN_COL, MEDIUM_GRAY_COL, GAME_SCREEN_WIDTH - SQR_SIZE * 3, SQR_SIZE / 2, true },
	}
{
	
}

void optionsMenu::MainMenu::drawEverything(Essentials& essentials) const
{
	soundImage.draw(essentials.rndWnd);
	musicImage.draw(essentials.rndWnd);
	title.draw(essentials.rndWnd);
	drawTextButtons(essentials);
}

void optionsMenu::MainMenu::updateButtons(Essentials& essentials)
{
	std::for_each(std::begin(categoriesTexts), std::end(categoriesTexts), 
					[&essentials](auto &btn){ btn.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT)); } );
	
}

bool optionsMenu::MainMenu::isButtonClicked(unsigned buttonNumber) const
{
	assert( buttonNumber < categoriesTexts.size() );
	return categoriesTexts[buttonNumber].buttonClicked();
}

void optionsMenu::MainMenu::drawTextButtons(Essentials& essentials) const
{
	std::for_each(std::begin(categoriesTexts), std::end(categoriesTexts), [&essentials](auto const &btn){ btn.drawButton(essentials.rndWnd); } );
}