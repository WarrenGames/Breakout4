#ifndef ONE_PLAYER_LEVEL_COMPLETE_INTERFACE_H
#define ONE_PLAYER_LEVEL_COMPLETE_INTERFACE_H

#include "text/sdl2ttf_font.h"
#include "texts/textLoader.h"
#include "texturing/texturesCombo.h"

struct Essentials;

enum{ 	LevelCompleteTitle,
		LevelComplete1_BrickRemains, 
		LevelCompleteBonifications, 
		LevelCompleteNoMoreCoin, 
		LevelCompleteAllBricksDestroyed,
		LevelComplete400_Bonus, 
		LevelComplete1_MoreCoin, 
		LevelCompleteCarryOnKeys, 
		LevelCompleteGameOver,
		LevelCompleteMax };

class LevelCompleteGUI
{
private:
	sdl2::Font fancyFont;
	TextsBlocks languagesTexts;
	std::vector< TextureCombo > texts;

public:
	explicit LevelCompleteGUI(Essentials& essentials);
	~LevelCompleteGUI() = default;
	LevelCompleteGUI( const LevelCompleteGUI& ) = delete;
	LevelCompleteGUI& operator= ( const LevelCompleteGUI& ) = delete;
	LevelCompleteGUI( LevelCompleteGUI&& ) = default;
	LevelCompleteGUI& operator= ( LevelCompleteGUI&& ) = default;
	
	void drawLevelSum(Essentials& essentials, unsigned levelEndType) const;

private:
	void drawPartiallyCompleteLevel(Essentials& essentials) const;
	void drawFullyCompleteLevel(Essentials& essentials) const;
	void drawGameOverLevel(Essentials& essentials) const;
};

#endif //ONE_PLAYER_LEVEL_COMPLETE_INTERFACE_H