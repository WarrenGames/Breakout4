#ifndef GAME_ONE_PLAYER_GAME_DEMO_RECORDING_CONTEXT_H
#define GAME_ONE_PLAYER_GAME_DEMO_RECORDING_CONTEXT_H

struct Essentials;

namespace onePlGame{
	namespace demoRecording{
		struct Interface;
		struct LevelSelection;
		
		void contextsList(Essentials& essentials);
		
		void mainContext(Essentials& essentials, unsigned& campaignType, bool& quitWholeContext);
		
		void campaignChoiceMainLoop(Essentials& essentials, onePlGame::demoRecording::Interface& interface, unsigned& campaignType, bool& quitWholeContext);
		
		void quitChoice(Essentials& essentials, bool& quitWholeContext);
		
		void shopCampaignSelection(Interface& interface, unsigned& campaignType);
		
		void noShopCampaignSelection(Interface& interface, unsigned& campaignType);
		
		void drawCampaignChoice(Essentials& essentials, const onePlGame::demoRecording::Interface& interface);
		
		void levelChoice(Essentials& essentials, unsigned& campaignType, bool& quitWholeContext);
		
		void levelChoiceMainLoop(Essentials& essentials, onePlGame::demoRecording::LevelSelection& levelSelection, bool& quitWholeContext);
		
		void drawLevelChoice(Essentials& essentials, const onePlGame::demoRecording::LevelSelection& levelSelection, bool& quitWholeContext);
		
		void runDemoRecording(Essentials& essentials, onePlGame::demoRecording::LevelSelection& levelSelection, bool& quitWholeContext);
		
		void setSomeStartingData(onePlGame::demoRecording::LevelSelection& levelSelection);
	}
}

#endif //GAME_ONE_PLAYER_GAME_DEMO_RECORDING_CONTEXT_H