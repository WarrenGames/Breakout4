#ifndef DUELS_PLAYER_DATA_GRAPHICS_H
#define DUELS_PLAYER_DATA_GRAPHICS_H

#include "widgets/buttons/highlightButtonWidget.h"
#include "texturing/texturesCombo.h"
#include "contexts/duels/inGameObjects/playerInputs/inputsConsts.h"
#include "contexts/duels/duelsConstexpr.h"
#include "contexts/duels/inGameObjects/playerInputs/inputsTypes.h"
#include <vector>

struct AppLogFiles;
namespace sdl2{ class RendererWindow; class Font; }
class TextsBlocks;

class PlayerInputButtons
{
private:
	std::vector< bool > mustUpdateDeviceType;
	std::vector< HighLightButton > deviceTypeBtn;
	std::vector< std::vector< bool > > mustTexturesBeUpdated;
	std::vector< std::vector< HighLightButton> > inputsButtons;
	TextureCombo pushKeyPrompt;
	TextureCombo pushJoystickButtonPrompt;

public:
	explicit PlayerInputButtons(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, const duels::ReadyToUseInputs& inputs, const TextsBlocks& texts);
	~PlayerInputButtons() = default;
	PlayerInputButtons( const PlayerInputButtons& ) = delete;
	PlayerInputButtons& operator= ( const PlayerInputButtons& ) = delete;
	PlayerInputButtons( PlayerInputButtons&& ) = default;
	PlayerInputButtons& operator= ( PlayerInputButtons&& ) = default;
	
	void setDeviceButtonToBeUpdated(std::size_t playerType);
	void setInputButtonToBeUpdated(std::size_t playerType, std::size_t inputPart);
	
	void useMouseDataForButtons(const Offset& mousePosition, bool mouseButtonState);
	void updateButtons(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, const duels::ReadyToUseInputs& inputs, const TextsBlocks& texts);
	
	void drawAllButtons(sdl2::RendererWindow& rndWnd) const;
	
	void changeDeviceType(duels::ReadyToUseInputs& inputs);
	void changeKeyboardBinding(sdl2::RendererWindow& rndWnd, duels::ReadyToUseInputs& inputs);
	void changeJoystickMoveBinding(duels::ReadyToUseInputs& inputs);
	void changeJoystickActionBinding(sdl2::RendererWindow& rndWnd, duels::ReadyToUseInputs& inputs);
	
private:
	void updatePlayerButtons(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, std::size_t playerType, const std::unique_ptr< duels::InputEntity >& playerInputs, const TextsBlocks& texts);
	void updateDeviceButton(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, std::size_t playerType, const std::string& text);
	void updateSingleButton(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, std::size_t playerType, std::size_t index, const std::string& text);
	
	void useMouseDataForDeviceButtons(const Offset& mousePosition, bool mouseButtonState);
	void useMouseDataForInputsButtons(const Offset& mousePosition, bool mouseButtonState);
	
	void drawDeviceButtons(sdl2::RendererWindow& rndWnd) const;
	void drawInputsButtons(sdl2::RendererWindow& rndWnd) const;
	
	void incrementDeviceType(duels::InputEntity& playerInput);
	void waitKeyDownAsEvent(SDL_Keycode& inputKeycode);
	
	void waitButtonDownAsEvent(Uint8& inputJoystickButton, Uint8 joystickNum);
	
	void resetAllInpBtnDueToDeviceChange(std::size_t player);
	
	void changeJoystickMoveWithJoystickNum(duels::ReadyToUseInputs& inputs, std::size_t player);
	void incrementJoystickMoveType(duels::InputEntity& playerInput, std::size_t player, const sdl2::JoystickEntity& openedJoystick);
	
	void changeBonusJoystickButton(sdl2::RendererWindow& rndWnd, duels::ReadyToUseInputs& inputs, std::size_t player);
	void changeZoneSpecificActionButton(sdl2::RendererWindow& rndWnd, duels::ReadyToUseInputs& inputs, std::size_t player);
	
	void populateDeviceTypeBtn(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, const duels::ReadyToUseInputs& inputs, const TextsBlocks& texts);
	void populateInputsButtons(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, const duels::ReadyToUseInputs& inputs, const TextsBlocks& texts);
};

#endif //DUELS_PLAYER_DATA_GRAPHICS_H