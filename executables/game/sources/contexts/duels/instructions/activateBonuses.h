#ifndef DUELS_ACTIVATE_BONUSES_H
#define DUELS_ACTIVATE_BONUSES_H

class BonusGenerator;
class SoundHandler;
class PlayerRacket;

namespace sdl2{
	class VerticalGradient;
}

namespace duels{

class ScoreDraw;
struct LevelOptions;
class BallsThings;

unsigned getOpponent(unsigned playerNum);

void improveSizeSelf(BonusGenerator& bonus, PlayerRacket& racket, const SoundHandler& sound);

void shrinkOpponent(BonusGenerator& bonus, PlayerRacket& opponentRacket, const SoundHandler& sound);

void freezeOpponent(BonusGenerator& bonus, PlayerRacket& opponentRacket, const SoundHandler& sound);

void stealOpponentBonus(BonusGenerator& thiefBonus, BonusGenerator& opponentBonus, const SoundHandler& sound);

void accelerateSelf(BonusGenerator& bonus, PlayerRacket& racket, sdl2::VerticalGradient& speedGradient, const SoundHandler& sound);

void slowDownOpponent(BonusGenerator& bonus, PlayerRacket& opponentRacket, sdl2::VerticalGradient& speedGradient, const SoundHandler& sound);

void addBall(BonusGenerator& bonus, BallsThings& balls, duels::LevelOptions& levelOptions);

void activeZoneSpecificBonus(BonusGenerator& bonus, bool& zoneSpecificFlag, bool canActivateSpecialBonus);

void negativeBonus(BonusGenerator& bonus, int& playerScore, const SoundHandler& sound, duels::ScoreDraw& scoreDrawing);

}

#endif //DUELS_ACTIVATE_BONUSES_H