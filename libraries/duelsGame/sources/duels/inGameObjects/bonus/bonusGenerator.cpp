#include "duels/inGameObjects/bonus/bonusGenerator.h"
#include "texturing/rendererWindow.h"
#include "consts/duelsConstexpr.h"
#include <cassert>

BonusGenerator::BonusGenerator(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned playerType, const std::vector<unsigned>& options):
	bonusPicker{options},
	bonusState{},
	bonusDrawer{logs, rndWnd, playerType},
	bonusType{ duels::DuelBonusMax }
{
	assert( options.size() == duels::DuelBonusMax );
}

bool BonusGenerator::wasLoadingPerfect() const
{
	return bonusDrawer.wasLoadingPerfect();
}

void BonusGenerator::playerGetBonusCoin()
{
	bonusState.startGenerateBonus();
}

void BonusGenerator::update()
{
	bonusState.update(bonusType);	
	requestBonus();
}

unsigned BonusGenerator::getBonusType() const
{
	return bonusType;
}

void BonusGenerator::drawVignetteIfAny(sdl2::RendererWindow& rndWnd) const
{
	if( bonusState.isVignetteToBeShown() && bonusType < duels::DuelBonusMax )
	{
		bonusDrawer.drawBonus(rndWnd, bonusType);
	}
}

void BonusGenerator::consumeBonus()
{
	bonusState.consumeBonus();
	bonusType = duels::DuelBonusMax;
}

void BonusGenerator::stealOpponentBonus(BonusGenerator& opponent)
{
	bonusType = opponent.getBonusType();
	opponent.consumeBonus();
}

bool BonusGenerator::isAnyBonusReady() const
{
	return bonusState.getState() == duels::BonusStateBonusReady;
}

void BonusGenerator::requestBonus()
{
	if( bonusState.canRequestBonusFromPicker() )
	{
		bonusType = bonusPicker.pickNextBonus();
	}
}