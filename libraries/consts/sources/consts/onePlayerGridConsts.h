#ifndef ONE_PLAYER_GRID_CONSTS_H
#define ONE_PLAYER_GRID_CONSTS_H

#include <cstddef>

constexpr std::size_t GridWidth = 20;
constexpr std::size_t GridHeight = 14;

constexpr std::size_t TenPointsBrickStateNumber = 9;
constexpr std::size_t HardBricksNumber = 3;
constexpr std::size_t LavaStoneBricksNumber = 3;

namespace bricks{

namespace index{
	enum{ 	NoBrick, 
			GenericBrick,
			RichBrick, 
			BonusCoin,
			GiftBrick,
			TenPointsBrick,	
			SolidBrick,
			IceBrick,
			HellBricks,
			Max };
}

namespace GenericBrick{ enum{ Blue, Green, Red, Gray, Max }; }

namespace RichBrick{ 
	enum{ SteelLeft, SteelRight, BronzeLeft, BronzeRight, SilverLeft, SilverRight, GoldLeft, GoldRight, Max }; 
	
	constexpr int SteelValue = 50;
	constexpr int BronzeValue = 100;
	constexpr int SilverValue = 200;
	constexpr int GoldValue = 400;
}

namespace bonuses{ enum{ BigBall, SpeedUp, SpeedDown, ENLARGE_RIMS, SHRINK_RIMS, ENLARGE_RACKET, SHRINK_RACKET, ONE_UP, GLUE, Max }; }

namespace iceBricks{ enum{ IceCube, PinguinBrickTexturePath, Max }; }

namespace hellBricks{ enum{ SkullBrick, LavaStone1, LavaStone2, LavaStone3, Max }; }

constexpr char GridEditorTexturesEnumFilePath[] = "data/textures/texturesPacksConfigurations/editorPackList.txt";
constexpr char TexturesPacksFilesDirectory[] = "data/textures/";

}

#endif //ONE_PLAYER_GRID_CONSTS_H