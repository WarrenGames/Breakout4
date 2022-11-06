#include "contexts/duels/matchConfig/bonusesSlots/bonusSlot.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "types/essentialsStruct.h"
#include "contexts/duels/duelsConstexpr.h"
#include <cassert>
#include <algorithm>

duels::BonusesSlot::BonusesSlot(Essentials& essentials, unsigned slotNumber):
	isLoadingPerfect{true},
	bonuses(duels::DuelBonusMax)
{
	std::fill( bonuses.begin(), bonuses.end(), 1);
	duels::BonusesSlot::openFileForLoading(essentials, slotNumber);
}

void duels::BonusesSlot::openFileForLoading(Essentials& essentials, unsigned slotNumber)
{
	if( std::ifstream slotFile{path::getBonusesGranularitySlotPath(essentials.prefPath, slotNumber) } )
	{
		for( auto &bonus : bonuses )
		{
			if( !( slotFile >> bonus ) )
			{
				isLoadingPerfect = false;
				break;
			}
		}
	}
	else{
		isLoadingPerfect = false;
		essentials.logs.error << "Error: couldn't open '" << path::getBonusesGranularitySlotPath(essentials.prefPath, slotNumber) << "' file in order to load bonuses slot.\n";
	}
}

bool duels::BonusesSlot::writeSlotDataToFile(Essentials& essentials, unsigned slotNumber) const
{
	if( std::ofstream slotFile{ path::getBonusesGranularitySlotPath(essentials.prefPath, slotNumber) } )
	{
		return std::all_of(bonuses.cbegin(), bonuses.cend(), [&slotFile](auto bonus)
		{
			if( slotFile << bonus << " " )
				return true;
			else
				return false;
		} 
		);
	}
	else{
		essentials.logs.error << "Error: couldn't write bonuses data in the following file: '" << path::getBonusesGranularitySlotPath(essentials.prefPath, slotNumber) << "' .\n";
		return false;
	}
}

unsigned duels::BonusesSlot::getBonusValue(unsigned bonusNum) const
{
	assert( bonusNum < bonuses.size() );
	return bonuses[bonusNum];
}

unsigned& duels::BonusesSlot::getBonusValue(unsigned bonusNum)
{
	assert( bonusNum < bonuses.size() );
	return bonuses[bonusNum];
}