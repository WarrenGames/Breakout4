#ifndef ONE_PLAYER_GAME_GAME_SLOT_DATA_H
#define ONE_PLAYER_GAME_GAME_SLOT_DATA_H

#include <string>
#include <vector>

struct PlayerData;
class TextsBlocks;

struct GameSlotData
{
	bool isAnActiveSave;
	unsigned campaignType;
	unsigned skillLevel;
	unsigned playerLives;
	double racketSpeed;
	unsigned racketSize;
	unsigned score;
	unsigned bonusCoinNumber;
	int rimsStartState;
	std::size_t levelCursor;
	std::vector< unsigned > bonusesInBag;
	std::string campaignAndDateInfos;
	std::string scoreAndCoinsInfos;
	
	explicit GameSlotData();
	~GameSlotData() = default;
	GameSlotData( const GameSlotData& ) = delete;
	GameSlotData& operator= ( const GameSlotData& ) = delete;
	GameSlotData( GameSlotData&& ) = default;
	GameSlotData& operator= ( GameSlotData&& ) = default;
	
	GameSlotData& operator =( const PlayerData& playerData );
	void setCampaign(const TextsBlocks& localeTexts);
	void addDateToString();
	void setScoreAndCoins(const TextsBlocks& localeTexts);
};

#endif //ONE_PLAYER_GAME_GAME_SLOT_DATA_H