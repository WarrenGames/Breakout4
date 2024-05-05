#include "contexts/onePlayerGame/skillLevelChoice/skillLevelChoiceGraphicalInterface.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

constexpr char SkillChoiceBackgroundTexturePath[] = "textures/wallpapers/skillChoice.png";

constexpr SDL_Color SkillButtonColor = { 191, 230, 192, 255 };

onePlGame::skillChoice::Interface::Interface(Essentials& essentials):
	fancyFont{essentials.logs.error, FancyFontPath, FontBigPointSize},
	languageTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::OnePlayerSkillLevel), onePlGame::skillChoice::TextSkillMax},
	screenBackground{essentials.logs, essentials.rndWnd, SkillChoiceBackgroundTexturePath, TexturePosition{ 0, 0, false, false } },
	screenTitle{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::skillChoice::TextChoose], WhiteColor, TexturePosition{GameScreenWidth/2, SQR_SIZE, true, true } },
	goBackButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::skillChoice::TextGoBack], GreenColor, WhiteColor, 
		TexturePosition{GameScreenWidth/2, SQR_SIZE*12, true, true} 
	}
{
	populateSkillButtons(essentials);
}

void onePlGame::skillChoice::Interface::update(const Essentials& essentials)
{
	updateSkillButtons(essentials);
	goBackButton.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT));
}

void onePlGame::skillChoice::Interface::updateSkillButtons(const Essentials& essentials)
{
	for( auto &btn : skillButtons )
	{
		btn.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	}
}

void onePlGame::skillChoice::Interface::drawEverything(Essentials& essentials)
{
	screenBackground.draw(essentials.rndWnd);
	screenTitle.draw(essentials.rndWnd);
	drawSkillButtons(essentials);
	goBackButton.drawButton(essentials.rndWnd);
}

void onePlGame::skillChoice::Interface::drawSkillButtons(Essentials& essentials) const
{
	for( auto const &btn : skillButtons )
	{
		btn.drawButton(essentials.rndWnd);
	}
}

void onePlGame::skillChoice::Interface::populateSkillButtons(Essentials& essentials)
{
	skillButtons.emplace_back( TextButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::skillChoice::TextEasySelection], GreenColor, SkillButtonColor, 
											TexturePosition{ GameScreenWidth/2, SQR_SIZE*4, true, true} } );
	skillButtons.emplace_back( TextButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::skillChoice::TextMediumSelection], GreenColor, SkillButtonColor, 
											TexturePosition{ GameScreenWidth/2, SQR_SIZE*6 + SQR_SIZE / 2, true, true} } );
	skillButtons.emplace_back( TextButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::skillChoice::TextHardSelection], GreenColor, SkillButtonColor, 
											TexturePosition{ GameScreenWidth/2, SQR_SIZE*9, true, true} } );
}
