#include "contexts/onePlayerGame/levelComponents/freeFunctions/ballWithGridCollisions.h"
#include "contexts/onePlayerGame/levelComponents/global/globalGameObject.h"
#include "crossLevel/playerData.h"
#include "contexts/onePlayerGame/levelComponents/freeFunctions/ballWithPinguinBrickCollisions.h"
#include "contexts/onePlayerGame/levelComponents/freeFunctions/withSkullBrickBallCollision.h"
#include "consts/onePlayerGridConsts.h"
#include "customTypes/positionTypes.h"
#include "consts/constexprScreen.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/constPaths.h"

void gridCol::collideBallWithBricksMatrix(LevelComponents& comp, const Offset& brickCoord, BallThings& ball, PlayerData& playerData)
{
	switch( comp.grid(brickCoord.x, brickCoord.y).index )
	{
		case BRICKS::INDEX::GEN_BRICK:
			gridCol::collideWithGenericBrick(comp, comp.grid(brickCoord.x, brickCoord.y), playerData);
			break;
		case BRICKS::INDEX::RICH_BRICK:
			gridCol::collideWithRichBrick(comp, brickCoord, playerData);
			break;
		case BRICKS::INDEX::BONUS_COIN:
			gridCol::collisionWithBonusCoinBrick(comp, comp.grid(brickCoord.x, brickCoord.y), playerData);
			break;
		case BRICKS::INDEX::GIFT_BRICK:
			gridCol::collideWithGiftBrick(comp, comp.grid(brickCoord.x, brickCoord.y), playerData, brickCoord);
			break;
		case BRICKS::INDEX::TEN_POINTS:
			collisionWithTenPointsBrick(comp, comp.grid(brickCoord.x, brickCoord.y), ball, playerData);
			break;
		case BRICKS::INDEX::SOLID:
			comp.sounds.playSound(onePlGame::SND_COL_BALL_W_BACKGRND);
			break;
		case BRICKS::INDEX::ICE_BRICKS:
			iceCol::collideWithIceBricks(comp, brickCoord, ball.isBallPowerful, playerData);
			break;
		case BRICKS::INDEX::HELL_BRICKS:
			hellCol::collideWithHellBricks(comp, brickCoord, ball.isBallPowerful, playerData);
			break;
	}
}


void gridCol::collideWithGenericBrick(LevelComponents& comp, BrickData& brickData, PlayerData& playerData)
{
	comp.sounds.playSound(onePlGame::SND_COL_BALL_W_BACKGRND);
	if( comp.ball.isBallPowerful )
	{
		playerData.score += brickData.property * 10;
		brickData.index = BRICKS::INDEX::NO_BRICK;
		brickData.property = 0;
	}
	else{
		if( brickData.property > 0 )
		{
			playerData.score += 10;
			brickData.property--;
		}
		else{
			playerData.score += 10;
			brickData.index = BRICKS::INDEX::NO_BRICK;
			brickData.property = 0;
		}
	}
}

void gridCol::collideWithRichBrick(LevelComponents& comp, const Offset& brickCoord, PlayerData& playerData)
{
	switch( comp.grid(brickCoord.x, brickCoord.y).property )
	{
		case BRICKS::RICH::STEEL_LEFT:
			collideWithLeftRichBrick(comp, brickCoord, BRICKS::RICH::STEEL_VALUE, playerData);
			break;
		case BRICKS::RICH::STEEL_RIGHT:
			collideWithRightRichBrick(comp, brickCoord, BRICKS::RICH::STEEL_VALUE, playerData);
			break;
		case BRICKS::RICH::BRONZE_LEFT:
			collideWithLeftRichBrick(comp, brickCoord, BRICKS::RICH::BRONZE_VALUE, playerData);
			break;
		case BRICKS::RICH::BRONZE_RIGHT:
			collideWithRightRichBrick(comp, brickCoord, BRICKS::RICH::BRONZE_VALUE, playerData);
			break;
		case BRICKS::RICH::SILVER_LEFT:
			collideWithLeftRichBrick(comp, brickCoord, BRICKS::RICH::SILVER_VALUE, playerData);
			break;
		case BRICKS::RICH::SILVER_RIGHT:
			collideWithRightRichBrick(comp, brickCoord, BRICKS::RICH::SILVER_VALUE, playerData);
			break;
		case BRICKS::RICH::GOLD_LEFT:
			collideWithLeftRichBrick(comp, brickCoord, BRICKS::RICH::GOLD_VALUE, playerData);
			break;
		case BRICKS::RICH::GOLD_RIGHT:
			collideWithRightRichBrick(comp, brickCoord, BRICKS::RICH::GOLD_VALUE, playerData);
			break;
	}
}

