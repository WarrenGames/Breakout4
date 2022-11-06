#include "contexts/duels/zones/allZonesConfig.h"
#include "logging/logsStruct.h"
#include "matrices/matrix2D.h"
#include "types/brickData.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"

bool duels::loadLevelGridIsSuccess(AppLogFiles& logs, MatrixTemp2D<BrickData>& levelGrid, const std::string& levelFileName )
{
	if( std::ifstream levelFile{ path::getDuelsLevelGridFile(levelFileName) } )
	{
		unsigned data{0};
		for( std::size_t y{0} ; y < levelGrid.height() ; ++y )
		{
			for( std::size_t x{0} ; x < levelGrid.width() ; ++x)
			{
				if( levelFile >> data )
				{
					levelGrid(x, y).index = data;
				}
				else{
					logs.error << "Error: reading '" << path::getDuelsLevelGridFile(levelFileName) << "' file failed at coordinates ( " << x << " , " << y << " ) .\n";
					return false;
				}
			}
		}
		return true;
	}
	else{
		logs.error << "Error: couldn't open the following file for a duel level: " << path::getDuelsLevelGridFile(levelFileName) << " .\n";
		return false;
	}
}