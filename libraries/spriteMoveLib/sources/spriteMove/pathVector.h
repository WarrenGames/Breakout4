#ifndef PATH_VECTOR_H
#define PATH_VECTOR_H

#include <chrono>

namespace spriteMove{

struct MoveVector
{
	int x;
	int y;
	double speed;
	std::chrono::milliseconds wait;
	
	explicit MoveVector();
	~MoveVector() = default;
	MoveVector( const MoveVector& ) = default;
	MoveVector& operator= ( const MoveVector& ) = default;
};

}

#endif //PATH_VECTOR_H