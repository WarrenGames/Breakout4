#include "contexts/onePlayerGame/bestScoresMenu/mainInterface.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/fontsConsts.h"
#include <cassert>

enum{ 	SCORES_TITLE_FROM_SHOP_CAMP, 
		SCORES_TITLE_FROM_STD_CAMP, 
		SCORES_QUIT, 
		SCORES_EASY, 
		SCORES_AVERAGE, 
		SCORES_HARD, 
		SCORES_EMPTY_ARRAY, 
		SCORES_SHOP_CAMPAIGN, 
		SCORES_STD_CAMPAIGN, 
		SCORES_MAX };

ScoresInterface::ScoresInterface(Essentials& essentials):
	isLoadingPerfect{true},
	chosenCampaign{ onePlGame::CAMPAIGN_WITH_SHOP },
	stdRaceScoresData{essentials, onePlGame::CAMPAIGN_NO_SHOP},
	shopRaceScoresData{essentials, onePlGame::CAMPAIGN_WITH_SHOP},
	gradientWallpaper{essentials.logs, essentials.rndWnd, SDL_Rect{ 0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT}, YELLOW_COL, RED_COL, GRAD_TEX_ON_Y},
	languageTexts{essentials.logs.error, path::getLanguageFile(essentials.language, "1player_bestScores.txt"), SCORES_MAX}, 
	fancyFont{essentials.logs.error, FANCYFONTPATH, FONT_MEDIUM_PTSIZE},
	stdRaceScoresTexts( onePlGame::SKILL_LEVEL_MAX ),
	shopRaceScoresTexts( onePlGame::SKILL_LEVEL_MAX ),
	emptyArrayText{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[SCORES_EMPTY_ARRAY], WHITE_COL, TexturePosition{} },
	blueBrick{essentials.logs, essentials.rndWnd, "textures/sprites/bricks/blueRim.png"},
	purpleBrick{essentials.logs, essentials.rndWnd,"textures/sprites/bricks/purpleRim.png"},
	shopCampaign{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[SCORES_SHOP_CAMPAIGN], GREEN_COL, WHITE_COL, 
					GAME_SCREEN_WIDTH / 4, GAME_SCREEN_HEIGHT - SQR_SIZE / 2, true},
	standardCampaign{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[SCORES_STD_CAMPAIGN], GREEN_COL, WHITE_COL,
					GAME_SCREEN_WIDTH * 3 / 4, GAME_SCREEN_HEIGHT - SQR_SIZE / 2, true},
	quitButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[SCORES_QUIT], GREEN_COL, MEDIUM_GRAY_COL, 
					GAME_SCREEN_WIDTH - SQR_SIZE * 2, SQR_SIZE / 2, true}
{
	createScoresTexts(essentials, stdRaceScoresData, stdRaceScoresTexts);
	createScoresTexts(essentials, shopRaceScoresData, shopRaceScoresTexts);
	createSkillText(essentials, onePlGame::SKILL_LEVEL_EASY, languageTexts[SCORES_EASY]);
	createSkillText(essentials, onePlGame::SKILL_LEVEL_INTERMEDIATE, languageTexts[SCORES_AVERAGE]);
	createSkillText(essentials, onePlGame::SKILL_LEVEL_HARD, languageTexts[SCORES_HARD]);
	createTitles(essentials);
}

