#ifndef ONE_PLAYER_DATA_SAVING_H
#define ONE_PLAYER_DATA_SAVING_H

#include <iosfwd>
#include <string>

struct GameSlotData;

namespace gameSaving{
	
	void writeDataToFile(std::ofstream& saveFile, const GameSlotData& slot);
	
	void writeWholeLine(std::ofstream& saveFile, const std::string& stringToSave, const std::string& stringMeaning);
	
	void campaignType(std::ofstream& saveFile, const GameSlotData& slot);
	
	void skillLevel(std::ofstream& saveFile, const GameSlotData& slot);
	
	void playerLives(std::ofstream& saveFile, const GameSlotData& slot);
	
	void racketSpeed(std::ofstream& saveFile, const GameSlotData& slot);
	
	void racketSize(std::ofstream& saveFile, const GameSlotData& slot);
	
	void score(std::ofstream& saveFile, const GameSlotData& slot);
	
	void bonusCoinNumber(std::ofstream& saveFile, const GameSlotData& slot);
	
	void rimState(std::ofstream& saveFile, const GameSlotData& slot);
	
	void levelCursor(std::ofstream& saveFile, const GameSlotData& slot);
	
	void bagBonus(std::ofstream& saveFile, const GameSlotData& slot);
}

#endif //ONE_PLAYER_DATA_SAVING_H