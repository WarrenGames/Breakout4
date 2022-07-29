#include "contexts/onePlayerGame/inputConfig/inputThings.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "keycodes/keycodesOverload.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include <cassert>

constexpr int BTN_W = SQR_SIZE * 4;
constexpr int BTN_H = SQR_SIZE;

onePlGame::InputThings::InputThings(Essentials& essentials):
	isLoadingPerfect{true},
	inputData{essentials},
	languageTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::ONE_PLAY_INPUT_CFG), onePlGame::LANG_INP_MAX},
	fancyFont{essentials.logs.error, FANCYFONTPATH, FONT_BIG_PTSIZE},
	staticGraphics{essentials, fancyFont, languageTexts},
	axisThresholdBox{essentials.logs, essentials.rndWnd, SDL_Rect{SQR_SIZE*6, GAME_SCREEN_HEIGHT-SQR_SIZE*3/2, SQR_SIZE*3, SQR_SIZE}, FONT_BIG_PTSIZE, inputData.joystickData.axisMoveThreshold},
	joystickMenu{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::LANG_INP_JOY_INFOS], BLACK_COL, {SQR_SIZE * 10, GAME_SCREEN_HEIGHT - SQR_SIZE - BTN_H / 2, BTN_W, BTN_H}, GREEN_COL}
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
	for( std::size_t i{0} ; i < onePlGame::INP_MAX ; ++i )
	{
		keycodesInputsTexts.emplace_back( HighLightButton{essentials.logs, essentials.rndWnd, fancyFont, getKeycodeString(i), BLACK_COL, 
															{SQR_SIZE*8, SQR_SIZE*(3 + static_cast<int>(i) ), BTN_W, BTN_H}, GREEN_COL} );
	}
}

void onePlGame::InputThings::createJoystickInputButtons(Essentials& essentials)
{
	joystickInputsTexts.emplace_back( HighLightButton{essentials.logs, essentials.rndWnd, fancyFont, getJoystickMoveString(), BLACK_COL, {SQR_SIZE*14, SQR_SIZE*3, BTN_W, BTN_H}, GREEN_COL} );
	joystickInputsTexts.emplace_back( HighLightButton{essentials.logs, essentials.rndWnd, fancyFont, getJoystickMoveString(), BLACK_COL, {SQR_SIZE*14, SQR_SIZE*4, BTN_W, BTN_H}, GREEN_COL} );
	joystickInputsTexts.emplace_back( HighLightButton{essentials.logs, essentials.rndWnd, fancyFont, getJoystickBtnString(onePlGame::JOYBTN_BALL_TRACE), BLACK_COL, {SQR_SIZE*14, SQR_SIZE*5, BTN_W, BTN_H}, GREEN_COL} );
	joystickInputsTexts.emplace_back( HighLightButton{essentials.logs, essentials.rndWnd, fancyFont, getJoystickBtnString(onePlGame::JOYBTN_LOOK_BAG), BLACK_COL, {SQR_SIZE*14, SQR_SIZE*6, BTN_W, BTN_H}, GREEN_COL} );
	joystickInputsTexts.emplace_back( HighLightButton{essentials.logs, essentials.rndWnd, fancyFont, getJoystickBtnString(onePlGame::JOYBTN_SWITCH), BLACK_COL, {SQR_SIZE*14, SQR_SIZE*7, BTN_W, BTN_H}, GREEN_COL} );
}

void onePlGame::InputThings::createMoveCrossButtons(Essentials& essentials)
{
	moveCross.emplace_back( HighLightButton{essentials.logs, essentials.rndWnd, fancyFont, getJoystickCrossMoveString(onePlGame::JOY_CROSS_MOVE_X), BLACK_COL, {SQR_SIZE*14, SQR_SIZE*8, BTN_W, BTN_H}, GREEN_COL} );
	moveCross.emplace_back( HighLightButton{essentials.logs, essentials.rndWnd, fancyFont, getJoystickCrossMoveString(onePlGame::JOY_CROSS_MOVE_Y), BLACK_COL, {SQR_SIZE*14, SQR_SIZE*9, BTN_W, BTN_H}, GREEN_COL} );
}

