#ifndef DUELS_ACTIVATE_BONUSES_H
#define DUELS_ACTIVATE_BONUSES_H

class BonusGenerator;
class SoundPlayer;
class PlayerRacket;

namespace sdl2{
	class VerticalGradient;
}

namespace duels{

class ScoreDraw;
struct LevelOptions;
class BallsThings;

unsigned getOpponent(unsigned playerNum);

void improveSizeSelf(BonusGenerator& bonus, PlayerRacket& racket, const SoundPlayer& soundPlayer);

void shrinkOpponent(BonusGenerator& bonus, PlayerRacket& opponentRacket, const SoundPlayer& soundPlayer);

void freezeOpponent(BonusGenerator& bonus, PlayerRacket& opponentRacket, const SoundPlayer& soundPlayer);

void stealOpponentBonus(BonusGenerator& thiefBonus, BonusGenerator& opponentBonus, const SoundPlayer& soundPlayer);

void accelerateSelf(BonusGenerator& bonus, PlayerRacket& racket, sdl2::VerticalGradient& speedGradient, const SoundPlayer& soundPlayer);

void slowDownOpponent(BonusGenerator& bonus, PlayerRacket& opponentRacket, sdl2::VerticalGradient& speedGradient, const SoundPlayer& soundPlayer);

void addBall(BonusGenerator& bonus, BallsThings& balls, duels::LevelOptions& levelOptions);

void activeZoneSpecificBonus(BonusGenerator& bonus, bool& zoneSpecificFlag, bool canActivateSpecialBonus);

void negativeBonus(BonusGenerator& bonus, int& playerScore, const SoundPlayer& soundPlayer, duels::ScoreDraw& scoreDrawing);

}

#endif //DUELS_ACTIVATE_BONUSES_H