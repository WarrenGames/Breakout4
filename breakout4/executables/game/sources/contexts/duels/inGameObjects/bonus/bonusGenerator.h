#ifndef DUELS_BONUS_GENERATOR_H
#define DUELS_BONUS_GENERATOR_H

#include "contexts/duels/inGameObjects/bonus/bonusPicker.h"
#include "contexts/duels/inGameObjects/bonus/bonusDrawer.h"
#include "contexts/duels/inGameObjects/bonus/bonusStateMachine.h"
#include <vector>

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }

class BonusGenerator
{
private:
	BonusPicker bonusPicker;
	BonusState bonusState;
	BonusDrawer bonusDrawer;
	unsigned bonusType;

public:
	explicit BonusGenerator(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned playerType, const std::vector<unsigned>& options);
	~BonusGenerator() = default;
	BonusGenerator( const BonusGenerator& ) = delete;
	BonusGenerator& operator= ( const BonusGenerator& ) = delete;
	BonusGenerator( BonusGenerator&& ) = default;
	BonusGenerator& operator= ( BonusGenerator&& ) = default;
	
	bool wasLoadingPerfect() const;
	
	void playerGetBonusCoin();
	void update();
	unsigned getBonusType() const;
	void drawVignetteIfAny(sdl2::RendererWindow& rndWnd) const;
	void consumeBonus();
	void stealOpponentBonus(BonusGenerator& opponent);
	bool isAnyBonusReady() const;
	
private:
	void requestBonus();
};

#endif //DUELS_BONUS_GENERATOR_H