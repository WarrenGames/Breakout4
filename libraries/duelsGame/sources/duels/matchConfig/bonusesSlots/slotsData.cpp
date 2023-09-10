#include "duels/matchConfig/bonusesSlots/slotsData.h"
#include "types/essentialsStruct.h"
#include "duels/matchConfig/bonusesSlots/slotsConsts.h"
#include "consts/duelsConstexpr.h"
#include <cassert>

duels::SlotsData::SlotsData(Essentials& essentials):
	isLoadingPerfect{true}
{
	for( unsigned slotNum{0} ; slotNum < SlotsNumber ; ++slotNum )
	{
		data.emplace_back( duels::BonusesSlot{essentials, slotNum} );
	}
}

duels::SlotsData::operator bool() const
{
	return isLoadingPerfect;
}

unsigned duels::SlotsData::getValue(unsigned slotNumber, unsigned bonusNumber) const
{
	assert( slotNumber < data.size() );
	assert( bonusNumber < duels::DuelBonusMax );
	return data[slotNumber].getBonusValue(bonusNumber);
}

unsigned& duels::SlotsData::getValue(unsigned slotNumber, unsigned bonusNumber)
{
	assert( slotNumber < data.size() );
	assert( bonusNumber < duels::DuelBonusMax );
	return data[slotNumber].getBonusValue(bonusNumber);
}

std::size_t duels::SlotsData::getSlotsNumber() const
{
	return data.size();
}

bool duels::SlotsData::writeBonusesData(Essentials& essentials, unsigned slotNumber) const
{
	assert( slotNumber < data.size() );
	return data[slotNumber].writeSlotDataToFile(essentials, slotNumber);
}