void gridCol::collideWithLeftRichBrick(LevelComponents& comp, const Offset& brickCoord, int brickValue, PlayerData& playerData)
{
	comp.sounds.playSound(onePlGame::SND_COL_BALL_W_BACKGRND);
	assert( brickValue == 50 || brickValue == 100 || brickValue == 200 || brickValue == 400 );
	playerData.score += brickValue;
	destroyRichBrick(comp, brickCoord);
	destroyRichBrick(comp, combineOffset(brickCoord, Offset{1, 0}));
}

void gridCol::collideWithRightRichBrick(LevelComponents& comp, const Offset& brickCoord, int brickValue, PlayerData& playerData)
{
	comp.sounds.playSound(onePlGame::SND_COL_BALL_W_BACKGRND);
	assert( brickValue == 50 || brickValue == 100 || brickValue == 200 || brickValue == 400 );
	playerData.score += brickValue;
	destroyRichBrick(comp, brickCoord);
	destroyRichBrick(comp, combineOffset(brickCoord, Offset{-1, 0}));
}

void gridCol::destroyRichBrick(LevelComponents& comp, const Offset& brickCoord)
{
	if( comp.grid.isSignedInsideBoundaries(brickCoord.x, brickCoord.y) )
	{
		comp.grid(brickCoord.x, brickCoord.y).index = BRICKS::INDEX::NO_BRICK;
	}
}

void gridCol::collisionWithBonusCoinBrick(LevelComponents& comp, BrickData& brickData, PlayerData& playerData)
{
	comp.sounds.playSound(onePlGame::SND_CREATE_NEW_COIN);
	brickData.index = BRICKS::INDEX::NO_BRICK;
	playerData.score += 10;
	playerData.bonusCoinsNumber++;
}

void gridCol::collideWithGiftBrick(LevelComponents& comp, BrickData& brickData, PlayerData& playerData, const Offset& brickCoord)
{
	comp.sounds.playSound(onePlGame::SND_CREATE_NEW_COIN);
	playerData.score += 10;
	comp.fallingBonuses.addNewFallingBonus(brickData.property, 
								AccurCoords{static_cast<double>(brickCoord.x * SQR_SIZE), 
											static_cast<double>(SQR_SIZE * (brickCoord.y + 1)) }, 
											FALL_BONUSES_SPEED, Offset{0, 1} );
	brickData.index = BRICKS::INDEX::NO_BRICK;
}

void gridCol::collisionWithTenPointsBrick(LevelComponents& comp, BrickData& brickData, BallThings& ball, PlayerData& playerData)
{
	if( ball.isBallPowerful )//Delete brick because of powerfull ball and add a bonus coin if with shop campaign/race or add big bonus of 100 pts
	{
		comp.sounds.playSound(onePlGame::SND_CREATE_NEW_COIN);
		brickData.property = TENPTS_BRICK_NUM - 1;
		brickData.index = BRICKS::INDEX::NO_BRICK;
		gridCol::tenPointsBrickDestruction(playerData, gridCol::getPointsFrom10PtsBrickProperty(brickData.property), 100);
	}
	else{
		if( brickData.property + 2 < TENPTS_BRICK_NUM )//Damage a little more the 10 pts brick but not deleting it
		{
			comp.sounds.playSound(onePlGame::SND_COL_RACK_W_COIN);
			playerData.score += 10;
			brickData.property += 1;
		}
		else{//Delete 10 pts brick (it has reached its maximum damage), and add a bonus coin if with shop campaign/race or add big bonus of 100 pts
			comp.sounds.playSound(onePlGame::SND_CREATE_NEW_COIN);
			brickData.property += 1;
			brickData.index = BRICKS::INDEX::NO_BRICK;
			gridCol::tenPointsBrickDestruction(playerData, 10, 100);
		}
	}
}

int gridCol::getPointsFrom10PtsBrickProperty(int brickProperty)
{
	return -10 * brickProperty + (static_cast<int>(TENPTS_BRICK_NUM) - 1) * 10;
}

void gridCol::tenPointsBrickDestruction(PlayerData& playerData, int addToScore, int bigBonusIfAny)
{
	switch( playerData.gameType )
	{
		case onePlGame::CAMPAIGN_WITH_SHOP:
			playerData.score += addToScore;
			playerData.bonusCoinsNumber++;
			break;
		case onePlGame::CAMPAIGN_NO_SHOP:
			playerData.score += addToScore;
			playerData.score += bigBonusIfAny;
			break;
	}
}