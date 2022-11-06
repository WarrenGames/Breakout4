#include "contexts/gameStarting/mainMenu/mainMenuWidgets.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include <cassert>

mainMenu::Widgets::Widgets(Essentials& essentials, const sdl2::Font& font, const TextsBlocks& texts)
{
	int y_pos{SQR_SIZE*5};
	for( auto const &txt : texts )
	{
		buttons.emplace_back( TextButton{essentials.logs, essentials.rndWnd, font, txt, WhiteColor, YellowColor, GameScreenWidth/2, y_pos, true} );
		y_pos += SQR_SIZE * 2;
	}
}

void mainMenu::Widgets::updateButton(const Offset& mousePosition, bool mouseButtonState)
{
	for( auto &btn : buttons )
		btn.updateButton(mousePosition.x, mousePosition.y, mouseButtonState);
}

void mainMenu::Widgets::drawButtons(sdl2::RendererWindow& rndWnd) const
{
	for( auto const &btn : buttons )
		btn.drawButton(rndWnd);
}

bool mainMenu::Widgets::isButtonClicked(std::size_t buttonIndex) const
{
	assert( buttonIndex < buttons.size() );
	return buttons[buttonIndex].buttonClicked();
}