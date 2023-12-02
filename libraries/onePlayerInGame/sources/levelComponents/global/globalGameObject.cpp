#include "levelComponents/global/globalGameObject.h"
#include "types/essentialsStruct.h"
#include "levelComponents/inputs/userInputs.h"
#include "crossLevel/playerData.h"
#include "levelComponents/antarcticEpisodeThings/antarcticPackage.h"
#include "levelComponents/hellEpisodeThings/hellPackage.h"
#include "levelComponents/freeFunctions/detectLevelEnd.h"
#include "levelComponents/freeFunctions/testBallPositionWithGrid.h"
#include "levelComponents/demosObjects/demoMainPackage.h"
#include "demos/loading/loadDemosVectorsDataSize.h"
#include "consts/rimsConsts.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/fontsConsts.h"
#include "consts/onePlayerGridConsts.h"
#include "consts/onePlayerBonusesConsts.h"
#include "demos/consts/demosConsts.h"
#include "generic/fileSystem/fileProcessing/filesNames.h"
#include "consts/onePlayerSounds.h"
#include <sstream>

LevelComponents::LevelComponents(Essentials& essentials, const PlayerData& playerData, std::size_t monstersNumber):
	isLoadingPerfect{true},
	levelEndType{onePlGame::LevelEndNotYet},
	fancyFont{essentials.logs.error, FancyFontPath, FontMediumPointSize},
	grid{ GridWidth, GridHeight },
	bricksTexturesLoader{essentials.logs, essentials.rndWnd},
	bricksSprites{bricksTexturesLoader},
	racket{essentials, playerData},
	racketPosition{essentials.logs, demos::getVectorsDataSize(essentials.logs, essentials.prefPath, file::DemoRacketPositionFile), playerData.demoKind, demos::RacketPositionStr},
	ball{ essentials.logs, essentials.rndWnd, monstersNumber },
	ballPosition{essentials.logs, demos::getVectorsDataSize(essentials.logs, essentials.prefPath, file::DemoBallPositionFile), playerData.demoKind, demos::BallPositionStr},
	bricksDestruction{essentials.logs, demos::getVectorsDataSize(essentials.logs, essentials.prefPath, file::DemoBrickDestructionFile), playerData.demoKind, demos::BrickDestructionStr},
	backgroundDrawer{essentials.logs, essentials.rndWnd, onePlGame::BackgroundTexturePath, GameSquaresWidth, GameSquaresHeight},
	infoBar{essentials},
	rims{essentials, playerData.rimsStartState},
	fallingBonuses{essentials},
	gameSoundSystem{ essentials.logs, essentials.prefPath, onePlGame::CommonSoundsFilePath, onePlGame::CommonChannelsFilePath, onePlGame::SoundMax, onePlGame::GroupTagMax },
	//sounds{essentials, onePlGame::CommonSoundsFilePath, onePlGame::CommonChannelsFilePath},
	soundsStack{ essentials.logs, demos::getVectorsDataSize(essentials.logs, essentials.prefPath, file::DemoSoundsEventsFile), playerData.demoKind, demos::SoundEventStr},
	traceCross{essentials},
	traceCrossPosition{ essentials.logs, demos::getVectorsDataSize(essentials.logs, essentials.prefPath, file::DemoTraceCrossPositionFile), playerData.demoKind, demos::TraceCrossPositionStr },
	cheating{essentials.prefPath, OnePlayerCheatFile},
	cheatButton{essentials.logs, essentials.rndWnd, fancyFont, ":-)", GreenColor, WhiteColor, GameScreenWidth - SQR_SIZE, SQR_SIZE / 2, true },
	explosionsLoader{ essentials.logs, essentials.rndWnd },
	explosionsSprites{ explosionsLoader },
	playedTimeCounter{ essentials }
{
	loadMatrix(essentials.logs.error, playerData.getMatrixPath());
	fallingBonuses.reserveGiftBricksData(grid);
	if( false == ( 		ball 
					&& grid.size() == GridWidth * GridHeight 
					&& backgroundDrawer 
					&& infoBar 
					&& traceCross 
					&& fallingBonuses
					&& gameSoundSystem.soundSystem.wasLoadingPerfect()
					&& explosionsLoader.wasLoadingPerfect()
					) )
	{
		isLoadingPerfect = false;
		essentials.logs.error << "Error: there was an error while loading level data.\n";
	}
}

