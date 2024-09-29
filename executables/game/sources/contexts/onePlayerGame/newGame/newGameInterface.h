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
		enum{ TextTitle, TextStartNewGame, TextLoadSavedGame, TextSeeDoneScores, RecordA_Demo, PlayDemo, TextGoBack, TextSkillMax };
		constexpr std::size_t BrickImagesNumber = 40;
		
		struct Interface
		{
			const sdl2::Font fancyFont;
			const TextsBlocks languageTexts;
			const TextureCombo screenTitle;
			const TextureCombo screenBackground;
			TextButton newGameButton;
			TextButton loadASavedGame;
			TextButton seeDoneScores;
			TextButton recordDemo;
			TextButton playDemo;
			TextButton goBackButton;
			TexturesFilesList bricksAnimation;
			ConstAnimDraw bricksSprites;
			std::vector< unsigned > animIndexes;
			AccurateTimeDelay animDelay;
			
			explicit Interface(Essentials& essentials);
			~Interface() = default;
			Interface( const Interface& ) = delete;
			Interface& operator= ( const Interface& ) = delete;
			Interface( Interface&& ) = default;
			Interface& operator= ( Interface&& ) = default;
			
			void update(const Essentials& essentials);
			void drawEverything(Essentials& essentials);
			void updateAnimation();
			void setIndexesAtInitialization();
		};
	}
}

#endif //ONE_PLAYER_NEW_GAME_INTERFACE_H