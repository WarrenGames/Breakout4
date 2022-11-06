#ifndef P1_GLOBAL_GAME_OBJECT_H
#define P1_GLOBAL_GAME_OBJECT_H

#include "contexts/onePlayerGame/levelComponents/onePlayerRacket/onePlayerRacket.h"
#include "contexts/onePlayerGame/levelComponents/balls/ballsThings.h"
#include "onePlayerGame/level/textures/bricksTexturesLoader.h"
#include "onePlayerGame/level/textures/bricksTexturesDrawer.h"
#include "generic/texturing/backgroundDrawer.h"
#include "contexts/onePlayerGame/levelComponents/traceCross/traceCross.h"
#include "contexts/onePlayerGame/levelComponents/infoBar/infoBar.h"
#include "contexts/onePlayerGame/levelComponents/rims/playerRims.h"
#include "contexts/onePlayerGame/levelComponents/fallingBonuses/fallingBonuses.h"
#include "contexts/onePlayerGame/levelComponents/global/monstersTriggers.h"
#include "generic/sounds/soundHandler.h"
#include "contexts/gameCommon/cheating/checkCheatingFile.h"
#include "contexts/gameCommon/explosions/allExplosions.h"
#include "contexts/gameCommon/explosions/explosionLoader.h"
#include "widgets/buttons/textButtonWidget.h"
#include "matrices/matrix3D.h"
#include "types/brickData.h"
#include "consts/onePlayerGridConsts.h"

struct PlayerData;
struct Essentials;
class LevelInputs;
struct AntarcticPackage;
namespace onePlGame{ class HellPackage; }

struct LevelComponents
{
	bool isLoadingPerfect;
	unsigned levelEndType;
	const sdl2::Font fancyFont;
	MatrixTemp2D< BrickData > grid;
	BricksTexturesLoader bricksTexturesLoader;
	OnePBricksTextures bricksSprites;
	OnePlayerRacket racket;
	BallThings ball;
	BackgroundDrawer backgroundDrawer;
	InfoBar infoBar;
	OnePlayerRims rims;
	FallingBonuses fallingBonuses;
	const SoundHandler sounds;
	MonsterTrigger monsterTrigger;
	TraceCross traceCross;
	AccurateTimeDelay crossMoveDelay;
	CheatingFile cheating;
	TextButton cheatButton;
	ExplosionsLoader explosionsLoader;
	AllExplosions explosionsSprites;

	explicit LevelComponents(Essentials& essentials, const PlayerData& playerData, std::size_t monstersNumber);
	~LevelComponents() = default;
	LevelComponents( const LevelComponents& ) = delete;
	LevelComponents& operator= ( const LevelComponents& ) = delete;
	LevelComponents( LevelComponents&& ) = default;
	LevelComponents& operator= ( LevelComponents&& ) = default;
	
	operator bool () const;
	void antarcticUpdate(Essentials& essentials, LevelInputs& levelInputs, PlayerData& playerData, bool& quitGame, AntarcticPackage& antarcticPackage);
	void hellUpdate(Essentials& essentials, LevelInputs& levelInputs, PlayerData& playerData, bool& quitGame, onePlGame::HellPackage& hellPackage);
	void standardLevelUpdate(Essentials& essentials, LevelInputs& levelInputs, PlayerData& playerData, bool& quitGame);
	void drawEverything(Essentials& essentials);
	unsigned getLevelEndType() const;
	void activateBagBonus(unsigned bagBonusIndex, PlayerData& playerData);
	void levelSketch(Essentials& essentials);
	void recordRimStateToPlayerData(PlayerData& playerData) const;
	void recordRacketLengthToPlayerData(PlayerData& playerData) const;
	void recordRacketSpeedToPlayerData(PlayerData& playerData) const;
	void finishTheLevelByCheating();
	
private:
	void commonUpdate(Essentials& essentials, LevelInputs& levelInputs, PlayerData& playerData, bool& quitGame);
	void loadMatrix(LogFile& log, const std::string& levelMatrixPath);
	void readFileLines(LogFile& log, std::ifstream& matrixFile, std::string& fileLine, Coord2D& coords, BrickData& brickData);
	void drawLevelMatrix(sdl2::RendererWindow& rndWnd);
	void actWithPlayerInputs(LevelInputs& levelInputs, bool somethingPreventMoveToRight, bool somethingPreventMoveToLeft);
	void moveRacketToLeft(const LevelInputs& levelInputs, bool somethingPreventMove);
	void moveRacketToRight(const LevelInputs& levelInputs, bool somethingPreventMove);
	void releaseBall(LevelInputs& levelInputs);
	
	void attachMainBallToRacket(const SDL_Rect& racketRect);
	
	void moveObjects();
	
	void collideBallWithRacket();
	
	void quitGameIfLevelEnded(bool& quitGame) const;
	
	void setRacketIsSticky(PlayerData& playerData);
	void speedUpPlayerRacket(PlayerData& playerData);
	void enlargePlayerRacket(PlayerData& playerData);
	void enlargeRims(PlayerData& playerData);
	void setBallIsPower(PlayerData& playerData);
	void addOneBallLiveToPlayer(PlayerData& playerData);
	
	void testBallCollisionWithRims();
	void updateTracingCrossPosition(const LevelInputs& levelInputs);
	void moveCrossWithJoystick(const LevelInputs& levelInputs);
	
	void drawCheatButton(Essentials& essentials) const;
	void updateCheatButton(const LevelInputs& levelInputs);
	
	void ballWithGridCollision(PlayerData& playerData);
	
	void rimsWithPinguinsCollisions(AntarcticPackage& antarcticPackage);
	void setPinguinsPathWithMouse(const Offset& mousePosition, bool mouseButtonState, AntarcticPackage& antarcticPackage);
	
	void triggerPinguinSpawn(AntarcticPackage& antarcticPackage);
	void triggerSkullSpawn(onePlGame::HellPackage& hellPackage);
};

#endif //P1_GLOBAL_GAME_OBJECT_H