LevelComponents::operator bool() const
{
	return isLoadingPerfect;
}

void LevelComponents::commonUpdate(Essentials& essentials, LevelInputs& levelInputs, PlayerData& playerData, bool& quitGame)
{
	setBallPosition(playerData);
	modifyBricksMatrixWithDemoStack(playerData);
	ballWithGridCollision(playerData);
	collideBallWithRacket();
	infoBar.updateDataTexts(essentials, playerData, racket.data);
	fallingBonuses.update();
	fallingBonuses.detectCollisionWithRacket(playerData, racket, rims, infoBar, gameSoundSystem.soundSystem.soundPlayer);
	rims.update();
	quitGameIfLevelEnded(quitGame, playerData, levelInputs);
	testBallCollisionWithRims();
	updateTracingCrossPosition(levelInputs, playerData);
	detectLiveLossWithScreenBottom(ball, levelEndType, playerData, gameSoundSystem.soundSystem.soundPlayer, infoBar, playedTimeCounter);
	updateCheatButton(levelInputs);
	finishTheLevelByCheating();
	racket.data.unfreezeIfPossible();
	playedTimeCounter.updateTextureIfNeeded(essentials);
	recordPosition(racketPosition, playerData, racket.data.get_x_pos(), racket.data.get_y_pos() );
	recordPosition(ballPosition, playerData, ball.move.get_x_position(), ball.move.get_y_position() );
	recordPosition(traceCrossPosition, playerData, traceCross.position.x, traceCross.position.y);
	playSoundsWithDemoStack(playerData);
}

void LevelComponents::standardLevelUpdate(Essentials& essentials, LevelInputs& levelInputs, PlayerData& playerData, bool& quitGame)
{
	commonUpdate(essentials, levelInputs, playerData, quitGame);
	actWithPlayerInputs(levelInputs, false, false, playerData);
}

void LevelComponents::antarcticUpdate(Essentials& essentials, LevelInputs& levelInputs, PlayerData& playerData, bool& quitGame, AntarcticPackage& antarcticPackage)
{
	commonUpdate(essentials, levelInputs, playerData, quitGame);
	actWithPlayerInputs(levelInputs, antarcticPackage.pinguinsData.atLeastOnePinguinOnRacketRight(racket.rect), antarcticPackage.pinguinsData.atLeastOnePinguinOnRacketLeft(racket.rect), 
						playerData);
	antarcticPackage.stalactitesData.testCollisionsWithRacket(racket, antarcticPackage.stalactitesDrawer, antarcticPackage.stalactitesRects, playerData, 
																gameSoundSystem.soundSystem.soundPlayer);
	antarcticPackage.stalactitesData.updateStalactites(antarcticPackage.stalactitesDrawer, antarcticPackage.stalactitesRects);
	antarcticPackage.stalactitesData.updateStalactitesTimers();
	rimsWithPinguinsCollisions(antarcticPackage);
	setPinguinsPathWithMouse(levelInputs.getMousePosition(), levelInputs.getMouseButtonState(SDL_BUTTON_LEFT), antarcticPackage);
	updatePinguins(antarcticPackage, levelInputs);
	antarcticPackage.pinguinsData.withBallBouncing(ball);
	antarcticPackage.pinguinsData.resetBallBouncing(ball);
	triggerPinguinSpawn(antarcticPackage);
}

void LevelComponents::hellUpdate(Essentials& essentials, LevelInputs& levelInputs, PlayerData& playerData, bool& quitGame, onePlGame::HellPackage& hellPackage)
{
	commonUpdate(essentials, levelInputs, playerData, quitGame);
	actWithPlayerInputs(levelInputs, false, false, playerData);
	triggerSkullSpawn(hellPackage);
	hellPackage.update(ball.move, racket, explosionsSprites, ball.texture, gameSoundSystem.soundSystem.soundPlayer);
}