void onePlGame::InputThings::createJoystickGraphicalStatus(Essentials& essentials)
{
	if( inputData.joystickData.joystickEntity )
	{
		joystickName.texture.loadBlendedText(essentials.logs, essentials.rndWnd, fancyFont, "Joystick: " + inputData.joystickData.joystickEntity.getName(), BLACK_COL);
		joystickName.resetSpritePosition( TexturePosition{SQR_SIZE, GAME_SCREEN_HEIGHT - SQR_SIZE*2, false, true} );
	}
	else{
		joystickName.texture.loadBlendedText(essentials.logs, essentials.rndWnd, fancyFont, inputData.joystickData.joystickEntity.getLoadingStatus(), BLACK_COL);
		joystickName.resetSpritePosition( TexturePosition{SQR_SIZE, GAME_SCREEN_HEIGHT-SQR_SIZE*2, false, true} );
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
	readJoyBtnHighlightBtn(essentials, joystickInputsTexts[onePlGame::INP_BALL_TRACE], onePlGame::JOYBTN_BALL_TRACE);
	readJoyBtnHighlightBtn(essentials, joystickInputsTexts[onePlGame::INP_LOOK_BAG], onePlGame::JOYBTN_LOOK_BAG);
	readJoyBtnHighlightBtn(essentials, joystickInputsTexts[onePlGame::INP_SWITCH], onePlGame::JOYBTN_SWITCH);
}

void onePlGame::InputThings::changeJoystickMoveStrings(Essentials& essentials)
{
	if( joystickInputsTexts[onePlGame::INP_MOVE_LEFT].buttonClicked() || joystickInputsTexts[onePlGame::INP_MOVE_RIGHT].buttonClicked() )
	{
		if( inputData.joystickData.joystickEntity )
		{
			tweakJoyAxesAndHatsNum();
			joystickInputsTexts[onePlGame::INP_MOVE_LEFT].changeText(essentials.logs, essentials.rndWnd, fancyFont, getJoystickMoveString(), BLACK_COL);
			joystickInputsTexts[onePlGame::INP_MOVE_RIGHT].changeText(essentials.logs, essentials.rndWnd, fancyFont, getJoystickMoveString(), BLACK_COL);
		}
	}
}

void onePlGame::InputThings::tweakJoyAxesAndHatsNum()
{
	if( inputData.joystickData.joyMoveType == onePlGame::JOYMOV_AXES )
	{
		tweakJoyAxes();
	}
	else if( inputData.joystickData.joyMoveType == onePlGame::JOYMOV_HATS )
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
		inputData.joystickData.joyMoveType = onePlGame::JOYMOV_HATS;
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
		inputData.joystickData.joyMoveType = onePlGame::JOYMOV_AXES;
		inputData.joystickData.axisOrHatNum = 0;
	}
}

void onePlGame::InputThings::tweakJoyMovError()
{
	inputData.joystickData.joyMoveType = onePlGame::JOYMOV_AXES;
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
	staticGraphics.askInputTextures[PUSH_NEW_KEY].draw(essentials.rndWnd);
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
					highlightButton.changeText(essentials.logs, essentials.rndWnd, fancyFont, getNameFromKeycode(event.key.keysym.sym), BLACK_COL);
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
	staticGraphics.askInputTextures[PUSH_NEW_BTN].draw(essentials.rndWnd);
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
				highlightButton.changeText(essentials.logs, essentials.rndWnd, fancyFont, getJoystickBtnString(buttonIndex), BLACK_COL);
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
	for( std::size_t i{0} ; i < onePlGame::JOY_CROSS_MOVE_MAX ; ++i )
	{
		if( moveCross[i].buttonClicked() && inputData.joystickData.joystickEntity )
		{
			tweakCrossMoveNums(inputData.joystickData.crossNum[i]);
			for( std::size_t i{0} ; i < moveCross.size() ; ++i )
			{
				moveCross[i].changeText(essentials.logs, essentials.rndWnd, fancyFont, getJoystickCrossMoveString(i), BLACK_COL);
			}
		}
	}
}

