#ifndef HALLOWEEN_AREA_H
#define HALLOWEEN_AREA_H

#include "matrices/matrix2D.h"
#include "types/brickData.h"
#include "customTypes/positionTypes.h"
#include "texturing/texturesCombo.h"

struct Essentials;
namespace sdl2{ class Font; }

namespace duels{
struct LevelOptions;
	
struct HalloweenArea
{
	bool isLoadingPerfect;
	MatrixTemp2D<BrickData> levelGrid;
	std::vector< Offset > ballsAndCoinsSpawn;
	TextureCombo blueRim;
	TextureCombo redRim;
	TextureCombo brick;
	TextureCombo pot;
	TextureCombo textBackground;
	TextureCombo remainingPoints;
	std::vector< TextureCombo > mushrooms;

	explicit HalloweenArea(Essentials& essentials, const sdl2::Font& arial, unsigned pointsToPlay);
	~HalloweenArea() = default;
	HalloweenArea( const HalloweenArea& ) = delete;
	HalloweenArea& operator= ( const HalloweenArea& ) = delete;
	HalloweenArea( HalloweenArea&& ) = default;
	HalloweenArea& operator= ( HalloweenArea&& ) = default;
	
	void loadMushrooms(Essentials& essentials);
	void setMushroomsPositions();
	void drawZone(sdl2::RendererWindow& rndWnd);
	void drawMushrooms(sdl2::RendererWindow& rndWnd, const duels::LevelOptions& levelOptions) const;
};

}

#endif //HALLOWEEN_AREA_H