#include "contexts/onePlayerGame/bestScoresMenu/mainInterface.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "consts/fontsConsts.h"
#include <cassert>

enum{ 	ScoresTitleFromShopCampaign, 
		ScoresTitleFromStandardCampaign, 
		ScoresQuit, 
		ScoresEasy, 
		ScoresAverage, 
		ScoresHard, 
		ScoresEmptyArray, 
		ScoresShopCampaign, 
		ScoresStandardCampaign, 
		ScoresMax };

ScoresInterface::ScoresInterface(Essentials& essentials):
	isLoadingPerfect{true},
	chosenCampaign{ onePlGame::CampaignWithShop },
	stdRaceScoresData{essentials, onePlGame::CampaignNoShop},
	shopRaceScoresData{essentials, onePlGame::CampaignWithShop},
	gradientWallpaper{essentials.logs, essentials.rndWnd, SDL_Rect{ 0, 0, GameScreenWidth, GameScreenHeight}, YellowColor, RedColor, GradientTextureOnY},
	languageTexts{essentials.logs.error, path::getLanguageFile(essentials.language, "1player_bestScores.txt"), ScoresMax}, 
	fancyFont{essentials.logs.error, FancyFontPath, FontMediumPointSize},
	stdRaceScoresTexts( onePlGame::SkillLevelMax ),
	shopRaceScoresTexts( onePlGame::SkillLevelMax ),
	emptyArrayText{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[ScoresEmptyArray], WhiteColor, TexturePosition{} },
	blueBrick{essentials.logs, essentials.rndWnd, "textures/sprites/bricks/blueRim.png"},
	purpleBrick{essentials.logs, essentials.rndWnd,"textures/sprites/bricks/purpleRim.png"},
	shopCampaign{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[ScoresShopCampaign], GreenColor, WhiteColor, 
					GameScreenWidth / 4, GameScreenHeight - SQR_SIZE / 2, true},
	standardCampaign{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[ScoresStandardCampaign], GreenColor, WhiteColor,
					GameScreenWidth * 3 / 4, GameScreenHeight - SQR_SIZE / 2, true},
	quitButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[ScoresQuit], GreenColor, MediumGrayColor, 
					GameScreenWidth - SQR_SIZE * 2, SQR_SIZE / 2, true}
{
	createScoresTexts(essentials, stdRaceScoresData, stdRaceScoresTexts);
	createScoresTexts(essentials, shopRaceScoresData, shopRaceScoresTexts);
	createSkillText(essentials, onePlGame::SkillLevelEasy, languageTexts[ScoresEasy]);
	createSkillText(essentials, onePlGame::SkillLevelIntermediate, languageTexts[ScoresAverage]);
	createSkillText(essentials, onePlGame::SkillLevelHard, languageTexts[ScoresHard]);
	createTitles(essentials);
}

ScoresInterface::ScoresInterface(Essentials& essentials, unsigned playerScore, unsigned skill, unsigned raceType):
	isLoadingPerfect{true},
	chosenCampaign{ onePlGame::CampaignWithShop },
	stdRaceScoresData{essentials, onePlGame::CampaignNoShop, playerScore, skill, raceType},
	shopRaceScoresData{essentials, onePlGame::CampaignWithShop, playerScore, skill, raceType},
	gradientWallpaper{essentials.logs, essentials.rndWnd, { 0, 0, GameScreenWidth, GameScreenHeight}, YellowColor, RedColor, GradientTextureOnY},
	languageTexts{essentials.logs.error, path::getLanguageFile(essentials.language, "1player_bestScores.txt"), ScoresMax}, 
	fancyFont{essentials.logs.error, FancyFontPath, FontMediumPointSize},
	stdRaceScoresTexts( onePlGame::SkillLevelMax ),
	shopRaceScoresTexts( onePlGame::SkillLevelMax ),
	emptyArrayText{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[ScoresEmptyArray], WhiteColor, TexturePosition{} },
	blueBrick{essentials.logs, essentials.rndWnd, "textures/sprites/bricks/blueRim.png"},
	purpleBrick{essentials.logs, essentials.rndWnd,"textures/sprites/bricks/purpleRim.png"},
	shopCampaign{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[ScoresShopCampaign], GreenColor, WhiteColor, 
					GameScreenWidth / 4, GameScreenHeight - SQR_SIZE / 2, true},
	standardCampaign{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[ScoresStandardCampaign], GreenColor, WhiteColor,
					GameScreenWidth * 3 / 4, GameScreenHeight - SQR_SIZE / 2, true},
	quitButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[ScoresQuit], GreenColor, MediumGrayColor, GameScreenWidth - SQR_SIZE * 2, SQR_SIZE / 2, true}
{
	createScoresTexts(essentials, stdRaceScoresData, stdRaceScoresTexts);
	createScoresTexts(essentials, shopRaceScoresData, shopRaceScoresTexts);
	createSkillText(essentials, onePlGame::SkillLevelEasy, languageTexts[ScoresEasy]);
	createSkillText(essentials, onePlGame::SkillLevelIntermediate, languageTexts[ScoresAverage]);
	createSkillText(essentials, onePlGame::SkillLevelHard, languageTexts[ScoresHard]);
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
		case onePlGame::CampaignWithShop:
			shopRaceScoresData.startSaving(essentials);
			break;
		case onePlGame::CampaignNoShop:
			stdRaceScoresData.startSaving(essentials);
			break;
		default:
			assert( false && "Error: bad switch value !" );
			break;
	}
}

