#include "contexts/duels/controls/objects/playerDataGraphics.h"
#include "texts/textLoader.h"
#include "texturing/rendererWindow.h"
#include "text/sdl2ttf_font.h"
#include "texturing/texturePosition.h"
#include "contexts/duels/controls/makeInpStringFromData.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "contexts/duels/controls/inputScreenConsts.h"
#include <cassert>
#include <algorithm>

constexpr int HL_BTN_W = 4*SQR_SIZE;
constexpr int HL_BTN_H = SQR_SIZE;

PlayerInputButtons::PlayerInputButtons(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, const duels::ReadyToUseInputs& inputs, const TextsBlocks& texts):
	mustUpdateDeviceType{ false, false},
	deviceTypeBtn{
		HighLightButton{logs, rndWnd, fancyFont, duels::getStringFromDeviceType(inputs.playerEnt[duels::PLAYER_BLUE], texts), BLACK_COL, SDL_Rect{7*SQR_SIZE, 4*SQR_SIZE, HL_BTN_W, HL_BTN_H}, ORANGE_COL},
		HighLightButton{logs, rndWnd, fancyFont, duels::getStringFromDeviceType(inputs.playerEnt[duels::PLAYER_RED], texts), BLACK_COL, SDL_Rect{12*SQR_SIZE, 4*SQR_SIZE, HL_BTN_W, HL_BTN_H}, ORANGE_COL}
	},
	mustTexturesBeUpdated{{
		{ false, false, false, false},
		{ false, false, false, false}
	}},
	inputsButtons{{
		{
			HighLightButton{ logs, rndWnd, fancyFont, duels::getStringFromLeftMove(inputs.playerEnt[duels::PLAYER_BLUE], texts), BLACK_COL, SDL_Rect{7*SQR_SIZE, 5*SQR_SIZE, HL_BTN_W, HL_BTN_H}, ORANGE_COL},
			HighLightButton{ logs, rndWnd, fancyFont, duels::getStringFromRightMove(inputs.playerEnt[duels::PLAYER_BLUE], texts), BLACK_COL, SDL_Rect{7*SQR_SIZE, 6*SQR_SIZE, HL_BTN_W, HL_BTN_H}, ORANGE_COL},
			HighLightButton{ logs, rndWnd, fancyFont, duels::getStringFromActiveBonus(inputs.playerEnt[duels::PLAYER_BLUE], texts), BLACK_COL, SDL_Rect{7*SQR_SIZE, 7*SQR_SIZE, HL_BTN_W, HL_BTN_H}, ORANGE_COL},
			HighLightButton{ logs, rndWnd, fancyFont, duels::getStringFromZoneSpecific(inputs.playerEnt[duels::PLAYER_BLUE], texts), BLACK_COL, SDL_Rect{7*SQR_SIZE, 8*SQR_SIZE, HL_BTN_W, HL_BTN_H}, ORANGE_COL}
		},
		{
			HighLightButton{ logs, rndWnd, fancyFont, duels::getStringFromLeftMove(inputs.playerEnt[duels::PLAYER_RED], texts), BLACK_COL, SDL_Rect{12*SQR_SIZE, 5*SQR_SIZE, HL_BTN_W, HL_BTN_H}, ORANGE_COL},
			HighLightButton{ logs, rndWnd, fancyFont, duels::getStringFromRightMove(inputs.playerEnt[duels::PLAYER_RED], texts), BLACK_COL, SDL_Rect{12*SQR_SIZE, 6*SQR_SIZE, HL_BTN_W, HL_BTN_H}, ORANGE_COL},
			HighLightButton{ logs, rndWnd, fancyFont, duels::getStringFromActiveBonus(inputs.playerEnt[duels::PLAYER_RED], texts), BLACK_COL, SDL_Rect{12*SQR_SIZE, 7*SQR_SIZE, HL_BTN_W, HL_BTN_H}, ORANGE_COL},
			HighLightButton{ logs, rndWnd, fancyFont, duels::getStringFromZoneSpecific(inputs.playerEnt[duels::PLAYER_RED], texts), BLACK_COL, SDL_Rect{12*SQR_SIZE, 8*SQR_SIZE, HL_BTN_W, HL_BTN_H}, ORANGE_COL}
		}
	}},
	pushKeyPrompt{logs, rndWnd, fancyFont, texts[duels::TXT_PUSH_KEY], BLACK_COL, 
		TexturePosition{GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT - SQR_SIZE * 4, true, true} },
	pushJoystickButtonPrompt{logs, rndWnd, fancyFont, texts[duels::TXT_PUSH_JOYBTN], BLACK_COL, 
		TexturePosition{GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT - SQR_SIZE * 4, true, true } }
{
	
}

