#ifndef ONEP_SKILL_LVL_CHOICE_GUI_H
#define ONEP_SKILL_LVL_CHOICE_GUI_H

#include "text/sdl2ttf_font.h"
#include "consts/fontsConsts.h"
#include "texts/textLoader.h"
#include "widgets/buttons/textButtonWidget.h"
#include "advancedDrawing/texturesLoading/fileTexturesList.h"
#include "advancedDrawing/texturesDrawing/constAnimationDrawing.h"
#include "time/accurateTime.h"
#include "consts/onePlayerLevelConsts.h"

struct Essentials;

namespace onePlGame{
	namespace skillChoice{
		enum{ TextChoose, TextGoBack, TextEasySelection, TextMediumSelection, TextHardSelection, TextSkillMax };
		constexpr std::size_t RacketsAnimationsNumber = 3;
		constexpr std::size_t RacketsFramesNumber = 40;
		
		struct Interface
		{
			sdl2::Font fancyFont;
			TextsBlocks languageTexts;
			TextureCombo screenBackground;
			TextureCombo screenTitle;
			std::vector< TextButton > skillButtons;
			TextButton goBackButton;
			
			explicit Interface(Essentials& essentials);
			~Interface() = default;
			Interface( const Interface& ) = delete;
			Interface& operator= ( const Interface& ) = delete;
			Interface( Interface&& ) = default;
			Interface& operator= ( Interface&& ) = default;
			void update(const Essentials& essentials);
			void updateSkillButtons(const Essentials& essentials);
			void drawEverything(Essentials& essentials);
			void drawSkillButtons(Essentials& essentials) const;
			void updateAnims();
			void populateSkillButtons(Essentials& essentials);
		};
	}
}

#endif //ONEP_SKILL_LVL_CHOICE_GUI_H