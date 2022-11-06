#ifndef DUELS_METAL_STRINGS_SWITCHS_DATA_H
#define DUELS_METAL_STRINGS_SWITCHS_DATA_H

#include "matrices/matrixStructs.h"
#include "time/accurateTime.h"
#include "SDL_rect.h"
#include <vector>

namespace metalStrings{ 
	
struct LevelBricks;

struct SingleSwitch
{
	unsigned state;//Can be: DirectionForward, DirectionRegress or DirectionStop
	Coord2D coords;//Contains the SQR_SIZE multiplier coordinates
	unsigned animFrame;
	unsigned playerNumberSwitch;
};

class SwitchsData
{
private:
	std::vector<SingleSwitch> switches; //Red player's switch is indexed as '0' , blue is indexed as '1'
	AccurateTimeDelay animDelay;
	
public:
	explicit SwitchsData(const metalStrings::LevelBricks& levelBricks);
	~SwitchsData() = default;
	SwitchsData( const SwitchsData& ) = delete;
	SwitchsData& operator= ( const SwitchsData& ) = delete;
	SwitchsData( SwitchsData&& ) = default;
	SwitchsData& operator= ( SwitchsData&& ) = default;
	
	const SingleSwitch& operator[](std::size_t switchNumber) const;
	SingleSwitch& operator[](std::size_t switchNumber);
	bool isPlayerOnSwitch(unsigned switchNumber, const SDL_Rect& playerRect) const;
	std::size_t size() const;
	void animTextures();
	void setSwitchsState(std::size_t switchNumber, unsigned stateEnum);
	void setPlayerSwitchState(std::size_t playerNum, unsigned stateEnum);
	void updateAnimation();
	
private:
	SDL_Rect getRectFromSwitch(unsigned switchNumber) const;
	void createSwitchesData(const metalStrings::LevelBricks& levelBricks);
};

}

#endif //DUELS_METAL_STRINGS_SWITCHS_DATA_H