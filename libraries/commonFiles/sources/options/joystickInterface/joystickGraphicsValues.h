#ifndef JOYSTICK_GRAPHICS_VALUES_H
#define JOYSTICK_GRAPHICS_VALUES_H

#include "joystick/joystickEntity.h"
#include "texturing/texturesCombo.h"
#include "texts/textLoader.h"
#include "SDL_keycode.h"
#include <vector>

struct AppLogFiles;

struct JoyEventsInfos
{
	std::vector<bool> joyButtons;
	std::vector<Uint8> joyHats;
	std::vector<Sint16> joyAxes;
	SDL_JoystickID joystickNumber;
	bool escapeState;
	bool sdl_Quit;
	
	explicit JoyEventsInfos(const sdl2::JoystickEntity& joyEnt);
	~JoyEventsInfos() = default;
	JoyEventsInfos( const JoyEventsInfos& ) = default;
	JoyEventsInfos& operator= ( const JoyEventsInfos& ) = default;
};

class JoystickValuesTextures
{
private:
	TextureCombo hatsSquare;
	TextureCombo buttonOff;
	TextureCombo buttonPushed;
	TextureCombo axisGradientOff;
	TextureCombo axisGradientRed;
	TextureCombo buttonsText;
	TextureCombo hatsText;
	TextureCombo axisText;
	JoyEventsInfos joyEventsInfos;
	std::vector<TextureCombo> numbersTextures;

public:
	explicit JoystickValuesTextures(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& arial, const TextsBlocks& joyLangTexts, const sdl2::JoystickEntity& joyEnt);
	~JoystickValuesTextures() = default;
	JoystickValuesTextures( const JoystickValuesTextures& ) = delete;
	JoystickValuesTextures& operator= ( const JoystickValuesTextures& ) = delete;
	JoystickValuesTextures( JoystickValuesTextures&& ) = default;
	JoystickValuesTextures& operator= ( JoystickValuesTextures&& ) = default;

	void updateEvents();
	bool isQuitTriggered() const;
	void drawAll(sdl2::RendererWindow& rndWnd);
	
private:
	void drawButtonsStates(sdl2::RendererWindow& rndWnd);
	void drawButtonsNumbers(sdl2::RendererWindow& rndWnd, std::size_t figureNum, int x_center_pos, int y_center_pos);
	void drawHatsSurfaces(sdl2::RendererWindow& rndWnd);
	void drawAxesValues(sdl2::RendererWindow& rndWnd);
	void appendEscapeKeyStatus(SDL_Keycode keycode, bool valueToSet);
	void createNumbersTextures(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& arial);
	void drawSingleButtonSurface(sdl2::RendererWindow& rndWnd, int x_pos, int y_pos, bool buttonState);
	void drawHatReticule(sdl2::RendererWindow& rndWnd, Uint8 hatValue, int x_pos, int y_pos);
	void drawSingleAxisSurface(sdl2::RendererWindow& rndWnd, int x_pos, int y_pos, Sint16 axisValue);
	void drawAxisValue(sdl2::RendererWindow& rndWnd, int x_pos, int y_pos, Sint16 axisValue);
};

#endif //JOYSTICK_GRAPHICS_VALUES_H