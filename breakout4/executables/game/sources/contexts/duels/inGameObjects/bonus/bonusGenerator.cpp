#include "contexts/duels/inGameObjects/bonus/bonusGenerator.h"
#include "texturing/rendererWindow.h"
#include "contexts/duels/duelsConstexpr.h"
#include <cassert>

BonusGenerator::BonusGenerator(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned playerType, const std::vector<unsigned>& options):
	bonusPicker{options},
	bonusState{},
	bonusDrawer{logs, rndWnd, playerType},
	bonusType{ duels::DB_MAX }
{
	assert( options.size() == duels::DB_MAX );
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
	if( bonusState.isVignetteToBeShown() && bonusType < duels::DB_MAX )
	{
		bonusDrawer.drawBonus(rndWnd, bonusType);
	}
}

void BonusGenerator::consumeBonus()
{
	bonusState.consumeBonus();
	bonusType = duels::DB_MAX;
}

void BonusGenerator::stealOpponentBonus(BonusGenerator& opponent)
{
	bonusType = opponent.getBonusType();
	opponent.consumeBonus();
}

bool BonusGenerator::isAnyBonusReady() const
{
	return bonusState.getState() == duels::BST_HAVEBONUS;
}

void BonusGenerator::requestBonus()
{
	if( bonusState.canRequestBonusFromPicker() )
	{
		bonusType = bonusPicker.pickNextBonus();
	}
}