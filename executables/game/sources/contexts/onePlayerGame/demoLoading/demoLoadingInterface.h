#ifndef CONTEXTS_ONE_PLAYER_GAME_DEMO_LOADING_INTERFACE_H
#define CONTEXTS_ONE_PLAYER_GAME_DEMO_LOADING_INTERFACE_H

#include "texts/textLoader.h"
#include "text/sdl2ttf_font.h"
#include "contexts/onePlayerGame/demoLoading/demoFilesDisplayer.h"

class ReadError;

namespace demosLoading{

struct Interface
{
	const TextsBlocks languagesTexts;
	const sdl2::Font fancyFont;
	demosLoading::DemoFilesDisplayer demoFilesDisplayer;
	TextButton quitButton;
	TextButton previousPage;
	TextButton nextPage;
	const TextureCombo titleText;
	const TextureCombo noLoadedDemoText;
	TextureCombo errorString;
	bool quitMenu;
	
	explicit Interface(Essentials& essentials);
	~Interface() = default;
	Interface( const Interface& ) = delete;
	Interface& operator= ( const Interface& ) = delete;
	Interface( Interface&& ) = default;
	Interface& operator= ( Interface&& ) = default;
	
	void updateButtons(const Offset& mousePosition, bool mouseLeftButtonState);
	void drawDemoAbsence(Essentials& essentials) const;
	void drawEverything(Essentials& essentials) const;
	void setErrorString(Essentials& essentials, const ReadError& e);
	void drawErrorString(Essentials& essentials) const;
};

}
#endif //CONTEXTS_ONE_PLAYER_GAME_DEMO_LOADING_INTERFACE_H