void LevelComponents::drawEverything(Essentials& essentials)
{
	backgroundDrawer.drawBackground(essentials.rndWnd);
	drawLevelMatrix(essentials.rndWnd);
	racket.drawRacket(essentials.rndWnd);
	ball.drawMainBall(essentials.rndWnd);
	infoBar.drawEverything(essentials.rndWnd);
	playedTimeCounter.drawElapsedTimeTexture(essentials);
	fallingBonuses.drawBonuses(essentials);
	rims.drawEverything(essentials);
	traceCross.drawCross(essentials, ball.isMainBallActive);
	drawCheatButton(essentials);
}

unsigned LevelComponents::getLevelEndType() const
{
	return levelEndType;
}

void LevelComponents::activateBagBonus(unsigned bagBonusIndex, PlayerData& playerData)
{
	assert( bagBonusIndex < onePlGame::BonusMax );
	switch( bagBonusIndex )
	{
		case onePlGame::BonusStickyRacket:
			setRacketIsSticky(playerData);
			break;
		case onePlGame::BonusRacketSpeedUp:
			speedUpPlayerRacket(playerData);
			break;
		case onePlGame::BonusEnlargeRacket:
			enlargePlayerRacket(playerData);
			break;
		case onePlGame::BonusEnlargeRim:
			enlargeRims(playerData);
			break;
		case onePlGame::BonusPowerBall:
			setBallIsPower(playerData);
			break;
		case onePlGame::BonusOneMoreBallLive:
			addOneBallLiveToPlayer(playerData);
			break;
	}
}

void LevelComponents::levelSketch(Essentials& essentials)
{
	backgroundDrawer.drawBackground(essentials.rndWnd);
	drawLevelMatrix(essentials.rndWnd);
}

void LevelComponents::recordRimStateToPlayerData(PlayerData& playerData) const
{
	playerData.rimsStartState = rims.getRimsStatus();
}

void LevelComponents::recordRacketLengthToPlayerData(PlayerData& playerData) const
{
	playerData.racketSize = racket.data.getSize();
}

void LevelComponents::recordRacketSpeedToPlayerData(PlayerData& playerData) const
{
	playerData.racketSpeed = racket.data.getSpeed();
}

void LevelComponents::finishTheLevelByCheating()
{
	if( cheatButton.buttonClicked() && cheating.wasFileWithDataFound() )
	{
		levelEndType = onePlGame::LevelEndComplete;
	}
}

void LevelComponents::moveMainPackageToLevelComponents(demos::MainPackage& demosMainPackage)//Needed to run a 'pre-recorded' demo (not to 'record' a demo)
{
	traceCrossPosition = std::move( demosMainPackage.traceCrossPosition );
	racketPosition = std::move( demosMainPackage.racketPosition );
	ballPosition = std::move( demosMainPackage.ballPosition );
	bricksDestruction = std::move( demosMainPackage.brickDestruction );
	soundsStack = std::move( demosMainPackage.soundsStack );
}

void LevelComponents::giveStacksContentsToMainPackage(demos::MainPackage& demosMainPackage)//Needed to 'record' a demo (not to 'run' a demo) after demo is complete
{
	demosMainPackage.traceCrossPosition = std::move( traceCrossPosition );
	demosMainPackage.racketPosition = std::move( racketPosition );
	demosMainPackage.ballPosition = std::move( ballPosition );
	demosMainPackage.brickDestruction = std::move( bricksDestruction );
	demosMainPackage.soundsStack = std::move( soundsStack );
}

void LevelComponents::joinDemosTimePoint()
{
	demosTimeDelay.joinTimePoints();
	racketPosition.setPrecedentTimePoint();
	ballPosition.setPrecedentTimePoint();
	bricksDestruction.setPrecedentTimePoint();
	soundsStack.setPrecedentTimePoint();
}

