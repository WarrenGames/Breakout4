#ifndef STEAM_SAMPLE_DATA_H
#define STEAM_SAMPLE_DATA_H

#include "time/accurateTime.h"
#include "spriteMove/objectMove.h"
#include <cstddef>

struct Offset;
struct AccurCoords;

struct SteamSample
{
	std::size_t frameNum;
	AccurateTimeDelay moveDelay;
	spriteMove::ObjectMoving moveSample;
	
	explicit SteamSample(const AccurCoords& startingPosition, double speed, const Offset& direction);
	~SteamSample() = default;
	SteamSample( const SteamSample& ) = delete;
	SteamSample& operator= ( const SteamSample& ) = delete;
	SteamSample( SteamSample&& ) = default;
	SteamSample& operator= ( SteamSample&& ) = default;
	
	void move(unsigned time);
	void anim(std::size_t frameMax, bool loop);
};

#endif //STEAM_SAMPLE_DATA_H