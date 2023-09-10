#ifndef INTERFACE_CONSTS_H
#define INTERFACE_CONSTS_H

constexpr int WindowWidth = 1024;
constexpr int WindowHeight = 768;

constexpr int LogWindowWidth = 1024;
constexpr int LogWindowHeight = 256;

constexpr int GuiLeftMargin = 32;
constexpr int GuiRightMargin = 320;

constexpr int TextCtrlWidth = 128;
constexpr int TextCtrlHeight = 24;
constexpr int TextCtrlBigWidth = 384;

constexpr int ColumnsNumber = 3;
constexpr int ColumnWidth = 320;
constexpr int BonusesRightMargin = 160;
constexpr int BonusesLeftMargin = 32;

constexpr int HeaderRightMargin = 240;
constexpr int HeaderLeftMargin = 32;

enum{ 	IndexCampaignType,		// = 0
		IndexLevelCursor,
		IndexSkillLevel,		// = 2
		IndexPlayerLives,
		IndexRacketSpeed,		// = 4
		IndexRacketSize,
		IndexScore,				// = 6
		IndexBonusCoinNumber,
		IndexRimState,			// = 8
		IndexMax				// = 9
};

enum{ 
	HeaderCampaignAndDate,
	HeaderScoreAndCoin,
	HeaderMax
};

constexpr char FrameTitle[] = "Saves editor";

constexpr char SavesEditorDataPath[] = "data/savesEditor/";

#endif //INTERFACE_CONSTS_H