#include "loading/loadData.h"
#include "gameSlots/gameSlotData.h"
#include "exceptions/readErrorExcept.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "gameSlots/slotConsts.h"
#include <fstream>

void gameLoading::readDataFromFile(std::ifstream& gameSave, GameSlotData& slot)
{
	gameLoading::readWholeLine(gameSave, slot.campaignAndDateInfos, CAMPAIGN_INFOS_STRING);
	gameLoading::readWholeLine(gameSave, slot.scoreAndCoinsInfos, SCORE_AND_COINS_STRING);
	gameLoading::readFileLines(gameSave, slot);
}

void gameLoading::readWholeLine(std::ifstream& gameSave, std::string& line, const std::string& errorMessage)
{
	if( !( std::getline(gameSave, line) ) )
	{
		throw ReadError{"Error: couldn't read '" + errorMessage + "' in game save file"};
	}
}

void gameLoading::readFileLines(std::ifstream& gameSave, GameSlotData& slot)
{
	std::string fileLine;
	unsigned triggerValue{0};
	while( std::getline(gameSave, fileLine ) )
	{
		std::istringstream lineStream{fileLine};
		if( lineStream >> triggerValue )
		{
			gameLoading::triggerDataProcessing(lineStream, slot, triggerValue);
		}
	}
}

void gameLoading::triggerDataProcessing(std::istringstream& lineStream, GameSlotData& slot, unsigned triggerValue)
{
	switch( triggerValue )
	{
		case SAVE_IND_CAMPAIGN_TYPE:
			gameLoading::campaignType(lineStream, slot);
			break;
		case SAVE_IND_SKILL_LEVEL:
			gameLoading::skillLevel(lineStream, slot);
			break;
		case SAVE_IND_PLAYER_LIVES:
			gameLoading::playerLives(lineStream, slot);
			break;
		case SAVE_IND_RACKET_SPEED:
			gameLoading::racketSpeed(lineStream, slot);
			break;
		case SAVE_IND_RACKET_SIZE:
			gameLoading::racketSize(lineStream, slot);
			break;
		case SAVE_IND_SCORE:
			gameLoading::score(lineStream, slot);
			break;
		case SAVE_IND_BONUS_COIN_NUMBER:
			gameLoading::bonusCoinNumber(lineStream, slot);
			break;
		case SAVE_IND_RIM_STATE:
			gameLoading::rimState(lineStream, slot);
			break;
		case SAVE_IND_LEVEL_CURSOR:
			gameLoading::levelCursor(lineStream, slot);
			break;
		case SAVE_IND_BAG_BONUS:
			gameLoading::bagBonus(lineStream, slot);
			break;
		default:
			gameLoading::badTriggerValue(triggerValue);
			break;
	}
}

void gameLoading::campaignType(std::istringstream& lineStream, GameSlotData& slot)
{
	if( ! ( lineStream >> slot.gameType ) )
	{
		throw ReadError{"Error: couldn't read 'camapign type value in game save."};
	}
}

void gameLoading::skillLevel(std::istringstream& lineStream, GameSlotData& slot)
{
	if( ! ( lineStream >> slot.skillLevel ) )
	{
		throw ReadError{"Error: couldn't read 'skill level' value in game save."};
	}
}

void gameLoading::playerLives(std::istringstream& lineStream, GameSlotData& slot)
{
	if( ! ( lineStream >> slot.playerLives ) )
	{
		throw ReadError{"Error: couldn't read 'player lives' value in game save."};
	}
}

void gameLoading::racketSpeed(std::istringstream& lineStream, GameSlotData& slot)
{
	if( ! ( lineStream >> slot.racketSpeed ) )
	{
		throw ReadError{"Error: couldn't read 'racket speed' value in game save."};
	}
}

void gameLoading::racketSize(std::istringstream& lineStream, GameSlotData& slot)
{
	if( ! ( lineStream >> slot.racketSize ) )
	{
		throw ReadError{"Error: couldn't read 'racket size' value in game save."};
	}
}

void gameLoading::score(std::istringstream& lineStream, GameSlotData& slot)
{
	if( ! ( lineStream >> slot.score ) )
	{
		throw ReadError{"Error: couldn't read 'score' value in game save."};
	}
}

void gameLoading::bonusCoinNumber(std::istringstream& lineStream, GameSlotData& slot)
{
	if( ! ( lineStream >> slot.bonusCoinNumber ) )
	{
		throw ReadError{"Error: couldn't read 'bonus coin number' value in game save."};
	}
}

void gameLoading::rimState(std::istringstream& lineStream, GameSlotData& slot)
{
	if( ! ( lineStream >> slot.rimsStartState ) )
	{
		throw ReadError{"Error: couldn't read 'rims state' value in game save."};
	}
}

void gameLoading::levelCursor(std::istringstream& lineStream, GameSlotData& slot)
{
	if( ! ( lineStream >> slot.levelCursor ) )
	{
		throw ReadError{"Error: couldn't read 'level cursor' value in game save."};
	}
}

void gameLoading::bagBonus(std::istringstream& lineStream, GameSlotData& slot)
{
	std::size_t bonusIndex{0};
	if( lineStream >> bonusIndex )
	{
		if( bonusIndex < slot.bonusesInBag.size() )
		{
			if( ! ( lineStream >> slot.bonusesInBag[bonusIndex] ) )
			{
				throw ReadError{"Error: couldn' t read 'bonus in bag' value in game save."};
			}
		}
		else{
			throw ReadError{"Error: read 'bonus index' value in a game save is too high."};
		}
	}
	else{
		throw ReadError{"Error: couldn't read 'bonus index' value in game save."};
	}
}

void gameLoading::badTriggerValue(unsigned triggerValue)
{
	throw ReadError{"Error: bad trigger value: '" + std::to_string( triggerValue ) + "' ."};
}