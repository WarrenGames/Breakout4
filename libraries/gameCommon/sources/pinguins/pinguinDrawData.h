#ifndef PINGUIN_DRAW_DATA_H
#define PINGUIN_DRAW_DATA_H

#include "spriteMove/objectMove.h"
#include "time/accurateTime.h"

struct SDL_Rect;

struct PinguinDrawData
{
	unsigned direction;
	unsigned frameNumber;
	spriteMove::ObjectMoving move;
	AccurateTimeDelay anim;
	
	PinguinDrawData(const AccurCoords& pinguinPos, double speed, const Offset& dirVectors);
	~PinguinDrawData() = default;
	PinguinDrawData( const PinguinDrawData& ) = delete;
	PinguinDrawData& operator= ( const PinguinDrawData& ) = delete;
	PinguinDrawData( PinguinDrawData&& ) = default;
	PinguinDrawData& operator= ( PinguinDrawData&& ) = default;
	
	void animPinguin();
	void bounceOffScreenEdges(int topycoord, const SDL_Rect& collisionRect);
	void bounceOffScreenRight(const SDL_Rect& collisionRect);
	void bounceOffScreenLeft(const SDL_Rect& collisionRect);
	void bounceOffScreenTop(int topycoord, const SDL_Rect& collisionRect);
	void bounceOffScreenBottom(const SDL_Rect& collisionRect);
	
	void setDirection();
};

#endif //PINGUIN_DRAW_DATA_H