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
	gameType{onePlGame::CAMPAIGN_MAX},
	skillLevel{onePlGame::SKILL_LEVEL_MAX},
	playerLives{0},
	racketSpeed{0},
	racketSize{0},
	score{0},
	bonusCoinNumber{0},
	rimsStartState{-1},
	levelCursor{0},
	bonusesInBag(onePlGame::BONUS_MAX, 0),
	campaignAndDateInfos{"empty string"},
	scoreAndCoinsInfos{"empty string"}
{

}

GameSlotData& GameSlotData::operator =( const PlayerData& playerData)
{
	gameType = playerData.gameType;
	skillLevel = playerData.skillLevel;
	playerLives = playerData.playerLives;
	racketSpeed = playerData.racketSpeed;
	racketSize = playerData.racketSize;
	score = playerData.score;
	bonusCoinNumber = playerData.bonusCoinsNumber;
	rimsStartState = playerData.rimsStartState;
	levelCursor = playerData.levelCursor;
	bonusesInBag = playerData.bonusesInBag;
	return *this;
}

void GameSlotData::setCampaign(const TextsBlocks& localeTexts)
{
	switch( gameType )
	{
		case onePlGame::CAMPAIGN_WITH_SHOP:
			campaignAndDateInfos = localeTexts[SAVE_NAME_CAMPAIGN_WITH_SHOP] + " ";
			break;
		case onePlGame::CAMPAIGN_NO_SHOP:
			campaignAndDateInfos = localeTexts[SAVE_NAME_CAMPAIGN_NO_SHOP] + " ";
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

	scoreAndCoinsInfos = localeTexts[SAVE_NAME_SCORE] + std::to_string( score ) + " -- " + localeTexts[SAVE_NAME_COINS_NUMBER] + std::to_string(bonusCoinNumber);
}