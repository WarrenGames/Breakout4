#ifndef DUELS_CONSTEXPRESSION_H
#define DUELS_CONSTEXPRESSION_H

#include "consts/constexprScreen.h"
#include "SDL.h"
#include <cstddef>

namespace duels{

constexpr std::size_t BALL_MAX = 4;

constexpr std::size_t COIN_MAX = 4;

constexpr std::size_t COIN_FRAMES_NUMBER = 25;

constexpr int SIZE_DECAL_COLLIDE_BOX = 2;

constexpr int COIN_LOOSE_COLLIDE_INT = 4;
constexpr int COIN_TEXTURE_SIZE = SQR_SIZE - COIN_LOOSE_COLLIDE_INT * 2;

constexpr int BALL_CORNER_INTERVAL = 11;
constexpr int BALL_TEXTURE_SIZE = SQR_SIZE / 2;

constexpr int SPAWN_INTERVAL_PRESENCE = SQR_SIZE;

//BonusState
enum{ BST_NOBONUS, BST_RANDGEN, BST_BLINK, BST_HAVEBONUS };
constexpr unsigned RANDGEN_TIME = 3000;
constexpr unsigned BLINK_TIME = 2000;
constexpr unsigned FRAME_TIME = 100;


//Bonus types
enum{ DB_IMPROVE_SIZE_SELF, // = 0
	  DB_SHRK_SIZE_OPPON,
	  DB_FREEZE_OPPON,
	  DB_STEAL_BONUS_OPPON,
	  DB_ACCEL_SELF,		// = 4
	  DB_SLOWDOWN_OPPON,
	  DB_ADD_BALL,
	  DB_ZONE_SPECIFIC,
	  DB_NEGATIVE_BONUS,	// = 8
	  DB_MAX				// = 9
	};

enum{PLAYER_BLUE, PLAYER_RED, PLAYER_MAX};

enum{ SMALL_RACKET, MEDIUM_RACKET, BIG_RACKET, RACKET_MAX };

constexpr int	RACKET_SIZEH = 10;
constexpr double RACKET_MIN_SPEED = 3;
constexpr double RACKET_MAX_SPEED = 8;
constexpr double RACKET_DEFAULT_SPEED = 5;
constexpr int	RACKET_SLOPE_INTERVAL = 9;

constexpr int SPEED_GRADIENT_WIDTH = SQR_SIZE / 4;
constexpr int SPEED_GRADIENT_HEIGHT = SQR_SIZE / 2;

//The SDL_Rect for the vertical gradient representing the speed of the players rackets
constexpr SDL_Rect BLUE_SPD_GRAD_RECT = { GAME_SCREEN_WIDTH - SQR_SIZE / 2 - SPEED_GRADIENT_WIDTH / 2, GAME_SCREEN_HEIGHT - SQR_SIZE / 2 - SPEED_GRADIENT_HEIGHT / 2, SPEED_GRADIENT_WIDTH, SPEED_GRADIENT_HEIGHT};
constexpr SDL_Rect RED_SPD_GRAD_RECT = { GAME_SCREEN_WIDTH - SQR_SIZE / 2 - SPEED_GRADIENT_WIDTH / 2, SQR_SIZE / 2 - SPEED_GRADIENT_HEIGHT / 2, SPEED_GRADIENT_WIDTH, SPEED_GRADIENT_HEIGHT};

enum{ OBJECT_IS_A_BALL, OBJECT_IS_A_COIN, OBJECT_MAX };

enum{ ZONE_STD, ZONE_HALLOWEEN, ZONE_STRING, ZONE_MAX };

//The textures index for the levels grids
enum{	GRID_ID_0, 				// = 0
		GRID_ID_BLUERIM,
		GRID_ID_REDRIM,			// = 2
		GRID_ID_X4, 
		GRID_ID_TOUGH1, 		// = 4
		GRID_ID_TOUGH2,
		GRID_ID_TOUGH3, 		// = 6
		GRID_ID_POT_TEXTURE,
		GRID_ID_POT_BLOCK, 		// = 8
		GRID_ID_BUTTON,
		GRID_ID_MAX				// = 10
};

enum{ SND_ENLARGE_RACKET,  	// = 0
	  SND_SHRINK_RACKET, 
	  SND_NEGATIVE_BON, 
	  SND_SPEED_MORE, 
	  SND_SPEED_LESS,  		// = 4
	  SND_STEAL_BON, 
	  SND_FREEZE, 
	  SND_COL_RACK_WBALL, 
	  SND_COL_COIN_WRACKET, // = 8
	  SND_COL_BALL_WBG, 
	  SND_NEW_COIN
};

constexpr char COMMON_SNDS_FILE_PATH[] = "data/sounds/duelsCommonSounds.ini";
constexpr char COMMON_CHANNELS_FILE_PATH[] = "data/sounds/duelsCommonChannels.ini";

constexpr char HALLOWEEN_SNDS_FILE_PATH[] = "data/sounds/duelsHalloweenSounds.ini";
constexpr char HALLOWEEN_CHANNELS_FILE_PATH[] = "data/sounds/duelsHalloweenChannels.ini";

enum{SND_ORGAN, SND_BUBBLES};

enum{	MATCH_CFG_TXT_CONFIG, 
		MATCH_CFG_TXT_PLAYER_INP, 
		MATCH_CFG_TXT_ZONE_CHOICE, 
		MATCH_CFG_TXT_RUN_ZONE, 
		MATCH_CFG_TXT_BLUE_PLAYER, 
		MATCH_CFG_TXT_RED_PLAYER, 
		MATCH_CFG_TXT_FIN_ACHIEV_1,
		MATCH_CFG_TXT_FIN_ACHIEV_2,
		MATCH_CFG_MAX};

constexpr char BLUE_RIM_TEXTURE_PATH[] = "textures/sprites/bricks/blueRim.png";
constexpr char RED_RIM_TEXTURE_PATH[] = "textures/sprites/bricks/purpleRim.png";

}

#endif //DUELS_CONSTEXPRESSION_H