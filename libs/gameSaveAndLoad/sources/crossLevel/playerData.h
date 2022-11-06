#ifndef PLAYER_DATA_STRUCT_H
#define PLAYER_DATA_STRUCT_H

#include "consts/onePlayerBonusesConsts.h"
#include <vector>
#include <string>

struct AppLogFiles;
struct GameSlotData;

struct LevelInfos
{
	unsigned levelType;//Is it a level with pinguin, hell skull and fire balls or a simple level
	std::string levelGridPath;
	std::string monsterFileName;
	std::string elementsFileName;
	
	LevelInfos();
};

struct PlayerData
{
	unsigned gameType;//Campaign enum
	unsigned skillLevel;
	unsigned playerLives;
	unsigned racketSize;
	double racketSpeed;
	unsigned score;
	unsigned bonusCoinsNumber;
	int rimsStartState;
	std::string campaignFilesDirectory;
	std::vector< LevelInfos > levelsListing;
	std::size_t levelCursor;
	std::vector< unsigned > bonusesInBag;
	std::vector< unsigned > bonusesCosts;

	explicit PlayerData(AppLogFiles& logs, unsigned gameType_, unsigned skillLevel_, const std::string& levelsListPath);
	explicit PlayerData();
	~PlayerData() = default;
	PlayerData( const PlayerData& ) = delete;
	PlayerData& operator= ( const PlayerData& ) = delete;
	PlayerData( PlayerData&& ) = default;
	PlayerData& operator= ( PlayerData&& ) = default;
	
	PlayerData& operator= ( const GameSlotData& slot );
	
	void laterInitialization(AppLogFiles& logs);
	
	void loadLevelsList(AppLogFiles& logs, const std::string& levelsListPath);
	void readLevelConfigFile(AppLogFiles& logs, const std::string& levelConfigFileName);
	void triggerLoadingWithIndex(AppLogFiles& logs, std::istringstream& lineStream, const std::string& levelConfigFileName, LevelInfos& levelInfos, unsigned index);
	void setGameType(AppLogFiles& logs, std::istringstream& lineStream, const std::string& levelConfigFileName, LevelInfos& levelInfos);
	void setFileName(AppLogFiles& logs, std::istringstream& lineStream, const std::string& levelConfigFileName, std::string& fileName);
	
	void readBonusesInBagConfigurationFile(AppLogFiles& logs, const std::string& filePath);
	
	void initPlayerData(AppLogFiles& logs);
	void easyInit();
	void intermInit();
	void hardInit();
	void setCursorToNextLevel();
	
	const std::string& getMatrixPath() const;
	const std::string& getMonstersFilePath() const;
	const std::string& getElementsFilePath() const;
	unsigned getLevelType() const;
	
	bool buyABonusIfPossible(std::size_t bonusIndex);
	
	std::string getLevelsPath(std::size_t gameType) const;
	void addBonusToBag(std::size_t bonusIndex);
};

#endif //PLAYER_DATA_STRUCT_H