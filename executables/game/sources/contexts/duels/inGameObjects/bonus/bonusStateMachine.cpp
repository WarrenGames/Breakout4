#include "contexts/duels/inGameObjects/bonus/bonusStateMachine.h"
#include "contexts/duels/duelsConstexpr.h"

BonusState::BonusState():
	state{ duels::BonusStateNoBonus },
	showVignette{ false },
	canRequestBonus{ false },
	bonusStateDelay{},
	intervalleDelay{}
{
	
}

void BonusState::startGenerateBonus()
{
	state = duels::BonusStateRandomGeneration;
	showVignette = true;
	bonusStateDelay.joinTimePoints();
	intervalleDelay.joinTimePoints();
}

void BonusState::update(unsigned& bonusType)
{
	switch( state )
	{
		case duels::BonusStateNoBonus:
			break;
		case duels::BonusStateRandomGeneration:
			randGenUpdate();
			loopBonusTypes(bonusType);
			break;
		case duels::BonusStateBlink:
			blinkUpdate();
			makeVignetteBlink();
			break;
		case duels::BonusStateBonusReady:
			break;
	}
}

void BonusState::randGenUpdate()
{
	if( bonusStateDelay.hasTimeElapsed(  std::chrono::milliseconds{duels::RandomGenerationMsTime} ) )
	{
		state = duels::BonusStateBlink;
		bonusStateDelay.joinTimePoints();
		canRequestBonus = true;
	}
}

void BonusState::loopBonusTypes(unsigned& bonusType)
{
	if( intervalleDelay.hasTimeElapsed(  std::chrono::milliseconds{duels::BonusFrameMsTime} ) )
	{
		if( bonusType + 1 < duels::DuelBonusMax )
			bonusType++;
		else{
			bonusType = 0;
		}
		intervalleDelay.joinTimePoints();
	}
}

void BonusState::blinkUpdate()
{
	if( bonusStateDelay.hasTimeElapsed(  std::chrono::milliseconds{duels::BonusBlinkMsTime} ) )
	{
		state = duels::BonusStateBonusReady;
		showVignette = true;
		bonusStateDelay.joinTimePoints();
	}
}

void BonusState::makeVignetteBlink()
{
	if( intervalleDelay.hasTimeElapsed(  std::chrono::milliseconds{duels::BonusFrameMsTime} ) )
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
	state = duels::BonusStateNoBonus;
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