ScoresInterface::ScoresInterface(Essentials& essentials, unsigned playerScore, unsigned skill, unsigned raceType):
	isLoadingPerfect{true},
	chosenCampaign{ onePlGame::CAMPAIGN_WITH_SHOP },
	stdRaceScoresData{essentials, onePlGame::CAMPAIGN_NO_SHOP, playerScore, skill, raceType},
	shopRaceScoresData{essentials, onePlGame::CAMPAIGN_WITH_SHOP, playerScore, skill, raceType},
	gradientWallpaper{essentials.logs, essentials.rndWnd, { 0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT}, YELLOW_COL, RED_COL, GRAD_TEX_ON_Y},
	languageTexts{essentials.logs.error, path::getLanguageFile(essentials.language, "1player_bestScores.txt"), SCORES_MAX}, 
	fancyFont{essentials.logs.error, FANCYFONTPATH, FONT_MEDIUM_PTSIZE},
	stdRaceScoresTexts( onePlGame::SKILL_LEVEL_MAX ),
	shopRaceScoresTexts( onePlGame::SKILL_LEVEL_MAX ),
	emptyArrayText{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[SCORES_EMPTY_ARRAY], WHITE_COL, TexturePosition{} },
	blueBrick{essentials.logs, essentials.rndWnd, "textures/sprites/bricks/blueRim.png"},
	purpleBrick{essentials.logs, essentials.rndWnd,"textures/sprites/bricks/purpleRim.png"},
	shopCampaign{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[SCORES_SHOP_CAMPAIGN], GREEN_COL, WHITE_COL, 
					GAME_SCREEN_WIDTH / 4, GAME_SCREEN_HEIGHT - SQR_SIZE / 2, true},
	standardCampaign{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[SCORES_STD_CAMPAIGN], GREEN_COL, WHITE_COL,
					GAME_SCREEN_WIDTH * 3 / 4, GAME_SCREEN_HEIGHT - SQR_SIZE / 2, true},
	quitButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[SCORES_QUIT], GREEN_COL, MEDIUM_GRAY_COL, GAME_SCREEN_WIDTH - SQR_SIZE * 2, SQR_SIZE / 2, true}
{
	createScoresTexts(essentials, stdRaceScoresData, stdRaceScoresTexts);
	createScoresTexts(essentials, shopRaceScoresData, shopRaceScoresTexts);
	createSkillText(essentials, onePlGame::SKILL_LEVEL_EASY, languageTexts[SCORES_EASY]);
	createSkillText(essentials, onePlGame::SKILL_LEVEL_INTERMEDIATE, languageTexts[SCORES_AVERAGE]);
	createSkillText(essentials, onePlGame::SKILL_LEVEL_HARD, languageTexts[SCORES_HARD]);
	createTitles(essentials);
}

void ScoresInterface::drawEverything(Essentials& essentials)
{
	gradientWallpaper.draw(essentials.rndWnd);
	drawTitle(essentials);
	drawSkillsTexts(essentials);
	drawAccordingToCampaign(essentials);
	quitButton.drawButton(essentials.rndWnd);
	drawCampaignRims(essentials);
	shopCampaign.drawButton(essentials.rndWnd);
	standardCampaign.drawButton(essentials.rndWnd);
}

void ScoresInterface::update(Essentials& essentials)
{
	quitButton.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	shopCampaign.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	standardCampaign.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	switchToShopCampaignScores();
	switchToStandardCampaignScores();
}

bool ScoresInterface::quitMenu() const
{
	return quitButton.buttonClicked();
}

void ScoresInterface::saveScoresToFile(Essentials& essentials, unsigned raceType) const
{
	switch( raceType )
	{
		case onePlGame::CAMPAIGN_WITH_SHOP:
			shopRaceScoresData.startSaving(essentials);
			break;
		case onePlGame::CAMPAIGN_NO_SHOP:
			stdRaceScoresData.startSaving(essentials);
			break;
		default:
			assert( false && "Error: bad switch value !" );
			break;
	}
}

void ScoresInterface::createScoresTexts(Essentials& essentials, const BestScoresData& data, std::vector< std::vector< TextureCombo > >& paramGraphics)
{
	assert( paramGraphics.size() == onePlGame::SKILL_LEVEL_MAX );
	for( std::size_t skill{0} ; skill < onePlGame::SKILL_LEVEL_MAX ; ++skill )
	{
		for( std::size_t sample{0} ; sample < data.getScoresNumber(skill) ; ++sample )
		{
			SDL_Color scoreSampleColor;
			if( data.getSample(skill, sample).scoreFromLastGame )
			{
				scoreSampleColor = MEDIUM_GRAY_COL;
			}
			else
			{
				scoreSampleColor = BLACK_COL;
			}
			paramGraphics[skill].emplace_back(TextureCombo{essentials.logs, essentials.rndWnd, fancyFont, data.getSample(skill, sample).getText(), 
																scoreSampleColor, 
												TexturePosition{GAME_SCREEN_WIDTH * static_cast<int>(skill + 1) / 4,
																static_cast<int>(sample) * SQR_SIZE / 2 + SQR_SIZE * 4, true, true} } );
		}
	}
}

void ScoresInterface::drawAccordingToCampaign(Essentials& essentials)
{
	switch( chosenCampaign )
	{
		case onePlGame::CAMPAIGN_WITH_SHOP:
			drawScores(essentials, shopRaceScoresTexts);
			break;
		case onePlGame::CAMPAIGN_NO_SHOP:
			drawScores(essentials, stdRaceScoresTexts);
			break;
		default:
			assert( "Error: wrong campaign type unsigned value" && false );
			break;
	}
}

void ScoresInterface::drawScores(Essentials& essentials, const std::vector< std::vector< TextureCombo > >& paramGraphics)
{
	assert( paramGraphics.size() == onePlGame::SKILL_LEVEL_MAX );
	for( std::size_t i{0} ; i < paramGraphics.size() ; ++i )
	{
		if( paramGraphics[i].empty() )
		{
			emptyArrayText.resetSpritePosition(TexturePosition{GAME_SCREEN_WIDTH * (static_cast<int>(i) + 1) / 4, SQR_SIZE * 4, true, true} );
			emptyArrayText.draw(essentials.rndWnd);
		}
		else{
			for( auto const &score : paramGraphics[i] )
			{
				score.draw(essentials.rndWnd);
			}
		}
	}
}

