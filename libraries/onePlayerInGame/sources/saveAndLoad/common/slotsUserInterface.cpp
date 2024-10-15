#include "saveAndLoad/common/slotsUserInterface.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "crossLevel/playerData.h"
#include "generic/fileSystem/fileProcessing/pathMakers.h"
#include "loading/loadData.h"
#include "saving/saveData.h"
#include "exceptions/readErrorExcept.h"
#include "exceptions/writeErrorExcept.h"
#include "fileSystem/fileSystem.h"
#include "consts/constexprScreen.h"
#include "consts/fontsConsts.h"
#include "consts/sdlColors.h"
#include "gameSlots/slotConsts.h"
#include <cassert>

constexpr SDL_Color SlotSquareColor = {215, 207, 174, 255};
constexpr SDL_Color TitleColor = { 223, 223, 0, 255 };

SlotsUserInterface::SlotsUserInterface(Essentials& essentials, unsigned contextFocus):
	localeTexts{essentials.logs.error, path::getLanguageFile(essentials.language, file::OnePlayerSaveAndLoad), SaveNameFocusingGameMax},
	arial{essentials.logs.error, ArialFontPath, FontSmallPointSize},
	fancyFont{essentials.logs.error, FancyFontPath, FontMediumPointSize},
	slotSquareTexture{essentials.logs, essentials.rndWnd, SlotSquareColor, SaveSlotSquareWidth, SaveSlotSquareHeight},
	quitButton{essentials.logs, essentials.rndWnd, fancyFont, localeTexts[SaveNameQuitMenu], GreenColor, WhiteColor, GameScreenWidth - SQR_SIZE * 2, SQR_SIZE, true},
	slotsData(SlotsNumber)
{
	createSlotsGraphics(essentials);
	createTitle(essentials, contextFocus);
	browseAllSlotsForInitialization(essentials);
}

void SlotsUserInterface::saveToFile(Essentials& essentials, const PlayerData& playerData)
{
	if( essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) )
	{
		for( unsigned slotIndex{0} ; slotIndex < SlotsNumber ; ++slotIndex )
		{
			if( slotsGraphics[slotIndex].isMouseOverSlot(essentials.inp.getMousePosition() ) )
			{
				savePlayerDataToSlot(essentials, slotIndex, playerData);
			}
		}
	}
}

bool SlotsUserInterface::canLoadSlot(Essentials& essentials, PlayerData& playerData) const
{
	if( essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) )
	{
		for( unsigned slotIndex{0} ; slotIndex < SlotsNumber ; ++slotIndex )
		{
			if( slotsData[slotIndex].isAnActiveSave && slotsGraphics[slotIndex].isMouseOverSlot(essentials.inp.getMousePosition() ) )
			{
				playerData = slotsData[slotIndex];
				return true;
			}
		}
	}
	return false;
}

void SlotsUserInterface::drawInterface(Essentials& essentials) const
{
	title.draw(essentials.rndWnd);
	quitButton.drawButton(essentials.rndWnd);
	drawAllSlots(essentials);
}

void SlotsUserInterface::update(Essentials& essentials)
{
	quitButton.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	updateBinButtons(essentials);
	deleteGameSaveIfAny(essentials);
}

bool SlotsUserInterface::isQuitButtonClicked() const
{
	return quitButton.buttonClicked();
}

void SlotsUserInterface::createSlotsGraphics(Essentials& essentials)
{
	for( int row{0} ; row < SaveSlotRowsNumber ; ++row )
	{
		for( int line{0} ; line < SaveSlotLinesNumber ; ++line )
		{
			slotsGraphics.emplace_back( SlotGraphics{ essentials, row, line, slotSquareTexture } );
		}
	}
}

void SlotsUserInterface::createTitle(Essentials& essentials, unsigned contextFocus)
{
	assert( SaveNameFocusingOnSaving == contextFocus || SaveNameFocusingOnLoading == contextFocus );
	if( SaveNameFocusingOnSaving == contextFocus )
	{
		title.texture.loadBlendedText(essentials.logs, essentials.rndWnd, fancyFont, localeTexts[SaveNameFocusingOnSaving], TitleColor);
		title.resetSpritePosition(TexturePosition{ GameScreenWidth / 2, SQR_SIZE, true, true } );
	}
	else if( SaveNameFocusingOnLoading == contextFocus )
	{
		title.texture.loadBlendedText(essentials.logs, essentials.rndWnd, fancyFont, localeTexts[SaveNameFocusingOnLoading], TitleColor); 
		title.resetSpritePosition(TexturePosition{GameScreenWidth / 2, SQR_SIZE, true, true} );
	}
}

