#ifndef ONE_PLAYER_IN_GAME_DEMOS_SAVE_DEMO_FILE_H
#define ONE_PLAYER_IN_GAME_DEMOS_SAVE_DEMO_FILE_H

#include "fileSystem/fileSystem.h"
#include <iosfwd>

namespace demos{ 
	struct MainPackage; 
	struct StartingData; 
	struct ActionData; 
	struct PositionStackData;
	struct Matrix2DAction;
	struct SoundStackData;
	struct TaggedPositionStackData;
	struct TaggedDirectionStackData;
	template<typename T>class Stack; 
}

namespace saveDemo{

	void openGameDemoFile(const fs::path& demoFilePath, const demos::MainPackage& mainPackage);

	void saveData(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::MainPackage& mainPackage);

	void saveCampaignType(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::StartingData& startingData);
	
	void saveLevelIndex(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::StartingData& startingData);
	
	void saveSkillLevel(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::StartingData& startingData);
	
	void savePlayerLives(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::StartingData& startingData);
	
	void saveRacketSize(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::StartingData& startingData);
	
	void saveScore(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::StartingData& startingData);
	
	void saveRacketSpeed(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::StartingData& startingData);
	
	void saveBonusCoinNumber(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::StartingData& startingData);
	
	void saveRimsStartState(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::StartingData& startingData);
	
	void saveGivenBonusInBag(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::StartingData& startingData);
	
	void saveSquareSize(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::StartingData& startingData);
	
	void saveActionEvent(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::Stack< demos::ActionData >& actionEvents, const std::string& itemType, unsigned indexEnum);
	
	void savePositionStackEvent(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::Stack< demos::PositionStackData >& positionStack, const std::string& itemType, unsigned indexEnum);
	
	void saveBrickDestructions(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::Stack< demos::Matrix2DAction >& bricksDestruction);
	
	void saveSoundEvents(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::Stack< demos::SoundStackData >& soundsEvent, const std::string& itemType, unsigned indexEnum);
	
	void saveTaggedPositions(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::Stack< demos::TaggedPositionStackData >& taggedPositions, const std::string& itemType, unsigned indexEnum);
	
	void saveTaggedDirections(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::Stack< demos::TaggedDirectionStackData >& taggedDirections, const std::string& itemType, unsigned indexEnum);
	
	void throwWriteErrorExcept(const fs::path& demoFilePath, const std::string& toSaveItem);
}

#endif //ONE_PLAYER_IN_GAME_DEMOS_SAVE_DEMO_FILE_H