#include "data/gameSlots.h"
#include "gameSlots/slotConsts.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/rimsConsts.h"
#include <stdexcept>

void GameSaveSlots::checkSlot() const
{
	checkSkillLevelValue();
	checkCampaignType();
	checkRacketSize();
	checkRimsState();
}

void GameSaveSlots::checkSkillLevelValue() const
{
	if( ! ( slot.skillLevel >= onePlGame::SkillLevelEasy && slot.skillLevel < onePlGame::SkillLevelMax ) )
	{
		throwExceptionIfAnyErrorHappen("skill level", onePlGame::SkillLevelEasy, onePlGame::SkillLevelMax);
	}
}

void GameSaveSlots::checkCampaignType() const
{
	if( ! ( slot.campaignType >= onePlGame::CampaignWithShop && slot.campaignType < onePlGame::CampaignMax ) )
	{
		throwExceptionIfAnyErrorHappen("campaign type value", onePlGame::CampaignWithShop, onePlGame::CampaignMax);
	}
}

void GameSaveSlots::checkRacketSize() const
{
	if( ! ( slot.racketSize >= onePlGame::SmallRacket && slot.racketSize < onePlGame::RacketMax ) )
	{
		throwExceptionIfAnyErrorHappen("racket size", onePlGame::SmallRacket, onePlGame::RacketMax);
	}
}

void GameSaveSlots::checkRimsState() const
{
	if( ! ( slot.rimsStartState >= rims::RimNullState && slot.rimsStartState < rims::RemoveMax ) )
	{
		throwExceptionIfAnyErrorHappen("rims state", rims::RimNullState, rims::RemoveMax);
	}
}

void GameSaveSlots::throwExceptionIfAnyErrorHappen(const std::string& wrongAttributeType, int startValue, int endExcludedValue) const
{
	throw std::runtime_error{wrongAttributeType + " is not between [" + std::to_string( startValue ) + " and " + std::to_string(endExcludedValue) + "[ (excluded)."};
}