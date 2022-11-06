#ifndef ONE_PLAYER_PINGUINS_H
#define ONE_PLAYER_PINGUINS_H

#include "contexts/gameCommon/pinguins/pinguinBehaviorData.h"
#include "time/accurateTime.h"
#include "SDL_rect.h"
#include <vector>
#include <string>

struct Essentials;
struct PlayerData;
struct AppLogFiles;
template<typename T>class MatrixTemp2D;
class SoundHandler;
struct BrickData;
struct BallThings;

class OnePlayerPinguin
{
private:
	std::vector< PinguinBehaviorData > pinguins;
	AccurateTimeDelay moveTime;
	AccurateTimeDelay mindPlayerTime;
	SDL_Rect collisionRect;
	unsigned neededHitsToRevokePinguin;
	bool hasMovedSince;
	bool isLoadingPerfect;

public:
	explicit OnePlayerPinguin(Essentials& essentials, const PlayerData& playerData);
	~OnePlayerPinguin() = default;
	OnePlayerPinguin( const OnePlayerPinguin& ) = delete;
	OnePlayerPinguin& operator= ( const OnePlayerPinguin& ) = delete;
	OnePlayerPinguin( OnePlayerPinguin&& ) = default;
	OnePlayerPinguin& operator= ( OnePlayerPinguin&& ) = default;
	
	std::vector< PinguinBehaviorData >::const_iterator begin() const;
	std::vector< PinguinBehaviorData >::const_iterator end() const;
	void update(const MatrixTemp2D<BrickData>& grid, const SDL_Rect& racketRect, bool playerLeftState, bool playerRightState, const SoundHandler& sounds);
	bool wasLoadingPerfect() const;
	std::size_t size() const;
	void activeOnePinguin();
	
	bool atLeastOnePinguinOnRacketLeft(const SDL_Rect& racketRect) const;
	bool atLeastOnePinguinOnRacketRight(const SDL_Rect& racketRect) const;
	void withBallBouncing(BallThings& ballThings);
	void resetBallBouncing(BallThings& ballThings);
	void makePinguinsBounceWithRims(const SDL_Rect& rimRect, const SoundHandler& sounds);
	void setPinguinPathWithMouse(const Offset& mousePosition, bool mouseButtonState);
	
private:
	void loadDataFile(AppLogFiles& logs, const std::string& levelDataFilePath);
	void readSingleLine(AppLogFiles& logs, const std::string& levelDataFilePath, std::istringstream& lineStream, unsigned lineIndex);
	void loadPinguinData(AppLogFiles& logs, const std::string& levelDataFilePath, std::istringstream& lineStream);
	void loadNeededHitsData(AppLogFiles& logs, unsigned skillLevel);
	
	void updateMove();
	void updateAnim();
	void updateCollisions(const MatrixTemp2D<BrickData>& grid, const SDL_Rect& racketRect);
	void browseForCollisions(const SDL_Rect& collisionRect, const MatrixTemp2D<BrickData>& grid);
	void resetPinguinDirectionIfCollision(PinguinBehaviorData& pinguin, bool wasThereCol);
	void collisionWithRacket(const SDL_Rect& racketRect);
	void makePinguinsQuack(const SDL_Rect& racketRect, bool playerLeftState, bool playerRightState, const SoundHandler& sounds);
	
	void tryToMindPlayer(const SDL_Rect& racketRect);
	
	void revokePinguinIfHitEnough();
	void forcePinguinsToStayBesideRacket(const SDL_Rect& racketRect);
	void resetPinguinStatusIfOffscreen();
};

#endif //ONE_PLAYER_PINGUINS_H