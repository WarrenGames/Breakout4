#include "contexts/onePlayerGame/levelComponents/fallingBonuses/fallingBonuses.h"
#include "types/essentialsStruct.h"
#include "crossLevel/playerData.h"
#include "contexts/onePlayerGame/levelComponents/onePlayerRacket/onePlayerRacket.h"
#include "contexts/onePlayerGame/levelComponents/balls/ballsThings.h"
#include "contexts/onePlayerGame/levelComponents/rims/playerRims.h"
#include "contexts/onePlayerGame/levelComponents/infoBar/infoBar.h"
#include "matrices/matrix2D.h"
#include "types/brickData.h"
#include "generic/sounds/soundHandler.h"
#include "consts/rimsConsts.h"
#include "consts/constexprScreen.h"
#include "consts/onePlayerLevelConsts.h"
#include <algorithm>
#include <fstream>
#include <cassert>

constexpr char TexturesDirectory[] = "textures/vignettes/onePlayerIcons/fallingBonuses/";

FallingBonusData::FallingBonusData(std::size_t bonusIndex, const AccurCoords& startCoords, double newSpeed, const Offset& newDirVectors):
	bonusType{bonusIndex},
	objectMove{startCoords, newSpeed, newDirVectors}
{
	
}

FallingBonuses::FallingBonuses(Essentials& essentials):
	isLoadingPerfect{true},
	haveBonusesMoved{true}
{
	loadTexture(essentials, "powerBallIcon.png");
	loadTexture(essentials, "speedUpIcon.png");
	loadTexture(essentials, "slowDownRacketIcon.png");
	loadTexture(essentials, "rimIcon.png");
	loadTexture(essentials, "rimIcon.png");
	loadTexture(essentials, "enlargeRacketIcon.png");
	loadTexture(essentials, "shrinkRacketIcon.png");
	loadTexture(essentials, "oneUpIcon.png");
	loadTexture(essentials, "glueIcon.png");
	checkEverythingIsLoaded(essentials);
}

void FallingBonuses::checkEverythingIsLoaded(Essentials& essentials)
{
	if( bonusesTextures.size() == bricks::bonuses::Max )
	{
		for( auto const &texture : bonusesTextures )
		{
			if( ! texture.texture )
			{
				isLoadingPerfect = false;
				essentials.logs.error << "Error: something is wrong with the falling bonuses textures, can't carry on.\n";
			}
		}
	}
	else{
		isLoadingPerfect = false;
		essentials.logs.error << "Error: something is wrong with the falling bonuses textures, can't carry on.\n";
	}
}

void FallingBonuses::loadTexture(Essentials& essentials, const std::string& texturePath)
{
	bonusesTextures.emplace_back(TextureCombo{essentials.logs, essentials.rndWnd, TexturesDirectory + texturePath});
}

void FallingBonuses::reserveGiftBricksData(const MatrixTemp2D< BrickData >& levelMatrix)
{
	bonusesData.reserve( std::count_if(std::cbegin(levelMatrix), std::cend(levelMatrix), [](auto &data){ return bricks::index::GiftBrick == data.index; } ) );
}

FallingBonuses::operator bool() const
{
	return isLoadingPerfect;
}

void FallingBonuses::drawBonuses(Essentials& essentials)
{
	if( false == bonusesData.empty() )
	{
		for( auto const &bonus : bonusesData )
		{
			if( bonus )
			{
				assert( bonus->bonusType < bonusesTextures.size() );
				bonusesTextures[bonus->bonusType].draw(essentials.rndWnd, bonus->objectMove.get_x_position(), bonus->objectMove.get_y_position() );
			}
		}
	}
}

void FallingBonuses::update()
{
	if( false == bonusesData.empty() )
	{
		if( moveBonuses.hasTimeElapsed( std::chrono::milliseconds{10} ) )
		{
			for( auto &bonus : bonusesData )
			{
				if( bonus ){
					bonus->objectMove.moveObject();
				}
			}
			moveBonuses.joinTimePoints();
			haveBonusesMoved = true;
		}
	}
}

void FallingBonuses::addNewFallingBonus(std::size_t bonusIndex, const AccurCoords& startCoords, double newSpeed, const Offset& newDirVectors)
{
	bonusesData.emplace_back( std::make_unique<FallingBonusData>(bonusIndex, startCoords, newSpeed, newDirVectors) );
}

