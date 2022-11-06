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

enum{ ScoreToReach, StartDuels, Quit, Max};
	
struct Widgets
{
	TextureCombo setFinalScore;
	TextButton runDuels;
	TextButton quitContext;
	UintEditBox scoreEdition;
	
	explicit Widgets(Essentials& essentials, const sdl2::Font& fancyFont, const TextsBlocks& texts, unsigned& finalScore);
	
	void update(Essentials& essentials, const Offset& mousePos, bool isMouseButtonPushed);
	void drawAll(Essentials& essentials) const;
};

}

}

#endif //FINAL_ACHIEVEMENT_WIDGETS_H