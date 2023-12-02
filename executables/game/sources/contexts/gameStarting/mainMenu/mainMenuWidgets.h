#ifndef MAIN_MENU_WIDGETS_H
#define MAIN_MENU_WIDGETS_H

#include "widgets/buttons/textButtonWidget.h"
#include "texts/textLoader.h"

struct Essentials;

namespace mainMenu{

enum{	OnePlayerGame, DuelsGame, Options, Credits, Quit, Max};
	
struct Widgets
{	
	std::vector< TextButton > buttons;
	
	explicit Widgets(Essentials& essentials, const sdl2::Font& font, const TextsBlocks& texts);
	~Widgets() = default;
	Widgets( const Widgets& ) = delete;
	Widgets& operator= ( const Widgets& ) = delete;
	Widgets( Widgets&& ) = default;
	Widgets& operator= ( Widgets&& ) = default;
	
	void updateButton(const Offset& mousePosition, bool mouseButtonState);
	void drawButtons(sdl2::RendererWindow& rndWnd) const;
	bool isButtonClicked(std::size_t buttonIndex) const;
};

}

#endif //MAIN_MENU_WIDGETS_H