void PlayerInputButtons::setDeviceButtonToBeUpdated(std::size_t playerType)
{
	assert( playerType < duels::PLAYER_MAX );
	mustUpdateDeviceType[playerType] = true;
}

void PlayerInputButtons::setInputButtonToBeUpdated(std::size_t playerType, std::size_t inputPart)
{
	assert( playerType < duels::PLAYER_MAX && inputPart < duels::INP_MAX );
	mustTexturesBeUpdated[playerType][inputPart] = true;
}

void PlayerInputButtons::useMouseDataForButtons(const Offset& mousePosition, bool mouseButtonState)
{
	useMouseDataForDeviceButtons(mousePosition, mouseButtonState);
	useMouseDataForInputsButtons(mousePosition, mouseButtonState);
}

void PlayerInputButtons::updateButtons(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, const duels::ReadyToUseInputs& inputs, const TextsBlocks& texts)
{
	updatePlayerButtons(logs, rndWnd, fancyFont, duels::PLAYER_BLUE, inputs.playerEnt[duels::PLAYER_BLUE], texts);
	updatePlayerButtons(logs, rndWnd, fancyFont, duels::PLAYER_RED, inputs.playerEnt[duels::PLAYER_RED], texts);
}

void PlayerInputButtons::drawAllButtons(sdl2::RendererWindow& rndWnd) const
{
	drawDeviceButtons(rndWnd);
	drawInputsButtons(rndWnd);
}

void PlayerInputButtons::changeDeviceType(duels::ReadyToUseInputs& inputs)
{
	for( std::size_t player{0} ; player < deviceTypeBtn.size() ; ++player )
	{
		if( deviceTypeBtn[player].buttonClicked() )
		{
			incrementDeviceType( *(inputs.playerEnt[player]) );
			inputs.setJoystickNumWithDeviceType();
			setDeviceButtonToBeUpdated(player);
			resetAllInpBtnDueToDeviceChange(player);
		}
	}
}

void PlayerInputButtons::changeKeyboardBinding(sdl2::RendererWindow& rndWnd, duels::ReadyToUseInputs& inputs)
{
	for( std::size_t player{0} ; player < inputsButtons.size() ; ++player )
	{
		for( std::size_t inputIndex{0} ; inputIndex < inputsButtons[player].size() ; ++inputIndex )
		{
			if( inputsButtons[player][inputIndex].buttonClicked() && inputs.playerEnt[player]->deviceType == duels::DEVICE_KEYBOARD )
			{
				pushKeyPrompt.draw(rndWnd);
				rndWnd.displayRenderer();
				waitKeyDownAsEvent( inputs.playerEnt[player]->keyboardInput[inputIndex] ); 
				setInputButtonToBeUpdated(player, inputIndex);
			}
		}
	}
}

void PlayerInputButtons::changeJoystickMoveBinding(duels::ReadyToUseInputs& inputs)
{
	for( std::size_t player{0} ; player < inputsButtons.size() ; ++player )
	{
		if( inputs.playerEnt[player] )
		{
			if( inputs.playerEnt[player]->deviceType == duels::DEVICE_JOYSTICK1 || inputs.playerEnt[player]->deviceType == duels::DEVICE_JOYSTICK2 )
			{
				for( std::size_t inputIndex{duels::INP_MOV_LEFT} ; inputIndex <= duels::INP_MOV_RIGHT ; ++inputIndex )
				{
					if( inputsButtons[player][inputIndex].buttonClicked() )
					{
						changeJoystickMoveWithJoystickNum(inputs, player);
					}
				}
			}
		}
	}
}

