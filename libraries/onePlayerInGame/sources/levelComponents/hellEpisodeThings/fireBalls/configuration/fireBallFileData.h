#ifndef ONE_PLAYER_FIRE_BALL_FILE_DATA_H
#define ONE_PLAYER_FIRE_BALL_FILE_DATA_H

struct FireBallFileData
{
	unsigned id;
	unsigned behaviorId;
	unsigned skillBits;
	int sqrSizeRelativePos;
	int totalWaitTime;
	int randomTimeInterval;
	unsigned seedAdd;
	
	explicit FireBallFileData();
	~FireBallFileData() = default;
	FireBallFileData( const FireBallFileData& ) = default;
	FireBallFileData& operator= ( const FireBallFileData& ) = default;
	FireBallFileData( FireBallFileData&& ) = default;
	FireBallFileData& operator= ( FireBallFileData&& ) = default;
};


#endif //ONE_PLAYER_FIRE_BALL_FILE_DATA_H