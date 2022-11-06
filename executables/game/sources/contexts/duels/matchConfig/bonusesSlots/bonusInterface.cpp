#include "contexts/duels/matchConfig/bonusesSlots/bonusInterface.h"
#include "types/essentialsStruct.h"
#include "contexts/duels/matchConfig/interface/zoneChoiceThings.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "sounds/loadSound.h"
#include "texturing/texturePosition.h"
#include "contexts/duels/inGameObjects/gameElements/duelsTypes.h"
#include "contexts/duels/matchConfig/bonusesSlots/slotsConsts.h"
#include "contexts/duels/duelsConstexpr.h"
#include "consts/sdlColors.h"
#include "consts/fontsConsts.h"
#include <cassert>

enum{ BonusPresetTitle, BonusPresetSlot, BonusPresetSave, BonusPresetLoad, BonusPresetQuit, BonusPresetMax };

duels::BonusesInterface::BonusesInterface(Essentials& essentials):
	languagesTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::DUELS_BON_SLOT_BASE), BonusPresetMax},
	fancyFont{essentials.logs.error, FancyFontPath, FontSmallPointSize},
	data{essentials},
	screenTitle{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[BonusPresetTitle], MediumGrayColor, 
					TexturePosition{GameScreenWidth / 2, SQR_SIZE / 2, true, true} },
	quit{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[BonusPresetQuit], GreenColor, WhiteColor, GameScreenWidth - SQR_SIZE * 2, GameScreenHeight - SQR_SIZE, true},
	saveWithSuccess{ loadSoundChunk(essentials.logs.error, "sounds/addOneUp.wav" ) }
{
	loadBoxes(essentials);
	loadSlotsTexts(essentials);
	loadSaveButtons(essentials);
}

duels::BonusesInterface::operator bool() const
{
	return data && fancyFont && languagesTexts;
}

void duels::BonusesInterface::drawEverything(Essentials& essentials) const
{
	drawBoxes(essentials);
	drawSlotsTexts(essentials);
	drawSaveButtons(essentials);
	drawLoadButtons(essentials);
	screenTitle.draw(essentials.rndWnd);
	quit.drawButton(essentials.rndWnd);
}

void duels::BonusesInterface::drawBoxes(Essentials& essentials) const
{
	for( auto const &box : editBoxes )
	{
		box.drawBoxWithoutFocus(essentials.rndWnd);
	}
}

void duels::BonusesInterface::drawSlotsTexts(Essentials& essentials) const
{
	for( auto const &text : slotsTexts )
	{
		text.draw(essentials.rndWnd);
	}
}

void duels::BonusesInterface::drawSaveButtons(Essentials& essentials) const
{
	for( auto const &btn : saveButtons )
	{
		btn.drawButton(essentials.rndWnd);
	}
}

void duels::BonusesInterface::drawLoadButtons(Essentials& essentials) const
{
	for( auto const &btn : loadButtons )
	{
		btn.drawButton(essentials.rndWnd);
	}
}

void duels::BonusesInterface::update(Essentials& essentials)
{
	updateBoxes(essentials);
	updateSaveButtons(essentials);
	updateLoadButtons(essentials);
	quit.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
}

void duels::BonusesInterface::updateBoxes(Essentials& essentials)
{
	for( auto &box : editBoxes )
	{
		box.catchUserFocus(essentials.logs, essentials.rndWnd, essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	}
}

void duels::BonusesInterface::updateSaveButtons(Essentials& essentials)
{
	for( auto &btn : saveButtons )
	{
		btn.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	}
}

void duels::BonusesInterface::updateLoadButtons(Essentials& essentials)
{
	for( auto &btn : loadButtons )
	{
		btn.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	}
}

void duels::BonusesInterface::writeData(Essentials& essentials) const
{
	for( unsigned buttonNumber{0} ; buttonNumber < saveButtons.size() ; ++buttonNumber )
	{
		if( saveButtons[buttonNumber].buttonClicked() )
		{
			if( data.writeBonusesData(essentials, buttonNumber) )
				Mix_PlayChannel(-1, saveWithSuccess.get(), 0);
		}
	}
}

void duels::BonusesInterface::loadDataToCurrent(Essentials& essentials, ZoneChoiceThings& zoneChoiceThings, bool& quitMenu) const
{
	for( unsigned buttonNumber{0} ; buttonNumber < loadButtons.size() ; ++buttonNumber )
	{
		if( loadButtons[buttonNumber].buttonClicked() )
		{
			for( unsigned bonusNumber{0} ; bonusNumber < duels::DuelBonusMax ; ++bonusNumber )
			{	
				assert( bonusNumber < zoneChoiceThings.levelOptions.bonuses.size() );
				zoneChoiceThings.levelOptions.bonuses[bonusNumber] = data.getValue(buttonNumber, bonusNumber);
			}
			zoneChoiceThings.bonusBoxes.updateGraphics(essentials.logs, essentials.rndWnd);
			quitMenu = true;
		}
	}
}

void duels::BonusesInterface::loadBoxes(Essentials& essentials)
{
	for( unsigned slotNumber{0} ; slotNumber < SlotsNumber ; ++slotNumber )
	{
		for( unsigned bonusNumber{0} ; bonusNumber < duels::DuelBonusMax ; ++bonusNumber )
		{
			editBoxes.emplace_back( UintEditBox{essentials.logs, essentials.rndWnd, 
												SDL_Rect{static_cast<int>(slotNumber) * SQR_SIZE*2 + SQR_SIZE * 3, static_cast<int>(bonusNumber) * SQR_SIZE + SQR_SIZE * 2, 
															SQR_SIZE, SQR_SIZE / 2},
												FontSmallPointSize, data.getValue(slotNumber, bonusNumber) } );
		}
	}
}

void duels::BonusesInterface::loadSlotsTexts(Essentials& essentials)
{
	for( std::size_t slotNumber{0} ; slotNumber < SlotsNumber ; ++slotNumber )
	{
		slotsTexts.emplace_back( TextureCombo{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[BonusPresetSlot] + std::to_string(slotNumber), WhiteColor, 
													TexturePosition{static_cast<int>(slotNumber) * SQR_SIZE * 2 + SQR_SIZE * 3 + SQR_SIZE / 2, SQR_SIZE / 2 + SQR_SIZE, true, true } } );
	}
}

void duels::BonusesInterface::loadSaveButtons(Essentials& essentials)
{
	for( std::size_t slotNumber{0} ; slotNumber < SlotsNumber ; ++slotNumber )
	{
		saveButtons.emplace_back( TextButton{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[BonusPresetSave], GreenColor, WhiteColor,
												static_cast<int>(slotNumber) * SQR_SIZE * 2 + SQR_SIZE * 3 + SQR_SIZE / 2, 12 * SQR_SIZE, true} );
		loadButtons.emplace_back( TextButton{essentials.logs, essentials.rndWnd, fancyFont, languagesTexts[BonusPresetLoad], BlueColor, WhiteColor,
												static_cast<int>(slotNumber) * SQR_SIZE * 2 + SQR_SIZE * 3 + SQR_SIZE / 2, 13 * SQR_SIZE, true} );
	}
}