#include "demosLoadingAndSaving/saving/saveDemoFile.h"
#include "levelComponents/demosObjects/demoMainPackage.h"
#include "consts/singlePlayerDemoConsts.h"
#include "exceptions/writeErrorExcept.h"
#include "consts/onePlayerGridConsts.h"
#include <fstream>

void saveDemo::openGameDemoFile(const fs::path& demoFilePath, const demos::MainPackage& mainPackage)
{
	if( std::ofstream demoFile{ demoFilePath } )
	{
		demoFile << std::fixed << std::setprecision(6);
		try{
			saveDemo::saveData(demoFilePath, demoFile, mainPackage);
		}
		catch( WriteError& e )
		{
			throw e;
		}
	}
	else{
		throw WriteError{"Error: couldn't open '" + demoFilePath.string() + "' in order to save demo data."};
	}
}

void saveDemo::saveData(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::MainPackage& mainPackage)
{
	saveDemo::saveCampaignType(demoFilePath, demoFile, mainPackage.startingData);
	saveDemo::saveSkillLevel(demoFilePath, demoFile, mainPackage.startingData);
	saveDemo::savePlayerLives(demoFilePath, demoFile, mainPackage.startingData);
	saveDemo::saveRacketSize(demoFilePath, demoFile, mainPackage.startingData);
	saveDemo::saveScore(demoFilePath, demoFile, mainPackage.startingData);
	saveDemo::saveRacketSpeed(demoFilePath, demoFile, mainPackage.startingData);
	saveDemo::saveBonusCoinNumber(demoFilePath, demoFile, mainPackage.startingData);
	saveDemo::saveRimsStartState(demoFilePath, demoFile, mainPackage.startingData);
	saveDemo::saveGivenBonusInBag(demoFilePath, demoFile, mainPackage.startingData);
	saveDemo::saveSquareSize(demoFilePath, demoFile, mainPackage.startingData);
	saveDemo::saveActionEvent(demoFilePath, demoFile, mainPackage.inputData, "player input events", onePlGame::demosFileIndex::ActionEvent);
	saveDemo::saveActionEvent(demoFilePath, demoFile, mainPackage.quitLevelEvent, "player quit level events", onePlGame::demosFileIndex::QuitLevelEvent);
	saveDemo::savePositionStackEvent(demoFilePath, demoFile, mainPackage.traceCrossPosition, "demo trace cross position", onePlGame::demosFileIndex::TraceCrossPosition);
	saveDemo::savePositionStackEvent(demoFilePath, demoFile, mainPackage.racketPosition, "demo racket positions", onePlGame::demosFileIndex::RacketPosition);
	saveDemo::savePositionStackEvent(demoFilePath, demoFile, mainPackage.ballPosition, "demo ball positions", onePlGame::demosFileIndex::BallPosition);
	saveDemo::saveBrickDestructions(demoFilePath, demoFile, mainPackage.brickDestruction);
	saveDemo::saveSoundEvents(demoFilePath, demoFile, mainPackage.soundsStack, "common sounds events", onePlGame::demosFileIndex::CommonSoundEvent);
	saveDemo::saveTaggedPositions(demoFilePath, demoFile, mainPackage.antarcticDemoPackage.pinguinsPositions, "pinguins positions", onePlGame::demosFileIndex::PinguinsPosition);
	saveDemo::saveTaggedDirections(demoFilePath, demoFile, mainPackage.antarcticDemoPackage.pinguinsDirection, "pinguins directions", onePlGame::demosFileIndex::PinguinsDirection);
	saveDemo::saveActionEvent(demoFilePath, demoFile, mainPackage.antarcticDemoPackage.pinguinsCreateAndDestroy, "pinguins create and destroy", onePlGame::demosFileIndex::PinguinsCreateAndDestroy);
	saveDemo::saveSoundEvents(demoFilePath, demoFile, mainPackage.antarcticDemoPackage.pinguinsQuacks, "pinguins quack sound event", onePlGame::demosFileIndex::PinguinQuackSoundEvent);
	saveDemo::saveMatrixSize(demoFilePath, demoFile, mainPackage.grid);
	saveDemo::saveMatrixElements(demoFilePath, demoFile, mainPackage.grid);
}

void saveDemo::saveCampaignType(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::StartingData& startingData)
{
	if( ! ( demoFile << onePlGame::demosFileIndex::CampaignType << " " << startingData.campaignType << '\n' ) )
	{
		saveDemo::throwWriteErrorExcept(demoFilePath, "campaign type");
	}
}

