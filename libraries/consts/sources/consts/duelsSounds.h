#ifndef CONSTS_PROJ_DUELS_SOUNDS_H
#define CONSTS_PROJ_DUELS_SOUNDS_H

namespace duels{

enum : unsigned{
		SoundEnlargeRacket,					// = 0
		SoundShrinkRacket, 
		SoundNegativeBonus, 				// = 2
		SoundSpeedUp, 
		SoundSpeedDown,						// = 4
		SoundStealBonus, 
		SoundFreeze, 						// = 6
		SoundCollisionRacketWithBall, 
		SoundCollisionCoinWithRacket,		// = 8
		SoundCollisionBallWithBackground, 
		SoundNewCoin,						// = 10
		SoundStandardMax					// = 11
};

constexpr char CommonSoundsFilePath[] = "data/sounds/duelsCommonSounds.ini";
constexpr char CommonChannelsFilePath[] = "data/sounds/duelsCommonChannels.ini";

constexpr char HalloweenSoundsFilePath[] = "data/sounds/duelsHalloweenSounds.ini";
constexpr char HalloweenChannelsFilePath[] = "data/sounds/duelsHalloweenChannels.ini";

enum : unsigned{
	SoundHalloweenOrgan = 11,
	SoundPotBubbles,
	SoundHalloweenMax // = 13
};

//constexpr unsigned GroupTagNumberMax = 16;

enum : unsigned{
	GroupTagBonusActivation = 0,
	GroupTagBallCollision = 2,
	GroupTagRacketWithCoinCollision = 3,
	GroupTagNewCoinSpawned,					// = 4
	GroupTagZoneSpecific,					// = 5
	GroupTagMax 							// = 6
};

}

#endif //CONSTS_PROJ_DUELS_SOUNDS_H