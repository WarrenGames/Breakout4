#ifndef DUELS_BONUS_SLOT_H
#define DUELS_BONUS_SLOT_H

#include <vector>

struct Essentials;

namespace duels{

class BonusesSlot
{
private:
	bool isLoadingPerfect;
	std::vector< unsigned > bonuses;

public:
	explicit BonusesSlot(Essentials& essentials, unsigned slotNumber);
	~BonusesSlot() = default;
	
	void openFileForLoading(Essentials& essentials, unsigned slotNumber);
	bool writeSlotDataToFile(Essentials& essentials, unsigned slotNumber) const;
	unsigned getBonusValue(unsigned bonusNum) const;
	unsigned& getBonusValue(unsigned bonusNum);
};
	
}

#endif //DUELS_BONUS_SLOT_H