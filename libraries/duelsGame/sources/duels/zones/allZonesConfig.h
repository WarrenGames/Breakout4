#ifndef DUELS_ALL_ZONES_CONFIG_H
#define DUELS_ALL_ZONES_CONFIG_H

#include <string>

struct AppLogFiles;
template< typename T > class MatrixTemp2D;
struct BrickData;

namespace duels{

bool loadLevelGridIsSuccess(AppLogFiles& logs, MatrixTemp2D<BrickData>& levelGrid, const std::string& levelFileName );

}

#endif //DUELS_ALL_ZONES_CONFIG_H