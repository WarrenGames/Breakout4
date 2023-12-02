#include "gameSlots/gameSlotData.h"
#include "crossLevel/playerData.h"
#include "texts/textLoader.h"
#include "time/dateAndTime.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/onePlayerBonusesConsts.h"
#include "consts/constPaths.h"
#include "gameSlots/slotConsts.h"

GameSlotData::GameSlotData():
	isAnActiveSave{false},
	campaignType{onePlGame::CampaignMax},
	skillLevel{onePlGame::SkillLevelMax},
	playerLives{0},
	racketSpeed{0},
	racketSize{0},
	score{0},
	bonusCoinNumber{0},
	rimsStartState{-1},
	levelCursor{0},
	bonusesInBag(onePlGame::BonusMax, 0),
	campaignAndDateInfos{"empty string"},
	scoreAndCoinsInfos{"empty string"}
{

}

GameSlotData& GameSlotData::operator =( const PlayerData& playerData)
{
	campaignType = playerData.campaignType;
	skillLevel = playerData.skillLevel;
	playerLives = playerData.playerLives;
	racketSpeed = playerData.racketSpeed;
	racketSize = playerData.racketSize;
	score = playerData.score;
	bonusCoinNumber = playerData.bonusCoinsNumber;
	rimsStartState = playerData.rimsStartState;
	levelCursor = playerData.levelIndex;
	bonusesInBag = playerData.bonusesInBag;
	return *this;
}

void GameSlotData::setCampaign(const TextsBlocks& localeTexts)
{
	switch( campaignType )
	{
		case onePlGame::CampaignWithShop:
			campaignAndDateInfos = localeTexts[SaveNameCampaignWithShop] + " ";
			break;
		case onePlGame::CampaignNoShop:
			campaignAndDateInfos = localeTexts[SaveNameCampaignNoShop] + " ";
			break;
		default:
			campaignAndDateInfos = "Campaign error ! ";
			break;
	}
}

void GameSlotData::addDateToString()
{
	campaignAndDateInfos += returnCurrentTimeAndDate();
}

void GameSlotData::setScoreAndCoins(const TextsBlocks& localeTexts)
{

	scoreAndCoinsInfos = localeTexts[SaveNameScore] + std::to_string( score ) + " -- " + localeTexts[SaveNameCoinsNumber] + std::to_string(bonusCoinNumber);
}