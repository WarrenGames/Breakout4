#ifndef SPRITE_MOVE_STAR_TYPE_HANDLE_FUNCTIONS_H
#define SPRITE_MOVE_STAR_TYPE_HANDLE_FUNCTIONS_H

struct Offset;

namespace spriteMove{
	
	struct MovementThings;
	struct StarTypeThings;
	
	void handleStarSpriteMove(spriteMove::MovementThings& move, spriteMove::StarTypeThings& starSprite, const Offset& increment);
	
	void handleAnim1DirMove(spriteMove::MovementThings& move, spriteMove::StarTypeThings& starSprite, const Offset& increment);
	
	void waitFirstTimeIfAny(spriteMove::MovementThings& move, spriteMove::StarTypeThings& starSprite);
	
	bool canCarryOnWithSameDir(const spriteMove::MovementThings& move, const spriteMove::StarTypeThings& starSprite);
	
	bool canCarryOnWithDifferentDir(const spriteMove::MovementThings& move, const spriteMove::StarTypeThings& starSprite);
	
	bool hasReachedPathEnd(const spriteMove::MovementThings& move);
}

#endif //SPRITE_MOVE_STAR_TYPE_HANDLE_FUNCTIONS_H