#ifndef ONE_PLAYER_LEVEL_RIMS_H
#define ONE_PLAYER_LEVEL_RIMS_H

#include "matrices/matrix2D.h"
#include "time/accurateTime.h"
#include "SDL_rect.h"
#include <vector>

class OnePlayerRimsState
{
private:
	MatrixTemp2D<SDL_Rect> rimsCoordinates;
	int activesRimsNumber;
	std::vector< unsigned > rimsMovement;
	AccurateTimeDelay rimMovementDelay;

public:
	explicit OnePlayerRimsState(int rimsStartState);
	~OnePlayerRimsState() = default;
	OnePlayerRimsState( const OnePlayerRimsState& ) = delete;
	OnePlayerRimsState& operator= ( const OnePlayerRimsState& ) = delete;
	OnePlayerRimsState( OnePlayerRimsState&& ) = default;
	OnePlayerRimsState& operator= ( OnePlayerRimsState&& ) = default;
	
	void update();
	int getRimsStatus() const;
	unsigned getRimMovement(std::size_t index) const;
	void changeStatus(int change);

	std::vector<SDL_Rect>::const_iterator begin() const;
	std::vector<SDL_Rect>::const_iterator end() const;
	
private:
	void moveActiveRims();
	void actWithRimStatus(std::size_t rimIndex);
	void moveRim(std::size_t rimIndex, int offsetAdd);
	
	void watchStatus();
	void setRimMoveType(int rimNum);
	
	void initializeOffsets(int rimsStartState);
};

#endif //ONE_PLAYER_LEVEL_RIMS_H