#ifndef BONUS_STATE_MACHINE_H
#define BONUS_STATE_MACHINE_H

#include "time/accurateTime.h"

class BonusState
{
private:
	unsigned state;
	bool showVignette;
	bool canRequestBonus;
	AccurateTimeDelay bonusStateDelay;
	AccurateTimeDelay intervalleDelay;

public:
	BonusState();
	~BonusState() = default;
	BonusState( const BonusState& ) = delete;
	BonusState& operator= ( const BonusState& ) = delete;
	BonusState( BonusState&& ) = default;
	BonusState& operator= ( BonusState&& ) = default;
	
	void startGenerateBonus();
	void update(unsigned& bonusType);
	
private:
	void randGenUpdate();
	
	void loopBonusTypes(unsigned& bonusType);
	
	void blinkUpdate();
	void makeVignetteBlink();

public:
	unsigned getState() const;
	
	bool isVignetteToBeShown() const;
	void consumeBonus();
	bool canRequestBonusFromPicker();
};

#endif //BONUS_STATE_MACHINE_H