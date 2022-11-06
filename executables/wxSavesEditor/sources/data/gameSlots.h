#ifndef GAME_SLOTS_ARRAY_H
#define GAME_SLOTS_ARRAY_H

#include "gameSlots/gameSlotData.h"
#include <vector>

struct GameSaveSlots
{
	GameSlotData slot;
	
	explicit GameSaveSlots();
	~GameSaveSlots() = default;
	GameSaveSlots( const GameSaveSlots& ) = delete;
	GameSaveSlots& operator= ( const GameSaveSlots& ) = delete;
	GameSaveSlots( GameSaveSlots&& ) = default;
	GameSaveSlots& operator= ( GameSaveSlots&& ) = default;
};

#endif //GAME_SLOTS_ARRAY_H