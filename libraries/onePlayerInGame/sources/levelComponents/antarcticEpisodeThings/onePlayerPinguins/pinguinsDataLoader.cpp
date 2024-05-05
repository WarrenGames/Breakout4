#include "levelComponents/antarcticEpisodeThings/onePlayerPinguins/pinguinsDataLoader.h"
#include "types/essentialsStruct.h"
#include "crossLevel/playerData.h"
#include "pinguins/pinguinConsts.h"
#include "consts/onePlayerLevelConsts.h"

constexpr char PinguinRevokeFile[] = "data/levels/1player/options/pinguinRevoke.cfg";

onePlGame::PinguinsDataLoader::PinguinsDataLoader(Essentials& essentials, const PlayerData& playerData):
	isLoadingPerfect{ true }
{
	loadDataFile(essentials.logs, playerData.getMonstersFilePath() );
	loadNeededHitsData(essentials.logs, playerData.skillLevel);
}

unsigned onePlGame::PinguinsDataLoader::getRevokingHits() const
{
	return revokingHits;
}

bool onePlGame::PinguinsDataLoader::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

std::vector< PinguinBehaviorData >::iterator onePlGame::PinguinsDataLoader::begin()
{
	return loadedData.begin();
}

std::vector< PinguinBehaviorData >::iterator onePlGame::PinguinsDataLoader::end()
{
	return loadedData.end();
}

void onePlGame::PinguinsDataLoader::loadDataFile(AppLogFiles& logs, const std::string& levelDataFilePath)
{
	if( std::ifstream dataFile{ levelDataFilePath } )
	{
		std::string fileLine;
		unsigned lineIndex{0};
		while( std::getline( dataFile, fileLine ) )
		{
			std::istringstream lineStream{fileLine};
			readSingleLine(logs, levelDataFilePath, lineStream, lineIndex);
		}
	}
	else{
		logs.error << "Error: couldn't open '" << levelDataFilePath << "' data file.\n";
		isLoadingPerfect = false;
	}
}

void onePlGame::PinguinsDataLoader::readSingleLine(AppLogFiles& logs, const std::string& levelDataFilePath, std::istringstream& lineStream, unsigned lineIndex)
{
	if( lineStream >> lineIndex )
	{
		switch( lineIndex )
		{
			case pinguin::fileIndex::NewPinguin:
				loadPinguinData(logs, levelDataFilePath, lineStream);
				break;
			default:
				logs.error << "Error: unknown 'line index' in '" << levelDataFilePath << "' file: " << lineIndex << " .\n";
				isLoadingPerfect = false;
				break;
		}
	}
	else{
		logs.error << "Error: couldn't read index in '" << levelDataFilePath << "' file.\n";
		isLoadingPerfect = false;
	}
}

void onePlGame::PinguinsDataLoader::loadPinguinData(AppLogFiles& logs, const std::string& levelDataFilePath, std::istringstream& lineStream)
{
	Offset startPos;
	Offset dirVectors;
	double speed;
	if( lineStream >> startPos.x >> startPos.y >> dirVectors.x >> dirVectors.y >> speed )
	{
		loadedData.emplace_back( PinguinBehaviorData{ AccurCoords{static_cast<double>(startPos.x * SQR_SIZE), 
																static_cast<double>(startPos.y * SQR_SIZE) }, 
																speed, 
																dirVectors } );
	}
	else{
		logs.error << "Error: while loading pinguin data in '" << levelDataFilePath << "' file.\n";
		isLoadingPerfect = false;
	}
}

void onePlGame::PinguinsDataLoader::loadNeededHitsData(AppLogFiles& logs, unsigned skillLevel)
{
	if( std::ifstream pinguinTolerance{PinguinRevokeFile} )
	{
		std::vector<unsigned> hits(onePlGame::SkillLevelMax);
		for( auto &number : hits )
		{
			if( !( pinguinTolerance >> number ) )
			{
				isLoadingPerfect = false;
				logs.error << "Error: reading data in '" << PinguinRevokeFile << "' file failed (probably there not enough data; " 
						 << onePlGame::SkillLevelMax << " of them are needed.\n";
			}
		}
		assert( static_cast<unsigned>(skillLevel) < hits.size() );
		revokingHits = hits[skillLevel];
		logs.warning << "Hits needed to revoke a pinguin in one player game: " << revokingHits << " .\n";
		
	}
	else{
		isLoadingPerfect = false;
		logs.error << "Error: couldn't load '" << PinguinRevokeFile << "' in order to load data relative to pinguin tolerance.\n";
	}
}