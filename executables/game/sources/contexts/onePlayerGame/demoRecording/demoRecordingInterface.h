#ifndef GAME_ONE_PLAYER_GAME_DEMO_RECORDING_INTERFACE_H
#define GAME_ONE_PLAYER_GAME_DEMO_RECORDING_INTERFACE_H

#include "contexts/onePlayerGame/inGameMainMenu/campaignChoice/campaignChoiceGraphicalInterface.h"

struct Essentials;

namespace onePlGame{

namespace demoRecording{

struct Interface
{
	CampaignChoiceGui interface;
	bool quitMenu;
	
	explicit Interface(Essentials& essentials);
	~Interface() = default;
	Interface( const Interface& ) = delete;
	Interface& operator= ( const Interface& ) = delete;
	Interface( Interface&& ) = default;
	Interface& operator= ( Interface&& ) = default;
};

}

}

#endif //GAME_ONE_PLAYER_GAME_DEMO_RECORDING_INTERFACE_H