#include "contexts/duels/inGameObjects/bonus/bonusStateMachine.h"
#include "contexts/duels/duelsConstexpr.h"

BonusState::BonusState():
	state{ duels::BST_NOBONUS },
	showVignette{ false },
	canRequestBonus{ false },
	bonusStateDelay{},
	intervalleDelay{}
{
	
}

void BonusState::startGenerateBonus()
{
	state = duels::BST_RANDGEN;
	showVignette = true;
	bonusStateDelay.joinTimePoints();
	intervalleDelay.joinTimePoints();
}

void BonusState::update(unsigned& bonusType)
{
	switch( state )
	{
		case duels::BST_NOBONUS:
			break;
		case duels::BST_RANDGEN:
			randGenUpdate();
			loopBonusTypes(bonusType);
			break;
		case duels::BST_BLINK:
			blinkUpdate();
			makeVignetteBlink();
			break;
		case duels::BST_HAVEBONUS:
			break;
	}
}

void BonusState::randGenUpdate()
{
	if( bonusStateDelay.hasTimeElapsed(  std::chrono::milliseconds{duels::RANDGEN_TIME} ) )
	{
		state = duels::BST_BLINK;
		bonusStateDelay.joinTimePoints();
		canRequestBonus = true;
	}
}

void BonusState::loopBonusTypes(unsigned& bonusType)
{
	if( intervalleDelay.hasTimeElapsed(  std::chrono::milliseconds{duels::FRAME_TIME} ) )
	{
		if( bonusType + 1 < duels::DB_MAX )
			bonusType++;
		else{
			bonusType = 0;
		}
		intervalleDelay.joinTimePoints();
	}
}

void BonusState::blinkUpdate()
{
	if( bonusStateDelay.hasTimeElapsed(  std::chrono::milliseconds{duels::BLINK_TIME} ) )
	{
		state = duels::BST_HAVEBONUS;
		showVignette = true;
		bonusStateDelay.joinTimePoints();
	}
}

void BonusState::makeVignetteBlink()
{
	if( intervalleDelay.hasTimeElapsed(  std::chrono::milliseconds{duels::FRAME_TIME} ) )
	{
		showVignette = !showVignette;
		intervalleDelay.joinTimePoints();
	}
}

unsigned BonusState::getState() const
{
	return state;
}

bool BonusState::isVignetteToBeShown() const
{
	return showVignette;
}

void BonusState::consumeBonus()
{
	state = duels::BST_NOBONUS;
}

bool BonusState::canRequestBonusFromPicker()
{
	if( canRequestBonus )
	{
		canRequestBonus = false;
		return true;
	}
	else{
		return false;
	}
}