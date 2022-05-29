#include "onePlayerGame/level/textures/bricksTexturesLoader.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include "consts/onePlayerGridConsts.h"

constexpr char GEN_BRICK_DATA_FILE_PATH[] = "data/textures/1player_genericBricks.txt";
constexpr char RICH_BRICK_DATA_FILE_PATH[] = "data/textures/1player_richBricks.txt";
constexpr char GIFT_BRICK_DATA_FILE_PATH[] = "data/textures/1player_giftsBricks.txt";
constexpr char TEN_PTS_BRICK_TEX_BASE[] = "textures/sprites/bricks/br10pts_game_";
constexpr char HARD_BRICKS_DATA_FILE_PATH[] = "data/textures/1player_hardBricks.txt";
constexpr char BONUS_BRICK_TEXTURE_PATH[] = "textures/sprites/bricks/bonusBrick_game.png";
constexpr char ICE_CUBE_BRICK_TEXTURE_PATH[] = "textures/sprites/bricks/iceCubeBrick_game.png";
constexpr char PINGUIN_BRICK[] = "textures/sprites/bricks/pinguinBrick_game.png";
constexpr char HELL_SKULL_BRICK_PATH[] = "textures/sprites/bricks/skullBrick_game.png";
constexpr char LAVA_BRICK_TEX_BASE[] = "textures/sprites/bricks/solidLavaBrick_game_";

BricksTexturesLoader::BricksTexturesLoader(AppLogFiles& logs, sdl2::RendererWindow& rndWnd):
	generic{ logs, rndWnd, GEN_BRICK_DATA_FILE_PATH },
	rich{ logs, rndWnd, RICH_BRICK_DATA_FILE_PATH },
	bonusBrick{ logs, rndWnd, BONUS_BRICK_TEXTURE_PATH },
	giftBricks{ logs, rndWnd, GIFT_BRICK_DATA_FILE_PATH },
	tenPtsBricks{ logs, rndWnd, TENPTS_BRICK_NUM, TEN_PTS_BRICK_TEX_BASE },
	hardBricks{ logs, rndWnd, HARD_BRICKS_DATA_FILE_PATH },
	iceCubeBrick{ logs, rndWnd, ICE_CUBE_BRICK_TEXTURE_PATH },
	pinguinBrick{ logs, rndWnd, PINGUIN_BRICK },
	skullBrick{ logs, rndWnd, HELL_SKULL_BRICK_PATH },
	lavaStoneBricks{ logs, rndWnd, LAVA_STONE_BRICKS_NUM, LAVA_BRICK_TEX_BASE }
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