#include "levelComponents/hellEpisodeThings/fireBalls/paths/fireBallPaths.h"
#include "logging/logsStruct.h"
#include "consts/hellConsts.h"
#include <sstream>

constexpr char FireBallsPathsEnum[] = "data/paths/fireBallsOnePlayerEnum.txt";

onePlGame::FireBallsPaths::FireBallsPaths():
	isLoadingPerfect{ true }
{
	
}

onePlGame::FireBallsPaths::FireBallsPaths(AppLogFiles& logs):
	isLoadingPerfect{ true }
{
	openMainFile(logs, FireBallsPathsEnum);
	
	if( paths.getMovesCount() != hell::FireBallPathMax )
	{
		logs.error << "Error: the number of loaded paths is not good: " << paths.getMovesCount() << " paths loaded, and " << hell::FireBallPathMax << " expected.\n";
		isLoadingPerfect = false;
	}
}

bool onePlGame::FireBallsPaths::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

void onePlGame::FireBallsPaths::openMainFile(AppLogFiles& logs, const std::string& mainFilePath)
{
	if( std::ifstream mainFile{ mainFilePath } )
	{
		std::string fileLine;
		while( std::getline( mainFile, fileLine ) )
		{
			addPathFromFile(logs, fileLine);
		}
	}
	else{
		logs.error << "Error: couldn't open '" << mainFilePath << "' main move file.\n";
		isLoadingPerfect = false;
	}
}

void onePlGame::FireBallsPaths::addPathFromFile(AppLogFiles& logs, const std::string& pathFile)
{
	if( std::ifstream file{pathFile} )
	{
		paths.pushBackNewMove(pathFile);
		spriteMove::MoveVector segment;
		unsigned milliseconds{0};
		std::string fileLine;
		while( std::getline( file, fileLine ) )
		{
			std::istringstream lineStream{fileLine};
			if( lineStream >> segment.x >> segment.y >> segment.speed >> milliseconds )
			{
				segment.wait = std::chrono::milliseconds{milliseconds};
				segment.speed = segment.speed * SQR_SIZE / 64;
				segment.x = segment.x * SQR_SIZE / 64;
				segment.y = segment.y * SQR_SIZE / 64;
				paths.addVectorToLastMove(segment);
			}
			else{
				logs.error << "Error: couldn't read line of '" << pathFile << "' move file.\n";
				isLoadingPerfect = false;
			}
		}
	}
	else{
		logs.error << "Error: couldn't open '" << pathFile << "' move file.\n";
		isLoadingPerfect = false;
	}
}