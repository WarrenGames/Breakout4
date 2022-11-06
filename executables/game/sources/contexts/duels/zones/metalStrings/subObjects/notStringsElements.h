#ifndef DUELS_MET_STR_NOT_STRING_ELEMENTS_H
#define DUELS_MET_STR_NOT_STRING_ELEMENTS_H

#include "matrices/matrix2D.h"
#include "types/brickData.h"
#include "texturing/texturesCombo.h"

struct Essentials;

namespace metalStrings{

class SwitchsData;
	
struct LevelBricks
{	
	bool isLoadingPerfect;
	MatrixTemp2D<BrickData> levelGrid;
	TextureCombo blueRim;
	TextureCombo redRim;
	TextureCombo brick;
	std::vector< TextureCombo > switchsTextures;

	explicit LevelBricks(Essentials& essentials);
	void drawZone(Essentials& essentials, const SwitchsData& switchs);
	void drawSwitch(Essentials& essentials, const SwitchsData& switchs, std::size_t x, std::size_t y);
	void loadSwitchsTextures(Essentials& essentials);
};

}

#endif //DUELS_MET_STR_NOT_STRING_ELEMENTS_H