#include "contexts/duels/instructions/activateBonuses.h"
#include "contexts/duels/inGameObjects/balls/ballsMain.h"
#include "contexts/duels/inGameObjects/bonus/bonusGenerator.h"
#include "contexts/duels/inGameObjects/rackets/racket.h"
#include "contexts/duels/inGameObjects/playerScore/playerScoreDrawing.h"
#include "texturing/verticalGradientTexture.h"
#include "generic/sounds/soundHandler.h"
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

void duels::improveSizeSelf(BonusGenerator& bonus, PlayerRacket& playerRacket, const SoundHandler& sound)
{
	if( playerRacket.canBeEnlarged() )
	{
		sound.playSound(duels::SoundEnlargeRacket);
		playerRacket.enlarge();
		bonus.consumeBonus();
	}
}

void duels::shrinkOpponent(BonusGenerator& bonus, PlayerRacket& opponentRacket, const SoundHandler& sound)
{
	if( opponentRacket.canBeShrinked() )
	{
		sound.playSound(duels::SoundShrinkRacket);
		opponentRacket.shrink();
		bonus.consumeBonus();
	}
}

void duels::freezeOpponent(BonusGenerator& bonus, PlayerRacket& opponentRacket, const SoundHandler& sound)
{
	if( opponentRacket.canBeFreeze() )
	{
		sound.playSound(duels::SoundFreeze);
		opponentRacket.freezeRacket();
		bonus.consumeBonus();
	}
}

void duels::stealOpponentBonus(BonusGenerator& thiefBonus, BonusGenerator& opponentBonus, const SoundHandler& sound)
{
	if( opponentBonus.getBonusType() < duels::DuelBonusMax )
	{
		sound.playSound(duels::SoundStealBonus);
		thiefBonus.stealOpponentBonus(opponentBonus);
	}
}

void duels::accelerateSelf(BonusGenerator& bonus, PlayerRacket& racket, sdl2::VerticalGradient& speedGradient, const SoundHandler& sound)
{
	if( racket.canSpeedUp() )
	{
		sound.playSound(duels::SoundSpeedUp);
		racket.changeSpeed(1);
		bonus.consumeBonus();
		speedGradient.setNewCounterValue(static_cast<int>(racket.getSpeed()-duels::RacketMinimumSpeed) );
	}
}

void duels::slowDownOpponent(BonusGenerator& bonus, PlayerRacket& opponentRacket, sdl2::VerticalGradient& speedGradient, const SoundHandler& sound)
{
	if( opponentRacket.canBeSlowedDown() )
	{
		sound.playSound(duels::SoundSpeedDown);
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

void duels::negativeBonus(BonusGenerator& bonus, int& playerScore, const SoundHandler& sound, duels::ScoreDraw& scoreDrawing)
{
	sound.playSound(duels::SoundNegativeBonus);
	playerScore--;
	bonus.consumeBonus();
	scoreDrawing.setUpdateFlag();
}