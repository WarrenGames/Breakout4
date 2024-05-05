#ifndef GAME_SLOTS_ARRAY_H
#define GAME_SLOTS_ARRAY_H

#include "gameSlots/gameSlotData.h"
#include <string>

struct GameSaveSlots
{
	GameSlotData slot;
	
	GameSaveSlots();
	~GameSaveSlots() = default;
	GameSaveSlots( const GameSaveSlots& ) = delete;
	GameSaveSlots& operator= ( const GameSaveSlots& ) = delete;
	GameSaveSlots( GameSaveSlots&& ) = default;
	GameSaveSlots& operator= ( GameSaveSlots&& ) = default;
	
	void giveSlotCoherentValues();
	
	void checkSlot() const;
	void checkSkillLevelValue() const;
	void checkCampaignType() const;
	void checkRacketSize() const;
	void checkRimsState() const;
	
	void throwExceptionIfAnyErrorHappen(const std::string& wrongAttributeType, int startValue, int endExcludedValue) const;
};

#endif //GAME_SLOTS_ARRAY_H