void SlotsUserInterface::loadSlotsDataFromGameSaves(Essentials& essentials, unsigned slotIndex)
{
	if( fs::exists( path::getGameSaveFullPath(essentials.prefPath, slotIndex) ) )
	{
		try{
			gameLoading::startLoading(essentials.logs, essentials.prefPath, slotsData[slotIndex], slotIndex);
			slotsGraphics[slotIndex].setSlotDataToFirstString(essentials, arial, slotsData[slotIndex]);
			slotsGraphics[slotIndex].setSlotDataToSecondString(essentials, arial, slotsData[slotIndex]);
			slotsData[slotIndex].isAnActiveSave = true;
		}
		catch( const ReadError& e )
		{
			slotsGraphics[slotIndex].setErrorStringFirstString(essentials, arial, localeTexts);
			slotsGraphics[slotIndex].setErrorStringSecondString(essentials, arial, e.what() );
			slotsData[slotIndex].isAnActiveSave = false;
		}
	}	
	else{
		slotsGraphics[slotIndex].setTextIfSlotFree(essentials, arial, localeTexts);
	}
}

void SlotsUserInterface::browseAllSlotsForInitialization(Essentials& essentials)
{
	for( unsigned slotIndex{0} ; slotIndex < SlotsNumber ; ++slotIndex )
	{
		loadSlotsDataFromGameSaves(essentials, slotIndex);
	}
}

void SlotsUserInterface::savePlayerDataToSlot(Essentials& essentials, unsigned slotIndex, const PlayerData& playerData)
{
	slotsData[slotIndex] = playerData;
	slotsData[slotIndex].setCampaign(localeTexts);
	slotsData[slotIndex].addDateToString();
	slotsData[slotIndex].setScoreAndCoins(localeTexts);
	try{
		gameSaving::startSaving(essentials.logs, essentials.prefPath, slotsData[slotIndex], slotIndex);
		slotsGraphics[slotIndex].setSlotDataToFirstString(essentials, arial, slotsData[slotIndex]);
		slotsGraphics[slotIndex].setSlotDataToSecondString(essentials, arial, slotsData[slotIndex]);
		slotsData[slotIndex].isAnActiveSave = true;
	}
	catch( const WriteError& e )
	{
		slotsGraphics[slotIndex].setErrorStringFirstString(essentials, arial, localeTexts);
		slotsGraphics[slotIndex].setErrorStringSecondString(essentials, arial, e.what() );
		slotsData[slotIndex].isAnActiveSave = false;
	}
}

void SlotsUserInterface::drawAllSlots(Essentials& essentials) const
{
	for( const auto &slot : slotsGraphics )
	{
		slot.drawSlot(essentials);
	}
}

void SlotsUserInterface::updateBinButtons(Essentials& essentials)
{
	for( auto &slot : slotsGraphics )
	{
		slot.deleteGameSaveButton.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT) );
	}
}

void SlotsUserInterface::deleteGameSaveIfAny(Essentials& essentials)
{
	for( unsigned slotIndex{0} ; slotIndex < SlotsNumber ; ++slotIndex )
	{
		if( slotsGraphics[slotIndex].deleteGameSaveButton.buttonClicked() )
		{
			if( fs::exists( path::getGameSaveFullPath(essentials.prefPath, slotIndex) ) )
			{
				if( fs::remove( path::getGameSaveFullPath(essentials.prefPath, slotIndex) ) )
				{
					slotsGraphics[slotIndex].setTextIfSlotFree(essentials, arial, localeTexts);
				}
			}
		}
	}
}

void gameSaving::startSaving(AppLogFiles& logs, const PrefPathFinder& prefPath, const GameSlotData& slot, unsigned gameSaveNumber)
{
	std::ofstream saveFile{ path::getGameSaveFullPath(prefPath, gameSaveNumber) };
	
	if( ! saveFile )
	{
		throw WriteError{"Error: unable to open '" + path::getGameSaveFullPath(prefPath, gameSaveNumber).string()
							+ "' file to save one player data #" + std::to_string(gameSaveNumber) + ".\n"};
	}
	try{
		gameSaving::writeDataToFile(saveFile, slot);
	}
	catch( WriteError& e )
	{
		logs.error << "Error while saving '" << path::getGameSaveFullPath(prefPath, gameSaveNumber) << "' file because: " << e.what() << ".\n";
		throw e;
	}
}

void gameLoading::startLoading(AppLogFiles& logs, const PrefPathFinder& prefPath, GameSlotData& slot, unsigned gameSaveNumber)
{
	std::ifstream gameSave{ path::getGameSaveFullPath(prefPath, gameSaveNumber) };
	
	if( ! gameSave )
	{
		throw ReadError{"Error: unable to open '" + path::getGameSaveFullPath(prefPath, gameSaveNumber).string()
							+ "' file to load one player data #" + std::to_string(gameSaveNumber) + ".\n"};
	}
	try{
		gameLoading::readDataFromFile(gameSave, slot);
	}
	catch( ReadError& e )
	{
		logs.error << "Error while loading '" << path::getGameSaveFullPath(prefPath, gameSaveNumber) << "' file because: " << e.what() << ".\n";
		throw e;
	}
}