#ifndef CONSTS_SINGLE_PLAYER_DEMOS_CONSTS_H
#define CONSTS_SINGLE_PLAYER_DEMOS_CONSTS_H

namespace onePlGame{

namespace demosFileIndex{
	enum{
		CampaignType,				// = 0
		LevelIndex,
		SkillLevel,					// = 2
		PlayerLives, 
		RacketSize,   				// = 4
		Score,
		RacketSpeed,				// = 6
		BonusCoinNumber, 
		RimStartState, 				// = 8
		GivenBonusInBag, 
		SquareSizeAtSaving,			// = 10
		ActionEvent,
		QuitLevelEvent,				// = 12
		TraceCrossPosition,
		RacketPosition,				// = 14
		BallPosition,
		BrickDestruction,			// = 16
		CommonSoundEvent,
		PinguinsPosition,			// = 18
		PinguinsDirection,
		PinguinsCreateAndDestroy,	// = 20
		PinguinQuackSoundEvent,
		IndexMax					// = 22
	};
}

}
#endif //CONSTS_SINGLE_PLAYER_DEMOS_CONSTS_H