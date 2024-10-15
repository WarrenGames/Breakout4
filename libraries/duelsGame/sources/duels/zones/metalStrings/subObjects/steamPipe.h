#ifndef DUELS_FACTORY_ZONE_STEAM_PIPE_H
#define DUELS_FACTORY_ZONE_STEAM_PIPE_H

#include "texturing/texturesCombo.h"
#include "steamData/steamSample.h"
#include <vector>
#include <memory>

struct Essentials;

class SteamPipe
{	
private:
	bool isLoadingPerfect;
	TextureCombo steamPipe;
	std::vector< TextureCombo > steamAnim;
	AccurateTimeDelay steamAnimDelay;
	std::vector< std::unique_ptr<SteamSample> > steamSamples;
	AccurateTimeDelay createDelay;
	
public:
	explicit SteamPipe(Essentials& essentials, const Offset& pipePosition);
	~SteamPipe() = default;
	SteamPipe( const SteamPipe& ) = delete;
	SteamPipe& operator= ( const SteamPipe& ) = delete;
	SteamPipe( SteamPipe&& ) = default;
	SteamPipe& operator= ( SteamPipe&& ) = default;
	
	operator bool() const;
	
	void update();
	void drawPipe(Essentials& essentials) const;
	void drawSteamSamples(Essentials& essentials);
	
private:
	void loadSteamAnimation(Essentials& essentials);
	void animateSteamClouds();
	void moveSteamClouds();
	void revokeOutdoorsClouds();
	void createNewSteamCloud();

};

#endif //DUELS_FACTORY_ZONE_STEAM_PIPE_H