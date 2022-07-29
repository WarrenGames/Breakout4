#ifndef SHOP_RACE_MAIN_MENU_GUI_H
#define SHOP_RACE_MAIN_MENU_GUI_H

#include "texts/textLoader.h"
#include "text/sdl2ttf_font.h"
#include "widgets/buttons/textButtonWidget.h"
#include "texturing/texturesCombo.h"
#include <vector>
#include <string>

struct Essentials;
struct Offset;

namespace onePlGame{
	namespace raceMainMenu{

		enum{ LANG_TITLE, LANG_SHOP_RACE, LANG_STD_RACE, LANG_SEE_NEXT_LVL, LANG_RUN_LVL, LANG_SAVE_GAME, LANG_CHANGE_INP, LANG_SHOP, LANG_QUIT, LANG_MAX};
		
		enum{ BTN_SEE_NEXT_LVL, BTN_RUN_LVL, BTN_SAVE_GAME, BTN_CHANGE_INP, BTN_QUIT, BTN_MAX};
		
		struct Interface
		{
			unsigned campaignType;
			const TextsBlocks languageTexts;
			const sdl2::Font fancyFont;
			const TextureCombo screenTitle;
			std::vector< TextButton > buttons;
			TextButton shopButton;
			const TextureCombo screenBackground;
			
			explicit Interface(Essentials& essentials, unsigned campaignType_);
			~Interface() = default;
			Interface( const Interface& ) = delete;
			Interface& operator= ( const Interface& ) = delete;
			Interface( Interface&& ) = default;
			Interface& operator= ( Interface&& ) = default;
			
			void updateButtons(const Offset& mousePosition, bool mouseButtonState);
			void drawEverything(Essentials& essentials) const;
			void drawButtons(Essentials& essentials) const;
			
			void updateShopButton(const Offset& mousePosition, bool mouseButtonState);
			void drawShopButton(Essentials& essentials) const;
			
			std::string getCampTitle(unsigned campaignType_);
		};

	}
}

#endif //SHOP_RACE_MAIN_MENU_GUI_H