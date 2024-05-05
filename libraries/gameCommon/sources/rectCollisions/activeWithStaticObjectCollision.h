#ifndef GAME_COMMON_RECT_COLLISION_ACTIVE_WITH_STATIC_OBJECT_COLLISION_H
#define GAME_COMMON_RECT_COLLISION_ACTIVE_WITH_STATIC_OBJECT_COLLISION_H

//Collisions with an object 'A' that bounces and with an inert object 'B' (that doesn't bounce or move)

namespace spriteMove{ class ObjectMoving; }
struct SDL_Rect;

namespace collision{

namespace activeAndStatic{
	bool isThereCollision(const spriteMove::ObjectMoving& moveA, const SDL_Rect& rectA, const SDL_Rect& rectB, int interval);
	
	void processBouncing(spriteMove::ObjectMoving& moveA, const SDL_Rect& rectA, const SDL_Rect& rectB);
	
	//Bouncing onto north of static object B
	void bouncingOntoNorth(spriteMove::ObjectMoving& moveA, const SDL_Rect& rectA, const SDL_Rect& rectB);
	//Bouncing onto south of static object B
	void bouncingOntoSouth(spriteMove::ObjectMoving& moveA, const SDL_Rect& rectA, const SDL_Rect& rectB);
	//Bouncing onto west of static object B
	void bouncingOntoWest(spriteMove::ObjectMoving& moveA, const SDL_Rect& rectA, const SDL_Rect& rectB);
	//Bouncing onto east of static object B
	void bouncingOntoEast(spriteMove::ObjectMoving& moveA, const SDL_Rect& rectA, const SDL_Rect& rectB);
}

}

#endif //GAME_COMMON_RECT_COLLISION_ACTIVE_WITH_STATIC_OBJECT_COLLISION_H