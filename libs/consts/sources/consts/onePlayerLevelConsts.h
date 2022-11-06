#ifndef ONE_PLAYER_LEVEL_CONSTS_H
#define ONE_PLAYER_LEVEL_CONSTS_H

namespace onePlGame{

enum{ 	CampaignWithShop, // = 0
		CampaignNoShop, 	// = 1
		CampaignMax };		// = 2

constexpr double BallStartingSpeed = 2;
constexpr double RacketStartingSpeed = 5;
constexpr double RacketMaxSpeed = 9;
constexpr unsigned MircroSecondsRefreshTimeRate = 1000 * 1000 / 60;
constexpr int InfoBoardY_Margin = 1;
constexpr unsigned CoinFramesNumber = 25;

enum{ 	SmallRacket, 
		MediumRacket, 
		BigRacket, 
		RacketMax };

constexpr int BallCornerInterval = 4;//For a SQR_SIZE value of 64 it is equal to '11'

enum{ 	InputMoveLeft, 				// = 0
		InputMoveRight, 			// = 1
		InputBallTrace, 			// = 2
		InputLookBag, 				// = 3
		InputSwitch, 				// = 4
		InputMax };					// = 5

enum{ 	LangInputLeft,				// = 0
		LangInputRight, 			// = 1
		LangInputBallTrace, 		// = 2
		LangInputLookBag, 			// = 3
		LangInputSwitch, 			// = 4
		LangInputTitle, 			// = 5
		LangInputPushNewKey, 		// = 6
		LangInputPushNewButton,		// = 7
		LangInputKeybaordRowTitle,	// = 8
		LangInputJoystickRowTitle,	// = 9
		LangInputAxisNum,			// = 10
		LangInputHatNum,			// = 11
		LangInputButtonNum,			// = 12
		LangInputErrorMoveType,	// = 13
		LangInputAxisThreshold,	// = 14
		LangInputCrossX_Move,		// = 15
		LangInputCrossY_Move,		// = 16
		LangInputMouse,				// = 17
		LangInputJoystickInfos,			// = 18
		LangInputMax };				// = 19

enum{	JoystickMoveAxes, 
		JoystickMoveHats, 
		JoystickMoveError};

enum{ 	JoysticButtonBallTrace, 
		JoysticButtonSearchBag, 
		JoysticButtonSwitch, 
		JoysticButtonMax };

enum{ 	CrossDeviceIsMouse,
		CrossDeviceIsJoystick };

constexpr char BackgroundTexturePath[] = "textures/sprites/bricks/bgBrick.png";

enum{ 	SkillLevelEasy, 
		SkillLevelIntermediate, 
		SkillLevelHard, 
		SkillLevelMax };

enum{ 	EpisodeSimple, 
		EpisodeArtic, 
		EpisodeHell, 
		EpisodeMax };

constexpr char ShopRaceLevelListFile[] = "data/levels/1player/shopRaceLevels.cfg";

constexpr char NoShopRaceLevelListFile[] = "data/levels/1player/stdRaceLevels.cfg";

enum{ 	LevelEndNotYet, 
		LevelEndPartially, 
		LevelEndComplete,
		LevelEndSurrender};

constexpr char CommonSoundsFilePath[] = "data/sounds/1playerStdSounds.ini";
constexpr char CommonChannelsFilePath[] = "data/sounds/1playerStdChannels.ini";

enum{	SoundEnlargeRacket,			// = 0
		SoundShrinkRacket,
		SoundSpeedUp,
		SoundSpeedDown,
		SoundAddOneUp,				// = 4
		SoundCantUseBonus,
		SoundRacketWithBallCollision,
		SoundBallWBgCollision,
		SoundBallLost,				// = 8
		SoundQuack,
		SoundRacketWithCoinCol,
		SoundCreateNewCoin,
		SoundImpactWithDamage,		// = 12
		SoundGameStart,
		SoundFireBall,				
		SoundMax };					// = 15

}

#endif //ONE_PLAYER_LEVEL_CONSTS_H