void LevelComponents::loadMatrix(LogFile& log, const std::string& levelMatrixPath)
{
	if( std::ifstream matrixFile{ levelMatrixPath } )
	{
		std::string fileLine;
		Coord2D coord{0, 0};
		BrickData brickData;
		readFileLines(log, matrixFile, fileLine, coord, brickData);
	}
	else{
		log << "Error: couldn't load the following matrix file: " << levelMatrixPath << " .\n";
		isLoadingPerfect = false;
	}
}

void LevelComponents::readFileLines(LogFile& log, std::ifstream& matrixFile, std::string& fileLine, Coord2D& coords, BrickData& brickData)
{
	std::size_t fileLineNumber{1};
	while( std::getline(matrixFile, fileLine) )
	{
		std::istringstream lineStream{ fileLine };
		if( lineStream >> coords.height >> coords.width >> brickData.index >> brickData.property )
		{
			if( coords.width < grid.width() && coords.height + 1 < grid.height() )
			{
				grid(coords.width, coords.height + 1 ) = brickData;
			}
		}
		else{
			log << "Error: couldn't read the line number " << fileLineNumber << " in a matrix file.\n";
			isLoadingPerfect = false;
		}
		fileLineNumber++;
	}
}

void LevelComponents::drawLevelMatrix(sdl2::RendererWindow& rndWnd)
{
	for( std::size_t width{0} ; width < grid.width() ; ++width )
	{
		for( std::size_t height{0} ; height < grid.height() ; ++height )
		{
			bricksSprites.drawSingleBrick(rndWnd, grid(width, height), Offset{SQR_SIZE * static_cast<int>(width), SQR_SIZE * (static_cast<int>(height) )} );
		}
	}
}

void LevelComponents::actWithPlayerInputs(LevelInputs& levelInputs, bool somethingPreventMoveToRight, bool somethingPreventMoveToLeft, const PlayerData& playerData)
{
	moveRacketToLeft(levelInputs, somethingPreventMoveToLeft, playerData);
	moveRacketToRight(levelInputs, somethingPreventMoveToRight, playerData);
	positionRacketWithDemoStack(playerData);
	releaseBall(levelInputs, playerData);
}

void LevelComponents::moveRacketToLeft(const LevelInputs& levelInputs, bool somethingPreventMove, const PlayerData& playerData)
{
	assert( playerData.demoKind < demos::GameDemoEnumMax );
	if( playerData.demoKind != demos::GameIsDemo 
		&& levelInputs.getFuncState(onePlGame::InputMoveLeft) 
		&& false == levelInputs.getFuncState(onePlGame::InputMoveRight) 
		&& false == somethingPreventMove )
	{
		racket.data.moveRacket(MoveToLeft, racket.standardRacket.getWidth(racket.data.getSize()));
		racket.setRacketRect();
	}
}

void LevelComponents::moveRacketToRight(const LevelInputs& levelInputs, bool somethingPreventMove, const PlayerData& playerData)
{
	assert( playerData.demoKind < demos::GameDemoEnumMax );
	if( playerData.demoKind != demos::GameIsDemo
		&& levelInputs.getFuncState(onePlGame::InputMoveRight) 
		&& false == levelInputs.getFuncState(onePlGame::InputMoveLeft) 
		&& false == somethingPreventMove )
	{
		racket.data.moveRacket(MoveToRight, racket.standardRacket.getWidth(racket.data.getSize()));
		racket.setRacketRect();
	}
}

void LevelComponents::releaseBall(LevelInputs& levelInputs, const PlayerData& playerData)
{
	if( demos::GameIsRecording == playerData.demoKind || demos::GameHasPlayerInputs == playerData.demoKind )
	{
		if( false == ball.isMainBallActive && levelInputs.getFuncState(onePlGame::InputBallTrace) )
		{
			const Offset ballDirectionVectors{ 	traceCross.position.x - ball.move.get_x_position(), 
											traceCross.position.y - ball.move.get_y_position()};
			ball.isMainBallActive = true;
			ball.move.setSpeed( ball.speeds.getSpeed(playerData.skillLevel) );
			giveObjectNewDirection(ball.move, ballDirectionVectors);
			levelInputs.voidSpecialAction(onePlGame::InputBallTrace);
			playedTimeCounter.carryOnTheGame();
		}
	}
}

