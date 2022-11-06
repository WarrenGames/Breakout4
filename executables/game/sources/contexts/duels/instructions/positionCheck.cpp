#include "contexts/duels/instructions/positionCheck.h"
#include "customTypes/positionTypes.h"
#include "types/spriteSize.h"
#include "spriteMove/objectMove.h"
#include "SDL_rect.h"
#include "consts/constexprScreen.h"

bool isElementInsideOfScreen(const spriteMove::ObjectMoving& objectMove, const SpriteSize& size)
{
	return objectMove.get_x_position() + size.w / 2 >= 0 && objectMove.get_x_position() - size.w / 2 < GameScreenWidth 
			&& objectMove.get_y_position() + size.h / 2 >= 0 && objectMove.get_y_position() - size.h / 2 < GameScreenHeight;
}

bool isMoveObjectOverSpawnPoint(const spriteMove::ObjectMoving& move, const SpriteSize& size, const Offset& spawnPoint)
{
	return move.get_x_position() + size.w / 2  >= spawnPoint.x 
		&& move.get_x_position() - size.w / 2  < spawnPoint.x
		&& move.get_y_position() + size.h / 2 >= spawnPoint.y
		&& move.get_y_position() - size.h / 2 < spawnPoint.y;
}

bool doesMoveObjectCollideWithRect(const spriteMove::ObjectMoving& move, const SpriteSize& size, const SDL_Rect& rect)
{
	return move.get_x_position() + size.w / 2 >= rect.x
		&& move.get_x_position() - size.w / 2 < rect.x + rect.w
		&& move.get_y_position() + size.h / 2 >= rect.y
		&& move.get_y_position() - size.h / 2 < rect.y + rect.h;
}

bool doesRectsCollide(const SDL_Rect& rectOne, const SDL_Rect& rectTwo)
{
	return rectOne.x + rectOne.w >= rectTwo.x 
		&& rectOne.x < rectTwo.x + rectTwo.w 
		&& rectOne.y + rectOne.h >= rectTwo.y
		&& rectOne.y < rectTwo.y + rectTwo.h;
}