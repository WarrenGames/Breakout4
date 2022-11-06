#ifndef DUELS_CONSTEXPRESSION_H
#define DUELS_CONSTEXPRESSION_H

#include "consts/constexprScreen.h"
#include "SDL_rect.h"
#include <cstddef>

namespace duels{

constexpr std::size_t BallMaxNumber = 4;

constexpr std::size_t CoinMaxNumber = 4;

constexpr std::size_t CoinFramesNumber = 25;

constexpr int SizeDecalCollideBox = 2;

constexpr int CoinLooseCollideInt = 4;
constexpr int CoinTextureSize = SQR_SIZE - CoinLooseCollideInt * 2;

constexpr int BallCornerInterval = 11;
constexpr int BallTextureSize = SQR_SIZE / 2;

//BonusState
enum{ BonusStateNoBonus, BonusStateRandomGeneration, BonusStateBlink, BonusStateBonusReady };
constexpr unsigned RandomGenerationMsTime = 3000;
constexpr unsigned BonusBlinkMsTime = 2000;
constexpr unsigned BonusFrameMsTime = 100;


//Bonus types
enum{	BonusImproveSizeSelf, // = 0
		BonusShrinkOpponentSize,
		BonusFreezeOpponent,
		BonusStealOpponentBonus,
		BonusSpeedUpSelf,		// = 4
		BonusSlowDownOpponent,
		BonusAddBall,
		BonusZoneSpecific,
		BonusNegativeBonus,	// = 8
		DuelBonusMax				// = 9
};

enum{PlayerBlue, PlayerRed, PlayerMax};

enum{ SmallRacket, MediumRacket, BigRacket, RacketMax };

constexpr int RacketHeightSize = 10;
constexpr double RacketMinimumSpeed = 3;
constexpr double RacketMaxSpeed = 8;
constexpr double RacketDefaultSpeed = 5;
constexpr int RacketSlopeInterval = 9;

constexpr int SpeedGradientWidth = SQR_SIZE / 4;
constexpr int SpeedGradientHeight = SQR_SIZE / 2;

//The SDL_Rect for the vertical gradient representing the speed of the players rackets
constexpr SDL_Rect BluePlayerSpeedGradientRect = { GameScreenWidth - SQR_SIZE / 2 - SpeedGradientWidth / 2, GameScreenHeight - SQR_SIZE / 2 - SpeedGradientHeight / 2, SpeedGradientWidth, SpeedGradientHeight};
constexpr SDL_Rect RedPlayerSpeedGradientRect = { GameScreenWidth - SQR_SIZE / 2 - SpeedGradientWidth / 2, SQR_SIZE / 2 - SpeedGradientHeight / 2, SpeedGradientWidth, SpeedGradientHeight};

enum{ ZoneStandard, ZoneHalloween, ZoneStrings, ZoneMax };

//The textures index for the levels grids
enum{	GridId_Empty, 				// = 0
		GridId_BlueRim,
		GridId_RedRim,			// = 2
		GridId_X4_Brick, 
		GridId_Tough1, 		// = 4
		GridId_Tough2,
		GridId_Tough3, 		// = 6
		GridId_PotTexture,
		GridId_PotBlock, 		// = 8
		GridId_Button,
		GridId_Max				// = 10
};

enum{	SoundEnlargeRacket,					// = 0
		SoundShrinkRacket, 
		SoundNegativeBonus, 
		SoundSpeedUp, 
		SoundSpeedDown,						// = 4
		SoundStealBonus, 
		SoundFreeze, 
		SoundCollisionRacketWithBall, 
		SoundCollisionCoinWithRacket,		// = 8
		SoundCollisionBallWithBackground, 
		SoundNewCoin
};

constexpr char CommonSoundsFilePath[] = "data/sounds/duelsCommonSounds.ini";
constexpr char CommonChannelsFilePath[] = "data/sounds/duelsCommonChannels.ini";

constexpr char HalloweenSoundsFilePath[] = "data/sounds/duelsHalloweenSounds.ini";
constexpr char HalloweenChannelsFilePath[] = "data/sounds/duelsHalloweenChannels.ini";

enum{ SoundHalloweenOrgan, SoundPotBubbles};

enum{	MatchConfigTextConfig, 
		MatchConfigTextPlayerInput, 
		MatchConfigTextZoneChoice, 
		MatchConfigTextRunZone, 
		MatchConfigTextBluePlayer, 
		MatchConfigTextRedPlayer, 
		MatchConfigTextAchieve1,
		MatchConfigTextAchieve2,
		MatchConfigTextMax
};

constexpr char BlueRimTexturePath[] = "textures/sprites/bricks/blueRim.png";
constexpr char RedRimTexturePath[] = "textures/sprites/bricks/purpleRim.png";

}

#endif //DUELS_CONSTEXPRESSION_H