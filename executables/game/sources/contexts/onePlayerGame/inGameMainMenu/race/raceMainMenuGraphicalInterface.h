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

		enum{ LanguageTitle, LanguageShopRace, LanguageStandardRace, LanguageSeeNextLevel, LanguageRunLevel, LanguageSaveGame, LanguageChangeInput, LanguageShop, LanguageQuit, LanguageMax};
		
		enum{ ButtonSeeNextLevel, ButtonRunLevel, ButtonSaveGame, ButtonChangeInput, ButtonQuit, ButtonMax};
		
		struct Interface
		{
			unsigned campaignType;
			TextsBlocks languageTexts;
			sdl2::Font fancyFont;
			TextureCombo screenTitle;
			std::vector< TextButton > buttons;
			TextButton shopButton;
			TextureCombo screenBackground;
			
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