void LevelComponents::setBallPosition(const PlayerData& playerData)
{
	if( playerData.demoKind == demos::GameHasPlayerInputs || playerData.demoKind == demos::GameIsRecording )
	{
		if( ball.isMainBallActive )
		{
			ball.moveMainBall();
		}
		else{
			attachMainBallToRacket(racket.rect);
		}
	}
	else if( playerData.demoKind == demos::GameIsDemo )
	{
		positionBallWithDemoStack();
	}
}

void LevelComponents::attachMainBallToRacket(const SDL_Rect& racketRect)
{
	ball.move.setPosition(Offset{racketRect.x + racketRect.w / 2, racketRect.y - ball.texture.sprite.height() / 2} );
}

void LevelComponents::collideBallWithRacket()
{
	ball.handleBallWithRacketCollision(racket.rect, racket.glueLevel, gameSoundSystem.soundSystem.soundPlayer);
}

void LevelComponents::quitGameIfLevelEnded(bool& quitGame, const PlayerData& playerData, LevelInputs& levelInputs) const
{
	if( levelEndType == onePlGame::LevelEndPartially || levelEndType == onePlGame::LevelEndComplete || levelEndType == onePlGame::LevelEndSurrender )
	{
		quitGame = true;
		if( playerData.demoKind == demos::GameIsRecording )
		{
			levelInputs.addQuitEvent();
		}
	}
}

void LevelComponents::setRacketIsSticky(PlayerData& playerData)
{
	if( playerData.bonusesInBag[onePlGame::BonusStickyRacket] >= 1 )
	{
		racket.glueLevel += 3;
		playerData.bonusesInBag[onePlGame::BonusStickyRacket]--;
	}
	else{
		gameSoundSystem.soundSystem.soundPlayer.playSoundOnGroup(onePlGame::SoundCantUseBonus, onePlGame::GroupTagBonusActivation);
	}
}

void LevelComponents::speedUpPlayerRacket(PlayerData& playerData)
{
	if( racket.data.canSpeedUp() && playerData.bonusesInBag[onePlGame::BonusRacketSpeedUp] >= 1 )
	{
		gameSoundSystem.soundSystem.soundPlayer.playSoundOnGroup(onePlGame::SoundSpeedUp, onePlGame::GroupTagBonusActivation);
		racket.data.addToSpeed( onePlGame::RacketSpeedBonusAdd );
		playerData.bonusesInBag[onePlGame::BonusRacketSpeedUp]--;
		infoBar.setUpdateFlag(infoBarTexts::RacketSpeed);
		infoBar.setUpdateFlag(infoBarTexts::BonusCoinNumber);
	}
	else{
		gameSoundSystem.soundSystem.soundPlayer.playSoundOnGroup(onePlGame::SoundCantUseBonus, onePlGame::GroupTagBonusActivation);
	}
}

void LevelComponents::enlargePlayerRacket(PlayerData& playerData)
{
	if( racket.data.canBeEnlarged() && playerData.bonusesInBag[onePlGame::BonusEnlargeRacket] >= 1 )
	{
		gameSoundSystem.soundSystem.soundPlayer.playSoundOnGroup(onePlGame::SoundEnlargeRacket, onePlGame::GroupTagBonusActivation);
		racket.data.enlarge();
		playerData.bonusesInBag[onePlGame::BonusEnlargeRacket]--;
		infoBar.setUpdateFlag(infoBarTexts::BonusCoinNumber);
	}
	else{
		gameSoundSystem.soundSystem.soundPlayer.playSoundOnGroup(onePlGame::SoundCantUseBonus, onePlGame::GroupTagBonusActivation);
	}
}