void FallingBonuses::detectCollisionWithRacket(PlayerData& playerData, OnePlayerRacket& racket, OnePlayerRims& rims, InfoBar& infoBar, const SoundHandler& sounds)
{
	if( false == bonusesData.empty() && haveBonusesMoved )
	{
		for( auto &bonus : bonusesData )
		{
			if( bonus )
			{
				if( bonus->objectMove.get_x_position() + SQR_SIZE >= racket.rect.x
					&& bonus->objectMove.get_x_position() < racket.rect.x + racket.rect.w
					&& bonus->objectMove.get_y_position() + SQR_SIZE >= racket.rect.y 
					&& bonus->objectMove.get_y_position() < racket.rect.y + racket.rect.h )
				{
					applyBonusModificationToPlayer(bonus, playerData, racket, rims, sounds);
					infoBar.updateEverything();
				}
			}
		}
		haveBonusesMoved = false;
	}
}

void FallingBonuses::applyBonusModificationToPlayer(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData, OnePlayerRacket& racket, OnePlayerRims& rims, const SoundHandler& sounds)
{
	if( bonus )
	{
		switch( bonus->bonusType )
		{
			case bricks::bonuses::BigBall:
				improveBall(bonus, playerData, sounds);
				break;
			case bricks::bonuses::SpeedUp:
				speedUpRacket(bonus, playerData, sounds);
				break;
			case bricks::bonuses::SpeedDown:
				speedDownRacket(bonus, playerData, racket, sounds);
				break;
			case bricks::bonuses::ENLARGE_RIMS:
				enlargeRims(bonus, playerData, sounds);
				break;
			case bricks::bonuses::SHRINK_RIMS:
				shrinkRims(bonus, rims, sounds);
				break;
			case bricks::bonuses::ENLARGE_RACKET:
				enlargeRacket(bonus, playerData, sounds);
				break;
			case bricks::bonuses::SHRINK_RACKET:
				shrinkRacket(bonus, racket, sounds);
				break;
			case bricks::bonuses::ONE_UP:
				addOneLife(bonus, playerData, sounds);
				break;
			case bricks::bonuses::GLUE:
				glueRacket(bonus, playerData);
				break;
			default:
				assert( false && "Error: bad 'bonusType' value." );
				break;
		}
	}
}

void FallingBonuses::improveBall(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData, const SoundHandler& sounds)
{
	sounds.playSound(onePlGame::SoundAddOneUp);
	playerData.addBonusToBag(onePlGame::BonusPowerBall);
	bonus.reset();
}

void FallingBonuses::speedUpRacket(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData, const SoundHandler& sounds)
{
	sounds.playSound(onePlGame::SoundSpeedUp);
	playerData.addBonusToBag(onePlGame::BonusRacketSpeedUp);
	bonus.reset();
}

void FallingBonuses::speedDownRacket(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData, OnePlayerRacket& racket, const SoundHandler& sounds)
{
	if( racket.data.getSpeed() >= 2.1 )
	{
		sounds.playSound(onePlGame::SoundSpeedDown);
		racket.data.addToSpeed(-0.1);
		playerData.racketSpeed -= 0.1;
	}
	bonus.reset();
}

void FallingBonuses::enlargeRims(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData, const SoundHandler& sounds)
{
	sounds.playSound(onePlGame::SoundEnlargeRacket);
	playerData.addBonusToBag(onePlGame::BonusEnlargeRim);
	bonus.reset();
}

void FallingBonuses::shrinkRims(std::unique_ptr< FallingBonusData >& bonus, OnePlayerRims& rims, const SoundHandler& sounds)
{
	if( rims.getRimsStatus() >= 0 )
	{
		sounds.playSound(onePlGame::SoundShrinkRacket);
		rims.changeStatus(-1);
	}
	bonus.reset();
}

void FallingBonuses::enlargeRacket(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData, const SoundHandler& sounds)
{
	sounds.playSound(onePlGame::SoundEnlargeRacket);
	playerData.addBonusToBag(onePlGame::BonusEnlargeRacket);
	bonus.reset();
}

void FallingBonuses::shrinkRacket(std::unique_ptr< FallingBonusData >& bonus, OnePlayerRacket& racket, const SoundHandler& sounds)
{
	if( racket.data.getSize() > 0 )
	{
		sounds.playSound(onePlGame::SoundShrinkRacket);
		racket.data.modifySize(-1);
	}
	bonus.reset();
}

void FallingBonuses::addOneLife(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData, const SoundHandler& sounds)
{
	sounds.playSound(onePlGame::SoundAddOneUp);
	playerData.addBonusToBag(onePlGame::BonusOneMoreBallLive);
	bonus.reset();
}

void FallingBonuses::glueRacket(std::unique_ptr< FallingBonusData >& bonus, PlayerData& playerData)
{
	playerData.addBonusToBag(onePlGame::BonusStickyRacket);
	bonus.reset();
}