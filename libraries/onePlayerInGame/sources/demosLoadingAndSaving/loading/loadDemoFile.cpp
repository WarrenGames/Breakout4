#include "demosLoadingAndSaving/loading/loadDemoFile.h"
#include "levelComponents/demosObjects/demoMainPackage.h"
#include "crossLevel/playerData.h"
#include "exceptions/readErrorExcept.h"
#include "consts/singlePlayerDemoConsts.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/onePlayerBonusesConsts.h"
#include "consts/rimsConsts.h"
#include "consts/constexprScreen.h"
#include <fstream>

void loadDemo::openFile(const fs::path& demoFilePath, demos::MainPackage& demosMainPackage, PlayerData& playerData)
{
	if( std::ifstream demoFile{ demoFilePath } )
	{
		try
		{
			loadDemo::readFileLines(demoFile, demoFilePath, demosMainPackage, playerData);
			demosMainPackage.useLegacyTransformsIfAny();
		}
		catch( ReadError& e )
		{
			throw e;
		}
	}
	else{
		throw ReadError{"Error: unable to open '" + demoFilePath.string() + "' demo file."};
	}
}

void loadDemo::readFileLines(std::ifstream& demoFile, const fs::path& demoFilePath, demos::MainPackage& demosMainPackage, PlayerData& playerData)
{
	std::string fileLine;
	int fileTriggerIndex{-1};
	std::size_t fileLineNumber{1};
	while( std::getline( demoFile, fileLine ) )
	{
		std::istringstream lineStream{ fileLine };
		if( lineStream >> fileTriggerIndex )
		{
			loadDemo::checkTriggerValue(demoFilePath, fileTriggerIndex, fileLineNumber);
			loadDemo::triggerAccordingToValue(demoFilePath, demosMainPackage, playerData, fileLineNumber, lineStream, fileTriggerIndex);
		}
		else{
			throw ReadError{"Error: couldn't read trigger index in '" + demoFilePath.string() + "' demo file at line number " + std::to_string( fileLineNumber ) + " ."};
		}
		fileLineNumber++;
	}
}

