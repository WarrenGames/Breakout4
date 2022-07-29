#ifndef ONE_PLAYER_LEVEL_COMPLETE_INTERFACE_H
#define ONE_PLAYER_LEVEL_COMPLETE_INTERFACE_H

#include "text/sdl2ttf_font.h"
#include "texts/textLoader.h"
#include "texturing/texturesCombo.h"

struct Essentials;

enum{ 	LVL_COMP_TITLE, 		// = 0
		LVL_COMP_1BR_REMAINS, 
		LVL_COMP_NO_BONIF, 
		LVL_COMP_NO_MORE_COIN, 
		LVL_COMP_ALL_BR_DESTR, 	// = 4
		LVL_COMP_400_BON, 
		LVL_COMP_1MORE_COIN, 
		LVL_COMP_CARRYON_KEYS, 
		LVL_COMP_GAMEOVER,		// = 8
		LVL_COMP_MAX };			// = 9

class LevelCompleteGUI
{
private:
	const sdl2::Font fancyFont;
	const TextsBlocks languagesTexts;
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