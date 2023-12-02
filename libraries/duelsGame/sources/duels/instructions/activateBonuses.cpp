#include "duels/instructions/activateBonuses.h"
#include "duels/inGameObjects/balls/ballsMain.h"
#include "duels/inGameObjects/bonus/bonusGenerator.h"
#include "duels/inGameObjects/rackets/racket.h"
#include "duels/inGameObjects/playerScore/playerScoreDrawing.h"
#include "texturing/verticalGradientTexture.h"
#include "soundSystem/soundsPlayer.h"
#include "consts/duelsSounds.h"
#include <cassert>

unsigned duels::getOpponent(unsigned playerNum)
{
	switch( playerNum )
	{
		case duels::PlayerBlue:
			return duels::PlayerRed;
			break;
		case duels::PlayerRed:
			return duels::PlayerBlue;
			break;
		default:
			assert( false && "Wrong player num value for opponent function." );
			return 2;
			break;
	}
}

void duels::improveSizeSelf(BonusGenerator& bonus, PlayerRacket& playerRacket, const SoundPlayer& soundPlayer)
{
	if( playerRacket.canBeEnlarged() )
	{
		soundPlayer.playSoundOnGroup(duels::SoundEnlargeRacket, duels::GroupTagBonusActivation);
		playerRacket.enlarge();
		bonus.consumeBonus();
	}
}

void duels::shrinkOpponent(BonusGenerator& bonus, PlayerRacket& opponentRacket, const SoundPlayer& soundPlayer)
{
	if( opponentRacket.canBeShrinked() )
	{
		soundPlayer.playSoundOnGroup(duels::SoundShrinkRacket, duels::GroupTagBonusActivation);
		opponentRacket.shrink();
		bonus.consumeBonus();
	}
}

void duels::freezeOpponent(BonusGenerator& bonus, PlayerRacket& opponentRacket, const SoundPlayer& soundPlayer)
{
	if( opponentRacket.canBeFreeze() )
	{
		soundPlayer.playSoundOnGroup(duels::SoundFreeze, duels::GroupTagBonusActivation);
		opponentRacket.freezeRacket();
		bonus.consumeBonus();
	}
}

void duels::stealOpponentBonus(BonusGenerator& thiefBonus, BonusGenerator& opponentBonus, const SoundPlayer& soundPlayer)
{
	if( opponentBonus.getBonusType() < duels::DuelBonusMax )
	{
		soundPlayer.playSoundOnGroup(duels::SoundStealBonus, duels::GroupTagBonusActivation);
		thiefBonus.stealOpponentBonus(opponentBonus);
	}
}

void duels::accelerateSelf(BonusGenerator& bonus, PlayerRacket& racket, sdl2::VerticalGradient& speedGradient, const SoundPlayer& soundPlayer)
{
	if( racket.canSpeedUp() )
	{
		soundPlayer.playSoundOnGroup(duels::SoundSpeedUp, duels::GroupTagBonusActivation);
		racket.changeSpeed(1);
		bonus.consumeBonus();
		speedGradient.setNewCounterValue(static_cast<int>(racket.getSpeed()-duels::RacketMinimumSpeed) );
	}
}

void duels::slowDownOpponent(BonusGenerator& bonus, PlayerRacket& opponentRacket, sdl2::VerticalGradient& speedGradient, const SoundPlayer& soundPlayer)
{
	if( opponentRacket.canBeSlowedDown() )
	{
		soundPlayer.playSoundOnGroup(duels::SoundSpeedDown, duels::GroupTagBonusActivation);
		opponentRacket.changeSpeed(-1);
		bonus.consumeBonus();
		speedGradient.setNewCounterValue(static_cast<int>(opponentRacket.getSpeed() - duels::RacketMinimumSpeed) );
	}
}

void duels::addBall(BonusGenerator& bonus, BallsThings& balls, duels::LevelOptions& levelOptions)
{
	if( balls.getEffectiveBallsCount() < levelOptions.ballsMax )
	{
		balls.setCanCreateBall();
		bonus.consumeBonus();
	}
}

void duels::activeZoneSpecificBonus(BonusGenerator& bonus, bool& zoneSpecificFlag, bool canActivateSpecialBonus)
{
	if( canActivateSpecialBonus )
	{
		zoneSpecificFlag = true;
		bonus.consumeBonus();
	}
}

void duels::negativeBonus(BonusGenerator& bonus, int& playerScore, const SoundPlayer& soundPlayer, duels::ScoreDraw& scoreDrawing)
{
	soundPlayer.playSoundOnGroup(duels::SoundNegativeBonus, duels::GroupTagBonusActivation);
	playerScore--;
	bonus.consumeBonus();
	scoreDrawing.setUpdateFlag();
}