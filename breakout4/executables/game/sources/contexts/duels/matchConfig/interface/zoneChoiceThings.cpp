#include "contexts/duels/matchConfig/interface/zoneChoiceThings.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/fontsConsts.h"



ZoneChoiceThings::ZoneChoiceThings(Essentials& essentials, unsigned finalAchievement):
	quitZoneChoice{false},
	selectedZone{ duels::ZONE_STD },
	fancyFont{essentials.logs.error, FANCYFONTPATH, FONT_BIG_PTSIZE},
	screenTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::DUELS_MATCH_CONFIG), duels::MATCH_CFG_MAX},
	levelOptions{essentials.logs, essentials.prefPath},
	bonusBoxes{essentials.logs, essentials.rndWnd, levelOptions.bonuses},
	graphics{essentials, fancyFont, screenTexts, levelOptions},
	helpTexts{essentials.logs, essentials.language, essentials.rndWnd},
	inputScreenButton{essentials.logs, essentials.rndWnd, fancyFont, screenTexts[duels::MATCH_CFG_TXT_PLAYER_INP], WHITE_COL, BLACK_COL, GAME_SCREEN_WIDTH * 3 / 4 + SQR_SIZE, GAME_SCREEN_HEIGHT - SQR_SIZE*7, true},
	zoneChoiceButton{essentials.logs, essentials.rndWnd, fancyFont, screenTexts[duels::MATCH_CFG_TXT_ZONE_CHOICE], WHITE_COL, BLACK_COL, GAME_SCREEN_WIDTH * 3 / 4 + SQR_SIZE, GAME_SCREEN_HEIGHT - SQR_SIZE * 6, true},
	runZoneButton{essentials.logs, essentials.rndWnd, fancyFont, screenTexts[duels::MATCH_CFG_TXT_RUN_ZONE], WHITE_COL, BLACK_COL, GAME_SCREEN_WIDTH * 3 / 4 + SQR_SIZE, GAME_SCREEN_HEIGHT - SQR_SIZE * 5, true},
	titleText{essentials.logs, essentials.rndWnd, fancyFont, screenTexts[duels::MATCH_CFG_TXT_CONFIG], WHITE_COL, TexturePosition{GAME_SCREEN_WIDTH/2, SQR_SIZE / 2, true, true} },
	finalAchievementHint{essentials.logs, essentials.rndWnd, fancyFont, screenTexts[duels::MATCH_CFG_TXT_FIN_ACHIEV_1] + std::to_string(finalAchievement) + 
	screenTexts[duels::MATCH_CFG_TXT_FIN_ACHIEV_2], BLACK_COL, TexturePosition{GAME_SCREEN_WIDTH/2, GAME_SCREEN_HEIGHT - SQR_SIZE*3 - SQR_SIZE/2, true, true} },
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