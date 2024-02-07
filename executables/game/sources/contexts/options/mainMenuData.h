#ifndef OPTION_CONTEXT_MAIN_MENU_DATA_H
#define OPTION_CONTEXT_MAIN_MENU_DATA_H

#include "texts/textLoader.h"
#include "text/sdl2ttf_font.h"
#include "texturing/texturesCombo.h"
#include "widgets/buttons/textButtonWidget.h"
#include "contexts/options/mainMenuConsts.h"
#include <vector>

struct Essentials;

namespace optionsMenu{

class MainMenu 
{
private:
	const TextsBlocks languagesTexts;
	const sdl2::Font fancyFont;
	const TextureCombo title;
	const TextureCombo soundImage;
	const TextureCombo musicImage;
	std::vector< TextButton > categoriesTexts;

public:
	explicit MainMenu(Essentials& essentials);
	~MainMenu() = default;
	MainMenu( const MainMenu& ) = delete;
	MainMenu& operator= ( const MainMenu& ) = delete;
	MainMenu( MainMenu&& ) = default;
	MainMenu& operator= ( MainMenu&& ) = default;
	
	void drawEverything(Essentials& essentials) const;
	void updateButtons(Essentials& essentials);
	bool isButtonClicked(unsigned buttonNumber) const;
	
private:
	void drawTextButtons(Essentials& essentials) const;
	void populateTextButtons(Essentials& essentials);
};

}

#endif //OPTION_CONTEXT_MAIN_MENU_DATA_H