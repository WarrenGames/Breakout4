#ifndef ONE_PLAYER_DETECT_LEVEL_END_H
#define ONE_PLAYER_DETECT_LEVEL_END_H

template < typename T > class MatrixTemp2D;
struct BallThings;
struct PlayerData;
class SoundPlayer;
class InfoBar;
struct BrickData;
struct PlayedTimeCounter;

void countBricks(const MatrixTemp2D<BrickData>& levelMat, unsigned& levelEndType);

void incrementAccordingToBrickID(const BrickData& brickData, unsigned& neededBricksNumber, unsigned& tenPointsBricksNumber);

unsigned getLevelEnd(unsigned tenPointsBricksNumber, unsigned neededBricksNumber);

void detectLiveLossWithScreenBottom(BallThings& ball, unsigned& levelEndType, PlayerData& playerData, const SoundPlayer& soundPlayer, InfoBar& infoBar, PlayedTimeCounter& playedTimeCounter);

void setLevelEndIfAny(unsigned& levelEndType, PlayerData& playerData, InfoBar& infoBar);


#endif //ONE_PLAYER_DETECT_LEVEL_END_H