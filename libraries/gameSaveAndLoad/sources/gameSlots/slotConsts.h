#ifndef SLOT_CONSTS_H
#define SLOT_CONSTS_H

#include "consts/constexprScreen.h"

constexpr int SaveSlotSquareWidth = GameScreenWidth / 2 - SQR_SIZE * 2;
constexpr int SaveSlotSquareHeight = SQR_SIZE;

constexpr int SaveSlotLinesNumber = 5;
constexpr int SaveSlotRowNumber = 2;

constexpr std::size_t SlotsNumber = SaveSlotLinesNumber * SaveSlotRowNumber;

constexpr char CampaignInfosString[] = "Campaign and date infos";
constexpr char ScoreAndCoinsString[] = "Score and coins infos";

enum{ 	SaveIdCampaignType,				// = 0
		SaveIdSkillLevel,
		SaveIdPlayerLives,				// = 2
		SaveIdRacketSpeed,
		SaveIdRacketSize,				// = 4
		SaveIdScore,
		SaveIdBonusCoinNumber,			// = 6
		SaveIdRimState,
		SaveIdLevelCursor,				// = 8
		SaveIdBagBonus,
		SaveIdMax 						// = 10
};

enum{	SaveNameFocusingOnSaving,		// = 0
		SaveNameFocusingOnLoading,
		SaveNameCampaignWithShop,			// = 2
		SaveNameCampaignNoShop,
		SaveNameScore,					// = 4
		SaveNameCoinsNumber,
		SaveNameSavingGaveAnError,		// = 6
		SaveNameThisSlotIsFree,
		SaveNameQuitMenu,				// = 8
		SaveNameFocusingGameMax		// = 9
};

#endif //SLOT_CONSTS_H