void loadDemo::triggerAccordingToValue(const fs::path& demoFilePath, demos::MainPackage& demosMainPackage, PlayerData& playerData, std::size_t fileLineNumber, 
											std::istringstream& lineStream, int triggerValue)
{
	switch( triggerValue )
	{
		case onePlGame::demosFileIndex::CampaignType:
			loadDemo::readCampaignType(demoFilePath, playerData, fileLineNumber, lineStream);
			break;
		case onePlGame::demosFileIndex::LevelIndex:
			loadDemo::readLevelIndex(demoFilePath, playerData, fileLineNumber, lineStream);
			break;
		case onePlGame::demosFileIndex::SkillLevel:
			loadDemo::readSkillLevel(demoFilePath, playerData, fileLineNumber, lineStream);
			break;
		case onePlGame::demosFileIndex::PlayerLives:
			loadDemo::readPlayerLives(demoFilePath, playerData, fileLineNumber, lineStream);
			break;
		case onePlGame::demosFileIndex::RacketSize:
			loadDemo::readRacketSize(demoFilePath, playerData, fileLineNumber, lineStream);
			break;
		case onePlGame::demosFileIndex::Score:
			loadDemo::readScore(demoFilePath, playerData, fileLineNumber, lineStream);
			break;
		case onePlGame::demosFileIndex::RacketSpeed:
			loadDemo::readRacketSpeed(demoFilePath, playerData, fileLineNumber, lineStream);
			break;
		case onePlGame::demosFileIndex::BonusCoinNumber:
			loadDemo::readBonusCoinsNumber(demoFilePath, playerData, fileLineNumber, lineStream);
			break;
		case onePlGame::demosFileIndex::RimStartState:
			loadDemo::readRimsStartState(demoFilePath, playerData, fileLineNumber, lineStream);
			break;
		case onePlGame::demosFileIndex::GivenBonusInBag:
			loadDemo::readGivenBonusInBag(demoFilePath, playerData, fileLineNumber, lineStream);
			break;
		case onePlGame::demosFileIndex::SquareSizeAtSaving:
			loadDemo::readSquareSizeAtSaving(demoFilePath, demosMainPackage, fileLineNumber, lineStream);
			break;
		case onePlGame::demosFileIndex::ActionEvent:
			loadDemo::readActionEvent(demoFilePath, demosMainPackage.inputData, fileLineNumber, lineStream, "demos input action data");
			break;
		case onePlGame::demosFileIndex::QuitLevelEvent:
			loadDemo::readActionEvent(demoFilePath, demosMainPackage.quitLevelEvent, fileLineNumber, lineStream, "demos quit level event");
			break;
		case onePlGame::demosFileIndex::TraceCrossPosition:
			loadDemo::readTraceCrossPosition(demoFilePath, demosMainPackage, fileLineNumber, lineStream);
			break;
		case onePlGame::demosFileIndex::RacketPosition:
			loadDemo::readRacketPosition(demoFilePath, demosMainPackage, fileLineNumber, lineStream);
			break;
		case onePlGame::demosFileIndex::BallPosition:
			loadDemo::readBallPosition(demoFilePath, demosMainPackage, fileLineNumber, lineStream);
			break;
		case onePlGame::demosFileIndex::BrickDestruction:
			loadDemo::readBrickDestructionData(demoFilePath, demosMainPackage, fileLineNumber, lineStream);
			break;
		case onePlGame::demosFileIndex::CommonSoundEvent:
			loadDemo::readSoundEvent(demoFilePath, demosMainPackage.soundsStack, fileLineNumber, lineStream, "common sounds events");
			break;
		case onePlGame::demosFileIndex::PinguinsPosition:
			loadDemo::readTaggedPositionEvent(demoFilePath, demosMainPackage.antarcticDemoPackage.pinguinsPositions, fileLineNumber, lineStream, "pinguins positions");
			break;
		case onePlGame::demosFileIndex::PinguinsDirection:
			loadDemo::readTaggedDirectionEvent(demoFilePath, demosMainPackage.antarcticDemoPackage.pinguinsDirection, fileLineNumber, lineStream, "pinguins directions");
			break;
		case onePlGame::demosFileIndex::PinguinsCreateAndDestroy:
			loadDemo::readActionEvent(demoFilePath, demosMainPackage.antarcticDemoPackage.pinguinsCreateAndDestroy, fileLineNumber, lineStream, "pinguins create and destroy");
			break;
		case onePlGame::demosFileIndex::PinguinQuackSoundEvent:
			loadDemo::readSoundEvent(demoFilePath, demosMainPackage.antarcticDemoPackage.pinguinsQuacks, fileLineNumber, lineStream, "pinguins quack sound event");
			break;
		default:
			loadDemo::throwLineReadError(demoFilePath, fileLineNumber, "Bad index value: " + std::to_string( triggerValue) + " .");
			break;
	}
}

void loadDemo::checkTriggerValue(const fs::path& demoFilePath, int triggerValue, std::size_t fileLineNumber)
{
	if( !( triggerValue >= 0 && triggerValue < onePlGame::demosFileIndex::IndexMax ) )
	{
		throw ReadError{"Error: bad trigger index value : '" + std::to_string( triggerValue ) + "' in '" + demoFilePath.string() + "' demo file at line number '" 
			+ std::to_string( fileLineNumber ) + " ."};
	}
}

void loadDemo::readCampaignType(const fs::path& demoFilePath, PlayerData& playerData, std::size_t fileLineNumber, std::istringstream& lineStream)
{
	unsigned campaignType{ onePlGame::CampaignMax };
	if( lineStream >> campaignType )
	{
		if( campaignType < onePlGame::CampaignMax )
		{
			playerData.campaignType = campaignType;
		}
		else{
			throw ReadError{"Error: wrong value of campaign type in '" + demoFilePath.string() + "' demo file at line number " + std::to_string( fileLineNumber ) + " ."};
		}
	}
	else{
		loadDemo::throwLineReadError(demoFilePath, fileLineNumber, "Campaign type");
	}
}

