#ifndef CONSTS_ONE_PLAYER_SOUNDS_CONSTEXPR_H
#define CONSTS_ONE_PLAYER_SOUNDS_CONSTEXPR_H

namespace onePlGame{

	constexpr char CommonSoundsFilePath[] = "data/sounds/1playerStdSounds.ini";
	constexpr char CommonChannelsFilePath[] = "data/sounds/1playerStdChannels.ini";

	enum : unsigned{
		SoundEnlargeRacket,			// = 0
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
		SoundMax					// = 15
	};
	
	enum : unsigned{
		GroupTagBonusActivation,			// = 0
		GroupTagEnemy,						// = 1
		GroupTagRacketWithBallCollision,	// = 2
		GroupTagCollisionRacketWithCoin,	// = 3
		GroupTagNewCoin,					// = 4
		GroupTagGameStart,					// = 5
		GroupTagMax							// = 6
	};

	//constexpr unsigned SoundGroupTagMax = 6;
}

#endif //CONSTS_ONE_PLAYER_SOUNDS_CONSTEXPR_H