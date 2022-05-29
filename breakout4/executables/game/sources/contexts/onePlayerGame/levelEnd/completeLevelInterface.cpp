#include "contexts/onePlayerGame/levelEnd/completeLevelInterface.h"
#include "types/essentialsStruct.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "advancedDrawing/interfaceGeneratorLanguage/elementsLoadingFunctions/texturesComponent.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/constexprScreen.h"
#include "consts/fontsConsts.h"
#include "consts/sdlColors.h"

constexpr char END_LVL_GUI_SCRIPT[] = "onePlayerLevelComplete.txt";

LevelCompleteGUI::LevelCompleteGUI(Essentials& essentials):
	fancyFont{essentials.logs.error, FANCYFONTPATH, FONT_BIG_PTSIZE},
	languagesTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::ONE_PLAY_LEVEL_END), LVL_COMP_MAX}
{
	if( languagesTexts && fancyFont )
	{
		igl::texture::openScriptFile(essentials.logs, essentials.rndWnd, fancyFont, languagesTexts, texts, path::getInterfaceScript(END_LVL_GUI_SCRIPT), SQR_SIZE);
	}
}

void LevelCompleteGUI::drawLevelSum(Essentials& essentials, unsigned levelEndType) const
{
	switch( levelEndType )
	{
		case onePlGame::LEVEL_END_PARTIALLY:
			drawPartiallyCompleteLevel(essentials);
			break;
		case onePlGame::LEVEL_END_COMPLETE:
			drawFullyCompleteLevel(essentials);
			break;
		case onePlGame::LEVEL_END_SURRENDER:
			drawGameOverLevel(essentials);
			break;
	}
}

void LevelCompleteGUI::drawPartiallyCompleteLevel(Essentials& essentials) const
{	
	texts[LVL_COMP_TITLE].draw(essentials.rndWnd);
	texts[LVL_COMP_1BR_REMAINS].draw(essentials.rndWnd);
	texts[LVL_COMP_NO_BONIF].draw(essentials.rndWnd);
	texts[LVL_COMP_NO_MORE_COIN].draw(essentials.rndWnd);
	texts[LVL_COMP_CARRYON_KEYS].draw(essentials.rndWnd);
}

void LevelCompleteGUI::drawFullyCompleteLevel(Essentials& essentials) const
{	
	texts[LVL_COMP_TITLE].draw(essentials.rndWnd);
	texts[LVL_COMP_ALL_BR_DESTR].draw(essentials.rndWnd);
	texts[LVL_COMP_400_BON].draw(essentials.rndWnd);
	texts[LVL_COMP_1MORE_COIN].draw(essentials.rndWnd);
	texts[LVL_COMP_CARRYON_KEYS].draw(essentials.rndWnd);
}

void LevelCompleteGUI::drawGameOverLevel(Essentials& essentials) const
{
	texts[LVL_COMP_GAMEOVER].draw(essentials.rndWnd);
	texts[LVL_COMP_CARRYON_KEYS].draw(essentials.rndWnd);
}
