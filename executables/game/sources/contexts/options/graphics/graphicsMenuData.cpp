#include "contexts/options/graphics/graphicsMenuData.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include "consts/fontsConsts.h"
#include "consts/sdlColors.h"
#include "contexts/options/graphics/graphicsOptionsConsts.h"
#include <fstream>

constexpr int BoxWidth = SQR_SIZE;
constexpr int BoxHeight = SQR_SIZE / 2;

optionsMenu::GraphicsData::GraphicsData(Essentials& essentials):
	languagesTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::OPT_MENU_GRAPHICS_PANEL), optionsMenu::TextGraphicMax},
	fancyFont{essentials.logs.error, FancyFontPath, FontBigPointSize},
	framePerSecond{ essentials.drawFreq.getFramesPerSecond() },
	frameEditBox{essentials.logs, essentials.rndWnd, SDL_Rect{ GameScreenWidth / 2, GameScreenHeight / 2 - BoxHeight / 2, BoxWidth, BoxHeight}, FontMediumPointSize, framePerSecond},
	panelTitle{ essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[optionsMenu::TextGraphicTitle], WhiteColor, TexturePosition{GameScreenWidth / 2, SQR_SIZE, true, true} },
	boxName{ essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[optionsMenu::TextGraphicBoxName], WhiteColor, TexturePosition{SQR_SIZE, GameScreenHeight / 2, false , true} },
	hintOnFrame{ essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[optionsMenu::TextGraphicHint], WhiteColor, TexturePosition{SQR_SIZE, GameScreenHeight - SQR_SIZE * 4, false, true} },
	quitButton{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[optionsMenu::TextGraphicQuit], GreenColor, MediumGrayColor, GameScreenWidth - SQR_SIZE * 3, SQR_SIZE / 2, true }
{
	
}

void optionsMenu::GraphicsData::updateBox(Essentials& essentials)
{
	frameEditBox.catchUserFocus(essentials.logs, essentials.rndWnd, essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	quitButton.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) ); 
}

void optionsMenu::GraphicsData::drawEverything(Essentials& essentials) const
{
	frameEditBox.drawBoxWithoutFocus(essentials.rndWnd);
	boxName.draw(essentials.rndWnd);
	hintOnFrame.draw(essentials.rndWnd);
	panelTitle.draw(essentials.rndWnd);
	quitButton.drawButton(essentials.rndWnd);
}

void optionsMenu::GraphicsData::writeFramePerSecondData(Essentials& essentials) const
{
	if( std::ofstream framePerSecondFile{ path::getConfigDirFile(essentials.prefPath, file::DRAW_FREQ_FILE) } )
	{
		framePerSecondFile << framePerSecond;
	}
	else{
		essentials.logs.error.wrFileOpeningError( path::getConfigDirFile(essentials.prefPath, file::DRAW_FREQ_FILE),
													"write the frame per second value.");
	}
}

unsigned optionsMenu::GraphicsData::getFramePerSecond() const
{
	return framePerSecond;
}

bool optionsMenu::GraphicsData::quitButtonClicked() const
{
	return quitButton.buttonClicked();
}