void PlayerInputButtons::changeJoystickActionBinding(sdl2::RendererWindow& rndWnd, duels::ReadyToUseInputs& inputs)
{
	for( std::size_t player{0} ; player < inputsButtons.size() ; ++player )
	{
		if( inputs.playerEnt[player] )
		{
			if( inputs.playerEnt[player]->deviceType == duels::DEVICE_JOYSTICK1 || inputs.playerEnt[player]->deviceType == duels::DEVICE_JOYSTICK2 )
			{
				changeBonusJoystickButton(rndWnd, inputs, player);
				changeZoneSpecificActionButton(rndWnd, inputs, player);
			}
		}
	}
}

void PlayerInputButtons::updatePlayerButtons(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, std::size_t playerType, const std::unique_ptr< duels::InputEntity >& playerInputs, const TextsBlocks& texts)
{
	updateDeviceButton(logs, rndWnd, fancyFont, playerType, duels::getStringFromDeviceType(playerInputs, texts) );
	updateSingleButton(logs, rndWnd, fancyFont, playerType, duels::INP_MOV_LEFT, duels::getStringFromLeftMove(playerInputs, texts) );
	updateSingleButton(logs, rndWnd, fancyFont, playerType, duels::INP_MOV_RIGHT, duels::getStringFromRightMove(playerInputs, texts) );
	updateSingleButton(logs, rndWnd, fancyFont, playerType, duels::INP_ACTIVBONUS, duels::getStringFromActiveBonus(playerInputs, texts) );
	updateSingleButton(logs, rndWnd, fancyFont, playerType, duels::INP_SPE_ZONE, duels::getStringFromZoneSpecific(playerInputs, texts) );
}

void PlayerInputButtons::updateDeviceButton(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, std::size_t playerType, const std::string& text)
{
	if( mustUpdateDeviceType[playerType] )
	{
		deviceTypeBtn[playerType].changeText(logs, rndWnd, fancyFont, text, BLACK_COL);
		mustUpdateDeviceType[playerType] = false;
	}
}

void PlayerInputButtons::updateSingleButton(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, std::size_t playerType, std::size_t index, const std::string& text)
{
	assert( playerType < duels::PLAYER_MAX && index < duels::INP_MAX );
	if( mustTexturesBeUpdated[playerType][index] )
	{
		inputsButtons[playerType][index].changeText(logs, rndWnd, fancyFont, text, BLACK_COL);
		mustTexturesBeUpdated[playerType][index] = false;
	}
}

void PlayerInputButtons::useMouseDataForDeviceButtons(const Offset& mousePosition, bool mouseButtonState)
{
	for( auto &btn : deviceTypeBtn )
	{
		btn.updateButton(mousePosition.x, mousePosition.y, mouseButtonState);
	}
}

void PlayerInputButtons::useMouseDataForInputsButtons(const Offset& mousePosition, bool mouseButtonState)
{
	for( auto &player : inputsButtons )
	{
		for( auto &btn : player )
		{
			btn.updateButton(mousePosition.x, mousePosition.y, mouseButtonState);
		}
	}
}

void PlayerInputButtons::drawDeviceButtons(sdl2::RendererWindow& rndWnd) const
{
	for( auto const &player : inputsButtons )
	{
		for( auto const &btn : player )
		{
			btn.drawButton(rndWnd);
		}
	}
}

void PlayerInputButtons::drawInputsButtons(sdl2::RendererWindow& rndWnd) const
{
	for( auto const &btn : deviceTypeBtn )
	{
		btn.drawButton(rndWnd);
	}
}

void PlayerInputButtons::incrementDeviceType(duels::InputEntity& playerInput)
{
	if( playerInput.deviceType + 1 < duels::DEVICE_MAX )
		playerInput.deviceType++;
	else
		playerInput.deviceType = duels::DEVICE_KEYBOARD;	
}

void PlayerInputButtons::waitKeyDownAsEvent(SDL_Keycode& inputKeycode)
{
	bool quit{false};
	SDL_Event event;
	while( SDL_PollEvent(&event) || false == quit )
	{
		switch( event.type )
		{
			case SDL_KEYDOWN:
				if( event.key.keysym.sym == SDLK_ESCAPE )
				{
					quit = true;
				}
				else{
					inputKeycode = event.key.keysym.sym;
					quit = true;
				}
				break;
			case SDL_QUIT:
				quit = true;
				break;
		}
	}
}

