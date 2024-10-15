#include "levelComponents/inGameBagThings/iconsPositionsLoader.h"
#include "logging/logsStruct.h"
#include "consts/constexprScreen.h"
#include <sstream>
#include <cassert>

BagIconsPositions::BagIconsPositions(AppLogFiles& logs, const std::string& filePath):
	isLoadingPerfect{true}
{
	loadData(logs, filePath);
}

bool BagIconsPositions::wasLoadingPerfect() const
{
	return isLoadingPerfect;
}

const Offset& BagIconsPositions::operator []( std::size_t index ) const
{
	assert( index < positions.size() );
	return positions[index];
}

std::size_t BagIconsPositions::size() const
{
	return positions.size();
}

void BagIconsPositions::loadData(AppLogFiles& logs, const std::string& filePath)
{
	if( std::ifstream dataFile{ filePath } )
	{
		std::string fileLine;
		Offset offset;
		while( std::getline( dataFile, fileLine ) )
		{
			std::istringstream lineStream{fileLine};
			if( lineStream >> offset.x >> offset.y )
			{
				convertValueIfNeeded(offset);
				positions.push_back( offset );
			}
			else{
				isLoadingPerfect = false;
				logs.error << "Error: couldn't read an offset line in '" << filePath << "' file.\n";
			}
		}
	}
	else{
		isLoadingPerfect = false;
		logs.error << "Error: couldn't open the file '" << filePath << "' in order to load the bag icons positions.\n";
	}
}

void BagIconsPositions::convertValueIfNeeded(Offset& offset) const
{
	if( SQR_SIZE != 64 )
	{
		offset.x = SQR_SIZE * offset.x / 64;
		offset.y = SQR_SIZE * offset.y / 64;
	}
}