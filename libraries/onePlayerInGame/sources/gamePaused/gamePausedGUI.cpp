#include "gamePaused/gamePausedGUI.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

constexpr char PauseWindowTexturePath[] = "textures/gameGUI/buttons/pauseWindow0.png";

PausedGameGUI::PausedGameGUI(Essentials& essentials):
	fancyFont{essentials.logs.error, FancyFontPath, FontBigPointSize},
	languagesTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::OnePlayerPausedGame), PausedGameMax},
	pauseWindow{essentials.logs, essentials.rndWnd, PauseWindowTexturePath, TexturePosition{ GameScreenWidth / 2, GameScreenHeight / 2, true, true} },
	pauseInfos{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[PausedGameInfos], YellowColor, TexturePosition{GameScreenWidth/2, GameScreenHeight / 2 - SQR_SIZE, true, true} },
	pressEscapeGoBack{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[PausedGameGoBack], YellowColor, TexturePosition{GameScreenWidth/2, GameScreenHeight / 2, true, true} },
	quitGame{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[PausedGameQuitButton], RedColor, WhiteColor, TexturePosition{GameScreenWidth/2, GameScreenHeight / 2 + SQR_SIZE, true, true} }
{
	
}

void PausedGameGUI::updateQuitButton(const Offset& mousePosition, bool mouseLeftButton)
{
	quitGame.updateButton(mousePosition, mouseLeftButton);
}

void PausedGameGUI::drawEverything(Essentials& essentials) const
{
	pauseWindow.draw(essentials.rndWnd);
	pauseInfos.draw(essentials.rndWnd);
	pressEscapeGoBack.draw(essentials.rndWnd);
	quitGame.drawButton(essentials.rndWnd);
}

bool PausedGameGUI::isQuitButtonClicked() const
{
	return quitGame.buttonClicked();
}