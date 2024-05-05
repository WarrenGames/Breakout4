#ifndef STAR_TYPE_THINGS_H
#define STAR_TYPE_THINGS_H

#include "time/accurateTime.h"
#include <vector>

namespace spriteMove{

struct MoveInfo;

struct StarTypeThings
{
	int padDirection;
	int turretDirection;
	int directionsNumber;
	std::vector<int> orientationInfos;
	AccurateTimeDelay rotationTimeDelay;
	std::chrono::milliseconds rotationTime;
	bool isInOrientationPhase;
	bool isOrientationClockwise;
	
	explicit StarTypeThings(int initialDirection, int directionsNumber_, unsigned rotationTimeMilliseconds );
	~StarTypeThings() = default;
	StarTypeThings( const StarTypeThings& ) = delete;
	StarTypeThings& operator= ( const StarTypeThings& ) = delete;
	StarTypeThings( StarTypeThings&& ) = default;
	StarTypeThings& operator= ( StarTypeThings&& ) = default;
	
	void orientateWithTiming();
	void determineClockwiseRotation(unsigned vectorNumber);
	
	int getDirPad() const;//get the texture index for enemy pad (can be equal to -1, so that's an int and not a unsigned int 
	int getDirTurret() const;//get the texture index for enemy turret (can be equal to -1, so that's an int and not a unsigned int 
	void createOrientationInfos(const std::vector<spriteMove::MoveInfo>& moveData);
};

}

#endif //STAR_TYPE_THINGS_H