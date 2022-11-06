#ifndef DUELS_INPUTS_SCREEN_MAIN_OBJECT_H
#define DUELS_INPUTS_SCREEN_MAIN_OBJECT_H

#include "contexts/duels/controls/objects/playerDataGraphics.h"
#include "contexts/duels/controls/objects/screenGraphics.h"
#include "contexts/duels/controls/objects/joysticksInfosDrawer.h"
#include "text/sdl2ttf_font.h"
#include "consts/fontsConsts.h"
#include "texts/textLoader.h"
#include "contexts/duels/inGameObjects/playerInputs/inputsTypes.h"

struct Essentials;

namespace duels{

struct InputScreenGlobal
{
	const TextsBlocks languageTexts;
	const sdl2::Font fancyFont;
	duels::ReadyToUseInputs inputsData;
	DuelsInpCfgGraphics screenGraphics;
	PlayerInputButtons inputButtons;
	JoystickInfosDrawer joysticksInfos;
	std::vector< TextureCombo > playerTitles;
	
	explicit InputScreenGlobal(Essentials& essentials);
	~InputScreenGlobal() = default;
	InputScreenGlobal( const InputScreenGlobal& ) = delete;
	InputScreenGlobal& operator= ( const InputScreenGlobal& ) = delete;
	InputScreenGlobal( InputScreenGlobal&& ) = default;
	InputScreenGlobal& operator= ( InputScreenGlobal&& ) = default;
	
	void drawEverything(Essentials& essentials) const;
	
	void update(Essentials& essentials);
	
	void saveInputsDataToFile(Essentials& essentials);
	
	void runJoystickDetailsInterface(Essentials& essentials);
	
	void drawArrayLines(Essentials& essentials) const;
	
	void drawPlayersTitles(Essentials& essentials) const;
};

}

#endif //DUELS_INPUTS_SCREEN_MAIN_OBJECT_H