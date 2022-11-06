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
		case bricks::index::GenericBrick:
			gridCol::collideWithGenericBrick(comp, comp.grid(brickCoord.x, brickCoord.y), playerData);
			break;
		case bricks::index::RichBrick:
			gridCol::collideWithRichBrick(comp, brickCoord, playerData);
			break;
		case bricks::index::BonusCoin:
			gridCol::collisionWithBonusCoinBrick(comp, comp.grid(brickCoord.x, brickCoord.y), playerData);
			break;
		case bricks::index::GiftBrick:
			gridCol::collideWithGiftBrick(comp, comp.grid(brickCoord.x, brickCoord.y), playerData, brickCoord);
			break;
		case bricks::index::TenPointsBrick:
			collisionWithTenPointsBrick(comp, comp.grid(brickCoord.x, brickCoord.y), ball, playerData);
			break;
		case bricks::index::SolidBrick:
			comp.sounds.playSound(onePlGame::SoundBallWBgCollision);
			break;
		case bricks::index::IceBrick:
			iceCol::collideWithIceBricks(comp, brickCoord, ball.isBallPowerful, playerData);
			break;
		case bricks::index::HellBricks:
			hellCol::collideWithHellBricks(comp, brickCoord, ball.isBallPowerful, playerData);
			break;
	}
}


void gridCol::collideWithGenericBrick(LevelComponents& comp, BrickData& brickData, PlayerData& playerData)
{
	comp.sounds.playSound(onePlGame::SoundBallWBgCollision);
	if( comp.ball.isBallPowerful )
	{
		playerData.score += brickData.property * 10;
		brickData.index = bricks::index::NoBrick;
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
			brickData.index = bricks::index::NoBrick;
			brickData.property = 0;
		}
	}
}

void gridCol::collideWithRichBrick(LevelComponents& comp, const Offset& brickCoord, PlayerData& playerData)
{
	switch( comp.grid(brickCoord.x, brickCoord.y).property )
	{
		case bricks::RichBrick::SteelLeft:
			collideWithLeftRichBrick(comp, brickCoord, bricks::RichBrick::SteelValue, playerData);
			break;
		case bricks::RichBrick::SteelRight:
			collideWithRightRichBrick(comp, brickCoord, bricks::RichBrick::SteelValue, playerData);
			break;
		case bricks::RichBrick::BronzeLeft:
			collideWithLeftRichBrick(comp, brickCoord, bricks::RichBrick::BronzeValue, playerData);
			break;
		case bricks::RichBrick::BronzeRight:
			collideWithRightRichBrick(comp, brickCoord, bricks::RichBrick::BronzeValue, playerData);
			break;
		case bricks::RichBrick::SilverLeft:
			collideWithLeftRichBrick(comp, brickCoord, bricks::RichBrick::SilverValue, playerData);
			break;
		case bricks::RichBrick::SilverRight:
			collideWithRightRichBrick(comp, brickCoord, bricks::RichBrick::SilverValue, playerData);
			break;
		case bricks::RichBrick::GoldLeft:
			collideWithLeftRichBrick(comp, brickCoord, bricks::RichBrick::GoldValue, playerData);
			break;
		case bricks::RichBrick::GoldRight:
			collideWithRightRichBrick(comp, brickCoord, bricks::RichBrick::GoldValue, playerData);
			break;
	}
}

void gridCol::collideWithLeftRichBrick(LevelComponents& comp, const Offset& brickCoord, int brickValue, PlayerData& playerData)
{
	comp.sounds.playSound(onePlGame::SoundBallWBgCollision);
	assert( brickValue == 50 || brickValue == 100 || brickValue == 200 || brickValue == 400 );
	playerData.score += brickValue;
	destroyRichBrick(comp, brickCoord);
	destroyRichBrick(comp, combineOffset(brickCoord, Offset{1, 0}));
}

void gridCol::collideWithRightRichBrick(LevelComponents& comp, const Offset& brickCoord, int brickValue, PlayerData& playerData)
{
	comp.sounds.playSound(onePlGame::SoundBallWBgCollision);
	assert( brickValue == 50 || brickValue == 100 || brickValue == 200 || brickValue == 400 );
	playerData.score += brickValue;
	destroyRichBrick(comp, brickCoord);
	destroyRichBrick(comp, combineOffset(brickCoord, Offset{-1, 0}));
}

void gridCol::destroyRichBrick(LevelComponents& comp, const Offset& brickCoord)
{
	if( comp.grid.isSignedInsideBoundaries(brickCoord.x, brickCoord.y) )
	{
		comp.grid(brickCoord.x, brickCoord.y).index = bricks::index::NoBrick;
	}
}

void gridCol::collisionWithBonusCoinBrick(LevelComponents& comp, BrickData& brickData, PlayerData& playerData)
{
	comp.sounds.playSound(onePlGame::SoundCreateNewCoin);
	brickData.index = bricks::index::NoBrick;
	playerData.score += 10;
	playerData.bonusCoinsNumber++;
}

void gridCol::collideWithGiftBrick(LevelComponents& comp, BrickData& brickData, PlayerData& playerData, const Offset& brickCoord)
{
	comp.sounds.playSound(onePlGame::SoundCreateNewCoin);
	playerData.score += 10;
	comp.fallingBonuses.addNewFallingBonus(brickData.property, 
								AccurCoords{static_cast<double>(brickCoord.x * SQR_SIZE), 
											static_cast<double>(SQR_SIZE * (brickCoord.y + 1)) }, 
											FallBonusesSpeed, Offset{0, 1} );
	brickData.index = bricks::index::NoBrick;
}

void gridCol::collisionWithTenPointsBrick(LevelComponents& comp, BrickData& brickData, BallThings& ball, PlayerData& playerData)
{
	if( ball.isBallPowerful )//Delete brick because of powerfull ball and add a bonus coin if with shop campaign/race or add big bonus of 100 pts
	{
		comp.sounds.playSound(onePlGame::SoundCreateNewCoin);
		brickData.property = TenPointsBrickStateNumber - 1;
		brickData.index = bricks::index::NoBrick;
		gridCol::tenPointsBrickDestruction(playerData, gridCol::getPointsFrom10PtsBrickProperty(brickData.property), 100);
	}
	else{
		if( brickData.property + 2 < TenPointsBrickStateNumber )//Damage a little more the 10 pts brick but not deleting it
		{
			comp.sounds.playSound(onePlGame::SoundRacketWithCoinCol);
			playerData.score += 10;
			brickData.property += 1;
		}
		else{//Delete 10 pts brick (it has reached its maximum damage), and add a bonus coin if with shop campaign/race or add big bonus of 100 pts
			comp.sounds.playSound(onePlGame::SoundCreateNewCoin);
			brickData.property += 1;
			brickData.index = bricks::index::NoBrick;
			gridCol::tenPointsBrickDestruction(playerData, 10, 100);
		}
	}
}

int gridCol::getPointsFrom10PtsBrickProperty(int brickProperty)
{
	return -10 * brickProperty + (static_cast<int>(TenPointsBrickStateNumber) - 1) * 10;
}

void gridCol::tenPointsBrickDestruction(PlayerData& playerData, int addToScore, int bigBonusIfAny)
{
	switch( playerData.gameType )
	{
		case onePlGame::CampaignWithShop:
			playerData.score += addToScore;
			playerData.bonusCoinsNumber++;
			break;
		case onePlGame::CampaignNoShop:
			playerData.score += addToScore;
			playerData.score += bigBonusIfAny;
			break;
	}
}