void LevelComponents::enlargeRims(PlayerData& playerData)
{
	if( rims.getRimsStatus() + 1 < rims::RemoveMax && playerData.bonusesInBag[onePlGame::BonusEnlargeRim] >= 1 )
	{
		gameSoundSystem.soundSystem.soundPlayer.playSoundOnGroup(onePlGame::SoundEnlargeRacket, onePlGame::GroupTagBonusActivation);
		rims.changeStatus(1);
		playerData.bonusesInBag[onePlGame::BonusEnlargeRim]--;
		infoBar.setUpdateFlag(infoBarTexts::BonusCoinNumber);
	}
	else{
		gameSoundSystem.soundSystem.soundPlayer.playSoundOnGroup(onePlGame::SoundCantUseBonus, onePlGame::GroupTagBonusActivation);
	}
}

void LevelComponents::setBallIsPower(PlayerData& playerData)
{
	if( false == ball.isBallPowerful && playerData.bonusesInBag[onePlGame::BonusPowerBall] >= 1 )
	{
		gameSoundSystem.soundSystem.soundPlayer.playSoundOnGroup(onePlGame::SoundImpactWithDamage, onePlGame::GroupTagNewCoin);
		ball.isBallPowerful = true;
		playerData.bonusesInBag[onePlGame::BonusPowerBall]--;
		infoBar.setUpdateFlag(infoBarTexts::BonusCoinNumber);
	}
	else{
		gameSoundSystem.soundSystem.soundPlayer.playSoundOnGroup(onePlGame::SoundCantUseBonus, onePlGame::GroupTagBonusActivation);
	}
}

void LevelComponents::addOneBallLiveToPlayer(PlayerData& playerData)
{
	if( playerData.bonusesInBag[onePlGame::BonusOneMoreBallLive] >= 1 )
	{
		playerData.playerLives++;
		playerData.bonusesInBag[onePlGame::BonusOneMoreBallLive]--;
		infoBar.setUpdateFlag(infoBarTexts::BallsInBag);
		infoBar.setUpdateFlag(infoBarTexts::BonusCoinNumber);
	}
	else{
		gameSoundSystem.soundSystem.soundPlayer.playSoundOnGroup(onePlGame::SoundCantUseBonus, onePlGame::GroupTagBonusActivation);
	}
}

void LevelComponents::testBallCollisionWithRims()
{
	ball.testCollisionWithRims(rims, gameSoundSystem.soundSystem.soundPlayer);
}

void LevelComponents::updateTracingCrossPosition(const LevelInputs& levelInputs, const PlayerData& playerData)
{
	if( demos::GameIsRecording == playerData.demoKind || demos::GameHasPlayerInputs == playerData.demoKind )
	{
		if( false == ball.isMainBallActive )
		{
			if( onePlGame::CrossDeviceIsMouse == levelInputs.getCrossMoveDeviceType() )
			{
				traceCross.position = levelInputs.getMousePosition();
				traceCross.position.x -= TraceCrossOffset;
				traceCross.position.y -= TraceCrossOffset;
			}
			else if( onePlGame::CrossDeviceIsJoystick == levelInputs.getCrossMoveDeviceType() )
			{
				moveCrossWithJoystick(levelInputs);
			}
		}
	}
	else if( demos::GameIsDemo == playerData.demoKind )
	{
		positionTraceCrossWithDemoStack(playerData);
	}
}

void LevelComponents::moveCrossWithJoystick(const LevelInputs& levelInputs)
{
	if( crossMoveDelay.hasTimeElapsed( std::chrono::milliseconds{10} ) )
	{
		if( levelInputs.getCrossMove().x > 0 )
		{
			traceCross.position.x += 1;
		}
		else if( levelInputs.getCrossMove().x < 0 )
		{
			traceCross.position.x -= 1;
		}
		if( levelInputs.getCrossMove().y > 0 )
		{
			traceCross.position.y -= 1;
		}
		else if( levelInputs.getCrossMove().y < 0 )
		{
			traceCross.position.y += 1;
		}
		crossMoveDelay.joinTimePoints();
	}
}

