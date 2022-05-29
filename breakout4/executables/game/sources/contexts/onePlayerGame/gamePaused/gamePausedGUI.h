#ifndef ONE_PLAYER_PAUSED_GAME_GUI_H
#define ONE_PLAYER_PAUSED_GAME_GUI_H

#include "text/sdl2ttf_font.h"
#include "consts/fontsConsts.h"
#include "texts/textLoader.h"
#include "widgets/buttons/textButtonWidget.h"

struct Essentials;

enum{ PAUSED_GAME_INFOS, PAUSED_GAME_GOBACK, PAUSED_GAME_QUIT_BTN, PAUSED_GAME_MAX };

class PausedGameGUI
{
private:
	const sdl2::Font fancyFont;
	const TextsBlocks languagesTexts;
	const TextureCombo pauseInfos;
	const TextureCombo pressEscapeGoBack;
	TextButton quitGame;

public:
	explicit PausedGameGUI(Essentials& essentials);
	~PausedGameGUI() = default;
	PausedGameGUI( const PausedGameGUI& ) = delete;
	PausedGameGUI& operator= ( const PausedGameGUI& ) = delete;
	PausedGameGUI( PausedGameGUI&& ) = default;
	PausedGameGUI& operator= ( PausedGameGUI&& ) = default;
	
	void updateQuitButton(const Offset& mousePosition, bool mouseLeftButton);
	void drawEverything(Essentials& essentials) const;
	bool isQuitButtonClicked() const;
};

#endif //ONE_PLAYER_PAUSED_GAME_GUI_H