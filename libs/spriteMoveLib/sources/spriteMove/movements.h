#ifndef H_CLASS_MOVEMENTS
#define H_CLASS_MOVEMENTS

#include "spriteMove/pathVector.h"
#include <vector>
#include <string>

namespace spriteMove{

struct VectorsGroup
{
	std::vector<MoveVector> vectors;
	std::string moveName;

	explicit VectorsGroup(const std::string& name);
	~VectorsGroup() = default;
	VectorsGroup( const VectorsGroup& ) = default;
	VectorsGroup& operator= ( const VectorsGroup& ) = default;
	VectorsGroup( VectorsGroup&& ) = default;
	VectorsGroup& operator= ( VectorsGroup&& ) = default;
};

class Movements
{
private:
	std::vector< VectorsGroup > movements;

public:
	Movements() = default;
	~Movements() = default;
	Movements( const Movements& ) = default;
	Movements& operator= ( const Movements& ) = default;
	Movements( Movements&& ) = default;
	Movements& operator= ( Movements&& ) = default;
	void pushBackNewMove(const std::string& moveName);
	void addVectorToLastMove(const MoveVector& vectorChunk);
	std::size_t getMovesCount() const;
	std::size_t getVectorCount(std::size_t moveNumber) const;
	const MoveVector& getVectorChunk(std::size_t moveNumber, std::size_t vectorNumber) const;
	MoveVector& getVectorChunk(std::size_t moveNumber, std::size_t vectorNumber);
	const std::string& getMoveName(std::size_t moveNumber) const;
	const VectorsGroup& getPath(std::size_t pathNumber) const;
	VectorsGroup& getPath(std::size_t pathNumber);
	
	void addVectorsGroup(const VectorsGroup& vectorsGroup);
};

}

#endif // H_CLASS_MOVEMENTS