void ScoresInterface::createScoresTexts(Essentials& essentials, const BestScoresData& data, std::vector< std::vector< TextureCombo > >& paramGraphics)
{
	assert( paramGraphics.size() == onePlGame::SkillLevelMax );
	for( std::size_t skill{0} ; skill < onePlGame::SkillLevelMax ; ++skill )
	{
		for( std::size_t sample{0} ; sample < data.getScoresNumber(skill) ; ++sample )
		{
			SDL_Color scoreSampleColor;
			if( data.getSample(skill, sample).scoreFromLastGame )
			{
				scoreSampleColor = MediumGrayColor;
			}
			else
			{
				scoreSampleColor = BlackColor;
			}
			paramGraphics[skill].emplace_back(TextureCombo{essentials.logs, essentials.rndWnd, fancyFont, data.getSample(skill, sample).getText(), 
																scoreSampleColor, 
												TexturePosition{GameScreenWidth * static_cast<int>(skill + 1) / 4,
																static_cast<int>(sample) * SQR_SIZE / 2 + SQR_SIZE * 4, true, true} } );
		}
	}
}

void ScoresInterface::drawAccordingToCampaign(Essentials& essentials)
{
	switch( chosenCampaign )
	{
		case onePlGame::CampaignWithShop:
			drawScores(essentials, shopRaceScoresTexts);
			break;
		case onePlGame::CampaignNoShop:
			drawScores(essentials, stdRaceScoresTexts);
			break;
		default:
			assert( "Error: wrong campaign type unsigned value" && false );
			break;
	}
}

void ScoresInterface::drawScores(Essentials& essentials, const std::vector< std::vector< TextureCombo > >& paramGraphics)
{
	assert( paramGraphics.size() == onePlGame::SkillLevelMax );
	for( std::size_t i{0} ; i < paramGraphics.size() ; ++i )
	{
		if( paramGraphics[i].empty() )
		{
			emptyArrayText.resetSpritePosition(TexturePosition{GameScreenWidth * (static_cast<int>(i) + 1) / 4, SQR_SIZE * 4, true, true} );
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
	skillsTexts.emplace_back( TextureCombo{essentials.logs, essentials.rndWnd, fancyFont, text, WhiteColor, 
								TexturePosition{GameScreenWidth * (skillNumber + 1) / 4, SQR_SIZE * 2, true, true} } );
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
	blueBrick.draw(essentials.rndWnd, GameScreenWidth / 4 - SQR_SIZE * 3, GameScreenHeight - SQR_SIZE);
	blueBrick.draw(essentials.rndWnd, GameScreenWidth / 4 - SQR_SIZE * 2, GameScreenHeight - SQR_SIZE);
	blueBrick.draw(essentials.rndWnd, GameScreenWidth / 4 - SQR_SIZE, GameScreenHeight - SQR_SIZE);
	blueBrick.draw(essentials.rndWnd, GameScreenWidth / 4, GameScreenHeight - SQR_SIZE);
	blueBrick.draw(essentials.rndWnd, GameScreenWidth / 4 + SQR_SIZE, GameScreenHeight - SQR_SIZE);
	blueBrick.draw(essentials.rndWnd, GameScreenWidth / 4 + SQR_SIZE * 2, GameScreenHeight - SQR_SIZE);
	purpleBrick.draw(essentials.rndWnd, GameScreenWidth * 3 / 4 - SQR_SIZE * 2, GameScreenHeight - SQR_SIZE);
	purpleBrick.draw(essentials.rndWnd, GameScreenWidth * 3 / 4 - SQR_SIZE * 3, GameScreenHeight - SQR_SIZE);
	purpleBrick.draw(essentials.rndWnd, GameScreenWidth * 3 / 4 - SQR_SIZE, GameScreenHeight - SQR_SIZE);
	purpleBrick.draw(essentials.rndWnd, GameScreenWidth * 3 / 4, GameScreenHeight - SQR_SIZE);
	purpleBrick.draw(essentials.rndWnd, GameScreenWidth * 3 / 4 + SQR_SIZE, GameScreenHeight - SQR_SIZE);
	purpleBrick.draw(essentials.rndWnd, GameScreenWidth * 3 / 4 + SQR_SIZE * 2, GameScreenHeight - SQR_SIZE);
}

void ScoresInterface::switchToShopCampaignScores()
{
	if( shopCampaign.buttonClicked() )
	{
		chosenCampaign = onePlGame::CampaignWithShop;
	}
}

void ScoresInterface::switchToStandardCampaignScores()
{
	if( standardCampaign.buttonClicked() )
	{
		chosenCampaign = onePlGame::CampaignNoShop;
	}
}

void ScoresInterface::drawTitle(Essentials& essentials) const
{
	assert( chosenCampaign < onePlGame::CampaignMax );
	titles[chosenCampaign].draw(essentials.rndWnd);
}

void ScoresInterface::createTitles(Essentials& essentials)
{
	titles.emplace_back( TextureCombo{ essentials.logs, essentials.rndWnd, fancyFont, languageTexts[ScoresTitleFromShopCampaign], MediumGrayColor, 
				TexturePosition{GameScreenWidth/2, SQR_SIZE, true, true } } );
	titles.emplace_back( TextureCombo{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[ScoresTitleFromStandardCampaign], MediumGrayColor, 
				TexturePosition{GameScreenWidth/2, SQR_SIZE, true, true} } );
}
