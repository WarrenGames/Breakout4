#ifndef COLLISION_BOUNCING_PROCESSING_H
#define COLLISION_BOUNCING_PROCESSING_H

class ObjectMoving;
struct SpriteSize;

namespace bouncing{

bool objectsCollide(const ObjectMoving& moveA, const SpriteSize& objAsize, const ObjectMoving& moveB, const SpriteSize& objBsize, int interval);
	
void processElementsBouncing(ObjectMoving& objAmove, ObjectMoving& objBmove, const SpriteSize& Bsize);

void objA_isToLeftOfObjB(ObjectMoving& objAmove, ObjectMoving& objBmove, const SpriteSize& Bsize);//Not to be used from outside

void objAbouncesOnB_left(ObjectMoving& objAmove, ObjectMoving& objBmove);//Not to be used from outside

void objA_isToRightOfObjB(ObjectMoving& objAmove, ObjectMoving& objBmove, const SpriteSize& Bsize);//Not to be used from outside

void objA_bouncesOnB_right(ObjectMoving& objAmove, ObjectMoving& objBmove);//Not to be used from outside

void objA_notOnLeftOrRightOfB_obj(ObjectMoving& objAmove, ObjectMoving& objBmove);//Not to be used from outside

}

#endif //COLLISION_BOUNCING_PROCESSING_H