void PlayerInputButtons::waitButtonDownAsEvent(Uint8& inputJoystickButton, Uint8 joystickNum)
{
	bool quit{false};
	SDL_Event event;
	while( SDL_PollEvent(&event) || false == quit )
	{
		switch( event.type )
		{
			case SDL_KEYDOWN:
				if( event.key.keysym.sym == SDLK_ESCAPE )
				{
					quit = true;
				}
				break;
			case SDL_JOYBUTTONDOWN:
				if( event.jbutton.which == joystickNum )
				{
					inputJoystickButton = event.jbutton.button;
					quit = true;
				}
				break;
			case SDL_QUIT:
				quit = true;
				break;
		}
	}
}

void PlayerInputButtons::resetAllInpBtnDueToDeviceChange(std::size_t player)
{
	std::fill(mustTexturesBeUpdated[player].begin(), mustTexturesBeUpdated[player].end(), true);
}

void PlayerInputButtons::changeJoystickMoveWithJoystickNum(duels::ReadyToUseInputs& inputs, std::size_t player)
{
	if( inputs.playerEnt[player]->deviceType == duels::DEVICE_JOYSTICK1 )
	{
		incrementJoystickMoveType(*(inputs.playerEnt[player]), player, inputs.openedJoysticks[0] );
	}
	else if( inputs.playerEnt[player]->deviceType == duels::DEVICE_JOYSTICK2 )
	{
		incrementJoystickMoveType(*(inputs.playerEnt[player]), player, inputs.openedJoysticks[1] );
	}
}

void PlayerInputButtons::incrementJoystickMoveType(duels::InputEntity& playerInput, std::size_t player, const sdl2::JoystickEntity& openedJoystick)
{
	if( openedJoystick )
	{
		if( playerInput.joystick.joyMoveType == duels::JOYMOV_AXES )
		{
			if( static_cast<unsigned>(playerInput.joystick.axisOrHatNum) + 1 < openedJoystick.getAxesNumber() )
				playerInput.joystick.axisOrHatNum++;
			else{
				playerInput.joystick.joyMoveType = duels::JOYMOV_HATS;
				playerInput.joystick.axisOrHatNum = 0;
			}
			setInputButtonToBeUpdated(player, duels::INP_MOV_LEFT);
			setInputButtonToBeUpdated(player, duels::INP_MOV_RIGHT);
		}
		else if( playerInput.joystick.joyMoveType == duels::JOYMOV_HATS )
		{
			if( static_cast<unsigned>(playerInput.joystick.axisOrHatNum) + 1 < openedJoystick.getHatsNumber() )
				playerInput.joystick.axisOrHatNum++;
			else{
				playerInput.joystick.joyMoveType = duels::JOYMOV_AXES;
				playerInput.joystick.axisOrHatNum = 0;
			}
			setInputButtonToBeUpdated(player, duels::INP_MOV_LEFT);
			setInputButtonToBeUpdated(player, duels::INP_MOV_RIGHT);
		}
	}
}

void PlayerInputButtons::changeBonusJoystickButton(sdl2::RendererWindow& rndWnd, duels::ReadyToUseInputs& inputs, std::size_t player)
{
	if( inputsButtons[player][duels::INP_ACTIVBONUS].buttonClicked() )
	{
		pushJoystickButtonPrompt.draw(rndWnd);
		rndWnd.displayRenderer();
		waitButtonDownAsEvent(inputs.playerEnt[player]->joystick.buttons[duels::JOY_BTN_BONUS], inputs.playerEnt[player]->joystick.joyNum);
		setInputButtonToBeUpdated(player, duels::INP_ACTIVBONUS);
	}
}

void PlayerInputButtons::changeZoneSpecificActionButton(sdl2::RendererWindow& rndWnd, duels::ReadyToUseInputs& inputs, std::size_t player)
{
	if( inputsButtons[player][duels::INP_SPE_ZONE].buttonClicked() )
	{
		pushJoystickButtonPrompt.draw(rndWnd);
		rndWnd.displayRenderer();
		waitButtonDownAsEvent(inputs.playerEnt[player]->joystick.buttons[duels::JOY_BTN_SPE_ZONE], inputs.playerEnt[player]->joystick.joyNum);
		setInputButtonToBeUpdated(player, duels::INP_SPE_ZONE);
	}
}