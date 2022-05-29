#ifndef FINAL_ACHIEVEMENT_WIDGETS_H
#define FINAL_ACHIEVEMENT_WIDGETS_H

#include "widgets/buttons/textButtonWidget.h"
#include "widgets/editBoxes/boxesIncludes.h"

struct Essentials;
namespace sdl2{ class Font; }
class TextsBlocks;
struct Offset;

namespace duels{

namespace finAchiev{

enum{ SCORE_TO_REACH, START_DUELS, QUIT, MAX};
	
struct Widgets
{
	TextureCombo setFinalScore;
	TextButton runDuels;
	TextButton quitContext;
	UintEditBox scoreEdition;
	
	Widgets(Essentials& essentials, const sdl2::Font& fancyFont, const TextsBlocks& texts, unsigned& finalScore);
	
	void update(Essentials& essentials, const Offset& mousePos, bool isMouseButtonPushed);
	void drawAll(Essentials& essentials) const;
};

}

}

#endif //FINAL_ACHIEVEMENT_WIDGETS_H