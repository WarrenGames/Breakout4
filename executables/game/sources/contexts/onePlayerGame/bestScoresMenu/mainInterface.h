#ifndef ONE_PLAYER_BEST_SCORES_MAIN_INTERFACE_H
#define ONE_PLAYER_BEST_SCORES_MAIN_INTERFACE_H

#include "contexts/onePlayerGame/bestScoresMenu/bestScoresData.h"
#include "texturing/texturesCombo.h"
#include "texturing/verticalGradientTexture.h"
#include "texts/textLoader.h"
#include "text/sdl2ttf_font.h"
#include "widgets/buttons/textButtonWidget.h"
#include "consts/onePlayerLevelConsts.h"
#include "consts/constPaths.h"
#include <vector>

struct Essentials;

class ScoresInterface
{
private:
	bool isLoadingPerfect;
	unsigned chosenCampaign;
	const BestScoresData stdRaceScoresData;
	const BestScoresData shopRaceScoresData;
	const TextureCombo gradientWallpaper;
	const TextsBlocks languageTexts;
	const sdl2::Font fancyFont;
	std::vector< TextureCombo > titles;
	std::vector< TextureCombo > skillsTexts;
	std::vector< std::vector< TextureCombo > > stdRaceScoresTexts;
	std::vector< std::vector< TextureCombo > > shopRaceScoresTexts;
	TextureCombo emptyArrayText;
	TextureCombo blueBrick;
	TextureCombo purpleBrick;
	TextButton shopCampaign;
	TextButton standardCampaign;
	TextButton quitButton;
	
public:
	explicit ScoresInterface(Essentials& essentials);
	explicit ScoresInterface(Essentials& essentials, unsigned playerScore, unsigned skill, unsigned raceType);
	~ScoresInterface() = default;
	ScoresInterface( const ScoresInterface& ) = delete;
	ScoresInterface& operator= ( const ScoresInterface& ) = delete;
	ScoresInterface( ScoresInterface&& ) = default;
	ScoresInterface& operator= ( ScoresInterface&& ) = default;
	
	void drawEverything(Essentials& essentials);
	void update(Essentials& essentials);
	bool quitMenu() const;
	void saveScoresToFile(Essentials& essentials, unsigned raceType) const;
	
private:
	void createScoresTexts(Essentials& essentials, const BestScoresData& data, std::vector< std::vector< TextureCombo > >& paramGraphics);
	void drawAccordingToCampaign(Essentials& essentials);
	void drawScores(Essentials& essentials, const std::vector< std::vector< TextureCombo > >& paramGraphics);
	void createSkillText(Essentials& essentials, int skillNumber, const std::string& text);
	void drawSkillsTexts(Essentials& essentials) const;
	void drawCampaignRims(Essentials& essentials);
	void switchToShopCampaignScores();
	void switchToStandardCampaignScores();
	void drawTitle(Essentials& essentials) const;
	void createTitles(Essentials& essentials);
};

#endif //ONE_PLAYER_BEST_SCORES_MAIN_INTERFACE_H