void LevelComponents::drawCheatButton(Essentials& essentials) const
{
	if( cheating.wasFileWithDataFound() )
	{
		cheatButton.drawButton(essentials.rndWnd);
	}
}

void LevelComponents::updateCheatButton(const LevelInputs& levelInputs)
{
	if( cheating.wasFileWithDataFound() )
	{
		cheatButton.updateButton(levelInputs.getMousePosition(), levelInputs.getMouseButtonState(SDL_BUTTON_LEFT) );
	}
}

void LevelComponents::ballWithGridCollision(PlayerData& playerData)
{
	if( ball.canDetectCollisionSince && ( playerData.demoKind == demos::GameHasPlayerInputs || playerData.demoKind == demos::GameIsRecording ) )
	{
		ballCol::testLeftCollision(*this, ball, playerData);
		ballCol::testRightCollision(*this, ball, playerData);
		ballCol::testTopCollision(*this, ball, playerData);
		ballCol::testBottomCollision(*this, ball, playerData);
		ballCol::testTopLeftCollision(*this, ball, playerData);
		ballCol::testTopRightCollision(*this, ball, playerData);
		ballCol::testBottomLeftCollision(*this, ball, playerData);
		ballCol::testBottomRightCollision(*this, ball, playerData);
		ballCol::testScreenLeftCollision(*this, ball);
		ballCol::testScreenRightCollision(*this, ball);
		ballCol::testScreenTopCollision(*this, ball);
		ball.canDetectCollisionSince = false;
	}
}

void LevelComponents::rimsWithPinguinsCollisions(AntarcticPackage& antarcticPackage)
{
	for( auto const &rim : rims )
	{
		antarcticPackage.pinguinsData.makePinguinsBounceWithRims(rim, gameSoundSystem.soundSystem.soundPlayer);
	}
}

void LevelComponents::setPinguinsPathWithMouse(const Offset& mousePosition, bool mouseButtonState, AntarcticPackage& antarcticPackage)
{
	antarcticPackage.pinguinsData.setPinguinPathWithMouse(mousePosition, mouseButtonState);
}

void LevelComponents::triggerPinguinSpawn(AntarcticPackage& antarcticPackage)
{
	if( monsterTrigger.canTrigger(Pinguin_monster_trigger) )
	{
		antarcticPackage.pinguinsData.activeOnePinguin(antarcticPackage.antarcticDemoPackage);
		monsterTrigger.setTriggerFlag(Pinguin_monster_trigger, false);
	}
}

void LevelComponents::triggerSkullSpawn(onePlGame::HellPackage& hellPackage)
{
	if( monsterTrigger.canTrigger(Hell_skull_monster_trigger) )
	{
		hellPackage.addPendingSkull();
		monsterTrigger.setTriggerFlag(Hell_skull_monster_trigger, false);
	}
}

void LevelComponents::recordPosition(demos::Stack< demos::PositionStackData >& stack, const PlayerData& playerData, int xPosition, int yPosition)
{
	if( playerData.demoKind == demos::GameIsRecording )
	{
		if( stack.getCommandsNumber() == 0 )//here, we don't test a precedent position because there is none.
		{
			stack.emplaceElement(demos::PositionStackData{demosTimeDelay.getCurrentElapsedMicrosecondsTime(), xPosition, yPosition} );
		}
		else if( stack.getCommandsNumber() + 1 < stack.getCapacity() && stack.getCommandsNumber() > 0 )//We check there is precedent data with position stacked.
		{
			if( !( stack.getLastElement().position.x == xPosition && stack.getLastElement().position.y == yPosition ) )
			{
				stack.emplaceElement(demos::PositionStackData{demosTimeDelay.getCurrentElapsedMicrosecondsTime(), xPosition, yPosition} );
			}
		}
		else{
			stack.setSizeNotSufficientFlag();
		}
	}
}

