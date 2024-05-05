#ifndef PLAYER_DATA_STRUCT_H
#define PLAYER_DATA_STRUCT_H

#include "crossLevel/levelsInfos.h"
#include <vector>
#include <string>

struct AppLogFiles;
struct GameSlotData;

struct PlayerData
{
	unsigned campaignType;//Campaign enum
	unsigned skillLevel;
	unsigned playerLives;
	unsigned racketSize;
	double racketSpeed;
	unsigned score;
	unsigned bonusCoinsNumber;
	int rimsStartState;
	unsigned demoKind;
	LevelsInfos levelsInfos;
	std::size_t levelIndex;
	std::vector< unsigned > bonusesInBag;
	std::vector< unsigned > bonusesCosts;

	explicit PlayerData(AppLogFiles& logs, unsigned campaignType_, unsigned skillLevel_, const fs::path& levelsListPath, unsigned demoEnumValue);
	explicit PlayerData(unsigned demoEnumValue);
	~PlayerData() = default;
	PlayerData( const PlayerData& ) = delete;
	PlayerData& operator= ( const PlayerData& ) = delete;
	PlayerData( PlayerData&& ) = default;
	PlayerData& operator= ( PlayerData&& ) = default;
	
	PlayerData& operator= ( const GameSlotData& slot );
	
	void laterInitialization(AppLogFiles& logs);
	
	void readBonusesInBagConfigurationFile(AppLogFiles& logs, const std::string& filePath);
	
	void initPlayerData(AppLogFiles& logs);
	void easyInit();
	void intermInit();
	void hardInit();
	void setCursorToNextLevel();
	
	bool buyABonusIfPossible(std::size_t bonusIndex);
	void addBonusToBag(std::size_t bonusIndex);
	unsigned getLevelType() const;
	std::string getMainLevelFileName() const;
	std::string getMatrixPath() const;
	std::string getElementsFilePath() const;
	std::string getMonstersFilePath() const;
};

#endif //PLAYER_DATA_STRUCT_H