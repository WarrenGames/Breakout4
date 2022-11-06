#include "contexts/onePlayerGame/skillLevelChoice/graphicalInterface.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

onePlGame::skillChoice::Interface::Interface(Essentials& essentials):
	fancyFont{essentials.logs.error, FancyFontPath, FontBigPointSize},
	languageTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::ONE_PLAY_SKILL_LEVEL), onePlGame::skillChoice::TextSkillMax},
	screenTitle{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::skillChoice::TextChoose], WhiteColor, TexturePosition{GameScreenWidth/2, SQR_SIZE, true, true } },
	goBackButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::skillChoice::TextGoBack], GreenColor, WhiteColor, TexturePosition{GameScreenWidth/2, SQR_SIZE*12, true, true} },
	animIndexes{ 0, 0, 0 },
	animPositions{ Offset{ SQR_SIZE * 4, SQR_SIZE * 4}, Offset{ GameScreenWidth - SQR_SIZE * 6, SQR_SIZE * 6}, Offset{ SQR_SIZE * 4, SQR_SIZE * 8} }
{
	populateSkillButtons(essentials);
	createAnims(essentials);
}

void onePlGame::skillChoice::Interface::update(const Essentials& essentials)
{
	updateSkillButtons(essentials);
	goBackButton.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT));
	updateAnims();
}

void onePlGame::skillChoice::Interface::updateSkillButtons(const Essentials& essentials)
{
	for( auto &btn : skillButtons )
	{
		btn.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	}
}

void onePlGame::skillChoice::Interface::drawEverything(Essentials& essentials)
{
	screenTitle.draw(essentials.rndWnd);
	drawSkillButtons(essentials);
	goBackButton.drawButton(essentials.rndWnd);
	drawAnims(essentials);
}

void onePlGame::skillChoice::Interface::drawSkillButtons(Essentials& essentials) const
{
	for( auto const &btn : skillButtons )
	{
		btn.drawButton(essentials.rndWnd);
	}
}

void onePlGame::skillChoice::Interface::createAnims(Essentials& essentials)
{
	for( std::size_t i{0} ; i < RacketsAnimationsNumber ; ++i )
	{
		racketsTextures.emplace_back( TexturesFilesList{essentials.logs, essentials.rndWnd, RacketsFramesNumber, "textures/gameGUI/animations/rackets/racketAnim_" + std::to_string(i) + "_"} );
		racketsSprites.emplace_back( ConstAnimDraw{ racketsTextures.back() } );
	}
}

void onePlGame::skillChoice::Interface::updateAnims()
{
	if( animDelay.hasTimeElapsed( std::chrono::milliseconds{100} ) )
	{
		for( auto &anim : animIndexes )
		{
			if( anim + 1 < RacketsFramesNumber )
			{
				anim++;
			}
			else{
				anim = 0;
			}
		}
		animDelay.joinTimePoints();
	}
}

void onePlGame::skillChoice::Interface::drawAnims(Essentials& essentials)
{
	for( std::size_t i{0} ; i < RacketsAnimationsNumber ; ++i )
	{
		racketsSprites[i].draw(essentials.rndWnd, animPositions[i], animIndexes[i]);
	}
}

void onePlGame::skillChoice::Interface::populateSkillButtons(Essentials& essentials)
{
	skillButtons.emplace_back( TextButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::skillChoice::TextEasySelection], GreenColor, WhiteColor, 
											TexturePosition{ GameScreenWidth/2, SQR_SIZE*5, true, true} } );
	skillButtons.emplace_back( TextButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::skillChoice::TextMediumSelection], GreenColor, WhiteColor, 
											TexturePosition{ GameScreenWidth/2, SQR_SIZE*7, true, true} } );
	skillButtons.emplace_back( TextButton{essentials.logs, essentials.rndWnd, fancyFont, languageTexts[onePlGame::skillChoice::TextHardSelection], GreenColor, WhiteColor, 
											TexturePosition{ GameScreenWidth/2, SQR_SIZE*9, true, true} } );
}
