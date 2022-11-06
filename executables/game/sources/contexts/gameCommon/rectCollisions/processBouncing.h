#ifndef COLLISION_BOUNCING_PROCESSING_H
#define COLLISION_BOUNCING_PROCESSING_H

namespace spriteMove{ class ObjectMoving; }
struct SpriteSize;

namespace bouncing{

bool objectsCollide(const spriteMove::ObjectMoving& moveA, const SpriteSize& objAsize, const spriteMove::ObjectMoving& moveB, const SpriteSize& objBsize, int interval);
	
void processElementsBouncing(spriteMove::ObjectMoving& objAmove, spriteMove::ObjectMoving& objBmove, const SpriteSize& Bsize);

void objA_isToLeftOfObjB(spriteMove::ObjectMoving& objAmove, spriteMove::ObjectMoving& objBmove, const SpriteSize& Bsize);//Not to be used from outside

void objAbouncesOnB_left(spriteMove::ObjectMoving& objAmove, spriteMove::ObjectMoving& objBmove);//Not to be used from outside

void objA_isToRightOfObjB(spriteMove::ObjectMoving& objAmove, spriteMove::ObjectMoving& objBmove, const SpriteSize& Bsize);//Not to be used from outside

void objA_bouncesOnB_right(spriteMove::ObjectMoving& objAmove, spriteMove::ObjectMoving& objBmove);//Not to be used from outside

void objA_notOnLeftOrRightOfB_obj(spriteMove::ObjectMoving& objAmove, spriteMove::ObjectMoving& objBmove);//Not to be used from outside

}

#endif //COLLISION_BOUNCING_PROCESSING_H