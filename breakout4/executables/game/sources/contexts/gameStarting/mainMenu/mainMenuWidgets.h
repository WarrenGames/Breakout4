#ifndef MAIN_MENU_WIDGETS_H
#define MAIN_MENU_WIDGETS_H

#include "widgets/buttons/textButtonWidget.h"
#include "texts/textLoader.h"

struct Essentials;

namespace mainMenu{

enum{ONEPLAYER_GAME, DUELS_GAME, OPTIONS, CREDITS, QUIT, MAX};
	
struct Widgets
{	
	std::vector< TextButton > buttons;
	
	Widgets(Essentials& essentials, const sdl2::Font& font, const TextsBlocks& texts);
	void updateButton(const Offset& mousePosition, bool mouseButtonState);
	void drawButtons(sdl2::RendererWindow& rndWnd) const;
	bool isButtonClicked(std::size_t buttonIndex) const;
};

}

#endif //MAIN_MENU_WIDGETS_H