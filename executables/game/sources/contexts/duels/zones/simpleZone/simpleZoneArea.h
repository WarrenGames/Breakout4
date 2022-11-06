#ifndef DUELS_SIMPLE_ZONE_AREA_H
#define DUELS_SIMPLE_ZONE_AREA_H

#include "matrices/matrix2D.h"
#include "types/brickData.h"
#include "customTypes/positionTypes.h"
#include "texturing/texturesCombo.h"

struct AppLogFiles;
namespace sdl2{ class RendererWindow; class Font; }

namespace duels{

struct SimpleZone
{
	bool isLoadingPerfect;
	MatrixTemp2D<BrickData> levelGrid;
	std::vector< Offset > ballsAndCoinsSpawn;
	TextureCombo blueRim;
	TextureCombo redRim;
	TextureCombo brick;
	TextureCombo textBackground;
	TextureCombo remainingPoints;
	
	explicit SimpleZone(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& arial, unsigned pointsToPlay);
	
	void drawZone(sdl2::RendererWindow& rndWnd);
};

}

#endif //DUELS_SIMPLE_ZONE_AREA_H