#include "contexts/duels/matchConfig/interface/zoneChoiceThings.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/fontsConsts.h"



ZoneChoiceThings::ZoneChoiceThings(Essentials& essentials, unsigned finalAchievement):
	quitZoneChoice{false},
	selectedZone{ duels::ZoneStandard },
	fancyFont{essentials.logs.error, FancyFontPath, FontBigPointSize},
	screenTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::DUELS_MATCH_CONFIG), duels::MatchConfigTextMax},
	levelOptions{essentials.logs, essentials.prefPath},
	bonusBoxes{essentials.logs, essentials.rndWnd, levelOptions.bonuses},
	graphics{essentials, fancyFont, screenTexts, levelOptions},
	helpTexts{essentials.logs, essentials.language, essentials.rndWnd},
	inputScreenButton{essentials.logs, essentials.rndWnd, fancyFont, screenTexts[duels::MatchConfigTextPlayerInput], WhiteColor, BlackColor, GameScreenWidth * 3 / 4 + SQR_SIZE, GameScreenHeight - SQR_SIZE*7, true},
	zoneChoiceButton{essentials.logs, essentials.rndWnd, fancyFont, screenTexts[duels::MatchConfigTextZoneChoice], WhiteColor, BlackColor, GameScreenWidth * 3 / 4 + SQR_SIZE, GameScreenHeight - SQR_SIZE * 6, true},
	runZoneButton{essentials.logs, essentials.rndWnd, fancyFont, screenTexts[duels::MatchConfigTextRunZone], WhiteColor, BlackColor, GameScreenWidth * 3 / 4 + SQR_SIZE, GameScreenHeight - SQR_SIZE * 5, true},
	titleText{essentials.logs, essentials.rndWnd, fancyFont, screenTexts[duels::MatchConfigTextConfig], WhiteColor, TexturePosition{GameScreenWidth/2, SQR_SIZE / 2, true, true} },
	finalAchievementHint{essentials.logs, essentials.rndWnd, fancyFont, screenTexts[duels::MatchConfigTextAchieve1] + std::to_string(finalAchievement) + 
	screenTexts[duels::MatchConfigTextAchieve2], BlackColor, TexturePosition{GameScreenWidth/2, GameScreenHeight - SQR_SIZE*3 - SQR_SIZE/2, true, true} },
	ballAndCoinOptions{essentials.logs, essentials.language, essentials.rndWnd, fancyFont, levelOptions}
{
	
}

void ZoneChoiceThings::drawEverything(Essentials& essentials, const Offset& mousePosition)
{
	graphics.drawEverything(essentials, selectedZone);
	bonusBoxes.drawBoxes(essentials.rndWnd);
	displayHelpText(essentials, mousePosition);
	inputScreenButton.drawButton(essentials.rndWnd);
	zoneChoiceButton.drawButton(essentials.rndWnd);
	runZoneButton.drawButton(essentials.rndWnd);
	ballAndCoinOptions.drawEverything(essentials.rndWnd);
	finalAchievementHint.draw(essentials.rndWnd);
	titleText.draw(essentials.rndWnd);
}

void ZoneChoiceThings::displayHelpText(Essentials& essentials, const Offset& mousePosition) const
{
	displayBonusesVignettesHelpText(essentials, mousePosition);
}

void ZoneChoiceThings::displayBonusesVignettesHelpText(Essentials& essentials, const Offset& mousePosition) const
{
	int editBoxIndex{ bonusBoxes.getIndexOfBoxWithMouseOver(mousePosition) };
	
	if( editBoxIndex >= 0 )
	{
		helpTexts.drawBonusesVignetteText(essentials.rndWnd, editBoxIndex);
	}
}

void ZoneChoiceThings::catchUserFocus(Essentials& essentials, const Offset& mousePosition, bool buttonState)
{
	bonusBoxes.catchUserFocus(essentials.logs, essentials.rndWnd, mousePosition, buttonState);
	ballAndCoinOptions.catchUserFocus(essentials.logs, essentials.rndWnd, mousePosition, buttonState);
}

void ZoneChoiceThings::updateScoreGraphics(Essentials& essentials)
{
	graphics.changeScoreGraphics(essentials, fancyFont, levelOptions);
}