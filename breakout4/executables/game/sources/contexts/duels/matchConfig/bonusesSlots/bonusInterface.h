#ifndef DUELS_BONUSES_INTERFACE_H
#define DUELS_BONUSES_INTERFACE_H

#include "texts/textLoader.h"
#include "widgets/editBoxes/uint_editBox.h"
#include "texturing/texturesCombo.h"
#include "contexts/duels/matchConfig/bonusesSlots/slotsData.h"
#include "widgets/buttons/textButtonWidget.h"
#include <vector>

struct ZoneChoiceThings;

namespace duels{

struct LevelOptions;
	
struct BonusesInterface
{
	const TextsBlocks languagesTexts;
	const sdl2::Font fancyFont;
	duels::SlotsData data;
	std::vector< UintEditBox > editBoxes;
	std::vector< TextureCombo > slotsTexts;
	std::vector< TextButton > saveButtons;
	std::vector< TextButton > loadButtons;
	const TextureCombo screenTitle;
	TextButton quit;
	sdl2::Mix_ChunkPtr saveWithSuccess;
	
	explicit BonusesInterface(Essentials& essentials);
	~BonusesInterface() = default;
	BonusesInterface( const BonusesInterface& ) = delete;
	BonusesInterface& operator= ( const BonusesInterface& ) = delete;
	BonusesInterface( BonusesInterface&& ) = default;
	BonusesInterface& operator= ( BonusesInterface&& ) = default;
	
	operator bool() const;
	
	void drawEverything(Essentials& essentials) const;
	void drawBoxes(Essentials& essentials) const;
	void drawSlotsTexts(Essentials& essentials) const;
	void drawSaveButtons(Essentials& essentials) const;
	void drawLoadButtons(Essentials& essentials) const;
	
	void update(Essentials& essentials);
	void updateBoxes(Essentials& essentials);
	void updateSaveButtons(Essentials& essentials);
	void updateLoadButtons(Essentials& essentials);
	
	void writeData(Essentials& essentials) const;
	void loadDataToCurrent(Essentials& essentials, ZoneChoiceThings& zoneChoiceThings, bool& quitMenu) const;
	
	void loadBoxes(Essentials& essentials);
	void loadSlotsTexts(Essentials& essentials);
	void loadSaveButtons(Essentials& essentials);
};

}

#endif //DUELS_BONUSES_INTERFACE_H