#ifndef CAMPAIGN_CHOICE_CONTEXT_H
#define CAMPAIGN_CHOICE_CONTEXT_H

struct Essentials;
struct CampaignChoiceGui;

namespace campaignChoice{
	void mainContext(Essentials& essentials, unsigned skillLevel);
	
	void updateInterface(Essentials& essentials, CampaignChoiceGui& interface);
	
	void redirectPlayer(Essentials& essentials, unsigned skillLevel, const CampaignChoiceGui& interface, bool& quitCampChoice);
	
	void runShopRace(Essentials& essentials, unsigned skillLevel, const CampaignChoiceGui& interface, bool& quitCampChoice);
	
	void runStandardRace(Essentials& essentials, unsigned skillLevel, const CampaignChoiceGui& interface, bool& quitCampChoice);
	
	void drawEverything(Essentials& essentials, const CampaignChoiceGui& interface, bool quitCampChoice);
	
	void quitChoice(Essentials& essentials, bool& quitCampChoice);
}

#endif //CAMPAIGN_CHOICE_CONTEXT_H