void saveDemo::saveSkillLevel(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::StartingData& startingData)
{
	if( ! ( demoFile << onePlGame::demosFileIndex::SkillLevel << " " << startingData.skillLevel << '\n' ) )
	{
		saveDemo::throwWriteErrorExcept(demoFilePath, "skill level");
	}
}
	
void saveDemo::savePlayerLives(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::StartingData& startingData)
{
	if( ! ( demoFile << onePlGame::demosFileIndex::PlayerLives << " " << startingData.playerLives << '\n' ) )
	{
		saveDemo::throwWriteErrorExcept(demoFilePath, "player lives");
	}
}
	
void saveDemo::saveRacketSize(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::StartingData& startingData)
{
	if( ! ( demoFile << onePlGame::demosFileIndex::RacketSize << " " << startingData.racketSize << '\n' ) )
	{
		saveDemo::throwWriteErrorExcept(demoFilePath, "racket size");
	}
}
	
void saveDemo::saveScore(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::StartingData& startingData)
{
	if( ! ( demoFile << onePlGame::demosFileIndex::Score << " " << startingData.score << '\n' ) )
	{
		saveDemo::throwWriteErrorExcept(demoFilePath, "player score");
	}
}
	
void saveDemo::saveRacketSpeed(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::StartingData& startingData)
{
	if( ! ( demoFile << onePlGame::demosFileIndex::RacketSpeed << " " << startingData.racketSpeed << '\n' ) )
	{
		saveDemo::throwWriteErrorExcept(demoFilePath, "racket speed");
	}
}
	
void saveDemo::saveBonusCoinNumber(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::StartingData& startingData)
{
	if( ! ( demoFile << onePlGame::demosFileIndex::BonusCoinNumber << " " << startingData.bonusCoinsNumber << '\n' ) )
	{
		saveDemo::throwWriteErrorExcept(demoFilePath, "bonusCoinsNumber");
	}
}
	
void saveDemo::saveRimsStartState(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::StartingData& startingData)
{
	if( ! ( demoFile << onePlGame::demosFileIndex::RimStartState << " " << startingData.rimsStartState << '\n' ) )
	{
		saveDemo::throwWriteErrorExcept(demoFilePath, "rims start state");
	}
}
	
void saveDemo::saveGivenBonusInBag(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::StartingData& startingData)
{
	for( std::size_t i{0} ; i < startingData.bonusesInBag.size() ; ++i )
	{
		if( ! ( demoFile << onePlGame::demosFileIndex::GivenBonusInBag << " " << i << " " << startingData.bonusesInBag[i] << '\n' ) )
		{
			saveDemo::throwWriteErrorExcept(demoFilePath, "bonuses in bag number " + std::to_string(i) );
		}
	}
}
	
void saveDemo::saveSquareSize(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::StartingData& startingData)
{
	if( ! ( demoFile << onePlGame::demosFileIndex::SquareSizeAtSaving << " " <<  startingData.squareSizeAtSaving << '\n' ) )
	{
		saveDemo::throwWriteErrorExcept(demoFilePath, "square size at demo recording time");
	}
}

void saveDemo::saveActionEvent(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::Stack< demos::ActionData >& inputEvents, const std::string& itemType, unsigned indexEnum)
{
	if( inputEvents.getCommandsNumber() > 0 )
	{
		for( std::vector< demos::ActionData >::const_reverse_iterator it = inputEvents.crbegin() ; it != inputEvents.crend() ; ++it )
		{
			if( ! ( demoFile << indexEnum << " " << static_cast<long int>(it->delay.count()) << " " << it->funcEnum << " " << it->actionState << '\n' ) )
			{
				saveDemo::throwWriteErrorExcept(demoFilePath, itemType);
			}
		}
	}
}
 
void saveDemo::savePositionStackEvent(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::Stack< demos::PositionStackData >& positionsStack, const std::string& itemType, unsigned indexEnum)
{
	if( positionsStack.getCommandsNumber() > 0 )
	{
		for( std::vector< demos::PositionStackData >::const_reverse_iterator it = positionsStack.crbegin() ; it != positionsStack.crend() ; ++it )
		{
			if( ! ( demoFile << indexEnum << " " << static_cast<long int>(it->delay.count()) << " " << it->position.x << " " << it->position.y << '\n' ) )
			{
				saveDemo::throwWriteErrorExcept(demoFilePath, itemType);
			}
		}
	}
}

