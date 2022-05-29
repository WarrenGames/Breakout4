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
		case duels::PLAYER_BLUE:
			return duels::PLAYER_RED;
			break;
		case duels::PLAYER_RED:
			return duels::PLAYER_BLUE;
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
		sound.playSound(duels::SND_ENLARGE_RACKET);
		playerRacket.enlarge();
		bonus.consumeBonus();
	}
}

void duels::shrinkOpponent(BonusGenerator& bonus, PlayerRacket& opponentRacket, const SoundHandler& sound)
{
	if( opponentRacket.canBeShrinked() )
	{
		sound.playSound(duels::SND_SHRINK_RACKET);
		opponentRacket.shrink();
		bonus.consumeBonus();
	}
}

void duels::freezeOpponent(BonusGenerator& bonus, PlayerRacket& opponentRacket, const SoundHandler& sound)
{
	if( opponentRacket.canBeFreeze() )
	{
		sound.playSound(duels::SND_FREEZE);
		opponentRacket.freezeRacket();
		bonus.consumeBonus();
	}
}

void duels::stealOpponentBonus(BonusGenerator& thiefBonus, BonusGenerator& opponentBonus, const SoundHandler& sound)
{
	if( opponentBonus.getBonusType() < duels::DB_MAX )
	{
		sound.playSound(duels::SND_STEAL_BON);
		thiefBonus.stealOpponentBonus(opponentBonus);
	}
}

void duels::accelerateSelf(BonusGenerator& bonus, PlayerRacket& racket, sdl2::VerticalGradient& speedGradient, const SoundHandler& sound)
{
	if( racket.canSpeedUp() )
	{
		sound.playSound(duels::SND_SPEED_MORE);
		racket.changeSpeed(1);
		bonus.consumeBonus();
		speedGradient.setNewCounterValue(static_cast<int>(racket.getSpeed()-duels::RACKET_MIN_SPEED) );
	}
}

void duels::slowDownOpponent(BonusGenerator& bonus, PlayerRacket& opponentRacket, sdl2::VerticalGradient& speedGradient, const SoundHandler& sound)
{
	if( opponentRacket.canBeSlowedDown() )
	{
		sound.playSound(duels::SND_SPEED_LESS);
		opponentRacket.changeSpeed(-1);
		bonus.consumeBonus();
		speedGradient.setNewCounterValue(static_cast<int>(opponentRacket.getSpeed() - duels::RACKET_MIN_SPEED) );
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
	sound.playSound(duels::SND_NEGATIVE_BON);
	playerScore--;
	bonus.consumeBonus();
	scoreDrawing.setUpdateFlag();
}