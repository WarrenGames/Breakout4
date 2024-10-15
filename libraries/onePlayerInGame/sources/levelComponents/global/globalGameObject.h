#ifndef P1_GLOBAL_GAME_OBJECT_H
#define P1_GLOBAL_GAME_OBJECT_H

#include "levelComponents/onePlayerRacket/onePlayerRacket.h"
#include "levelComponents/balls/ballsThings.h"
#include "demos/templates/demoStack.h"
#include "demos/positions/positionStackData.h"
#include "demos/objectsDestruction/matrixDemoData.h"
#include "demos/sounds/soundsStackData.h"
#include "onePlayerGame/level/textures/bricksTexturesLoader.h"
#include "onePlayerGame/level/textures/bricksTexturesDrawer.h"
#include "generic/texturing/backgroundDrawer.h"
#include "levelComponents/traceCross/traceCross.h"
#include "levelComponents/infoBar/infoBar.h"
#include "levelComponents/rims/rimsGlobal.h"
#include "levelComponents/fallingBonuses/fallingBonuses.h"
#include "levelComponents/global/monstersTriggers.h"
#include "generic/gameSoundSystem/gameSoundSystem.h"
#include "cheating/checkCheatingFile.h"
#include "explosions/allExplosions.h"
#include "explosions/explosionLoader.h"
#include "levelComponents/infoBar/playedTimeCounter.h"
#include "widgets/buttons/textButtonWidget.h"
#include "types/brickData.h"

struct PlayerData;
struct Essentials;
class LevelInputs;
struct AntarcticPackage;
namespace onePlGame{ class HellPackage; }
namespace demos{ struct MainPackage; }

struct LevelComponents
{
	bool isLoadingPerfect;
	unsigned levelEndType;
	sdl2::Font fancyFont;
	MatrixTemp2D< BrickData > grid;
	BricksTexturesLoader bricksTexturesLoader;
	OnePBricksTextures bricksSprites;
	OnePlayerRacket racket;
	demos::Stack< demos::PositionStackData > racketPosition;
	BallThings ball;
	demos::Stack< demos::PositionStackData > ballPosition;
	demos::Stack< demos::Matrix2DAction > bricksDestruction;
	BackgroundDrawer backgroundDrawer;
	InfoBar infoBar;
	OnePlayerRimsSystem rims;
	FallingBonuses fallingBonuses;
	GameSoundSystem gameSoundSystem;
	demos::Stack< demos::SoundStackData > soundsStack;
	MonsterTrigger monsterTrigger;
	TraceCross traceCross;
	demos::Stack< demos::PositionStackData > traceCrossPosition;
	AccurateTimeDelay crossMoveDelay;
	CheatingFile cheating;
	TextButton cheatButton;
	ExplosionsLoader explosionsLoader;
	AllExplosions explosionsSprites;
	PlayedTimeCounter playedTimeCounter;
	AccurateTimeDelay demosTimeDelay;

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
	void moveMainPackageToLevelComponents(demos::MainPackage& demosMainPackage);//Needed to run a 'pre-recorded' demo (not to 'record' a demo)
	void giveStacksContentsToMainPackage(demos::MainPackage& demosMainPackage);//Needed to 'record' a demo (not to 'run' a demo)
	void joinDemosTimePoint();
	
private:
	void commonUpdate(Essentials& essentials, LevelInputs& levelInputs, PlayerData& playerData, bool& quitGame);
	void loadMatrix(LogFile& log, const std::string& levelMatrixPath);
	void readFileLines(LogFile& log, std::ifstream& matrixFile, std::string& fileLine, Coord2D& coords, BrickData& brickData);
	void drawLevelMatrix(sdl2::RendererWindow& rndWnd);
	void actWithPlayerInputs(LevelInputs& levelInputs, bool somethingPreventMoveToRight, bool somethingPreventMoveToLeft, const PlayerData& playerData);
	void moveRacketToLeft(const LevelInputs& levelInputs, bool somethingPreventMove, const PlayerData& playerData);
	void moveRacketToRight(const LevelInputs& levelInputs, bool somethingPreventMove, const PlayerData& playerData);
	void releaseBall(LevelInputs& levelInputs, const PlayerData& playerData);
	
	void setBallPosition(const PlayerData& playerData);
	void attachMainBallToRacket(const SDL_Rect& racketRect);
	
	void collideBallWithRacket(unsigned demoKind);
	
	void quitGameIfLevelEnded(bool& quitGame, const PlayerData& playerData, LevelInputs& levelInputs) const;
	
	void setRacketIsSticky(PlayerData& playerData);
	void speedUpPlayerRacket(PlayerData& playerData);
	void enlargePlayerRacket(PlayerData& playerData);
	void enlargeRims(PlayerData& playerData);
	void setBallIsPower(PlayerData& playerData);
	void addOneBallLiveToPlayer(PlayerData& playerData);
	
	void testBallCollisionWithRims();
	void updateTracingCrossPosition(const LevelInputs& levelInputs, const PlayerData& playerData);
	void moveCrossWithJoystick(const LevelInputs& levelInputs);
	
	void drawCheatButton(Essentials& essentials) const;
	void updateCheatButton(const LevelInputs& levelInputs);
	
	void ballWithGridCollision(PlayerData& playerData);
	
	void rimsWithPinguinsCollisions(AntarcticPackage& antarcticPackage);
	void setPinguinsPathWithMouse(const Offset& mousePosition, bool mouseButtonState, AntarcticPackage& antarcticPackage);
	
	void triggerPinguinSpawn(AntarcticPackage& antarcticPackage);
	void triggerSkullSpawn(onePlGame::HellPackage& hellPackage);
	void recordPosition(demos::Stack< demos::PositionStackData >& stack, const PlayerData& playerData, int xPosition, int yPosition);
	
	void positionBallWithDemoStack();
	void positionRacketWithDemoStack(const PlayerData& playerData);
	void positionTraceCrossWithDemoStack(const PlayerData& playerData);
	void modifyBricksMatrixWithDemoStack(const PlayerData& playerData);
	void playSoundsWithDemoStack(const PlayerData& playerData);
	void updatePinguins(AntarcticPackage& antarcticPackage, LevelInputs& levelInputs);
	void browseRimsForCollisionsWithPinguins(AntarcticPackage& antarcticPackage);
};

#endif //P1_GLOBAL_GAME_OBJECT_H