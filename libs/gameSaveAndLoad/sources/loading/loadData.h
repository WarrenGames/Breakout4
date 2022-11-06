#ifndef ONE_PLAYER_DATA_LOADING_H
#define ONE_PLAYER_DATA_LOADING_H

#include <iosfwd>
#include <string>
#include <sstream>

struct GameSlotData;

namespace gameLoading{
	
	void readDataFromFile(std::ifstream& gameSave, GameSlotData& slot);
	
	void readWholeLine(std::ifstream& gameSave, std::string& line, const std::string& errorMessage);
	
	void readFileLines(std::ifstream& gameSave, GameSlotData& slot);
	
	void triggerDataProcessing(std::istringstream& lineStream, GameSlotData& slot, unsigned triggerValue);
	
	void campaignType(std::istringstream& lineStream, GameSlotData& slot);
	
	void skillLevel(std::istringstream& lineStream, GameSlotData& slot);
	
	void playerLives(std::istringstream& lineStream, GameSlotData& slot);
	
	void racketSpeed(std::istringstream& lineStream, GameSlotData& slot);
	
	void racketSize(std::istringstream& lineStream, GameSlotData& slot);
	
	void score(std::istringstream& lineStream, GameSlotData& slot);
	
	void bonusCoinNumber(std::istringstream& lineStream, GameSlotData& slot);
	
	void rimState(std::istringstream& lineStream, GameSlotData& slot);
	
	void levelCursor(std::istringstream& lineStream, GameSlotData& slot);
	
	void bagBonus(std::istringstream& lineStream, GameSlotData& slot);
	
	void badTriggerValue(unsigned triggerValue);
}

#endif //ONE_PLAYER_DATA_LOADING_H