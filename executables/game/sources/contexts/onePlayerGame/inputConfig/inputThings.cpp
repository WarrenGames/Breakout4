#include "contexts/onePlayerGame/inputConfig/inputThings.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "keycodes/keycodesOverload.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include <cassert>

constexpr int ButtonWidth = SQR_SIZE * 4;
constexpr int ButtonHeight = SQR_SIZE;

onePlGame::InputThings::InputThings(Essentials& essentials):
	isLoadingPerfect{true},
	inputData{essentials},
	languageTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::ONE_PLAY_INPUT_CFG), onePlGame::LangInputMax},
	fancyFont{essentials.logs.error, FancyFontPath, FontBigPointSize},
	staticGraphics{essentials, fancyFont, languageTexts},
	axisThresholdBox{essentials.logs, essentials.rndWnd, SDL_Rect{SQR_SIZE*6, GameScreenHeight-SQR_SIZE*3/2, SQR_SIZE*3, SQR_SIZE}, FontBigPointSize, inputData.joystickData.axisMoveThreshold},
	joystickMenu{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::LangInputJoystickInfos], BlackColor, {SQR_SIZE * 10, GameScreenHeight - SQR_SIZE - ButtonHeight / 2, ButtonWidth, ButtonHeight}, GreenColor}
{
	createJoystickGraphicalStatus(essentials);
	createKeycodesInputsButtons(essentials);
	createJoystickInputButtons(essentials);
	createMoveCrossButtons(essentials);
}

onePlGame::InputThings::operator bool() const
{
	return isLoadingPerfect;
}

void onePlGame::InputThings::createKeycodesInputsButtons(Essentials& essentials)
{
	for( std::size_t i{0} ; i < onePlGame::InputMax ; ++i )
	{
		keycodesInputsTexts.emplace_back( HighLightButton{essentials.logs, essentials.rndWnd, fancyFont, getKeycodeString(i), BlackColor, 
															{SQR_SIZE*8, SQR_SIZE*(3 + static_cast<int>(i) ), ButtonWidth, ButtonHeight}, GreenColor} );
	}
}

void onePlGame::InputThings::createJoystickInputButtons(Essentials& essentials)
{
	joystickInputsTexts.emplace_back( HighLightButton{essentials.logs, essentials.rndWnd, fancyFont, getJoystickMoveString(), BlackColor, {SQR_SIZE*14, SQR_SIZE*3, ButtonWidth, ButtonHeight}, GreenColor} );
	joystickInputsTexts.emplace_back( HighLightButton{essentials.logs, essentials.rndWnd, fancyFont, getJoystickMoveString(), BlackColor, {SQR_SIZE*14, SQR_SIZE*4, ButtonWidth, ButtonHeight}, GreenColor} );
	joystickInputsTexts.emplace_back( HighLightButton{essentials.logs, essentials.rndWnd, fancyFont, getJoystickBtnString(onePlGame::JoysticButtonBallTrace), BlackColor, {SQR_SIZE*14, SQR_SIZE*5, ButtonWidth, ButtonHeight}, GreenColor} );
	joystickInputsTexts.emplace_back( HighLightButton{essentials.logs, essentials.rndWnd, fancyFont, getJoystickBtnString(onePlGame::JoysticButtonSearchBag), BlackColor, {SQR_SIZE*14, SQR_SIZE*6, ButtonWidth, ButtonHeight}, GreenColor} );
	joystickInputsTexts.emplace_back( HighLightButton{essentials.logs, essentials.rndWnd, fancyFont, getJoystickBtnString(onePlGame::JoysticButtonSwitch), BlackColor, {SQR_SIZE*14, SQR_SIZE*7, ButtonWidth, ButtonHeight}, GreenColor} );
}

void onePlGame::InputThings::createMoveCrossButtons(Essentials& essentials)
{
	moveCross.emplace_back( HighLightButton{essentials.logs, essentials.rndWnd, fancyFont, getJoystickCrossMoveString(onePlGame::JoystickCrossMoveX), BlackColor, {SQR_SIZE*14, SQR_SIZE*8, ButtonWidth, ButtonHeight}, GreenColor} );
	moveCross.emplace_back( HighLightButton{essentials.logs, essentials.rndWnd, fancyFont, getJoystickCrossMoveString(onePlGame::JoystickCrossMoveY), BlackColor, {SQR_SIZE*14, SQR_SIZE*9, ButtonWidth, ButtonHeight}, GreenColor} );
}

