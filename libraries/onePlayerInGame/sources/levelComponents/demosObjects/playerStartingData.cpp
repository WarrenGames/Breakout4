#include "levelComponents/demosObjects/playerStartingData.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/onePlayerBonusesConsts.h"
#include "consts/rimsConsts.h"
#include "consts/constexprScreen.h"

demos::StartingData::StartingData():
	campaignType{ onePlGame::CampaignMax },
	levelIndex{ 0 },
	skillLevel{ onePlGame::SkillLevelMax },
	playerLives{ 0 },
	racketSize{ onePlGame::RacketMax },
	score{ 0 },
	bonusCoinsNumber{ 0 },
	rimsStartState{ rims::RimNullState },
	squareSizeAtSaving{ SQR_SIZE },
	racketSpeed{ 0 },
	bonusesInBag( onePlGame::BonusMax, 0 )
{
	
}