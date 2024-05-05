#ifndef VERTICAL_BARRIER_DRAWING_H
#define VERTICAL_BARRIER_DRAWING_H

#include "texturing/texturesCombo.h"
#include "customTypes/positionTypes.h"
#include <vector>

struct Essentials;

class VerticalBarrierDrawing
{
private:
	std::vector< Offset > positions;//Top barrier has index '0' of this vector
	TextureCombo verticalBarrier;

public:
	explicit VerticalBarrierDrawing(Essentials& essentials, const std::vector<Offset>& barriersPositions);
	~VerticalBarrierDrawing() = default;
	VerticalBarrierDrawing( const VerticalBarrierDrawing& ) = delete;
	VerticalBarrierDrawing& operator= ( const VerticalBarrierDrawing& ) = delete;
	VerticalBarrierDrawing( VerticalBarrierDrawing&& ) = default;
	VerticalBarrierDrawing& operator= ( VerticalBarrierDrawing&& ) = default;
	
	void drawBarriers(Essentials& essentials);
	void moveUpBarrier(std::size_t barrierNumber);
	void moveDownBarrier(std::size_t barrierNumber);
	
	const Offset& getBarrierPosition(std::size_t playerNum) const;
	
	SDL_Rect getRect(std::size_t barrierNum) const;
	
	std::size_t size() const;
};

#endif //VERTICAL_BARRIER_DRAWING_H