void onePlGame::InputThings::createJoystickGraphicalStatus(Essentials& essentials)
{
	if( inputData.joystickData.joystickEntity )
	{
		joystickName.texture.loadBlendedText(essentials.logs, essentials.rndWnd, fancyFont, "Joystick: " + inputData.joystickData.joystickEntity.getName(), BlackColor);
		joystickName.resetSpritePosition( TexturePosition{SQR_SIZE, GameScreenHeight - SQR_SIZE*2, false, true} );
	}
	else{
		joystickName.texture.loadBlendedText(essentials.logs, essentials.rndWnd, fancyFont, inputData.joystickData.joystickEntity.getLoadingStatus(), BlackColor);
		joystickName.resetSpritePosition( TexturePosition{SQR_SIZE, GameScreenHeight-SQR_SIZE*2, false, true} );
	}
}

void onePlGame::InputThings::drawKeycodesButtons(Essentials& essentials) const
{
	for( const auto &btn : keycodesInputsTexts )
	{
		btn.drawButton(essentials.rndWnd);
	}
}

void onePlGame::InputThings::drawJoystickButtons(Essentials& essentials) const
{
	for( const auto &btn : joystickInputsTexts )
	{
		btn.drawButton(essentials.rndWnd);
	}
}

void onePlGame::InputThings::drawJoystickCrossButtons(Essentials& essentials) const
{
	for( auto const &btn : moveCross )
	{
		btn.drawButton(essentials.rndWnd);
	}
}

void onePlGame::InputThings::drawEverything(Essentials& essentials) const
{
	if( essentials.drawFreq.canDrawGame() )
	{
		staticGraphics.drawEverything(essentials);
		staticGraphics.drawInputArrayLines(essentials);
		drawKeycodesButtons(essentials);
		drawJoystickButtons(essentials);
		drawJoystickCrossButtons(essentials);
		joystickName.draw(essentials.rndWnd);
		joystickMenu.drawButton(essentials.rndWnd);
		axisThresholdBox.drawBoxWithoutFocus(essentials.rndWnd);
		essentials.rndWnd.displayRenderer();
	}
}

void onePlGame::InputThings::updateEverything(Essentials& essentials)
{
	updateKeycodesButtons(essentials);
	updateJoystickButtons(essentials);
	updateJoystickCrossButtons(essentials);
	changeKeycodesButtonsString(essentials);
	changeJoystickButtonsStrings(essentials);
	changeJoystickMoveStrings(essentials);
	axisThresholdBox.catchUserFocus(essentials.logs, essentials.rndWnd, essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	changeCrossMoveStrings(essentials);
	joystickMenu.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT));
}

void onePlGame::InputThings::updateKeycodesButtons(Essentials& essentials)
{
	for( auto &btn : keycodesInputsTexts )
	{
		btn.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	}
}

void onePlGame::InputThings::updateJoystickButtons(Essentials& essentials)
{
	for( auto & btn : joystickInputsTexts )
	{
		btn.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	}
}

void onePlGame::InputThings::updateJoystickCrossButtons(Essentials& essentials)
{
	for( auto & btn : moveCross )
	{
		btn.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	}
}

void onePlGame::InputThings::changeKeycodesButtonsString(Essentials& essentials)
{
	for( std::size_t i{0} ; i < keycodesInputsTexts.size() ; ++i )
	{
		if( keycodesInputsTexts[i].buttonClicked() )
		{
			waitForKeycodeToBePushed(essentials, keycodesInputsTexts[i], i);
		}
	}
}

void onePlGame::InputThings::changeJoystickButtonsStrings(Essentials& essentials)
{
	readJoyBtnHighlightBtn(essentials, joystickInputsTexts[onePlGame::InputBallTrace], onePlGame::JoysticButtonBallTrace);
	readJoyBtnHighlightBtn(essentials, joystickInputsTexts[onePlGame::InputLookBag], onePlGame::JoysticButtonSearchBag);
	readJoyBtnHighlightBtn(essentials, joystickInputsTexts[onePlGame::InputSwitch], onePlGame::JoysticButtonSwitch);
}

void onePlGame::InputThings::changeJoystickMoveStrings(Essentials& essentials)
{
	if( joystickInputsTexts[onePlGame::InputMoveLeft].buttonClicked() || joystickInputsTexts[onePlGame::InputMoveRight].buttonClicked() )
	{
		if( inputData.joystickData.joystickEntity )
		{
			tweakJoyAxesAndHatsNum();
			joystickInputsTexts[onePlGame::InputMoveLeft].changeText(essentials.logs, essentials.rndWnd, fancyFont, getJoystickMoveString(), BlackColor);
			joystickInputsTexts[onePlGame::InputMoveRight].changeText(essentials.logs, essentials.rndWnd, fancyFont, getJoystickMoveString(), BlackColor);
		}
	}
}

