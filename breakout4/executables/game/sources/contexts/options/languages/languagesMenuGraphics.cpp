#include "contexts/options/languages/languagesMenuGraphics.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/constexprScreen.h"
#include "consts/fontsConsts.h"
#include "consts/sdlColors.h"
#include "consts/constPaths.h"

enum{ OPT_LANG_PANEL_TITLE, OPT_LANG_PANEL_RESTART, OPT_LANG_PANEL_CUR_LANG, OPT_LANG_PANEL_SELECT_HERE, OPT_LANG_PANEL_MAX};

LanguageOptionsGraphics::LanguageOptionsGraphics(Essentials& essentials):
	isLoadingPerfect{true},
	hasLanguageChanged{false},
	langIndex{0},
	languagesStrings{essentials.logs.error, path::getLanguageFile(essentials.language, file::OPT_MENU_LANG_PANEL), OPT_LANG_PANEL_MAX},
	fancyFont{essentials.logs.error, FANCYFONTPATH, FONT_MEDIUM_PTSIZE},
	startingLanguage{essentials.logs, essentials.rndWnd, fancyFont, languagesStrings[OPT_LANG_PANEL_CUR_LANG] + essentials.language, 
						WHITE_COL, TexturePosition{GAME_SCREEN_WIDTH / 2 + SQR_SIZE, GAME_SCREEN_HEIGHT / 2, false, true} },
	screenTitle{essentials.logs, essentials.rndWnd, fancyFont, languagesStrings[OPT_LANG_PANEL_TITLE], WHITE_COL, TexturePosition{GAME_SCREEN_WIDTH / 2, SQR_SIZE, true, true} },
	restartHint{essentials.logs, essentials.rndWnd, fancyFont, languagesStrings[OPT_LANG_PANEL_RESTART], WHITE_COL, TexturePosition{SQR_SIZE, GAME_SCREEN_HEIGHT - SQR_SIZE, false, true} },
	selectHere{essentials.logs, essentials.rndWnd, fancyFont, languagesStrings[OPT_LANG_PANEL_SELECT_HERE], WHITE_COL, TexturePosition{SQR_SIZE * 3, SQR_SIZE * 3, false, true} }
{
	loadAvailableLanguages(essentials, path::getChosenLangFile(essentials.prefPath, LANGUAGES_ENUM_FILENAME) );
}
	

void LanguageOptionsGraphics::drawEverything(Essentials& essentials) const
{
	screenTitle.draw(essentials.rndWnd);
	drawButtons(essentials);
	drawSelectedLanguage(essentials);
	selectHere.draw(essentials.rndWnd);
}

void LanguageOptionsGraphics::drawButtons(Essentials& essentials) const
{
	for( auto const &button : languagesButtons )
	{
		button.drawButton(essentials.rndWnd);
	}
}

void LanguageOptionsGraphics::drawSelectedLanguage(Essentials& essentials) const
{	
	if( hasLanguageChanged )
	{
		if( langIndex < languagesTexts.size() )
		{
			languagesTexts[langIndex].draw(essentials.rndWnd);
		}
		restartHint.draw(essentials.rndWnd);
	}
	else{
		startingLanguage.draw(essentials.rndWnd);
	}
}

void LanguageOptionsGraphics::update(Essentials& essentials)
{
	for (auto &button : languagesButtons )
	{
		button.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	}
}

void LanguageOptionsGraphics::loadAvailableLanguages(Essentials& essentials, const std::string& languagesListPath)
{
	if( std::ifstream languagesListFile{ languagesListPath } )
	{
		std::string fileLine;
		while( std::getline( languagesListFile, fileLine ) )
		{
			if( fileLine[0] != '#' )
			{
				languagesList.push_back(fileLine);
			}
		}
		int yPosition{SQR_SIZE*4};
		for( auto const &line : languagesList )
		{
			languagesButtons.emplace_back(TextButton{essentials.logs, essentials.rndWnd, fancyFont, line, GREEN_COL, WHITE_COL,  SQR_SIZE * 4, yPosition, true} );
			languagesTexts.emplace_back( TextureCombo{ essentials.logs, essentials.rndWnd, fancyFont, languagesStrings[OPT_LANG_PANEL_CUR_LANG] +  line, 
														WHITE_COL, TexturePosition{GAME_SCREEN_WIDTH / 2 + SQR_SIZE, GAME_SCREEN_HEIGHT / 2, false, true} });
			yPosition += SQR_SIZE;
		}
	}
	else{
		essentials.logs.error << "Error: couldn't open the file '" << languagesListPath << "' in order to load the languages of the game.\n";
	}
}

void LanguageOptionsGraphics::changeLanguage()
{
	for( std::size_t i{0} ; i < languagesButtons.size() ; ++i )
	{
		if( languagesButtons[i].buttonClicked() )
		{
			langIndex = i;
			hasLanguageChanged = true;
		}
	}
}

void LanguageOptionsGraphics::writeNewLanguageIfChanged(Essentials& essentials)
{
	if( hasLanguageChanged && langIndex < languagesList.size() )
	{
		if( std::ofstream languageFile{ path::getChosenLangFile(essentials.prefPath, CHOSEN_LANG_FILENAME) } )
		{
			languageFile << languagesList[langIndex] << std::endl;
		}
		else{
			essentials.logs.error << "Error: couldn't open '" << path::getChosenLangFile(essentials.prefPath, CHOSEN_LANG_FILENAME) << "' file to write language change.\n";
		}
	}
}