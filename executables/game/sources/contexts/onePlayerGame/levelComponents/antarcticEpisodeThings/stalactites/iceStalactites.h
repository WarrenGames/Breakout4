#ifndef ONE_PLAYER_GAME_ICE_STALACTITES_DATA_H
#define ONE_PLAYER_GAME_ICE_STALACTITES_DATA_H

#include "contexts/gameCommon/stalactites/onePlayerStalactiteData.h"
#include "contexts/gameCommon/stalactites/racketFreezesDurationsLoader.h"
#include "time/accurateTime.h"

struct Essentials;
struct PlayerData;
struct OnePlayerRacket;
class SoundHandler;
class StalactitesDrawer;
class RectLoader;

class IceStalactitesElements
{
private:
	std::vector< OnePlayerStalactiteData > elements;
	std::vector< int > decal;
	AccurateTimeDelay rumbleDelay;
	AccurateTimeDelay moveDelay;
	freezes::FreezeDurations freezeDurations;
	bool isLoadingPerfect;
	
public:
	explicit IceStalactitesElements(Essentials& essentials, const PlayerData& playerData);
	~IceStalactitesElements() = default;
	IceStalactitesElements( const IceStalactitesElements& ) = delete;
	IceStalactitesElements& operator= ( const IceStalactitesElements& ) = delete;
	IceStalactitesElements( IceStalactitesElements&& ) = default;
	IceStalactitesElements& operator= ( IceStalactitesElements&& ) = default;
	
	bool wasLoadingPerfect() const;
	void updateStalactites(const StalactitesDrawer& drawer, const RectLoader& rects);
	void updateStalactitesTimers();
	void testCollisionsWithRacket(OnePlayerRacket& playerRacket, const StalactitesDrawer& drawer, const RectLoader& rects, const PlayerData& playerData, const SoundHandler& sounds);
	std::vector< OnePlayerStalactiteData >::const_iterator begin() const;
	std::vector< OnePlayerStalactiteData >::const_iterator end() const;
	
private:
	void setDecalValues();
	void loadStalactitesConfig(Essentials& essentials, const PlayerData& playerData);
	void loadSingleStalactite(Essentials& essentials, const PlayerData& playerData, std::istringstream& lineStream, unsigned lineNum);
	void logEverythingWentFine(Essentials& essentials, const PlayerData& playerData) const;
	void updateRumble();
	void updateFall();
};

#endif //ONE_PLAYER_GAME_ICE_STALACTITES_DATA_H