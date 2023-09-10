#ifndef DUELS_BONUS_SLOT_H
#define DUELS_BONUS_SLOT_H

#include <vector>

struct Essentials;

namespace duels{

class BonusesSlot
{
private:
	std::vector< unsigned > bonuses;
	bool isLoadingPerfect;

public:
	explicit BonusesSlot(Essentials& essentials, unsigned slotNumber);
	~BonusesSlot() = default;
	BonusesSlot( const BonusesSlot& ) = default;
	BonusesSlot& operator= ( const BonusesSlot& ) = default;
	BonusesSlot( BonusesSlot&& ) = default;
	BonusesSlot& operator= ( BonusesSlot&& ) = default;
	
	void openFileForLoading(Essentials& essentials, unsigned slotNumber);
	bool writeSlotDataToFile(Essentials& essentials, unsigned slotNumber) const;
	unsigned getBonusValue(unsigned bonusNum) const;
	unsigned& getBonusValue(unsigned bonusNum);
};
	
}

#endif //DUELS_BONUS_SLOT_H