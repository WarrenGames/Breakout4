#include "onePlayerGame/level/textures/bricksTexturesLoader.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include "consts/onePlayerGridConsts.h"

constexpr char GenericBrickDataFilePath[] = "data/textures/1player_genericBricks.txt";
constexpr char RichBrickDataFilePath[] = "data/textures/1player_richBricks.txt";
constexpr char GiftBrickDataFilePath[] = "data/textures/1player_giftsBricks.txt";
constexpr char TenPointsBrickTextureBaseName[] = "textures/sprites/bricks/br10pts_game_";
constexpr char HardBrickDataFilePath[] = "data/textures/1player_hardBricks.txt";
constexpr char BonusBrickTexturePath[] = "textures/sprites/bricks/bonusBrick_game.png";
constexpr char IceCubeBrickTexturePath[] = "textures/sprites/bricks/iceCubeBrick_game.png";
constexpr char PinguinBrickTexturePath[] = "textures/sprites/bricks/pinguinBrick_game.png";
constexpr char HellSkullBrickTexturePath[] = "textures/sprites/bricks/skullBrick_game.png";
constexpr char LavaBrickTextureBaseName[] = "textures/sprites/bricks/solidLavaBrick_game_";

BricksTexturesLoader::BricksTexturesLoader(AppLogFiles& logs, sdl2::RendererWindow& rndWnd):
	generic{ logs, rndWnd, GenericBrickDataFilePath },
	rich{ logs, rndWnd, RichBrickDataFilePath },
	bonusBrick{ logs, rndWnd, BonusBrickTexturePath },
	giftBricks{ logs, rndWnd, GiftBrickDataFilePath },
	tenPtsBricks{ logs, rndWnd, TenPointsBrickStateNumber, TenPointsBrickTextureBaseName },
	hardBricks{ logs, rndWnd, HardBrickDataFilePath },
	iceCubeBrick{ logs, rndWnd, IceCubeBrickTexturePath },
	pinguinBrick{ logs, rndWnd, PinguinBrickTexturePath },
	skullBrick{ logs, rndWnd, HellSkullBrickTexturePath },
	lavaStoneBricks{ logs, rndWnd, LavaStoneBricksNumber, LavaBrickTextureBaseName }
{
	
}

BricksTexturesLoader::operator bool() const
{
	return generic.wasLoadingPerfect() 
		&& rich.wasLoadingPerfect()
		&& bonusBrick.wasLoadingPerfect()
		&& giftBricks.wasLoadingPerfect()
		&& tenPtsBricks.wasLoadingPerfect()
		&& hardBricks.wasLoadingPerfect()
		&& iceCubeBrick.wasLoadingPerfect()
		&& pinguinBrick.wasLoadingPerfect()
		&& skullBrick.wasLoadingPerfect()
		&& lavaStoneBricks.wasLoadingPerfect();
}