void saveDemo::saveBrickDestructions(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::Stack< demos::Matrix2DAction >& bricksDestruction)
{
	if( bricksDestruction.getCommandsNumber() > 0 )
	{
		for( std::vector< demos::Matrix2DAction >::const_reverse_iterator it = bricksDestruction.crbegin() ; it != bricksDestruction.crend() ; ++it )
		{
			if( ! ( demoFile << onePlGame::demosFileIndex::BrickDestruction << " " << static_cast<long int>(it->delay.count()) << " " 
						<< it->coords.width << " " << it->coords.height << " " << it->brickData.index << " " << it->brickData.property << '\n' ) )
			{
				saveDemo::throwWriteErrorExcept(demoFilePath, "brick destruction");
			}
		}
	}
}

void saveDemo::saveSoundEvents(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::Stack< demos::SoundStackData >& soundsEvent, const std::string& itemType, unsigned indexEnum)
{
	if( soundsEvent.getCommandsNumber() > 0 )
	{
		for( std::vector< demos::SoundStackData >::const_reverse_iterator it = soundsEvent.crbegin() ; it != soundsEvent.crend() ; ++it )
		{
			if( ! ( demoFile << indexEnum << " " << static_cast<long int>( it->delay.count() ) << " " << it->soundEnum << " " << it->groupTag << '\n' ) )
			{
				saveDemo::throwWriteErrorExcept(demoFilePath, itemType);
			}
		}
	}
}

void saveDemo::saveTaggedPositions(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::Stack< demos::TaggedPositionStackData >& taggedPositions, const std::string& itemType, unsigned indexEnum)
{
	if( taggedPositions.getCommandsNumber() > 0 )
	{
		for( std::vector< demos::TaggedPositionStackData >::const_reverse_iterator it = taggedPositions.crbegin() ; it != taggedPositions.crend() ; ++it )
		{
			if( ! ( demoFile << indexEnum << " " << static_cast<long int>( it->delay.count() ) << " "
							<< it->itemTagNumber << " " << it->position.x << " " << it->position.y << '\n' ) )
			{
				saveDemo::throwWriteErrorExcept(demoFilePath, itemType);
			}
		}
	}
}

void saveDemo::saveTaggedDirections(const fs::path& demoFilePath, std::ofstream& demoFile, const demos::Stack< demos::TaggedDirectionStackData >& taggedDirections, const std::string& itemType, unsigned indexEnum)
{
	if( taggedDirections.getCommandsNumber() > 0 )
	{
		for( std::vector< demos::TaggedDirectionStackData >::const_reverse_iterator it = taggedDirections.crbegin() ; it != taggedDirections.crend() ; ++it )
		{
			if( ! ( demoFile << indexEnum << " " << static_cast<long int>( it->delay.count() ) << " " << it->itemTagNumber << " " << it->direction << '\n' ) )
			{
				saveDemo::throwWriteErrorExcept(demoFilePath, itemType);
			}
		}
	}
}

void saveDemo::saveMatrixSize(const fs::path& demoFilePath, std::ofstream& demoFile, const MatrixTemp2D< BrickData >& levelMatrix)
{
	if( ! ( demoFile << onePlGame::demosFileIndex::MatrixSize << " " << levelMatrix.width() << " " << levelMatrix.height() << '\n' ) )
	{
		saveDemo::throwWriteErrorExcept(demoFilePath, "matrixSize");
	}
}

void saveDemo::saveMatrixElements(const fs::path& demoFilePath, std::ofstream& demoFile, const MatrixTemp2D< BrickData >& levelMatrix)
{
	for( std::size_t height{0} ; height < levelMatrix.height() ; ++height )
	{
		for (std::size_t width{ 0 }; width < levelMatrix.width(); ++width)
		{
			if( levelMatrix(width, height).index != bricks::index::NoBrick )
			{
				if (!(demoFile << onePlGame::demosFileIndex::MatrixElement << " " << height << " " << width << " "
					<< levelMatrix(width, height).index << " " << levelMatrix(width, height).property << '\n'))
				{
					saveDemo::throwWriteErrorExcept(demoFilePath, "matrix element");
				}
			}
		}
	}
}

void saveDemo::throwWriteErrorExcept(const fs::path& demoFilePath, const std::string& toSaveItem)
{
	throw WriteError{"Error: couldn't write '" + toSaveItem + "' in '" + demoFilePath.string() + "' demo file."};
}
