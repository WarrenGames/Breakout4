#ifndef ONE_PLAYER_RIMS_GLOBAL_SYSTEM_H
#define ONE_PLAYER_RIMS_GLOBAL_SYSTEM_H

#include "levelComponents/rims/playerRims.h"
#include "levelComponents/rims/rimsScoreStock.h"
#include "levelComponents/rims/rimsScoreValueDrawing.h"
#include "levelComponents/rims/rimsPast.h"
#include "texturing/texturesCombo.h"

struct Essentials;

class OnePlayerRimsSystem
{
private:
	TextureCombo rimTexture;
	OnePlayerRimsState rimsState;
	RimsScoreStock rimsScoresStock;
	RimsScoreValueDrawing rimsScoreValueDrawing;
	OnePlayerRimsPast rimsPast;
	AccurateTimeDelay pointsInfosDuration;
	std::size_t textIndex;
	bool canDrawBonusText;
	
public:
	OnePlayerRimsSystem(Essentials& essentials, int rimsStartState);
	~OnePlayerRimsSystem() = default;
	OnePlayerRimsSystem( const OnePlayerRimsSystem& ) = delete;
	OnePlayerRimsSystem& operator= ( const OnePlayerRimsSystem& ) = delete;
	OnePlayerRimsSystem( OnePlayerRimsSystem&& ) = default;
	OnePlayerRimsSystem& operator= ( OnePlayerRimsSystem&& ) = default;
	
	std::vector<SDL_Rect>::const_iterator begin() const;
	std::vector<SDL_Rect>::const_iterator end() const;
	
	void drawRims(Essentials& essentials);
	void drawPointsText(Essentials& essentials) const;
	
	void rimsUpdate();
	int getRimsStatus() const;
	void changeStatus(int change);
	void setDrawBonusTextFlag();
	void declareRimAppeared();
	int getReservedScoreIfAny();
	
private:
	void updateDrawBoolValue();
	void setRimWasActiveOnce(int change);
	void activeNewTextOrDefaultOne(int status);
	void stockScore(int change);
	
};

#endif //ONE_PLAYER_RIMS_GLOBAL_SYSTEM_H