void onePlGame::InputThings::tweakJoyAxesAndHatsNum()
{
	if( inputData.joystickData.joyMoveType == onePlGame::JoystickMoveAxes )
	{
		tweakJoyAxes();
	}
	else if( inputData.joystickData.joyMoveType == onePlGame::JoystickMoveHats )
	{
		tweakJoyHats();
	}
	else{
		tweakJoyMovError();
	}
}

void onePlGame::InputThings::tweakJoyAxes()
{
	if( inputData.joystickData.axisOrHatNum + 1 < inputData.joystickData.joystickEntity.getAxesNumber() )
	{
		inputData.joystickData.axisOrHatNum++;
	}
	else{
		inputData.joystickData.joyMoveType = onePlGame::JoystickMoveHats;
		inputData.joystickData.axisOrHatNum = 0;
	}
}

void onePlGame::InputThings::tweakJoyHats()
{
	if( inputData.joystickData.axisOrHatNum + 1 < inputData.joystickData.joystickEntity.getHatsNumber() )
	{
		inputData.joystickData.axisOrHatNum++;
	}
	else{
		inputData.joystickData.joyMoveType = onePlGame::JoystickMoveAxes;
		inputData.joystickData.axisOrHatNum = 0;
	}
}

void onePlGame::InputThings::tweakJoyMovError()
{
	inputData.joystickData.joyMoveType = onePlGame::JoystickMoveAxes;
	inputData.joystickData.axisOrHatNum = 0;
}

void onePlGame::InputThings::readJoyBtnHighlightBtn(Essentials& essentials, HighLightButton& highlightButton, std::size_t buttonIndex)
{
	if( highlightButton.buttonClicked() )
	{
		waitForJoyBtnToBePushed(essentials, highlightButton, buttonIndex);
	}
}

void onePlGame::InputThings::waitForKeycodeToBePushed(Essentials& essentials, HighLightButton& highlightButton, std::size_t keycodeIndex)
{
	staticGraphics.askInputTextures[PushNewKey].draw(essentials.rndWnd);
	essentials.rndWnd.displayRenderer();
	bool quitWaitingState{false};
	SDL_Event event;
	while( false == quitWaitingState )
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_KEYDOWN:
				if( event.key.keysym.sym == SDLK_ESCAPE )
				{
					quitWaitingState = true;
				}
				else{
					inputData.customKeys[keycodeIndex] = event.key.keysym.sym;
					highlightButton.changeText(essentials.logs, essentials.rndWnd, fancyFont, getNameFromKeycode(event.key.keysym.sym), BlackColor);
					quitWaitingState = true;
				}
				break;
			case SDL_QUIT:
				quitWaitingState = true;
				break;
		}
	}
}

void onePlGame::InputThings::waitForJoyBtnToBePushed(Essentials& essentials, HighLightButton& highlightButton, std::size_t buttonIndex)
{
	staticGraphics.askInputTextures[PushNewButton].draw(essentials.rndWnd);
	essentials.rndWnd.displayRenderer();
	bool quitWaitingState{false};
	SDL_Event event;
	while( false == quitWaitingState )
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_KEYDOWN:
				if( event.key.keysym.sym == SDLK_ESCAPE )
				{
					quitWaitingState = true;
				}
				break;
			case SDL_JOYBUTTONDOWN:
				inputData.joystickData.joyButtons[buttonIndex] = static_cast<unsigned>(event.jbutton.button);
				highlightButton.changeText(essentials.logs, essentials.rndWnd, fancyFont, getJoystickBtnString(buttonIndex), BlackColor);
				quitWaitingState = true;
				break;
			case SDL_QUIT:
				quitWaitingState = true;
				break;
		}
	}
}

void onePlGame::InputThings::changeCrossMoveStrings(Essentials& essentials)
{
	for( std::size_t i{0} ; i < onePlGame::JoystickCrossMoveMax ; ++i )
	{
		if( moveCross[i].buttonClicked() && inputData.joystickData.joystickEntity )
		{
			tweakCrossMoveNums(inputData.joystickData.crossNum[i]);
			for( std::size_t i{0} ; i < moveCross.size() ; ++i )
			{
				moveCross[i].changeText(essentials.logs, essentials.rndWnd, fancyFont, getJoystickCrossMoveString(i), BlackColor);
			}
		}
	}
}

