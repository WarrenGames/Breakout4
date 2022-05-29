#include "contexts/onePlayerGame/gamePaused/gamePausedGUI.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

PausedGameGUI::PausedGameGUI(Essentials& essentials):
	fancyFont{essentials.logs.error, FANCYFONTPATH, FONT_BIG_PTSIZE},
	languagesTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::ONE_PLAY_PAUSED_GAME), PAUSED_GAME_MAX},
	pauseInfos{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[PAUSED_GAME_INFOS], YELLOW_COL, TexturePosition{GAME_SCREEN_WIDTH/2, GAME_SCREEN_HEIGHT - SQR_SIZE * 4, true, true} },
	pressEscapeGoBack{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[PAUSED_GAME_GOBACK], YELLOW_COL, TexturePosition{GAME_SCREEN_WIDTH/2, GAME_SCREEN_HEIGHT - SQR_SIZE * 3, true, true} },
	quitGame{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[PAUSED_GAME_QUIT_BTN], RED_COL, WHITE_COL, TexturePosition{GAME_SCREEN_WIDTH/2, GAME_SCREEN_HEIGHT - SQR_SIZE*2, true, true} }
{
	
}

void PausedGameGUI::updateQuitButton(const Offset& mousePosition, bool mouseLeftButton)
{
	quitGame.updateButton(mousePosition, mouseLeftButton);
}

void PausedGameGUI::drawEverything(Essentials& essentials) const
{
	pauseInfos.draw(essentials.rndWnd);
	pressEscapeGoBack.draw(essentials.rndWnd);
	quitGame.drawButton(essentials.rndWnd);
}

bool PausedGameGUI::isQuitButtonClicked() const
{
	return quitGame.buttonClicked();
}