void onePlGame::InputThings::tweakCrossMoveNums(unsigned& crossMoveNum)
{
	if( inputData.joystickData.crossMoveType == onePlGame::JOYMOV_AXES )
	{
		tweakCrossMoveAxes(crossMoveNum);
	}
	else if( inputData.joystickData.crossMoveType == onePlGame::JOYMOV_HATS )
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
		inputData.joystickData.crossMoveType = onePlGame::JOYMOV_HATS;
		inputData.joystickData.crossNum[onePlGame::JOY_CROSS_MOVE_X] = 0;
		inputData.joystickData.crossNum[onePlGame::JOY_CROSS_MOVE_Y] = 0;
	}
}

void onePlGame::InputThings::tweakCrossMoveHats(unsigned& crossMoveNum)
{
	if( crossMoveNum + 1 < inputData.joystickData.joystickEntity.getHatsNumber() )
	{
		inputData.joystickData.crossNum[onePlGame::JOY_CROSS_MOVE_X]++;
		inputData.joystickData.crossNum[onePlGame::JOY_CROSS_MOVE_Y]++;
	}
	else{
		inputData.joystickData.crossMoveType = onePlGame::JOYMOV_AXES;
		inputData.joystickData.crossNum[onePlGame::JOY_CROSS_MOVE_X] = 0;
		inputData.joystickData.crossNum[onePlGame::JOY_CROSS_MOVE_Y] = 0;
	}
}

void onePlGame::InputThings::tweakCrossMoveError()
{
	inputData.joystickData.crossMoveType = onePlGame::JOYMOV_AXES;
	inputData.joystickData.crossNum[onePlGame::JOY_CROSS_MOVE_X] = 0;
	inputData.joystickData.crossNum[onePlGame::JOY_CROSS_MOVE_Y] = 0;
}

std::string onePlGame::InputThings::getKeycodeString(std::size_t arrayIndex)
{
	assert( arrayIndex < onePlGame::INP_MAX );
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
		case onePlGame::JOYMOV_AXES:
			return std::string{ languageTexts[onePlGame::LANG_INP_AXIS_NUM] + " " + std::to_string(inputData.joystickData.axisOrHatNum) };
			break;
		case onePlGame::JOYMOV_HATS:
			return std::string{ languageTexts[onePlGame::LANG_INP_HAT_NUM] + " " + std::to_string(inputData.joystickData.axisOrHatNum) };
			break;
		default:
			return languageTexts[onePlGame::LANG_INP_ERROR_MOVE_TYPE];
			break;
	}
}

std::string onePlGame::InputThings::getJoystickBtnString(std::size_t buttonIndex)
{
	return std::string{ languageTexts[onePlGame::LANG_INP_BUTTON_NUM] + " " + std::to_string( inputData.joystickData.joyButtons[buttonIndex] ) };
}

std::string onePlGame::InputThings::getJoystickCrossMoveString(std::size_t moveAxis)
{
	assert( moveAxis < inputData.joystickData.crossNum.size() );
	switch( inputData.joystickData.crossMoveType )
	{
		case onePlGame::JOYMOV_AXES:
			return std::string{ languageTexts[onePlGame::LANG_INP_AXIS_NUM] + " " + std::to_string(inputData.joystickData.crossNum[moveAxis]) };
			break;
		case onePlGame::JOYMOV_HATS:
			return std::string{ languageTexts[onePlGame::LANG_INP_HAT_NUM] + " " + std::to_string(inputData.joystickData.crossNum[moveAxis]) };
			break;
		default:
			return languageTexts[onePlGame::LANG_INP_ERROR_MOVE_TYPE];
			break;
	}
}

void onePlGame::InputThings::writeDataToConfigFiles(Essentials& essentials)
{
	inputData.writeKeyboardFile(essentials);
	inputData.joystickData.writeJoystickFile(essentials);
	inputData.joystickData.writeDestCrossJoystickFile(essentials);
}