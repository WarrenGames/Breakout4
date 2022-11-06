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
			const sdl2::Font fancyFont;
			const TextsBlocks languageTexts;
			const TextureCombo screenTitle;
			std::vector< TextButton > skillButtons;
			TextButton goBackButton;
			std::vector<TexturesFilesList> racketsTextures;
			std::vector<ConstAnimDraw> racketsSprites;
			std::vector< unsigned > animIndexes;
			std::vector< Offset > animPositions;
			AccurateTimeDelay animDelay;
			
			explicit Interface(Essentials& essentials);
			void update(const Essentials& essentials);
			void updateSkillButtons(const Essentials& essentials);
			void drawEverything(Essentials& essentials);
			void drawSkillButtons(Essentials& essentials) const;
			void createAnims(Essentials& essentials);
			void updateAnims();
			void drawAnims(Essentials& essentials);
			void populateSkillButtons(Essentials& essentials);
		};
	}
}

#endif //ONEP_SKILL_LVL_CHOICE_GUI_H