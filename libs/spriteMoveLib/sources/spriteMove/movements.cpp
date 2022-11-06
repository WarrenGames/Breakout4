#include "spriteMove/movements.h"
#include <cassert>

spriteMove::VectorsGroup::VectorsGroup(const std::string& name):
	moveName{name}
{
	
}

void spriteMove::Movements::pushBackNewMove(const std::string& moveName)
{
	movements.emplace_back( VectorsGroup{ moveName } );
}

void spriteMove::Movements::addVectorToLastMove(const MoveVector& vectorChunk)
{
	( movements.back() ).vectors.push_back(vectorChunk );
}

std::size_t spriteMove::Movements::getMovesCount() const
{
	return movements.size();
}

std::size_t spriteMove::Movements::getVectorCount(std::size_t moveNumber) const
{
	assert( moveNumber < movements.size() );
	return movements[moveNumber].vectors.size();
}

const spriteMove::MoveVector& spriteMove::Movements::getVectorChunk(std::size_t moveNumber, std::size_t vectorNumber) const
{
	assert( moveNumber < movements.size() && vectorNumber < movements[moveNumber].vectors.size() );
	
	return movements[moveNumber].vectors[vectorNumber];
}

spriteMove::MoveVector& spriteMove::Movements::getVectorChunk(std::size_t moveNumber, std::size_t vectorNumber)
{
	assert( moveNumber < movements.size() && vectorNumber < movements[moveNumber].vectors.size() );
	
	return movements[moveNumber].vectors[vectorNumber];
}

const std::string& spriteMove::Movements::getMoveName(std::size_t moveNumber) const
{
	assert( moveNumber < movements.size() );
	
	return movements[moveNumber].moveName;
}

const spriteMove::VectorsGroup& spriteMove::Movements::getPath(std::size_t pathNumber) const
{
	assert( pathNumber < movements.size() );
	return movements[pathNumber];
}

spriteMove::VectorsGroup& spriteMove::Movements::getPath(std::size_t pathNumber)
{
	assert( pathNumber < movements.size() );
	return movements[pathNumber];
}

void spriteMove::Movements::addVectorsGroup(const VectorsGroup& vectorsGroup)
{
	movements.emplace_back(vectorsGroup);
}