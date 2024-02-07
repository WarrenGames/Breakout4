#ifndef ONE_PLAYER_CAMPAIGN_END_H
#define ONE_PLAYER_CAMPAIGN_END_H

struct Essentials;
struct PlayerData;

namespace onePlGame{

namespace campaignEnd{
	struct Interface;
	
	void context(Essentials& essentials, const PlayerData& playerData);
	
	void waitForUserInput(Essentials& essentials, bool& quitMenu);
	
	void drawEverything(Essentials& essentials, const onePlGame::campaignEnd::Interface& interface);
}

}

#endif //ONE_PLAYER_CAMPAIGN_END_H