void ScoresInterface::createSkillText(Essentials& essentials, int skillNumber, const std::string& text)
{
	skillsTexts.emplace_back( TextureCombo{essentials.logs, essentials.rndWnd, fancyFont, text, WHITE_COL, 
								TexturePosition{GAME_SCREEN_WIDTH * (skillNumber + 1) / 4, SQR_SIZE * 2, true, true} } );
}

void ScoresInterface::drawSkillsTexts(Essentials& essentials) const
{
	for( auto const &text : skillsTexts )
	{
		text.draw(essentials.rndWnd);
	}
}

void ScoresInterface::drawCampaignRims(Essentials& essentials)
{
	blueBrick.draw(essentials.rndWnd, GAME_SCREEN_WIDTH / 4 - SQR_SIZE * 3, GAME_SCREEN_HEIGHT - SQR_SIZE);
	blueBrick.draw(essentials.rndWnd, GAME_SCREEN_WIDTH / 4 - SQR_SIZE * 2, GAME_SCREEN_HEIGHT - SQR_SIZE);
	blueBrick.draw(essentials.rndWnd, GAME_SCREEN_WIDTH / 4 - SQR_SIZE, GAME_SCREEN_HEIGHT - SQR_SIZE);
	blueBrick.draw(essentials.rndWnd, GAME_SCREEN_WIDTH / 4, GAME_SCREEN_HEIGHT - SQR_SIZE);
	blueBrick.draw(essentials.rndWnd, GAME_SCREEN_WIDTH / 4 + SQR_SIZE, GAME_SCREEN_HEIGHT - SQR_SIZE);
	blueBrick.draw(essentials.rndWnd, GAME_SCREEN_WIDTH / 4 + SQR_SIZE * 2, GAME_SCREEN_HEIGHT - SQR_SIZE);
	purpleBrick.draw(essentials.rndWnd, GAME_SCREEN_WIDTH * 3 / 4 - SQR_SIZE * 2, GAME_SCREEN_HEIGHT - SQR_SIZE);
	purpleBrick.draw(essentials.rndWnd, GAME_SCREEN_WIDTH * 3 / 4 - SQR_SIZE * 3, GAME_SCREEN_HEIGHT - SQR_SIZE);
	purpleBrick.draw(essentials.rndWnd, GAME_SCREEN_WIDTH * 3 / 4 - SQR_SIZE, GAME_SCREEN_HEIGHT - SQR_SIZE);
	purpleBrick.draw(essentials.rndWnd, GAME_SCREEN_WIDTH * 3 / 4, GAME_SCREEN_HEIGHT - SQR_SIZE);
	purpleBrick.draw(essentials.rndWnd, GAME_SCREEN_WIDTH * 3 / 4 + SQR_SIZE, GAME_SCREEN_HEIGHT - SQR_SIZE);
	purpleBrick.draw(essentials.rndWnd, GAME_SCREEN_WIDTH * 3 / 4 + SQR_SIZE * 2, GAME_SCREEN_HEIGHT - SQR_SIZE);
}

void ScoresInterface::switchToShopCampaignScores()
{
	if( shopCampaign.buttonClicked() )
	{
		chosenCampaign = onePlGame::CAMPAIGN_WITH_SHOP;
	}
}

void ScoresInterface::switchToStandardCampaignScores()
{
	if( standardCampaign.buttonClicked() )
	{
		chosenCampaign = onePlGame::CAMPAIGN_NO_SHOP;
	}
}

void ScoresInterface::drawTitle(Essentials& essentials) const
{
	assert( chosenCampaign < onePlGame::CAMPAIGN_MAX );
	titles[chosenCampaign].draw(essentials.rndWnd);
}

void ScoresInterface::createTitles(Essentials& essentials)
{
	titles.emplace_back( TextureCombo{ essentials.logs, essentials.rndWnd, fancyFont, languageTexts[SCORES_TITLE_FROM_SHOP_CAMP], MEDIUM_GRAY_COL, 
				TexturePosition{GAME_SCREEN_WIDTH/2, SQR_SIZE, true, true } } );
	titles.emplace_back( TextureCombo{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[SCORES_TITLE_FROM_STD_CAMP], MEDIUM_GRAY_COL, 
				TexturePosition{GAME_SCREEN_WIDTH/2, SQR_SIZE, true, true} } );
}