void LevelComponents::positionBallWithDemoStack()
{
	//No 'PlayerData' function parameter because 'demoKind' value is checked above for 'demos::GameIsDemo' possible value
	while( ballPosition.getCommandsNumber() > 0 && ballPosition.hasLastTimeElapsed() )
	{
		ball.move.setPosition(ballPosition.getLastElement().position);
		ballPosition.pop_back();
	}
}

void LevelComponents::positionRacketWithDemoStack(const PlayerData& playerData)
{
	if( playerData.demoKind == demos::GameIsDemo )
	{
		while( racketPosition.getCommandsNumber() > 0 && racketPosition.hasLastTimeElapsed() )
		{
			racket.data.positionRacket(racketPosition.getLastElement().position);
			racket.setRacketRect();
			racketPosition.pop_back();
		}
	}
}

void LevelComponents::positionTraceCrossWithDemoStack(const PlayerData& playerData)
{
	if( playerData.demoKind == demos::GameIsDemo )
	{
		while( traceCrossPosition.getCommandsNumber() > 0 && traceCrossPosition.hasLastTimeElapsed() )
		{
			traceCross.position = traceCrossPosition.getLastElement().position;
			traceCrossPosition.pop_back();
		}
	}
}

void LevelComponents::modifyBricksMatrixWithDemoStack(const PlayerData& playerData)
{
	if( playerData.demoKind == demos::GameIsDemo )
	{
		while( bricksDestruction.getCommandsNumber() > 0 && bricksDestruction.hasLastTimeElapsed() )
		{
			if( grid.isInsideBoundaries(bricksDestruction.getLastElement().coords ) )
			{
				grid( bricksDestruction.getLastElement().coords ) = bricksDestruction.getLastElement().brickData;
			}
			bricksDestruction.pop_back();
		}
	}
}

void LevelComponents::playSoundsWithDemoStack(const PlayerData& playerData)
{
	if( playerData.demoKind == demos::GameIsDemo )
	{
		while( soundsStack.getCommandsNumber() > 0 && soundsStack.hasLastTimeElapsed() )
		{
			gameSoundSystem.soundSystem.soundPlayer.playSoundOnGroup( soundsStack.getLastElement().soundEnum, soundsStack.getLastElement().groupTag );
			soundsStack.pop_back();
		}
	}
}

void LevelComponents::updatePinguins(AntarcticPackage& antarcticPackage, LevelInputs& levelInputs)
{
	antarcticPackage.pinguinsData.updateMove(antarcticPackage.antarcticDemoPackage);
	antarcticPackage.pinguinsData.updateAnim();
	antarcticPackage.pinguinsData.rotatePinguinIfAny(antarcticPackage.antarcticDemoPackage);
	antarcticPackage.pinguinsData.updateCollisions(grid, racket.rect, antarcticPackage.antarcticDemoPackage);
	browseRimsForCollisionsWithPinguins(antarcticPackage);
	antarcticPackage.pinguinsData.makePinguinsQuack(racket.rect, levelInputs.getFuncState(onePlGame::InputMoveLeft), levelInputs.getFuncState(onePlGame::InputMoveRight), 
														gameSoundSystem.soundSystem.soundPlayer, antarcticPackage.antarcticDemoPackage);
	antarcticPackage.pinguinsData.tryToMindPlayer(racket.rect);
	antarcticPackage.pinguinsData.revokePinguinIfHitEnough(antarcticPackage.antarcticDemoPackage);
	antarcticPackage.pinguinsData.forcePinguinsToStayBesideRacket(racket.rect);
	antarcticPackage.pinguinsData.createOrDestroyPinguinsWithStack(antarcticPackage.antarcticDemoPackage);
	antarcticPackage.pinguinsData.playRecordedQuackSounds(antarcticPackage.antarcticDemoPackage, gameSoundSystem.soundSystem.soundPlayer);
}

void LevelComponents::browseRimsForCollisionsWithPinguins(AntarcticPackage& antarcticPackage)
{
	for( auto const &rim : rims )
	{
		antarcticPackage.pinguinsData.collisionWithPlayerRim(rim);
	}
}
