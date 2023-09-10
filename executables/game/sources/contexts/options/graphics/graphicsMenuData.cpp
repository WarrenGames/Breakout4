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
	languagesTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::OptionMenuGraphicsPanel), optionsMenu::TextGraphicMax},
	fancyFont{essentials.logs.error, FancyFontPath, FontBigPointSize},
	framePerSecond{ essentials.drawFreq.getFramesPerSecond() },
	frameEditBox{essentials.logs, essentials.rndWnd, SDL_Rect{ GameScreenWidth / 2, GameScreenHeight / 2 - BoxHeight / 2, BoxWidth, BoxHeight}, FontMediumPointSize, framePerSecond},
	displaySdl2Logo{true},
	displayLogoEditBox{essentials.logs, essentials.rndWnd, SDL_Rect{ GameScreenWidth / 2 + SQR_SIZE * 2, GameScreenHeight / 2 - SQR_SIZE * 4 - BoxHeight / 2, BoxWidth, BoxHeight},
							FontMediumPointSize, displaySdl2Logo},
	panelTitle{ essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[optionsMenu::TextGraphicTitle], WhiteColor, TexturePosition{GameScreenWidth / 2, SQR_SIZE, true, true} },
	displayLogoInfoText{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[optionsMenu::TextGraphicLogoDisplay], WhiteColor, 
							TexturePosition{SQR_SIZE, GameScreenHeight / 2 - SQR_SIZE * 4, false, true} },
	boxName{ essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[optionsMenu::TextGraphicBoxName], WhiteColor, TexturePosition{SQR_SIZE, GameScreenHeight / 2, false , true} },
	hintOnFrame{ essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[optionsMenu::TextGraphicHint], WhiteColor, TexturePosition{SQR_SIZE, GameScreenHeight - SQR_SIZE * 4, false, true} },
	quitButton{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[optionsMenu::TextGraphicQuit], GreenColor, MediumGrayColor, GameScreenWidth - SQR_SIZE * 3, SQR_SIZE / 2, true }
{
	readSdl2LogoDisplayingFile(essentials);
}

void optionsMenu::GraphicsData::updateBox(Essentials& essentials)
{
	frameEditBox.catchUserFocus(essentials.logs, essentials.rndWnd, essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	displayLogoEditBox.catchUserFocus(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	quitButton.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) ); 
}

void optionsMenu::GraphicsData::drawEverything(Essentials& essentials) const
{
	frameEditBox.drawBoxWithoutFocus(essentials.rndWnd);
	displayLogoInfoText.draw(essentials.rndWnd);
	displayLogoEditBox.drawBox(essentials.rndWnd);
	boxName.draw(essentials.rndWnd);
	hintOnFrame.draw(essentials.rndWnd);
	panelTitle.draw(essentials.rndWnd);
	quitButton.drawButton(essentials.rndWnd);
}

void optionsMenu::GraphicsData::writeFramePerSecondData(Essentials& essentials) const
{
	if( std::ofstream framePerSecondFile{ path::getConfigDirFile(essentials.prefPath, file::DrawFrequencyFile) } )
	{
		framePerSecondFile << framePerSecond;
	}
	else{
		essentials.logs.error.wrFileOpeningError( path::getConfigDirFile(essentials.prefPath, file::DrawFrequencyFile),
													"write the frame per second value.");
	}
}

void optionsMenu::GraphicsData::writeSdl2LogoDisplaying(Essentials& essentials) const
{
	if( std::ofstream logoDisplayStatusFile{ path::getConfigDirFile(essentials.prefPath, file::DisplaySdl2LogoStatusFile) } )
	{
		logoDisplayStatusFile << displaySdl2Logo;
	}
}

void optionsMenu::GraphicsData::writeDataToFiles(Essentials& essentials) const
{
	writeFramePerSecondData(essentials);
	writeSdl2LogoDisplaying(essentials);
}

unsigned optionsMenu::GraphicsData::getFramePerSecond() const
{
	return framePerSecond;
}

bool optionsMenu::GraphicsData::quitButtonClicked() const
{
	return quitButton.buttonClicked();
}

void optionsMenu::GraphicsData::readSdl2LogoDisplayingFile(Essentials& essentials)
{
	if( std::ifstream logoDisplayStatusFile{ path::getConfigDirFile(essentials.prefPath, file::DisplaySdl2LogoStatusFile) } )
	{
		logoDisplayStatusFile >> displaySdl2Logo;
	}
}