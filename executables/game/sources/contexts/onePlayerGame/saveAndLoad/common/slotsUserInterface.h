#ifndef SLOTS_GRAPHICAL_USER_INTERFACE_H
#define SLOTS_GRAPHICAL_USER_INTERFACE_H

#include "texts/textLoader.h"
#include "text/sdl2ttf_font.h"
#include "widgets/buttons/textButtonWidget.h"
#include "contexts/onePlayerGame/saveAndLoad/common/slotGraphics.h"
#include "gameSlots/gameSlotData.h"
#include <vector>

class PrefPathFinder;
struct PlayerData;

class SlotsUserInterface
{
private:
	const TextsBlocks localeTexts;
	const sdl2::Font arial;
	const sdl2::Font fancyFont;
	TextureCombo title;
	TextButton quitButton;
	std::vector< GameSlotData > slotsData;
	std::vector< SlotGraphics > slotsGraphics;

public:
	explicit SlotsUserInterface(Essentials& essentials, unsigned contextFocus);
	~SlotsUserInterface() = default;
	SlotsUserInterface( const SlotsUserInterface& ) = delete;
	SlotsUserInterface& operator= ( const SlotsUserInterface& ) = delete;
	SlotsUserInterface( SlotsUserInterface&& ) = default;
	SlotsUserInterface& operator= ( SlotsUserInterface&& ) = default;
	
	void saveToFile(Essentials& essentials, const PlayerData& playerData);
	bool canLoadSlot(Essentials& essentials, PlayerData& playerData) const;
	void drawInterface(Essentials& essentials) const;
	void update(Essentials& essentials);
	bool isQuitButtonClicked() const;
	
private:
	void createSlotsGraphics(Essentials& essentials);
	void createTitle(Essentials& essentials, unsigned contextFocus);
	void loadSlotsDataFromGameSaves(Essentials& essentials, unsigned slotIndex);
	void browseAllSlotsForInitialization(Essentials& essentials);
	void savePlayerDataToSlot(Essentials& essentials, unsigned slotIndex, const PlayerData& playerData);
	void drawAllSlots(Essentials& essentials) const;
	void updateBinButtons(Essentials& essentials);
	void deleteGameSaveIfAny(Essentials& essentials);
};


namespace gameSaving{
	void startSaving(AppLogFiles& logs, const PrefPathFinder& prefPath, const GameSlotData& slot, unsigned gameSaveNumber);
}

namespace gameLoading{
	void startLoading(AppLogFiles& logs, const PrefPathFinder& prefPath, GameSlotData& slot, unsigned gameSaveNumber);
}

#endif //SLOTS_GRAPHICAL_USER_INTERFACE_H