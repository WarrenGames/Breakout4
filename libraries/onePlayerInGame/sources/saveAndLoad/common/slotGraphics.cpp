#include "saveAndLoad/common/slotGraphics.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "gameSlots/gameSlotData.h"
#include "time/dateAndTime.h"
#include "texts/textLoader.h"
#include "gameSlots/slotConsts.h"
#include "consts/constPaths.h"
#include "consts/sdlColors.h"

SlotGraphics::SlotGraphics(Essentials& essentials, std::size_t gameSaveNumber):
	slotSquare{essentials.logs, essentials.rndWnd, SDL_Color{215, 207, 174, 255}, SaveSlotSquareWidth, SaveSlotSquareHeight,
		TexturePosition{static_cast<int>(gameSaveNumber) / SaveSlotLinesNumber * GameScreenWidth / 2 + SQR_SIZE, 
						(static_cast<int>(gameSaveNumber) % SaveSlotLinesNumber) * (SaveSlotSquareHeight + SQR_SIZE) + SQR_SIZE * 3} },
	deleteGameSaveButton{essentials.logs, essentials.rndWnd, "textures/gameGUI/buttons/binButton.png",
						static_cast<int>(gameSaveNumber) / SaveSlotLinesNumber * GameScreenWidth / 2 + SQR_SIZE + SaveSlotSquareWidth, 
										(static_cast<int>(gameSaveNumber) % SaveSlotLinesNumber) * (SaveSlotSquareHeight + SQR_SIZE) + SQR_SIZE * 3} 
{}

void SlotGraphics::drawSlot(Essentials& essentials) const
{
	slotSquare.draw(essentials.rndWnd);
	campaignAndDate.draw(essentials.rndWnd);
	scoreAndCoins.draw(essentials.rndWnd);
	deleteGameSaveButton.drawButton(essentials.rndWnd);
}

bool SlotGraphics::isMouseOverSlot(const Offset& mousePosition) const
{
	return mousePosition.x >= slotSquare.sprite.x_pos() && mousePosition.x < slotSquare.sprite.x_pos() + slotSquare.sprite.width()
		&& mousePosition.y >= slotSquare.sprite.y_pos() && mousePosition.y < slotSquare.sprite.y_pos() + slotSquare.sprite.height();
}

void SlotGraphics::setSlotDataToFirstString(Essentials& essentials, const sdl2::Font& arial, const GameSlotData& slot)
{
	campaignAndDate.texture.loadBlendedText(essentials.logs, essentials.rndWnd, arial, slot.campaignAndDateInfos, BlackColor);
	campaignAndDate.resetSpritePosition(TexturePosition{slotSquare.sprite.x_pos() + SQR_SIZE / 4, slotSquare.sprite.y_pos() + slotSquare.sprite.height() / 3, false, true});
}

void SlotGraphics::setSlotDataToSecondString(Essentials& essentials, const sdl2::Font& arial, const GameSlotData& slot)
{
	scoreAndCoins.texture.loadBlendedText(essentials.logs, essentials.rndWnd, arial, slot.scoreAndCoinsInfos, BlackColor);
	scoreAndCoins.resetSpritePosition(TexturePosition{slotSquare.sprite.x_pos() + SQR_SIZE / 4, slotSquare.sprite.y_pos() + slotSquare.sprite.height() * 2 / 3, false, true});
}

void SlotGraphics::setErrorStringFirstString(Essentials& essentials, const sdl2::Font& arial, const TextsBlocks& localeTexts)
{
	campaignAndDate.texture.loadBlendedText(essentials.logs, essentials.rndWnd, arial, localeTexts[SaveNameSavingGaveAnError], RedColor);
	campaignAndDate.resetSpritePosition(TexturePosition{slotSquare.sprite.x_pos() + SQR_SIZE / 4, slotSquare.sprite.y_pos() + slotSquare.sprite.height() / 3, false, true});
}

void SlotGraphics::setErrorStringSecondString(Essentials& essentials, const sdl2::Font& arial, const std::string& error)
{
	scoreAndCoins.texture.loadBlendedText(essentials.logs, essentials.rndWnd, arial, error, RedColor);
	scoreAndCoins.resetSpritePosition(TexturePosition{slotSquare.sprite.x_pos() + SQR_SIZE / 4, slotSquare.sprite.y_pos() + slotSquare.sprite.height() / 3, false, true});
}

void SlotGraphics::setTextIfSlotFree(Essentials& essentials, const sdl2::Font& arial, const TextsBlocks& localeTexts)
{
	campaignAndDate.texture.loadBlendedText(essentials.logs, essentials.rndWnd, arial, localeTexts[SaveNameThisSlotIsFree], MediumGrayColor);
	campaignAndDate.resetSpritePosition(TexturePosition{slotSquare.sprite.x_pos() + SQR_SIZE / 4, slotSquare.sprite.y_pos() + slotSquare.sprite.height() / 3, false, true});
	scoreAndCoins.texture.loadBlendedText(essentials.logs, essentials.rndWnd, arial, "----", MediumGrayColor);
	scoreAndCoins.resetSpritePosition(TexturePosition{slotSquare.sprite.x_pos() + SQR_SIZE / 4, slotSquare.sprite.y_pos() + slotSquare.sprite.height() * 2 / 3, false, true});
}