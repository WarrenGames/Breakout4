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
	languagesTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::OptionMenuMainPanel), optionsMenu::TextMenusMax},
	fancyFont{essentials.logs.error, FancyFontPath, FontBigPointSize},
	title{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[optionsMenu::TextMainMenuTitle], WhiteColor, TexturePosition{GameScreenWidth / 2, SQR_SIZE * 2, true, true} },
	soundImage{essentials.logs, essentials.rndWnd, "textures/gameGUI/optionsVignettes/audioVignette.png", TexturePosition{GameScreenWidth / 4, SQR_SIZE * 12, true, true } },
	musicImage{essentials.logs, essentials.rndWnd, "textures/gameGUI/optionsVignettes/musicVignette.png", TexturePosition{GameScreenWidth * 3 / 4, SQR_SIZE * 12, true, true } }
{
	populateTextButtons(essentials);
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
	std::for_each(std::cbegin(categoriesTexts), std::cend(categoriesTexts), [&essentials](auto const &btn){ btn.drawButton(essentials.rndWnd); } );
}

void optionsMenu::MainMenu::populateTextButtons(Essentials& essentials)
{
	categoriesTexts.emplace_back( TextButton{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[optionsMenu::TextLanguageMenu], 
												GreenColor, WhiteColor, GameScreenWidth / 4, SQR_SIZE * 6, true} );
	categoriesTexts.emplace_back( TextButton{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[optionsMenu::TextGraphicsMenu], 
												GreenColor, WhiteColor, GameScreenWidth * 3 / 4, SQR_SIZE * 6, true});
	categoriesTexts.emplace_back( TextButton{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[optionsMenu::TextSoundMenu], 
												GreenColor, WhiteColor, GameScreenWidth / 4, SQR_SIZE * 12, true} );
	categoriesTexts.emplace_back( TextButton{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[optionsMenu::TextMusicMenu], 
												GreenColor, WhiteColor, GameScreenWidth * 3 / 4, SQR_SIZE * 12, true} );
	categoriesTexts.emplace_back( TextButton{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[optionsMenu::TextQuitMenu], 
												GreenColor, MediumGrayColor, GameScreenWidth - SQR_SIZE * 3, SQR_SIZE / 2, true } );
}
