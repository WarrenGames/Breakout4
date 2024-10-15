#ifndef ONE_PLAYER_IN_GAME_DEMOS_LOAD_DEMO_FILE_H
#define ONE_PLAYER_IN_GAME_DEMOS_LOAD_DEMO_FILE_H

#include "fileSystem/fileSystem.h"
#include <iosfwd>
#include <sstream>
#include <string>

namespace demos{ 
	struct MainPackage; 
	template<typename T>class Stack;
	struct ActionData;
	struct TaggedPositionStackData;
	struct TaggedDirectionStackData;
	struct SoundStackData;
}
struct PlayerData;
struct BrickData;
template<typename T>class MatrixTemp2D;

namespace loadDemo{
	void openFile(const fs::path& demoFilePath, demos::MainPackage& demosMainPackage, PlayerData& playerData);
	
	void readFileLines(std::ifstream& demoFile, const fs::path& demoFilePath, demos::MainPackage& demosMainPackage, PlayerData& playerData);
	
	void triggerAccordingToValue(const fs::path& demoFilePath, demos::MainPackage& demosMainPackage, PlayerData& playerData, std::size_t fileLineNumber, 
									std::istringstream& lineStream, int triggerValue);
	
	void checkTriggerValue(const fs::path& demoFilePath, int triggerValue, std::size_t fileLineNumber);
	
	void readCampaignType(const fs::path& demoFilePath, PlayerData& playerData, std::size_t fileLineNumber, std::istringstream& lineStream);
		
	void readSkillLevel(const fs::path& demoFilePath, PlayerData& playerData, std::size_t fileLineNumber, std::istringstream& lineStream);
	
	void readPlayerLives(const fs::path& demoFilePath, PlayerData& playerData, std::size_t fileLineNumber, std::istringstream& lineStream);
	
	void readRacketSize(const fs::path& demoFilePath, PlayerData& playerData, std::size_t fileLineNumber, std::istringstream& lineStream);
	
	void readScore(const fs::path& demoFilePath, PlayerData& playerData, std::size_t fileLineNumber, std::istringstream& lineStream);
	
	void readRacketSpeed(const fs::path& demoFilePath, PlayerData& playerData, std::size_t fileLineNumber, std::istringstream& lineStream);
	
	void readBonusCoinsNumber(const fs::path& demoFilePath, PlayerData& playerData, std::size_t fileLineNumber, std::istringstream& lineStream);
	
	void readRimsStartState(const fs::path& demoFilePath, PlayerData& playerData, std::size_t fileLineNumber, std::istringstream& lineStream);
	
	void readGivenBonusInBag(const fs::path& demoFilePath, PlayerData& playerData, std::size_t fileLineNumber, std::istringstream& lineStream);
	
	void readSquareSizeAtSaving(const fs::path& demoFilePath, demos::MainPackage& demosMainPackage, std::size_t fileLineNumber, std::istringstream& lineStream);
	
	void readActionEvent(const fs::path& demoFilePath, demos::Stack< demos::ActionData >& actionStack, std::size_t fileLineNumber, std::istringstream& lineStream, const std::string& itemType);
	
	void readTraceCrossPosition(const fs::path& demoFilePath, demos::MainPackage& demosMainPackage, std::size_t fileLineNumber, std::istringstream& lineStream);
	
	void readRacketPosition(const fs::path& demoFilePath, demos::MainPackage& demosMainPackage, std::size_t fileLineNumber, std::istringstream& lineStream);
	
	void readBallPosition(const fs::path& demoFilePath, demos::MainPackage& demosMainPackage, std::size_t fileLineNumber, std::istringstream& lineStream);
	
	void readBrickDestructionData(const fs::path& demoFilePath, demos::MainPackage& demosMainPackage, std::size_t fileLineNumber, std::istringstream& lineStream);
	
	void readSoundEvent(const fs::path& demoFilePath, demos::Stack< demos::SoundStackData >& soundsStack, std::size_t fileLineNumber, std::istringstream& lineStream, const std::string& itemType);
	
	void readTaggedPositionEvent(const fs::path& demoFilePath, demos::Stack< demos::TaggedPositionStackData >& positionStack, std::size_t fileLineNumber, std::istringstream& lineStream, const std::string& itemType);
	
	void readTaggedDirectionEvent(const fs::path& demoFilePath, demos::Stack< demos::TaggedDirectionStackData >& positionStack, std::size_t fileLineNumber, std::istringstream& lineStream, const std::string& itemType);
	
	void readMatrixSize(const fs::path& demoFilePath, MatrixTemp2D< BrickData >& levelMatrix, std::size_t fileLineNumber, std::istringstream& lineStream);
	
	void readMatrixElementData(const fs::path& demoFilePath, MatrixTemp2D< BrickData >& levelMatrix, std::size_t fileLineNumber, std::istringstream& lineStream);
	
	void throwLineReadError(const fs::path& demoFilePath, std::size_t fileLineNumber, const std::string& errorItem);
}

#endif //ONE_PLAYER_IN_GAME_DEMOS_LOAD_DEMO_FILE_H