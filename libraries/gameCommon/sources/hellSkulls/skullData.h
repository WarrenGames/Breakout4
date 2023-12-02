#ifndef HELL_SKULL_DATA_H
#define HELL_SKULL_DATA_H

#include "spriteMove/objectMove.h"
#include "time/accurateTime.h"

struct SkullData
{
	unsigned direction;
	unsigned frameNumber;
	unsigned explosionFrameIndex;
	spriteMove::ObjectMoving move;
	AccurateTimeDelay anim;
	
	explicit SkullData();
	explicit SkullData(const Offset& pos, double speed, const Offset& moveDirection);
	~SkullData() = default;
	SkullData( const SkullData& ) = delete;
	SkullData& operator= ( const SkullData& ) = delete;
	SkullData( SkullData&& ) = default;
	SkullData& operator= ( SkullData&& ) = default;
	
	void animSkull();
	void moveSkull();
	void setDirection();
	void animSkullExplosion(unsigned explosionMsDelay, unsigned explosionFramesNumber, bool& isSkullActive);
};

#endif //HELL_SKULL_DATA_H