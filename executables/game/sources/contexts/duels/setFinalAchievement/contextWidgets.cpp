#include "contexts/duels/setFinalAchievement/contextWidgets.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "texts/textLoader.h" 
#include "consts/constexprScreen.h"
#include "consts/fontsConsts.h"
#include "consts/sdlColors.h"

duels::finAchiev::Widgets::Widgets(Essentials& essentials, const sdl2::Font& fancyFont, const TextsBlocks& texts, unsigned& finalScore):
	setFinalScore{essentials.logs, essentials.rndWnd, fancyFont, texts[duels::finAchiev::ScoreToReach], BlackColor, TexturePosition{SQR_SIZE, SQR_SIZE * 4, false, true} },
	runDuels{essentials.logs, essentials.rndWnd, fancyFont, texts[duels::finAchiev::StartDuels], WhiteColor, BlackColor, SQR_SIZE*4, GameScreenHeight- SQR_SIZE*2, true},
	quitContext{essentials.logs, essentials.rndWnd, fancyFont, texts[duels::finAchiev::Quit], WhiteColor, BlackColor, GameScreenWidth - SQR_SIZE*4, GameScreenHeight- SQR_SIZE*2, true},
	scoreEdition{essentials.logs, essentials.rndWnd, {SQR_SIZE*8, SQR_SIZE*4-SQR_SIZE/2, SQR_SIZE*4, SQR_SIZE}, FontBigPointSize, finalScore}	
{
	
}

void duels::finAchiev::Widgets::update(Essentials& essentials, const Offset& mousePos, bool isMouseButtonPushed)
{
	runDuels.updateButton(mousePos.x, mousePos.y, isMouseButtonPushed);
	quitContext.updateButton(mousePos.x, mousePos.y, isMouseButtonPushed);
	scoreEdition.catchUserFocus(essentials.logs, essentials.rndWnd, mousePos, isMouseButtonPushed);
}

void duels::finAchiev::Widgets::drawAll(Essentials& essentials) const
{
	setFinalScore.draw(essentials.rndWnd);
	runDuels.drawButton(essentials.rndWnd);
	quitContext.drawButton(essentials.rndWnd);
	scoreEdition.drawBoxWithoutFocus(essentials.rndWnd);
}