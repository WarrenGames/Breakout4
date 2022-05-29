#include "saving/saveData.h"
#include "gameSlots/gameSlotData.h"
#include "exceptions/writeErrorExcept.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "gameSlots/slotConsts.h"
#include <fstream>

void gameSaving::writeDataToFile(std::ofstream& saveFile, const GameSlotData& slot)
{
	gameSaving::writeWholeLine(saveFile, slot.campaignAndDateInfos, CAMPAIGN_INFOS_STRING);
	gameSaving::writeWholeLine(saveFile, slot.scoreAndCoinsInfos, SCORE_AND_COINS_STRING);
	gameSaving::campaignType(saveFile, slot);
	gameSaving::skillLevel(saveFile, slot);
	gameSaving::playerLives(saveFile, slot);
	gameSaving::racketSpeed(saveFile, slot);
	gameSaving::racketSize(saveFile, slot);
	gameSaving::score(saveFile, slot);
	gameSaving::bonusCoinNumber(saveFile, slot);
	gameSaving::rimState(saveFile, slot);
	gameSaving::levelCursor(saveFile, slot);
	gameSaving::bagBonus(saveFile, slot);
}

void gameSaving::writeWholeLine(std::ofstream& saveFile, const std::string& stringToSave, const std::string& stringMeaning)
{
	if( ! ( saveFile << stringToSave << '\n' ) )
	{
		throw WriteError{"Error: couldn't write the string for the '" + stringMeaning + "'.\n"};
	}
}

void gameSaving::campaignType(std::ofstream& saveFile, const GameSlotData& slot)
{
	if( !( saveFile << SAVE_IND_CAMPAIGN_TYPE << " " << slot.gameType << '\n' ) )
	{
		throw WriteError{"Error: couldn't write 'campaign type' for one player game saving."};
	}
}

void gameSaving::skillLevel(std::ofstream& saveFile, const GameSlotData& slot)
{
	if( !( saveFile << SAVE_IND_SKILL_LEVEL << " " << slot.skillLevel << '\n' ) )
	{
		throw WriteError{"Error: couldn't write 'skill level' for one player game saving."};
	}
}

void gameSaving::playerLives(std::ofstream& saveFile, const GameSlotData& slot)
{
	if( !( saveFile << SAVE_IND_PLAYER_LIVES << " " << slot.playerLives << '\n' ) )
	{
		throw WriteError{"Error: couldn't write 'player lives' for one player game saving."};
	}
}

void gameSaving::racketSpeed(std::ofstream& saveFile, const GameSlotData& slot)
{
	if( ! ( saveFile << SAVE_IND_RACKET_SPEED << " " << slot.racketSpeed << '\n' ) )
	{
		throw WriteError{"Error: couldn't write 'racket speed' for one player game saving."};
	}
}

void gameSaving::racketSize(std::ofstream& saveFile, const GameSlotData& slot)
{
	if( !( saveFile << SAVE_IND_RACKET_SIZE << " " << slot.racketSize << '\n' ) )
	{
		throw WriteError{"Error: couldn't write 'racket size' for one player game saving."};
	}
}

void gameSaving::score(std::ofstream& saveFile, const GameSlotData& slot)
{
	if( !( saveFile << SAVE_IND_SCORE << " " << slot.score << '\n' ) )
	{
		throw WriteError{"Error: couldn't write 'score' for one player game saving."};
	}
}

void gameSaving::bonusCoinNumber(std::ofstream& saveFile, const GameSlotData& slot)
{
	if( !( saveFile << SAVE_IND_BONUS_COIN_NUMBER << " " << slot.bonusCoinNumber << '\n' ) )
	{
		throw WriteError{"Error: couldn't write 'bonus coin number' for one player game saving."};
	}
}

void gameSaving::rimState(std::ofstream& saveFile, const GameSlotData& slot)
{
	if( !( saveFile << SAVE_IND_RIM_STATE << " " << slot.rimsStartState << '\n' ) )
	{
		throw WriteError{"Error: couldn't write 'rim start state' for one player game saving."};
	}
}

void gameSaving::levelCursor(std::ofstream& saveFile, const GameSlotData& slot)
{
	if( !( saveFile << SAVE_IND_LEVEL_CURSOR << " " << slot.levelCursor << '\n' ) )
	{
		throw WriteError{"Error: couldn't write 'level cursor' for one player game saving."};
	}
}

void gameSaving::bagBonus(std::ofstream& saveFile, const GameSlotData& slot)
{
	for( std::size_t i{0} ; i < slot.bonusesInBag.size() ; ++i )
	{
		if( ! ( saveFile << SAVE_IND_BAG_BONUS << " " << i << " " << slot.bonusesInBag[i] << '\n' ) )
		{
			throw WriteError{"Error: couldn't write 'bag bonus #" + std::to_string(i) + "' for one player game saving."};
		}
	}
}