void loadDemo::readLevelIndex(const fs::path& demoFilePath, PlayerData& playerData, std::size_t fileLineNumber, std::istringstream& lineStream)
{
	unsigned levelIndex{0};
	if( lineStream >> levelIndex )
	{
		playerData.levelIndex = levelIndex;
	}
	else{
		loadDemo::throwLineReadError(demoFilePath, fileLineNumber, "level index");
	}
}

void loadDemo::readSkillLevel(const fs::path& demoFilePath, PlayerData& playerData, std::size_t fileLineNumber, std::istringstream& lineStream)
{
	unsigned readSkillLevel{ onePlGame::SkillLevelMax };
	if( lineStream >> readSkillLevel )
	{
		if( readSkillLevel < onePlGame::SkillLevelMax )
		{
			playerData.skillLevel = readSkillLevel;
		}
		else{
			throw ReadError{"Error: wrong 'skill level' value in '" + demoFilePath.string() + "' demo file at line number " + std::to_string( fileLineNumber ) + " ."};
		}
	}
	else{
		loadDemo::throwLineReadError(demoFilePath, fileLineNumber, "skill level");	
	}
}

void loadDemo::readPlayerLives(const fs::path& demoFilePath, PlayerData& playerData, std::size_t fileLineNumber, std::istringstream& lineStream)
{
	unsigned readPlayerLives{0};
	if( lineStream >> readPlayerLives )
	{
		playerData.playerLives = readPlayerLives;
	}
	else{
		loadDemo::throwLineReadError(demoFilePath, fileLineNumber, "player lives");
	}
}

void loadDemo::readRacketSize(const fs::path& demoFilePath, PlayerData& playerData, std::size_t fileLineNumber, std::istringstream& lineStream)
{
	unsigned readRacketSize{ onePlGame::RacketMax };
	if( lineStream >> readRacketSize )
	{
		playerData.racketSize = readRacketSize;
	}
	else{
		loadDemo::throwLineReadError(demoFilePath, fileLineNumber, "racket size");
	}
}

void loadDemo::readScore(const fs::path& demoFilePath, PlayerData& playerData, std::size_t fileLineNumber, std::istringstream& lineStream)
{
	unsigned readScore{0};
	if( lineStream >> readScore )
	{
		playerData.score = readScore;
	}
	else{
		loadDemo::throwLineReadError(demoFilePath, fileLineNumber, "player score");
	}
}

void loadDemo::readRacketSpeed(const fs::path& demoFilePath, PlayerData& playerData, std::size_t fileLineNumber, std::istringstream& lineStream)
{
	double readRacketSpeed{0};
	if( lineStream >> readRacketSpeed )
	{
		if( readRacketSpeed > 0 && readRacketSpeed < onePlGame::RacketMaxSpeed )
		{
			playerData.racketSpeed = readRacketSpeed;
		}
		else{
			throw ReadError{"Error: bad racket speed value (" + std::to_string( readRacketSpeed ) + " in '" + demoFilePath.string() 
								+ "' demo file. It must be between 0 and " + std::to_string( onePlGame::RacketMaxSpeed ) + " ."};
		}
	}
	else{
		loadDemo::throwLineReadError(demoFilePath, fileLineNumber, "racket speed");
	}
}

void loadDemo::readBonusCoinsNumber(const fs::path& demoFilePath, PlayerData& playerData, std::size_t fileLineNumber, std::istringstream& lineStream)
{
	unsigned readBonusCoinsNumber{0};
	if( lineStream >> readBonusCoinsNumber )
	{
		playerData.bonusCoinsNumber = readBonusCoinsNumber;
	}
	else{
		loadDemo::throwLineReadError(demoFilePath, fileLineNumber, "bonus coin number");
	}
}

