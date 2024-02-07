#ifndef BONUS_PICKER_H
#define BONUS_PICKER_H

#include <vector>
#include <random>

class BonusPicker
{
private:
	std::vector< unsigned > bonusPack;
	std::vector< unsigned >::const_iterator nextBonusIt;
	std::mt19937 mersenne;
	unsigned tempBonus;
	
public:
	explicit BonusPicker(const std::vector<unsigned>& options);
	~BonusPicker() = default;
	BonusPicker( const BonusPicker& ) = delete;
	BonusPicker& operator= ( const BonusPicker& ) = delete;
	BonusPicker( BonusPicker&& ) = default;
	BonusPicker& operator= ( BonusPicker&& ) = default;

	unsigned pickNextBonus();
	void setIteratorToBegin();

private:
	void fillBonusPack(const std::vector<unsigned>& options);
	void shuffleArray();
	
};

#endif //BONUS_PICKER_H