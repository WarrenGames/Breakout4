#include "levelEnd/completeLevelInterface.h"
#include "types/essentialsStruct.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "advancedDrawing/interfaceGeneratorLanguage/elementsLoadingFunctions/texturesComponent.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/constexprScreen.h"
#include "consts/fontsConsts.h"
#include "consts/sdlColors.h"

constexpr char EndLevelGuiScript[] = "onePlayerLevelComplete.txt";

LevelCompleteGUI::LevelCompleteGUI(Essentials& essentials):
	fancyFont{essentials.logs.error, FancyFontPath, FontBigPointSize},
	languagesTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::OnePlayerLevelEnd), LevelCompleteMax}
{
	if( languagesTexts && fancyFont )
	{
		igl::texture::openScriptFile(essentials.logs, essentials.rndWnd, fancyFont, languagesTexts, texts, path::getInterfaceScript(EndLevelGuiScript), SQR_SIZE);
	}
}

void LevelCompleteGUI::drawLevelSum(Essentials& essentials, unsigned levelEndType) const
{
	switch( levelEndType )
	{
		case onePlGame::LevelEndPartially:
			drawPartiallyCompleteLevel(essentials);
			break;
		case onePlGame::LevelEndComplete:
			drawFullyCompleteLevel(essentials);
			break;
		case onePlGame::LevelEndSurrender:
			drawGameOverLevel(essentials);
			break;
	}
}

void LevelCompleteGUI::drawPartiallyCompleteLevel(Essentials& essentials) const
{	
	texts[LevelCompleteTitle].draw(essentials.rndWnd);
	texts[LevelComplete1_BrickRemains].draw(essentials.rndWnd);
	texts[LevelCompleteBonifications].draw(essentials.rndWnd);
	texts[LevelCompleteNoMoreCoin].draw(essentials.rndWnd);
	texts[LevelCompleteCarryOnKeys].draw(essentials.rndWnd);
}

void LevelCompleteGUI::drawFullyCompleteLevel(Essentials& essentials) const
{	
	texts[LevelCompleteTitle].draw(essentials.rndWnd);
	texts[LevelCompleteAllBricksDestroyed].draw(essentials.rndWnd);
	texts[LevelComplete400_Bonus].draw(essentials.rndWnd);
	texts[LevelComplete1_MoreCoin].draw(essentials.rndWnd);
	texts[LevelCompleteCarryOnKeys].draw(essentials.rndWnd);
}

void LevelCompleteGUI::drawGameOverLevel(Essentials& essentials) const
{
	texts[LevelCompleteGameOver].draw(essentials.rndWnd);
	texts[LevelCompleteCarryOnKeys].draw(essentials.rndWnd);
}
