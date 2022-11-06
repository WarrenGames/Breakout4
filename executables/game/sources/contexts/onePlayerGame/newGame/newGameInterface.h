#ifndef ONE_PLAYER_NEW_GAME_INTERFACE_H
#define ONE_PLAYER_NEW_GAME_INTERFACE_H


#include "text/sdl2ttf_font.h"
#include "texts/textLoader.h"
#include "texturing/texturesCombo.h"
#include "widgets/buttons/textButtonWidget.h"
#include "advancedDrawing/texturesLoading/fileTexturesList.h"
#include "advancedDrawing/texturesDrawing/constAnimationDrawing.h"
#include "time/accurateTime.h"

struct Essentials;

namespace onePlGame{
	namespace newGame{
		enum{ TextTitle, TextStartNewGame, TextLoadSavedGame, TextSeeDoneScores, TextGoBack, TextSkillMax };
		constexpr std::size_t BrickImagesNumber = 40;
		
		struct Interface
		{
			const sdl2::Font fancyFont;
			const TextsBlocks languageTexts;
			const TextureCombo screenTitle;
			TextButton newGameButton;
			TextButton loadASavedGame;
			TextButton seeDoneScores;
			TextButton goBackButton;
			TexturesFilesList bricksAnimation;
			ConstAnimDraw bricksSprites;
			std::vector< unsigned > animIndexes;
			AccurateTimeDelay animDelay;
			
			explicit Interface(Essentials& essentials);
			~Interface() = default;
			void update(const Essentials& essentials);
			void drawEverything(Essentials& essentials);
			void updateAnimation();
		};
	}
}

#endif //ONE_PLAYER_NEW_GAME_INTERFACE_H