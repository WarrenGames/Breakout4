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
#include <array>

struct Essentials;

namespace onePlGame{
	namespace skillChoice{
		enum{ TXT_CHOOSE, TXT_GO_BACK, TXT_EASY, TXT_MEDIUM, TXT_HARD, TXT_MAX };
		constexpr std::size_t ANIMS_NUMBER = 3;
		constexpr std::size_t RACKETS_FRAMES_NUM = 40;
		
		struct Interface
		{
			const sdl2::Font fancyFont;
			const TextsBlocks languageTexts;
			const TextureCombo screenTitle;
			std::array< TextButton, onePlGame::SKILL_LEVEL_MAX > skillButtons;
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
		};
	}
}

#endif //ONEP_SKILL_LVL_CHOICE_GUI_H