#include "contexts/onePlayerGame/levelComponents/global/globalGameObject.h"
#include "types/essentialsStruct.h"
#include "contexts/onePlayerGame/levelComponents/inputs/userInputs.h"
#include "crossLevel/playerData.h"
#include "contexts/onePlayerGame/levelComponents/antarcticEpisodeThings/antarcticPackage.h"
#include "contexts/onePlayerGame/levelComponents/hellEpisodeThings/hellPackage.h"
#include "contexts/onePlayerGame/levelComponents/freeFunctions/detectLevelEnd.h"
#include "contexts/onePlayerGame/levelComponents/freeFunctions/testBallPositionWithGrid.h"
#include "consts/rimsConsts.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/fontsConsts.h"
#include <sstream>

LevelComponents::LevelComponents(Essentials& essentials, const PlayerData& playerData, std::size_t monstersNumber):
	isLoadingPerfect{true},
	levelEndType{onePlGame::LevelEndNotYet},
	fancyFont{essentials.logs.error, FancyFontPath, FontMediumPointSize},
	grid{ GridWidth, GridHeight },
	bricksTexturesLoader{essentials.logs, essentials.rndWnd},
	bricksSprites{bricksTexturesLoader},
	racket{essentials, playerData},
	ball{ essentials.logs, essentials.rndWnd, monstersNumber },
	backgroundDrawer{essentials.logs, essentials.rndWnd, onePlGame::BackgroundTexturePath, GameSquaresWidth, GameSquaresHeight},
	infoBar{essentials},
	rims{essentials, playerData.rimsStartState},
	fallingBonuses{essentials},
	sounds{essentials, onePlGame::CommonSoundsFilePath, onePlGame::CommonChannelsFilePath},
	traceCross{essentials},
	cheating{essentials.prefPath, OnePlayerCheatFile},
	cheatButton{essentials.logs, essentials.rndWnd, fancyFont, ":-)", GreenColor, WhiteColor, GameScreenWidth - SQR_SIZE, SQR_SIZE / 2, true },
	explosionsLoader{ essentials.logs, essentials.rndWnd },
	explosionsSprites{ explosionsLoader }
{
	loadMatrix(essentials.logs.error, playerData.getMatrixPath());
	fallingBonuses.reserveGiftBricksData(grid);
	if( false == ( 		ball 
					&& grid.size() == GridWidth * GridHeight 
					&& backgroundDrawer 
					&& infoBar 
					&& traceCross 
					&& fallingBonuses
					&& sounds.wasLoadingPerfect()
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
	attachMainBallToRacket(racket.rect);
	moveObjects();
	ballWithGridCollision(playerData);
	ball.accelerateSpeed(playerData.skillLevel);
	collideBallWithRacket();
	infoBar.updateDataTexts(essentials, playerData, racket.data);
	fallingBonuses.update();
	fallingBonuses.detectCollisionWithRacket(playerData, racket, rims, infoBar, sounds);
	rims.update();
	quitGameIfLevelEnded(quitGame);
	testBallCollisionWithRims();
	updateTracingCrossPosition(levelInputs);
	detectLiveLossWithScreenBottom(ball, levelEndType, playerData, sounds, infoBar);
	updateCheatButton(levelInputs);
	finishTheLevelByCheating();
	racket.data.unfreezeIfPossible();
}

void LevelComponents::standardLevelUpdate(Essentials& essentials, LevelInputs& levelInputs, PlayerData& playerData, bool& quitGame)
{
	commonUpdate(essentials, levelInputs, playerData, quitGame);
	actWithPlayerInputs(levelInputs, false, false);
}

void LevelComponents::antarcticUpdate(Essentials& essentials, LevelInputs& levelInputs, PlayerData& playerData, bool& quitGame, AntarcticPackage& antarcticPackage)
{
	commonUpdate(essentials, levelInputs, playerData, quitGame);
	actWithPlayerInputs(levelInputs, antarcticPackage.pinguinsData.atLeastOnePinguinOnRacketRight(racket.rect), antarcticPackage.pinguinsData.atLeastOnePinguinOnRacketLeft(racket.rect) );
	antarcticPackage.stalactitesData.testCollisionsWithRacket(racket, antarcticPackage.stalactitesDrawer, antarcticPackage.stalactitesRects, playerData, sounds);
	antarcticPackage.stalactitesData.updateStalactites(antarcticPackage.stalactitesDrawer, antarcticPackage.stalactitesRects);
	antarcticPackage.stalactitesData.updateStalactitesTimers();
	rimsWithPinguinsCollisions(antarcticPackage);
	setPinguinsPathWithMouse(levelInputs.getMousePosition(), levelInputs.getMouseButtonState(SDL_BUTTON_LEFT), antarcticPackage);
	antarcticPackage.pinguinsData.update(grid, racket.rect, levelInputs.getFuncState(onePlGame::InputMoveLeft), levelInputs.getFuncState(onePlGame::InputMoveRight), sounds);
	antarcticPackage.pinguinsData.withBallBouncing(ball);
	antarcticPackage.pinguinsData.resetBallBouncing(ball);
	triggerPinguinSpawn(antarcticPackage);
}

void LevelComponents::hellUpdate(Essentials& essentials, LevelInputs& levelInputs, PlayerData& playerData, bool& quitGame, onePlGame::HellPackage& hellPackage)
{
	commonUpdate(essentials, levelInputs, playerData, quitGame);
	actWithPlayerInputs(levelInputs, false, false);
	triggerSkullSpawn(hellPackage);
	hellPackage.update(ball.move, racket, explosionsSprites, ball.texture, sounds);
}

void LevelComponents::drawEverything(Essentials& essentials)
{
	backgroundDrawer.drawBackground(essentials.rndWnd);
	drawLevelMatrix(essentials.rndWnd);
	racket.drawRacket(essentials.rndWnd);
	ball.drawMainBall(essentials.rndWnd);
	infoBar.drawEverything(essentials.rndWnd);
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

void LevelComponents::actWithPlayerInputs(LevelInputs& levelInputs, bool somethingPreventMoveToRight, bool somethingPreventMoveToLeft)
{
	moveRacketToLeft(levelInputs, somethingPreventMoveToLeft);
	moveRacketToRight(levelInputs, somethingPreventMoveToRight);
	releaseBall(levelInputs);
}

void LevelComponents::moveRacketToLeft(const LevelInputs& levelInputs, bool somethingPreventMove)
{
	if( levelInputs.getFuncState(onePlGame::InputMoveLeft) && false == levelInputs.getFuncState(onePlGame::InputMoveRight) 
		&& false == somethingPreventMove )
	{
		racket.data.moveRacket(MoveToLeft, racket.standardRacket.getWidth(racket.data.getSize()));
		racket.setRacketRect();
	}
}

void LevelComponents::moveRacketToRight(const LevelInputs& levelInputs, bool somethingPreventMove)
{
	if( levelInputs.getFuncState(onePlGame::InputMoveRight) && false == levelInputs.getFuncState(onePlGame::InputMoveLeft) 
		&& false == somethingPreventMove )
	{
		racket.data.moveRacket(MoveToRight, racket.standardRacket.getWidth(racket.data.getSize()));
		racket.setRacketRect();
	}
}

void LevelComponents::releaseBall(LevelInputs& levelInputs)
{
	if( false == ball.isMainBallActive && levelInputs.getFuncState(onePlGame::InputBallTrace) )
	{
		const Offset ballDirectionVectors{ 	traceCross.position.x - ball.move.get_x_position(), 
											traceCross.position.y - ball.move.get_y_position()};
		ball.isMainBallActive = true;
		ball.move.setSpeed(onePlGame::BallStartingSpeed);
		giveObjectNewDirection(ball.move, ballDirectionVectors);
		levelInputs.setFuncState(onePlGame::InputBallTrace, false);
	}
}

void LevelComponents::attachMainBallToRacket(const SDL_Rect& racketRect)
{
	if( false == ball.isMainBallActive )
	{
		ball.move.setPosition(Offset{racketRect.x + racketRect.w / 2, racketRect.y - ball.texture.sprite.height() / 2} );
	}
}

void LevelComponents::moveObjects()
{
	ball.moveMainBall();
}

void LevelComponents::collideBallWithRacket()
{
	ball.handleBallWithRacketCollision(racket.rect, racket.glueLevel, sounds);
}

void LevelComponents::quitGameIfLevelEnded(bool& quitGame) const
{
	if( levelEndType == onePlGame::LevelEndPartially || levelEndType == onePlGame::LevelEndComplete || levelEndType == onePlGame::LevelEndSurrender )
		quitGame = true;
}

void LevelComponents::setRacketIsSticky(PlayerData& playerData)
{
	if( playerData.bonusesInBag[onePlGame::BonusStickyRacket] >= 1 )
	{
		racket.glueLevel += 3;
		playerData.bonusesInBag[onePlGame::BonusStickyRacket]--;
	}
	else{
		sounds.playSound(onePlGame::SoundCantUseBonus);
	}
}

void LevelComponents::speedUpPlayerRacket(PlayerData& playerData)
{
	if( racket.data.canSpeedUp() && playerData.bonusesInBag[onePlGame::BonusRacketSpeedUp] >= 1 )
	{
		sounds.playSound(onePlGame::SoundSpeedUp);
		racket.data.addToSpeed( onePlGame::RacketSpeedBonusAdd );
		playerData.bonusesInBag[onePlGame::BonusRacketSpeedUp]--;
		infoBar.setUpdateFlag(infoBarTexts::RacketSpeed);
		infoBar.setUpdateFlag(infoBarTexts::BonusCoinNumber);
	}
	else{
		sounds.playSound(onePlGame::SoundCantUseBonus);
	}
}

void LevelComponents::enlargePlayerRacket(PlayerData& playerData)
{
	if( racket.data.canBeEnlarged() && playerData.bonusesInBag[onePlGame::BonusEnlargeRacket] >= 1 )
	{
		sounds.playSound(onePlGame::SoundEnlargeRacket);
		racket.data.enlarge();
		playerData.bonusesInBag[onePlGame::BonusEnlargeRacket]--;
		infoBar.setUpdateFlag(infoBarTexts::BonusCoinNumber);
	}
	else{
		sounds.playSound(onePlGame::SoundCantUseBonus);
	}
}

void LevelComponents::enlargeRims(PlayerData& playerData)
{
	if( rims.getRimsStatus() + 1 < rims::RemoveMax && playerData.bonusesInBag[onePlGame::BonusEnlargeRim] >= 1 )
	{
		sounds.playSound(onePlGame::SoundEnlargeRacket);
		rims.changeStatus(1);
		playerData.bonusesInBag[onePlGame::BonusEnlargeRim]--;
		infoBar.setUpdateFlag(infoBarTexts::BonusCoinNumber);
	}
	else{
		sounds.playSound(onePlGame::SoundCantUseBonus);
	}
}

void LevelComponents::setBallIsPower(PlayerData& playerData)
{
	if( false == ball.isBallPowerful && playerData.bonusesInBag[onePlGame::BonusPowerBall] >= 1 )
	{
		sounds.playSound(onePlGame::SoundImpactWithDamage);
		ball.isBallPowerful = true;
		playerData.bonusesInBag[onePlGame::BonusPowerBall]--;
		infoBar.setUpdateFlag(infoBarTexts::BonusCoinNumber);
	}
	else{
		sounds.playSound(onePlGame::SoundCantUseBonus);
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
		sounds.playSound(onePlGame::SoundCantUseBonus);
	}
}

void LevelComponents::testBallCollisionWithRims()
{
	ball.testCollisionWithRims(rims, sounds);
}

void LevelComponents::updateTracingCrossPosition(const LevelInputs& levelInputs)
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
	if( ball.canDetectCollisionSince )
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
		antarcticPackage.pinguinsData.makePinguinsBounceWithRims(rim, sounds);
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
		antarcticPackage.pinguinsData.activeOnePinguin();
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