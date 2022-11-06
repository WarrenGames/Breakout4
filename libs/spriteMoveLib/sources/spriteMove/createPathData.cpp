#include "spriteMove/createPathData.h"
#include "spriteMove/movements.h"
#include "spriteMove/spriteMoveData.h"
#include <cassert>

void spriteMove::createPathData(spriteMove::MovementThings& moveThing, const spriteMove::Movements& movements, std::size_t moveNumber, Offset startPosition)
{
	assert( moveNumber < movements.getMovesCount() );
	
	for( std::size_t i{0} ; i < movements.getVectorCount(moveNumber) ; ++i )
	{
		moveThing.addMoveInfoElement( 	movements.getVectorChunk(moveNumber, i).x, 
										movements.getVectorChunk(moveNumber, i).y,
										startPosition.x + movements.getVectorChunk(moveNumber, i).x,
										startPosition.y + movements.getVectorChunk(moveNumber, i).y,
										movements.getVectorChunk(moveNumber, i).speed,
										movements.getVectorChunk(moveNumber, i).wait
										);
		startPosition.x += movements.getVectorChunk(moveNumber, i).x;
		startPosition.y += movements.getVectorChunk(moveNumber, i).y;
	}
}

void spriteMove::createPathData(spriteMove::MovementThings& moveThing, const spriteMove::VectorsGroup& path, Offset startPosition)
{
	for( auto const &segment : path.vectors )
	{
		moveThing.addMoveInfoElement( segment.x, segment.y, startPosition.x + segment.x, startPosition.y + segment.y, segment.speed, segment.wait);
		
		startPosition.x += segment.x;
		startPosition.y += segment.y;
	}
}