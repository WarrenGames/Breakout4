#ifndef ONE_PLAYER_GRID_CONSTS_H
#define ONE_PLAYER_GRID_CONSTS_H

#include <cstddef>

constexpr std::size_t GRID_WIDTH = 20;
constexpr std::size_t GRID_HEIGHT = 14;

enum{BRICK_ID, BRICK_PROP, BRICK_Z};

constexpr std::size_t TENPTS_BRICK_NUM = 9;
constexpr std::size_t HARD_BRICKS_NUM = 3;
constexpr std::size_t LAVA_STONE_BRICKS_NUM = 3;

namespace BRICKS{

namespace INDEX{
	enum{ 	NO_BRICK, 
			GEN_BRICK,
			RICH_BRICK, 
			BONUS_COIN,
			GIFT_BRICK,
			TEN_POINTS,	
			SOLID,
			ICE_BRICKS,
			HELL_BRICKS,
			MAX };
}

namespace GENERIC{ enum{ BLUE, GREEN, RED, GRAY, MAX }; }

namespace RICH{ 
	enum{ STEEL_LEFT, STEEL_RIGHT, BRONZE_LEFT, BRONZE_RIGHT, SILVER_LEFT, SILVER_RIGHT, GOLD_LEFT, GOLD_RIGHT, MAX }; 
	
	constexpr int STEEL_VALUE = 50;
	constexpr int BRONZE_VALUE = 100;
	constexpr int SILVER_VALUE = 200;
	constexpr int GOLD_VALUE = 400;
}

namespace BONUSES{ enum{ BIG_BALL, SPEED_UP, SPEED_DOWN, ENLARGE_RIMS, SHRINK_RIMS, ENLARGE_RACKET, SHRINK_RACKET, ONE_UP, GLUE, MAX }; }

namespace ICE_BR{ enum{ ICE_CUBE, PINGUIN_BRICK, MAX }; }

namespace HELL_BR{ enum{ SKULL_BRICK, LAVA_STONE_1, LAVA_STONE_2, LAVA_STONE_3, MAX }; }

}

#endif //ONE_PLAYER_GRID_CONSTS_H