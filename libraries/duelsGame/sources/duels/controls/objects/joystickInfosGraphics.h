#ifndef JOYSTICK_INFOS_GRAPHICS_H
#define JOYSTICK_INFOS_GRAPHICS_H

//#include "duels/inGameObjects/playerInputs/inputsTypes.h"
//#include "consts/fontsConsts.h"

#include "joystick/joystickEntity.h"
#include "widgets/buttons/highlightButtonWidget.h"
#include "texturing/texturesCombo.h"

struct Essentials;
struct AppLogFiles;
namespace sdl2{ class RendererWindow; class Font; }
class TextsBlocks;

struct JoyInfosTextsGraphics
{
	sdl2::JoystickEntity joyEnt;
	HighLightButton seeJoystickInfos;
	TextureCombo joyName;
	TextureCombo joyHatNum;
	TextureCombo joyAxesNum;
	TextureCombo joyButtonsNum;
	
	JoyInfosTextsGraphics(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, unsigned player, const TextsBlocks& texts);
	~JoyInfosTextsGraphics() = default;
	JoyInfosTextsGraphics( const JoyInfosTextsGraphics& ) = delete;
	JoyInfosTextsGraphics& operator= ( const JoyInfosTextsGraphics& ) = delete;
	JoyInfosTextsGraphics( JoyInfosTextsGraphics&& ) = default;
	JoyInfosTextsGraphics& operator= ( JoyInfosTextsGraphics&& ) = default;
	
	void resetTexts(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, unsigned player, const TextsBlocks& texts);
	std::string getHatNumberText(const TextsBlocks& texts);
	std::string getAxesNumberText(const TextsBlocks& texts);
	std::string getButtonsNumberText(const TextsBlocks& texts);
	
	void update(Essentials& essentials);
	
	void drawTexts(sdl2::RendererWindow& rndWnd) const;
};

#endif //JOYSTICK_INFOS_GRAPHICS_H