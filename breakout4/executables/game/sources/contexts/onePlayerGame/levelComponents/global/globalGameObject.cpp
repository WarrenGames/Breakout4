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
	levelEndType{onePlGame::LEVEL_END_NO},
	fancyFont{essentials.logs.error, FANCYFONTPATH, FONT_MEDIUM_PTSIZE},
	grid{ GRID_WIDTH, GRID_HEIGHT },
	bricksTexturesLoader{essentials.logs, essentials.rndWnd},
	bricksSprites{bricksTexturesLoader},
	racket{essentials, playerData},
	ball{ essentials.logs, essentials.rndWnd, monstersNumber },
	backgroundDrawer{essentials.logs, essentials.rndWnd, onePlGame::BG_TEXTURE_PATH, GAME_SQUARES_WIDTH, GAME_SQUARES_HEIGHT},
	infoBar{essentials},
	rims{essentials, playerData.rimsStartState},
	fallingBonuses{essentials},
	sounds{essentials, onePlGame::COMMON_SNDS_FILE_PATH, onePlGame::COMMON_CHANNELS_FILE_PATH},
	traceCross{essentials},
	cheating{essentials.prefPath, ONE_PLAYER_CHEAT_FILE},
	cheatButton{essentials.logs, essentials.rndWnd, fancyFont, ":-)", GREEN_COL, WHITE_COL, GAME_SCREEN_WIDTH - SQR_SIZE, SQR_SIZE / 2, true },
	explosionsLoader{ essentials.logs, essentials.rndWnd },
	explosionsSprites{ explosionsLoader }
{
	loadMatrix(essentials.logs.error, playerData.getMatrixPath());
	fallingBonuses.reserveGiftBricksData(grid);
	if( false == ( 		ball 
					&& grid.size() == GRID_WIDTH * GRID_HEIGHT 
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
	fallingBonuses.detectCollisionWithRacket(playerData, racket, ball, rims, infoBar, sounds);
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
	antarcticPackage.pinguinsData.update(grid, racket.rect, levelInputs.getFuncState(onePlGame::INP_MOVE_LEFT), levelInputs.getFuncState(onePlGame::INP_MOVE_RIGHT), sounds);
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
	assert( bagBonusIndex < onePlGame::BONUS_MAX );
	switch( bagBonusIndex )
	{
		case onePlGame::BONUS_STICKY:
			setRacketIsSticky(playerData);
			break;
		case onePlGame::BONUS_RACKET_SPEEDUP:
			speedUpPlayerRacket(playerData);
			break;
		case onePlGame::BONUS_ENLARGE_RACKET:
			enlargePlayerRacket(playerData);
			break;
		case onePlGame::BONUS_ENLARGE_RIM:
			enlargeRims(playerData);
			break;
		case onePlGame::BONUS_POWERBALL:
			setBallIsPower(playerData);
			break;
		case onePlGame::BONUS_ONE_UP:
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
		levelEndType = onePlGame::LEVEL_END_COMPLETE;
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
	if( levelInputs.getFuncState(onePlGame::INP_MOVE_LEFT) && false == levelInputs.getFuncState(onePlGame::INP_MOVE_RIGHT) 
		&& false == somethingPreventMove )
	{
		racket.data.moveRacket(MOVE_TO_LEFT, racket.standardRacket.getWidth(racket.data.getSize()));
		racket.setRacketRect();
	}
}

void LevelComponents::moveRacketToRight(const LevelInputs& levelInputs, bool somethingPreventMove)
{
	if( levelInputs.getFuncState(onePlGame::INP_MOVE_RIGHT) && false == levelInputs.getFuncState(onePlGame::INP_MOVE_LEFT) 
		&& false == somethingPreventMove )
	{
		racket.data.moveRacket(MOVE_TO_RIGHT, racket.standardRacket.getWidth(racket.data.getSize()));
		racket.setRacketRect();
	}
}

void LevelComponents::releaseBall(LevelInputs& levelInputs)
{
	if( false == ball.isMainBallActive && levelInputs.getFuncState(onePlGame::INP_BALL_TRACE) )
	{
		const Offset ballDirectionVectors{ 	traceCross.position.x - ball.move.get_x_position(), 
											traceCross.position.y - ball.move.get_y_position()};
		ball.isMainBallActive = true;
		ball.move.setSpeed(onePlGame::BALL_STARTING_SPEED);
		giveObjectNewDirection(ball.move, ballDirectionVectors);
		levelInputs.setFuncState(onePlGame::INP_BALL_TRACE, false);
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
	if( levelEndType == onePlGame::LEVEL_END_PARTIALLY || levelEndType == onePlGame::LEVEL_END_COMPLETE || levelEndType == onePlGame::LEVEL_END_SURRENDER )
		quitGame = true;
}

void LevelComponents::setRacketIsSticky(PlayerData& playerData)
{
	if( playerData.bonusesInBag[onePlGame::BONUS_STICKY] >= 1 )
	{
		racket.glueLevel += 3;
		playerData.bonusesInBag[onePlGame::BONUS_STICKY]--;
	}
	else{
		sounds.playSound(onePlGame::SND_CANT_USE_BONUS);
	}
}

void LevelComponents::speedUpPlayerRacket(PlayerData& playerData)
{
	if( racket.data.canSpeedUp() && playerData.bonusesInBag[onePlGame::BONUS_RACKET_SPEEDUP] >= 1 )
	{
		sounds.playSound(onePlGame::SND_SPEED_MORE);
		racket.data.addToSpeed( onePlGame::RACKET_SPEED_BONUS_ADD );
		playerData.bonusesInBag[onePlGame::BONUS_RACKET_SPEEDUP]--;
		infoBar.setUpdateFlag(infoBarTexts::RACKET_SPEED);
		infoBar.setUpdateFlag(infoBarTexts::BONUS_COINS_NUM);
	}
	else{
		sounds.playSound(onePlGame::SND_CANT_USE_BONUS);
	}
}

void LevelComponents::enlargePlayerRacket(PlayerData& playerData)
{
	if( racket.data.canBeEnlarged() && playerData.bonusesInBag[onePlGame::BONUS_ENLARGE_RACKET] >= 1 )
	{
		sounds.playSound(onePlGame::SND_ENLARGE_RACKET);
		racket.data.enlarge();
		playerData.bonusesInBag[onePlGame::BONUS_ENLARGE_RACKET]--;
		infoBar.setUpdateFlag(infoBarTexts::BONUS_COINS_NUM);
	}
	else{
		sounds.playSound(onePlGame::SND_CANT_USE_BONUS);
	}
}

void LevelComponents::enlargeRims(PlayerData& playerData)
{
	if( rims.getRimsStatus() + 1 < rims::RIM_MAX && playerData.bonusesInBag[onePlGame::BONUS_ENLARGE_RIM] >= 1 )
	{
		sounds.playSound(onePlGame::SND_ENLARGE_RACKET);
		rims.changeStatus(1);
		playerData.bonusesInBag[onePlGame::BONUS_ENLARGE_RIM]--;
		infoBar.setUpdateFlag(infoBarTexts::BONUS_COINS_NUM);
	}
	else{
		sounds.playSound(onePlGame::SND_CANT_USE_BONUS);
	}
}

void LevelComponents::setBallIsPower(PlayerData& playerData)
{
	if( false == ball.isBallPowerful && playerData.bonusesInBag[onePlGame::BONUS_POWERBALL] >= 1 )
	{
		sounds.playSound(onePlGame::SND_IMPACT_W_DAMAGE);
		ball.isBallPowerful = true;
		playerData.bonusesInBag[onePlGame::BONUS_POWERBALL]--;
		infoBar.setUpdateFlag(infoBarTexts::BONUS_COINS_NUM);
	}
	else{
		sounds.playSound(onePlGame::SND_CANT_USE_BONUS);
	}
}

void LevelComponents::addOneBallLiveToPlayer(PlayerData& playerData)
{
	if( playerData.bonusesInBag[onePlGame::BONUS_ONE_UP] >= 1 )
	{
		playerData.playerLives++;
		playerData.bonusesInBag[onePlGame::BONUS_ONE_UP]--;
		infoBar.setUpdateFlag(infoBarTexts::BALLS_IN_BAG);
		infoBar.setUpdateFlag(infoBarTexts::BONUS_COINS_NUM);
	}
	else{
		sounds.playSound(onePlGame::SND_CANT_USE_BONUS);
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
		if( onePlGame::CROSS_DEVICE_IS_MOUSE == levelInputs.getCrossMoveDeviceType() )
		{
			traceCross.position = levelInputs.getMousePosition();
			traceCross.position.x -= TRACE_CROSS_OFFSET;
			traceCross.position.y -= TRACE_CROSS_OFFSET;
		}
		else if( onePlGame::CROSS_DEVICE_IS_JOYSTICK == levelInputs.getCrossMoveDeviceType() )
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