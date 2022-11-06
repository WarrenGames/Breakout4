#include "contexts/options/languages/languagesMenuGraphics.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/constexprScreen.h"
#include "consts/fontsConsts.h"
#include "consts/sdlColors.h"
#include "consts/constPaths.h"

enum{ OptionLanguagePanelTitle, OptionLanguagePanelRestart, OptionLanguagePanelCurrentLanguage, OptionLanguagePanelSelectHere, OptionLanguagePanelMax};

LanguageOptionsGraphics::LanguageOptionsGraphics(Essentials& essentials):
	isLoadingPerfect{true},
	hasLanguageChanged{false},
	langIndex{0},
	languagesStrings{essentials.logs.error, path::getLanguageFile(essentials.language, file::OPT_MENU_LANG_PANEL), OptionLanguagePanelMax},
	fancyFont{essentials.logs.error, FancyFontPath, FontMediumPointSize},
	startingLanguage{essentials.logs, essentials.rndWnd, fancyFont, languagesStrings[OptionLanguagePanelCurrentLanguage] + essentials.language, 
						WhiteColor, TexturePosition{GameScreenWidth / 2 + SQR_SIZE, GameScreenHeight / 2, false, true} },
	screenTitle{essentials.logs, essentials.rndWnd, fancyFont, languagesStrings[OptionLanguagePanelTitle], WhiteColor, TexturePosition{GameScreenWidth / 2, SQR_SIZE, true, true} },
	restartHint{essentials.logs, essentials.rndWnd, fancyFont, languagesStrings[OptionLanguagePanelRestart], WhiteColor, TexturePosition{SQR_SIZE, GameScreenHeight - SQR_SIZE, false, true} },
	selectHere{essentials.logs, essentials.rndWnd, fancyFont, languagesStrings[OptionLanguagePanelSelectHere], WhiteColor, TexturePosition{SQR_SIZE * 3, SQR_SIZE * 3, false, true} }
{
	loadAvailableLanguages(essentials, path::getChosenLangFile(essentials.prefPath, LanguagesEnumFileName) );
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
			languagesButtons.emplace_back(TextButton{essentials.logs, essentials.rndWnd, fancyFont, line, GreenColor, WhiteColor,  SQR_SIZE * 4, yPosition, true} );
			languagesTexts.emplace_back( TextureCombo{ essentials.logs, essentials.rndWnd, fancyFont, languagesStrings[OptionLanguagePanelCurrentLanguage] +  line, 
														WhiteColor, TexturePosition{GameScreenWidth / 2 + SQR_SIZE, GameScreenHeight / 2, false, true} });
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
		if( std::ofstream languageFile{ path::getChosenLangFile(essentials.prefPath, ChosenLanguageFileName) } )
		{
			languageFile << languagesList[langIndex] << std::endl;
		}
		else{
			essentials.logs.error << "Error: couldn't open '" << path::getChosenLangFile(essentials.prefPath, ChosenLanguageFileName) << "' file to write language change.\n";
		}
	}
}