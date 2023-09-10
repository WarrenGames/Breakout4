#ifndef ONE_PLAYER_LEVEL_RIMS_H
#define ONE_PLAYER_LEVEL_RIMS_H

#include "texturing/texturesCombo.h"
#include "matrices/matrix2D.h"
#include "time/accurateTime.h"
#include <vector>

struct Essentials;

class OnePlayerRims
{
private:
	TextureCombo rimTexture;
	MatrixTemp2D<SDL_Rect> rimsCoordinates;
	int activesRimsNumber;
	std::vector< unsigned > rimsMovement;
	AccurateTimeDelay rimMovementDelay;

public:
	explicit OnePlayerRims(Essentials& essentials, int rimsStartState);
	~OnePlayerRims() = default;
	OnePlayerRims( const OnePlayerRims& ) = delete;
	OnePlayerRims& operator= ( const OnePlayerRims& ) = delete;
	OnePlayerRims( OnePlayerRims&& ) = default;
	OnePlayerRims& operator= ( OnePlayerRims&& ) = default;
	
	void update();
	int getRimsStatus() const;
	void changeStatus(int change);
	void drawEverything(Essentials& essentials);
	
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