#ifndef CONSTS_SINGLE_PLAYER_DEMOS_CONSTS_H
#define CONSTS_SINGLE_PLAYER_DEMOS_CONSTS_H

namespace onePlGame{

namespace demosFileIndex{
	enum{
		CampaignType,				// = 0
		SkillLevel,					
		PlayerLives, 				// = 2
		RacketSize,   				
		Score,						// = 4
		RacketSpeed,
		BonusCoinNumber, 			// = 6
		RimStartState,
		GivenBonusInBag, 			// = 8
		SquareSizeAtSaving,
		ActionEvent,				// = 10
		QuitLevelEvent,
		TraceCrossPosition,			// = 12
		RacketPosition,				
		BallPosition,				// = 14
		BrickDestruction,
		CommonSoundEvent,			// = 16
		PinguinsPosition,			
		PinguinsDirection,			// = 18
		PinguinsCreateAndDestroy,	
		PinguinQuackSoundEvent,		// = 20
		MatrixSize,					
		MatrixElement,				// = 22
		IndexMax					// = 23
	};
}

}
#endif //CONSTS_SINGLE_PLAYER_DEMOS_CONSTS_H