void loadDemo::readRimsStartState(const fs::path& demoFilePath, PlayerData& playerData, std::size_t fileLineNumber, std::istringstream& lineStream)
{
	int readRimsStartState{ rims::RimNullState };
	if( lineStream >> readRimsStartState )
	{
		if( readRimsStartState >= rims::RimNullState && readRimsStartState < rims::RemoveMax )
		{
			playerData.rimsStartState = readRimsStartState;
		}
		else{
			throw ReadError{"Error: bad 'rims start state' value: " + std::to_string( readRimsStartState ) + " in '" + demoFilePath.string() + 
								"' demo file it must be between " + std::to_string( rims::RimNullState ) + " and " + std::to_string( rims::RemoveMax )
								+ "( not included )."};
		}
	}
	else{
		loadDemo::throwLineReadError(demoFilePath, fileLineNumber, "rims start state");
	}
}

void loadDemo::readGivenBonusInBag(const fs::path& demoFilePath, PlayerData& playerData, std::size_t fileLineNumber, std::istringstream& lineStream)
{
	std::size_t bonusIndex{onePlGame::BonusMax};
	unsigned bonusCount{0};
	if( lineStream >> bonusIndex >> bonusCount )
	{
		if( bonusIndex < onePlGame::BonusMax )
		{
			playerData.bonusesInBag[bonusIndex] = bonusCount;
		}
		else{
			throw ReadError{"Error: bad 'bonusIndex' value (" + std::to_string( bonusIndex ) + ") in '" + demoFilePath.string() 
								+ "' demo file. It must be strictly inferior to " + std::to_string( onePlGame::BonusMax ) + " ."};
		}
	}
	else{
		loadDemo::throwLineReadError(demoFilePath, fileLineNumber, "given bonus count in player bag");
	}
}

void loadDemo::readSquareSizeAtSaving(const fs::path& demoFilePath, demos::MainPackage& demosMainPackage, std::size_t fileLineNumber, std::istringstream& lineStream)
{
	int readSquareSize{SQR_SIZE};
	if( lineStream >> readSquareSize )
	{
		demosMainPackage.startingData.squareSizeAtSaving = readSquareSize;
	}
	else{
		loadDemo::throwLineReadError(demoFilePath, fileLineNumber, "square size at recording demo time");
	}
}

void loadDemo::readActionEvent(const fs::path& demoFilePath, demos::Stack< demos::ActionData >& actionStack, std::size_t fileLineNumber, std::istringstream& lineStream, const std::string& itemType)
{
	demos::ActionData actionData;
	long int delay{0};
	if( lineStream >> delay >> actionData.funcEnum >> actionData.actionState )
	{
		actionData.delay = std::chrono::microseconds{delay};
		actionStack.emplaceElement(actionData);
	}
	else{
		loadDemo::throwLineReadError(demoFilePath, fileLineNumber, itemType);
	}
}

void loadDemo::readTraceCrossPosition(const fs::path& demoFilePath, demos::MainPackage& demosMainPackage, std::size_t fileLineNumber, std::istringstream& lineStream)
{
	demos::PositionStackData positionData;
	long int delay{0};
	if( lineStream >> delay >> positionData.position.x >> positionData.position.y )
	{
		positionData.delay = std::chrono::microseconds{delay};
		demosMainPackage.traceCrossPosition.emplaceElement(positionData);
	}
	else{
		loadDemo::throwLineReadError(demoFilePath, fileLineNumber, "demos trace cross position data");
	}
}

