#include "duels/controls/objects/mainObject.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "duels/controls/inputScreenConsts.h"
#include "consts/constexprScreen.h"
#include "consts/fontsConsts.h"
#include "consts/sdlColors.h"

duels::InputScreenGlobal::InputScreenGlobal(Essentials& essentials):
	languageTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::DuelsInputScreen), duels::TextSkillMax},
	fancyFont{essentials.logs.error, FancyFontPath, FontBigPointSize},
	inputsData{essentials.logs, essentials.prefPath},
	screenGraphics{essentials.logs, essentials.rndWnd, fancyFont, languageTexts},
	inputButtons{essentials.logs, essentials.rndWnd, fancyFont, inputsData, languageTexts},
	joysticksInfos{essentials.logs, essentials.rndWnd, fancyFont, languageTexts}
{
	playerTitles.emplace_back( TextureCombo{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[duels::TextBluePlayer], BlackColor, 
											TexturePosition{SQR_SIZE*9, SQR_SIZE* 3 + SQR_SIZE/2, true, true } } );
	playerTitles.emplace_back( TextureCombo{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[duels::TextRedPlayer], BlackColor, 
											TexturePosition{ SQR_SIZE*14, SQR_SIZE* 3 + SQR_SIZE/2, true, true} } );
}

void duels::InputScreenGlobal::drawEverything(Essentials& essentials) const
{
	screenGraphics.drawEverything(essentials.rndWnd);
	inputButtons.drawAllButtons(essentials.rndWnd);
	joysticksInfos.drawEverything(essentials.rndWnd);
	drawArrayLines(essentials);
	drawPlayersTitles(essentials);
}

void duels::InputScreenGlobal::update(Essentials& essentials)
{
	inputButtons.updateButtons(essentials.logs, essentials.rndWnd, fancyFont, inputsData, languageTexts);
	inputButtons.useMouseDataForButtons(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	inputButtons.changeDeviceType(inputsData);
	inputButtons.changeKeyboardBinding(essentials.rndWnd, inputsData);
	inputButtons.changeJoystickMoveBinding(inputsData);
	inputButtons.changeJoystickActionBinding(essentials.rndWnd, inputsData);
	joysticksInfos.update(essentials);
}

void duels::InputScreenGlobal::saveInputsDataToFile(Essentials& essentials)
{
	inputsData.saveDataToFile(essentials.logs, essentials.prefPath);
}

void duels::InputScreenGlobal::runJoystickDetailsInterface(Essentials& essentials)
{
	joysticksInfos.runJoystickDetailsInterface(essentials, fancyFont);
}

void duels::InputScreenGlobal::drawArrayLines(Essentials& essentials) const
{
	essentials.rndWnd.drawRect(WhiteColor, SDL_Rect{SQR_SIZE/2,					SQR_SIZE*4, SQR_SIZE*6,	SQR_SIZE*5});
	essentials.rndWnd.drawRect(WhiteColor, SDL_Rect{SQR_SIZE*6 + SQR_SIZE / 2,	SQR_SIZE*4, SQR_SIZE*5,	SQR_SIZE*5});
	essentials.rndWnd.drawRect(WhiteColor, SDL_Rect{SQR_SIZE*11 + SQR_SIZE / 2, 	SQR_SIZE*4, SQR_SIZE*5,	SQR_SIZE*5});
	
	essentials.rndWnd.drawRect(WhiteColor, SDL_Rect{SQR_SIZE*6 + SQR_SIZE / 2, SQR_SIZE*3, SQR_SIZE * 5, SQR_SIZE});
	essentials.rndWnd.drawRect(WhiteColor, SDL_Rect{SQR_SIZE*11 + SQR_SIZE / 2, SQR_SIZE*3, SQR_SIZE*5, SQR_SIZE});
	
}

void duels::InputScreenGlobal::drawPlayersTitles(Essentials& essentials) const
{
	for( auto const &txt : playerTitles )
	{
		txt.draw(essentials.rndWnd);
	}
}