#ifndef ONE_PLAYER_LEVEL_CONSTS_H
#define ONE_PLAYER_LEVEL_CONSTS_H

namespace onePlGame{

enum{ 	CAMPAIGN_WITH_SHOP, // = 0
		CAMPAIGN_NO_SHOP, 	// = 1
		CAMPAIGN_MAX };		// = 2

constexpr double BALL_STARTING_SPEED = 2;
constexpr double RACKET_STARTING_SPEED = 5;
constexpr double RACKET_MAX_SPEED = 9;
constexpr unsigned MICRO_SEC_REFRESH_TIME_RATE = 1000 * 1000 / 60;
constexpr int RACKET_TEXTURE_HEIGHT = 10;
constexpr int INFO_BOARD_Y_MARGIN = 1;
constexpr unsigned COIN_FRAMES_NUMBER = 25;

enum{ 	SMALL_RACKET, 
		MEDIUM_RACKET, 
		BIG_RACKET, 
		RACKET_MAX };

constexpr int BALL_CORNER_INTERVAL = 4;//For a SQR_SIZE value of 64 it is equal to '11'

enum{ 	INP_MOVE_LEFT, 				// = 0
		INP_MOVE_RIGHT, 			// = 1
		INP_BALL_TRACE, 			// = 2
		INP_LOOK_BAG, 				// = 3
		INP_SWITCH, 				// = 4
		INP_MAX };					// = 5

enum{ 	LANG_INP_LEFT,				// = 0
		LANG_INP_RIGHT, 			// = 1
		LANG_INP_BALL_TRACE, 		// = 2
		LANG_INP_LOOK_BAG, 			// = 3
		LANG_INP_SWITCH, 			// = 4
		LANG_INP_TITLE, 			// = 5
		LANG_INP_PUSHNEWKEY, 		// = 6
		LANG_INP_PUSHNEWBTN, 		// = 7
		LANG_INP_KEYB_ROW_TITLE,	// = 8
		LANG_INP_JOY_ROW_TITLE,		// = 9
		LANG_INP_AXIS_NUM,			// = 10
		LANG_INP_HAT_NUM,			// = 11
		LANG_INP_BUTTON_NUM,		// = 12
		LANG_INP_ERROR_MOVE_TYPE,	// = 13
		LANG_INP_AXIS_THRESHOLD,	// = 14
		LANG_INP_CROSS_X_MOVE,		// = 15
		LANG_INP_CROSS_Y_MOVE,		// = 16
		LANG_INP_MOUSE,				// = 17
		LANG_INP_JOY_INFOS,			// = 18
		LANG_INP_MAX };				// = 19

enum{	JOYMOV_AXES, 
		JOYMOV_HATS, 
		JOYMOV_ERROR};

enum{ 	JOYBTN_BALL_TRACE, 
		JOYBTN_LOOK_BAG, 
		JOYBTN_SWITCH, 
		JOYBTN_MAX };

enum{ 	CROSS_DEVICE_IS_MOUSE,
		CROSS_DEVICE_IS_JOYSTICK };

constexpr char BG_TEXTURE_PATH[] = "textures/sprites/bricks/bgBrick.png";

enum{ 	SKILL_LEVEL_EASY, 
		SKILL_LEVEL_INTERMEDIATE, 
		SKILL_LEVEL_HARD, 
		SKILL_LEVEL_MAX };

enum{ 	EPISODE_SIMPLE, 
		EPISODE_ARTIC, 
		EPISODE_HELL, 
		EPISODE_MAX };

constexpr char SHOP_RACE_LVL_LIST[] = "data/levels/1player/shopRaceLevels.cfg";

constexpr char NO_SHOP_RACE_LVL_LIST[] = "data/levels/1player/noShopRaceLevels.cfg";

constexpr char LEVELS_DIR[] = "data/levels/1player/";
constexpr char SHOP_LEVELS_DIR[] = "shopRace/";
constexpr char STD_RACE_LEVELS_DIR[] = "stdRace/";

enum{ 	LEVEL_END_NO, 
		LEVEL_END_PARTIALLY, 
		LEVEL_END_COMPLETE,
		LEVEL_END_SURRENDER};

constexpr char COMMON_SNDS_FILE_PATH[] = "data/sounds/1playerStdSounds.ini";
constexpr char COMMON_CHANNELS_FILE_PATH[] = "data/sounds/1playerStdChannels.ini";

enum{	SND_ENLARGE_RACKET,			// = 0
		SND_SHRINK_RACKET,
		SND_SPEED_MORE,
		SND_SPEED_LESS,
		SND_ADD_ONE_UP,				// = 4
		SND_CANT_USE_BONUS,
		SND_COL_RACK_W_BALL,
		SND_COL_BALL_W_BACKGRND,
		SND_BALL_LOST,				// = 8
		SND_QUACK,
		SND_COL_RACK_W_COIN,
		SND_CREATE_NEW_COIN,
		SND_IMPACT_W_DAMAGE,		// = 12
		SND_GAME_START,
		SND_FIRE_BALL,				
		SND_MAX };					// = 15

}

#endif //ONE_PLAYER_LEVEL_CONSTS_H