void onePlGame::InputThings::tweakCrossMoveNums(unsigned& crossMoveNum)
{
	if( inputData.joystickData.crossMoveType == onePlGame::JoystickMoveAxes )
	{
		tweakCrossMoveAxes(crossMoveNum);
	}
	else if( inputData.joystickData.crossMoveType == onePlGame::JoystickMoveHats )
	{
		tweakCrossMoveHats(crossMoveNum);
	}
	else{
		tweakCrossMoveError();
	}
}

void onePlGame::InputThings::tweakCrossMoveAxes(unsigned& crossMoveNum)
{
	if( crossMoveNum + 1 < inputData.joystickData.joystickEntity.getAxesNumber() )
	{
		crossMoveNum++;
	}
	else{
		inputData.joystickData.crossMoveType = onePlGame::JoystickMoveHats;
		inputData.joystickData.crossNum[onePlGame::JoystickCrossMoveX] = 0;
		inputData.joystickData.crossNum[onePlGame::JoystickCrossMoveY] = 0;
	}
}

void onePlGame::InputThings::tweakCrossMoveHats(unsigned& crossMoveNum)
{
	if( crossMoveNum + 1 < inputData.joystickData.joystickEntity.getHatsNumber() )
	{
		inputData.joystickData.crossNum[onePlGame::JoystickCrossMoveX]++;
		inputData.joystickData.crossNum[onePlGame::JoystickCrossMoveY]++;
	}
	else{
		inputData.joystickData.crossMoveType = onePlGame::JoystickMoveAxes;
		inputData.joystickData.crossNum[onePlGame::JoystickCrossMoveX] = 0;
		inputData.joystickData.crossNum[onePlGame::JoystickCrossMoveY] = 0;
	}
}

void onePlGame::InputThings::tweakCrossMoveError()
{
	inputData.joystickData.crossMoveType = onePlGame::JoystickMoveAxes;
	inputData.joystickData.crossNum[onePlGame::JoystickCrossMoveX] = 0;
	inputData.joystickData.crossNum[onePlGame::JoystickCrossMoveY] = 0;
}

std::string onePlGame::InputThings::getKeycodeString(std::size_t arrayIndex)
{
	assert( arrayIndex < onePlGame::InputMax );
	if( inputData.isLoadingPerfect )
	{
		return getNameFromKeycode(inputData.customKeys[arrayIndex]);
	}
	else{
		return "error loading file !";
	}
}

std::string onePlGame::InputThings::getJoystickMoveString()
{
	switch( inputData.joystickData.joyMoveType )
	{
		case onePlGame::JoystickMoveAxes:
			return std::string{ languageTexts[onePlGame::LangInputAxisNum] + " " + std::to_string(inputData.joystickData.axisOrHatNum) };
			break;
		case onePlGame::JoystickMoveHats:
			return std::string{ languageTexts[onePlGame::LangInputHatNum] + " " + std::to_string(inputData.joystickData.axisOrHatNum) };
			break;
		default:
			return languageTexts[onePlGame::LangInputErrorMoveType];
			break;
	}
}

std::string onePlGame::InputThings::getJoystickBtnString(std::size_t buttonIndex)
{
	return std::string{ languageTexts[onePlGame::LangInputButtonNum] + " " + std::to_string( inputData.joystickData.joyButtons[buttonIndex] ) };
}

std::string onePlGame::InputThings::getJoystickCrossMoveString(std::size_t moveAxis)
{
	assert( moveAxis < inputData.joystickData.crossNum.size() );
	switch( inputData.joystickData.crossMoveType )
	{
		case onePlGame::JoystickMoveAxes:
			return std::string{ languageTexts[onePlGame::LangInputAxisNum] + " " + std::to_string(inputData.joystickData.crossNum[moveAxis]) };
			break;
		case onePlGame::JoystickMoveHats:
			return std::string{ languageTexts[onePlGame::LangInputHatNum] + " " + std::to_string(inputData.joystickData.crossNum[moveAxis]) };
			break;
		default:
			return languageTexts[onePlGame::LangInputErrorMoveType];
			break;
	}
}

void onePlGame::InputThings::writeDataToConfigFiles(Essentials& essentials)
{
	inputData.writeKeyboardFile(essentials);
	inputData.joystickData.writeJoystickFile(essentials);
	inputData.joystickData.writeDestCrossJoystickFile(essentials);
}