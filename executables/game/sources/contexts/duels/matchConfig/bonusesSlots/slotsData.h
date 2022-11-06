#ifndef DUELS_WHOLE_SLOTS_DATA_H
#define DUELS_WHOLE_SLOTS_DATA_H

#include "contexts/duels/matchConfig/bonusesSlots/bonusSlot.h"

namespace duels{

class SlotsData
{
private:
	bool isLoadingPerfect;
	std::vector< duels::BonusesSlot > data;

public:
	explicit SlotsData(Essentials& essentials);
	~SlotsData() = default;
	SlotsData( const SlotsData& ) = delete;
	SlotsData& operator= ( const SlotsData& ) = delete;
	SlotsData( SlotsData&& ) = default;
	SlotsData& operator= ( SlotsData&& ) = default;
	
	operator bool() const;
	unsigned getValue(unsigned slotNumber, unsigned bonusNumber) const;
	unsigned& getValue(unsigned slotNumber, unsigned bonusNumber);
	std::size_t getSlotsNumber() const;
	bool writeBonusesData(Essentials& essentials, unsigned slotNumber) const;
};

}

#endif //DUELS_WHOLE_SLOTS_DATA_H