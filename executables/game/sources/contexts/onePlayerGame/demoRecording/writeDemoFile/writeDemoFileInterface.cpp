#include "contexts/onePlayerGame/demoRecording/writeDemoFile/writeDemoFileInterface.h"
#include "types/essentialsStruct.h"
#include "crossLevel/playerData.h"
#include "levelComponents/demosObjects/demoMainPackage.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "contexts/onePlayerGame/demoRecording/writeDemoFile/getTemplatedString.h"
#include "time/dateAndTime.h"
#include "texturing/texturePosition.h"
#include "consts/fontsConsts.h"
#include "consts/sdlColors.h"
#include "consts/constPaths.h"

constexpr char LanguageFile[] = "1player_writeDemoFile.txt";

constexpr int BoxWidth = SQR_SIZE * 8;
constexpr int BoxHeight = SQR_SIZE * 1;
constexpr int StringMaxSize = 60;

demos::WriteDemoFileInterface::WriteDemoFileInterface(Essentials& essentials, const PlayerData& playerData, const demos::MainPackage& mainPackage):
	languagesTexts{essentials.logs.error, path::getLanguageFile(essentials.language, LanguageFile), demos::WriteMax},
	fancyFont{essentials.logs.error, FancyFontPath, FontMediumPointSize},
	arialFont{essentials.logs.error, ArialFontPath, FontSmallPointSize},
	fileName{ playerData.getMainLevelFileName() + returnCurrentTimeAndDate() + ".demo" },
	titleText{ essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[demos::WriteTitle], WhiteColor, TexturePosition{ GameScreenWidth / 2, SQR_SIZE, true, true} },
	fileNameText{ essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[demos::WriteFileName], WhiteColor, TexturePosition{ SQR_SIZE, SQR_SIZE * 2, false, true} },
	fileNameEditBox{ essentials.logs, essentials.rndWnd, SDL_Rect{ fileNameText.sprite.width() + SQR_SIZE * 2, SQR_SIZE * 2 - BoxHeight / 2, BoxWidth, BoxHeight}, 
						FontMediumPointSize, fileName, StringMaxSize },
	saveButton{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[demos::WriteSaveFileToDisk], GreenColor, MediumGrayColor, 
					TexturePosition{SQR_SIZE*16, SQR_SIZE*4, true, true} },
	quitButton{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[demos::WriteQuitInterface], GreenColor, MediumGrayColor, 
					TexturePosition{SQR_SIZE*4, SQR_SIZE*4, true, true} },
	savingDirectory{essentials.logs, essentials.rndWnd, arialFont, languagesTexts[demos::WriteSavingDirectory] + essentials.prefPath.getPath() + DemosFilesDirectory, WhiteColor, 
					TexturePosition{ SQR_SIZE / 2, SQR_SIZE * 5, false, true} },
	quit{false}
{
	makeStackStrings(essentials, mainPackage);
}

void demos::WriteDemoFileInterface::drawEverything(Essentials& essentials) const
{
	titleText.draw(essentials.rndWnd);
	fileNameText.draw(essentials.rndWnd);
	fileNameEditBox.drawBoxWithoutFocus(essentials.rndWnd);
	saveButton.drawButton(essentials.rndWnd);
	quitButton.drawButton(essentials.rndWnd);
	savingDirectory.draw(essentials.rndWnd);
	drawStacksStrings(essentials);
}

void demos::WriteDemoFileInterface::updateInterface(Essentials& essentials)
{
	fileNameEditBox.catchUserFocus(essentials.logs, essentials.rndWnd, essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	saveButton.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	quitButton.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
}

void demos::WriteDemoFileInterface::makeStackStrings(Essentials& essentials, const demos::MainPackage& mainPackage)
{
	stacksSumStrings.emplace_back( TextureCombo{essentials.logs, essentials.rndWnd, fancyFont, getSizeFlag(mainPackage.inputData, demos::InputDataStr), getColor(mainPackage.inputData), 
		TexturePosition{ SQR_SIZE, SQR_SIZE*7, false, true } } );
	stacksSumStrings.emplace_back( TextureCombo{essentials.logs, essentials.rndWnd, fancyFont, getSizeFlag(mainPackage.quitLevelEvent, demos::QuitLevelEventStr), getColor(mainPackage.quitLevelEvent), 
		TexturePosition{ SQR_SIZE, SQR_SIZE*8, false, true } } );
	stacksSumStrings.emplace_back( TextureCombo{essentials.logs, essentials.rndWnd, fancyFont, getSizeFlag(mainPackage.traceCrossPosition, demos::TraceCrossPositionStr), getColor(mainPackage.traceCrossPosition), 
		TexturePosition{ SQR_SIZE, SQR_SIZE*9, false, true } } );
	stacksSumStrings.emplace_back( TextureCombo{essentials.logs, essentials.rndWnd, fancyFont, getSizeFlag(mainPackage.racketPosition, demos::RacketPositionStr), getColor(mainPackage.racketPosition), 
		TexturePosition{ SQR_SIZE, SQR_SIZE*10, false, true } } );
	stacksSumStrings.emplace_back( TextureCombo{essentials.logs, essentials.rndWnd, fancyFont, getSizeFlag(mainPackage.ballPosition, demos::BallPositionStr), getColor(mainPackage.ballPosition), 
		TexturePosition{ SQR_SIZE, SQR_SIZE*11, false, true } } );
	stacksSumStrings.emplace_back( TextureCombo{essentials.logs, essentials.rndWnd, fancyFont, getSizeFlag(mainPackage.brickDestruction, demos::BrickDestructionStr), getColor(mainPackage.brickDestruction), 
		TexturePosition{ SQR_SIZE, SQR_SIZE*12, false, true } } );
}

void demos::WriteDemoFileInterface::drawStacksStrings(Essentials& essentials) const
{
	for( auto const &txt : stacksSumStrings )
	{
		txt.draw(essentials.rndWnd);
	}
}