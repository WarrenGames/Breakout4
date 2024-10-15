#ifndef GAME_COMMON_STALACTITES_DATA_H
#define GAME_COMMON_STALACTITES_DATA_H

#include "spriteMove/objectMove.h"
#include <vector>

struct SDL_Rect;
struct Offset;

class StalactiteData
{
private:
	spriteMove::ObjectMoving move;
	Offset startPosition;
	std::size_t trembleIndex;
	unsigned direction;
	unsigned rumbleCount;
	unsigned state;

public:
	explicit StalactiteData(const Offset& position);
	explicit StalactiteData(const Offset& position, unsigned newDirection);
	~StalactiteData() = default;
	StalactiteData( const StalactiteData& ) = delete;
	StalactiteData& operator= ( const StalactiteData& ) = delete;
	StalactiteData( StalactiteData&& ) = default;
	StalactiteData& operator= ( StalactiteData&& ) = default;
	
	void rumble(const std::vector< int >& rumbleArray);
	void incrementRumbleIndex(const std::vector< int >& rumbleArray);
	void startFallingIfRumbleEnds();
	void makeFalling();
	
	void resetStalactitePosition();
	unsigned getDirection() const;
	Offset getPosition() const;
	int getXCoordinate() const;
	int getYCoordinate() const;
	void setState(unsigned newState);
	unsigned getState() const;
	
	bool doesCollideWithRacket(const SDL_Rect& racketRect, const Offset& stalactiteTextureDimensions, const SDL_Rect& stalactiteRect) const;
};

#endif //GAME_COMMON_STALACTITES_DATA_H