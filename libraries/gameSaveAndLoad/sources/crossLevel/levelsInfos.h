#ifndef GAME_SAVE_AND_LOAD_LIB_LEVELS_INFOS_H
#define GAME_SAVE_AND_LOAD_LIB_LEVELS_INFOS_H

#include "fileSystem/fileSystem.h"
#include <string>
#include <vector>
#include <sstream>

struct AppLogFiles;

struct SingleLevelInfos
{
	unsigned levelType;//Is it a level with pinguin, hell skull and fire balls or a simple level
	std::string mainLevelFileName;
	std::string levelGridPath;
	std::string monsterFileName;
	std::string elementsFileName;
	
	SingleLevelInfos();
	~SingleLevelInfos() = default;
	SingleLevelInfos( const SingleLevelInfos& ) = delete;
	SingleLevelInfos& operator= ( const SingleLevelInfos& ) = delete;
	SingleLevelInfos( SingleLevelInfos&& ) = default;
	SingleLevelInfos& operator= ( SingleLevelInfos&& ) = default;
	
};

class LevelsInfos
{
private:
	std::vector< SingleLevelInfos > levelsListing;
	std::string campaignFilesDirectory;
	
public:
	explicit LevelsInfos(AppLogFiles& logs, unsigned gameType, const fs::path& levelsListPath);
	explicit LevelsInfos() = default;
	~LevelsInfos() = default;
	LevelsInfos( const LevelsInfos& ) = delete;
	LevelsInfos& operator= ( const LevelsInfos& ) = delete;
	LevelsInfos( LevelsInfos&& ) = default;
	LevelsInfos& operator= ( LevelsInfos&& ) = default;
	
	unsigned getLevelType(std::size_t levelIndex) const;
	const std::string& getMainLevelFileName(std::size_t levelIndex) const;
	const std::string& getMatrixPath(std::size_t levelIndex) const;
	const std::string& getMonstersFilePath(std::size_t levelIndex) const;
	const std::string& getElementsFilePath(std::size_t levelIndex) const;
	void setCampaignFilesDirectory(unsigned gameType);
	void loadLevelsList(AppLogFiles& logs, const fs::path& levelsListPath);
	std::size_t size() const;
	
private:
	void readLevelConfigFile(AppLogFiles& logs, const std::string& levelConfigFileName);
	void triggerLoadingWithIndex(AppLogFiles& logs, std::istringstream& lineStream, const std::string& levelConfigFileName, SingleLevelInfos& levelInfos, unsigned index);
	void setGameType(AppLogFiles& logs, std::istringstream& lineStream, const std::string& levelConfigFileName, SingleLevelInfos& levelInfos);
	void setFileName(AppLogFiles& logs, std::istringstream& lineStream, const std::string& levelConfigFileName, std::string& fileName);
	std::string getLevelsPath(std::size_t gameType) const;
};

#endif //GAME_SAVE_AND_LOAD_LIB_LEVELS_INFOS_H