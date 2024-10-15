#include "contexts/onePlayerGame/demoLoading/demoLoadingInterface.h"
#include "types/essentialsStruct.h"
#include "exceptions/readErrorExcept.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "texturing/texturePosition.h"
#include "consts/constexprScreen.h"
#include "consts/fontsConsts.h"
#include "consts/sdlColors.h"

enum{
	TxtDemo_Title,
	TxtDemo_Quit,
	TxtDemo_PreviousPage,
	TxtDemo_NextPage,
	TxtDemo_NoAvailableDemo,
	TxtDemo_Max
};

constexpr char LanguageFileName[] = "1player_demoLoadingInterface.txt";

demosLoading::Interface::Interface(Essentials& essentials):
	languagesTexts{essentials.logs.error, path::getLanguageFile(essentials.language, LanguageFileName), TxtDemo_Max },
	fancyFont{essentials.logs.error, FancyFontPath, FontMediumPointSize},
	demoFilesDisplayer{essentials, fancyFont},
	quitButton{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[TxtDemo_Quit], MediumGrayColor, WhiteColor, TexturePosition{ SQR_SIZE * 2, SQR_SIZE, true, true} },
	previousPage{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[TxtDemo_PreviousPage], MediumGrayColor, WhiteColor, TexturePosition{ SQR_SIZE * 2, SQR_SIZE * 3, true, true} },
	nextPage{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[TxtDemo_NextPage], MediumGrayColor, WhiteColor, 
				TexturePosition{ GameScreenWidth - SQR_SIZE * 2, SQR_SIZE * 3, true, true} },
	titleText{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[TxtDemo_Title], WhiteColor, TexturePosition{ GameScreenWidth / 2, SQR_SIZE, true, true } },
	noLoadedDemoText{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[TxtDemo_NoAvailableDemo], RedColor, TexturePosition{ GameScreenWidth / 2, GameScreenHeight / 2, true, true} },
	quitMenu{ false }
{
	
}

void demosLoading::Interface::drawEverything(Essentials& essentials) const
{
	quitButton.drawButton(essentials.rndWnd);
	previousPage.drawButton(essentials.rndWnd);
	nextPage.drawButton(essentials.rndWnd);
	titleText.draw(essentials.rndWnd);
	drawErrorString(essentials);
	drawDemoAbsence(essentials);
}

void demosLoading::Interface::drawDemoAbsence(Essentials& essentials) const
{
	if( demoFilesDisplayer.demoData.empty() )
	{
		noLoadedDemoText.draw(essentials.rndWnd);
	}
	else{
		demoFilesDisplayer.drawCurrentPage(essentials);
	}
}

void demosLoading::Interface::updateButtons(const Offset& mousePosition, bool mouseLeftButtonState)
{
	quitButton.updateButton(mousePosition, mouseLeftButtonState);
	previousPage.updateButton(mousePosition, mouseLeftButtonState);
	nextPage.updateButton(mousePosition, mouseLeftButtonState);
	demoFilesDisplayer.updateActiveButtons(mousePosition, mouseLeftButtonState);
}

void demosLoading::Interface::setErrorString(Essentials& essentials, const ReadError& e)
{
	if( const sdl2::Font arialFont{essentials.logs.error, ArialFontPath, FontMediumPointSize} )
	{
		errorString.texture.loadBlendedText(essentials.logs, essentials.rndWnd, arialFont, e.what(), RedColor );
		errorString.catchTexture();
		errorString.resetSpritePosition(TexturePosition{ GameScreenWidth / 2, GameScreenHeight - SQR_SIZE, true, true} );
	}
}

void demosLoading::Interface::drawErrorString(Essentials& essentials) const
{
	if( errorString )
	{
		errorString.draw(essentials.rndWnd);
	}
}