void loadDemo::readRacketPosition(const fs::path& demoFilePath, demos::MainPackage& demosMainPackage, std::size_t fileLineNumber, std::istringstream& lineStream)
{
	demos::PositionStackData positionData;
	long int delay{0};
	if( lineStream >> delay >> positionData.position.x >> positionData.position.y )
	{
		positionData.delay = std::chrono::microseconds{delay};
		demosMainPackage.racketPosition.emplaceElement(positionData);
	}
	else{
		loadDemo::throwLineReadError(demoFilePath, fileLineNumber, "demos racket position data");
	}
}

void loadDemo::readBallPosition(const fs::path& demoFilePath, demos::MainPackage& demosMainPackage, std::size_t fileLineNumber, std::istringstream& lineStream)
{
	demos::PositionStackData positionData;
	long int delay{0};
	if( lineStream >> delay >> positionData.position.x >> positionData.position.y )
	{
		positionData.delay = std::chrono::microseconds{delay};
		demosMainPackage.ballPosition.emplaceElement(positionData);
	}
	else{
		loadDemo::throwLineReadError(demoFilePath, fileLineNumber, "demos ball position data");
	}
}

void loadDemo::readBrickDestructionData(const fs::path& demoFilePath, demos::MainPackage& demosMainPackage, std::size_t fileLineNumber, std::istringstream& lineStream)
{
	demos::Matrix2DAction matrix2DAction;
	long int delay{0};
	if( lineStream >> delay >> matrix2DAction.coords.width >> matrix2DAction.coords.height >> matrix2DAction.brickData.index >> matrix2DAction.brickData.property )
	{
		matrix2DAction.delay = std::chrono::microseconds{delay};
		demosMainPackage.brickDestruction.emplaceElement(matrix2DAction);
	}
	else{
		loadDemo::throwLineReadError(demoFilePath, fileLineNumber, "demos bricks destruction data");
	}
}

void loadDemo::readSoundEvent(const fs::path& demoFilePath, demos::Stack< demos::SoundStackData >& soundsStack, std::size_t fileLineNumber, std::istringstream& lineStream, const std::string& itemType)
{
	demos::SoundStackData soundEvent;
	long int delay{0};
	if( lineStream >> delay >> soundEvent.soundEnum >> soundEvent.groupTag )
	{
		soundEvent.delay = std::chrono::microseconds{delay};
		soundsStack.emplaceElement(soundEvent);
	}
	else{
		loadDemo::throwLineReadError(demoFilePath, fileLineNumber, itemType);
	}
}

void loadDemo::readTaggedPositionEvent(const fs::path& demoFilePath, demos::Stack< demos::TaggedPositionStackData >& positionStack, std::size_t fileLineNumber, std::istringstream& lineStream, const std::string& itemType)
{
	demos::TaggedPositionStackData taggedData;
	long int delay{0};
	if( lineStream >> delay >> taggedData.itemTagNumber >> taggedData.position.x >> taggedData.position.y )
	{
		taggedData.delay = std::chrono::microseconds{delay};
		positionStack.emplaceElement(taggedData);
	}
	else{
		loadDemo::throwLineReadError(demoFilePath, fileLineNumber, itemType);
	}
}

void loadDemo::readTaggedDirectionEvent(const fs::path& demoFilePath, demos::Stack< demos::TaggedDirectionStackData >& positionStack, std::size_t fileLineNumber, std::istringstream& lineStream, const std::string& itemType)
{
	demos::TaggedDirectionStackData taggedData;
	long int delay{0};
	if( lineStream >> delay >> taggedData.itemTagNumber >> taggedData.direction )
	{
		taggedData.delay = std::chrono::microseconds{delay};
		positionStack.emplaceElement(taggedData);
	}
	else{
		loadDemo::throwLineReadError(demoFilePath, fileLineNumber, itemType);
	}
}

void loadDemo::throwLineReadError(const fs::path& demoFilePath, std::size_t fileLineNumber, const std::string& errorItem)
{
	throw ReadError{"Error: couldn't read '" + errorItem + "' in " + demoFilePath.string() + "' demo file at line number " + std::to_string( fileLineNumber ) + " ."};
}