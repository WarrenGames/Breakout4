#include "saveAndLoad/common/slotGraphics.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "gameSlots/gameSlotData.h"
#include "time/dateAndTime.h"
#include "texts/textLoader.h"
#include "gameSlots/slotConsts.h"
#include "consts/constPaths.h"
#include "consts/sdlColors.h"

constexpr SDL_Color SlotSquareColor = {215, 207, 174, 255};

SlotGraphics::SlotGraphics(Essentials& essentials, int row, int line, const sdl2::TextureLoader& squareTexture):// std::size_t gameSaveNumber):
	slotSquareSprite{squareTexture, slots::getXPosition(row), slots::getYPosition(line) },
	deleteGameSaveButton{essentials.logs, essentials.rndWnd, "textures/gameGUI/buttons/binButton.png", slots::getXPosition(row) + SaveSlotSquareWidth, slots::getYPosition(line) }
{

}

void SlotGraphics::drawSlot(Essentials& essentials) const
{
	slotSquareSprite.draw(essentials.rndWnd);
	campaignAndDate.draw(essentials.rndWnd);
	scoreAndCoins.draw(essentials.rndWnd);
	deleteGameSaveButton.drawButton(essentials.rndWnd);
}

bool SlotGraphics::isMouseOverSlot(const Offset& mousePosition) const
{
	return mousePosition.x >= slotSquareSprite.x_pos() && mousePosition.x < slotSquareSprite.x_pos() + slotSquareSprite.width()
		&& mousePosition.y >= slotSquareSprite.y_pos() && mousePosition.y < slotSquareSprite.y_pos() + slotSquareSprite.height();
}

void SlotGraphics::setSlotDataToFirstString(Essentials& essentials, const sdl2::Font& arial, const GameSlotData& slot)
{
	campaignAndDate.texture.loadBlendedText(essentials.logs, essentials.rndWnd, arial, slot.campaignAndDateInfos, BlackColor);
	campaignAndDate.resetSpritePosition(TexturePosition{slotSquareSprite.x_pos() + SQR_SIZE / 4, slotSquareSprite.y_pos() + slotSquareSprite.height() / 3, false, true});
}

void SlotGraphics::setSlotDataToSecondString(Essentials& essentials, const sdl2::Font& arial, const GameSlotData& slot)
{
	scoreAndCoins.texture.loadBlendedText(essentials.logs, essentials.rndWnd, arial, slot.scoreAndCoinsInfos, BlackColor);
	scoreAndCoins.resetSpritePosition(TexturePosition{slotSquareSprite.x_pos() + SQR_SIZE / 4, slotSquareSprite.y_pos() + slotSquareSprite.height() * 2 / 3, false, true});
}

void SlotGraphics::setErrorStringFirstString(Essentials& essentials, const sdl2::Font& arial, const TextsBlocks& localeTexts)
{
	campaignAndDate.texture.loadBlendedText(essentials.logs, essentials.rndWnd, arial, localeTexts[SaveNameSavingGaveAnError], RedColor);
	campaignAndDate.resetSpritePosition(TexturePosition{slotSquareSprite.x_pos() + SQR_SIZE / 4, slotSquareSprite.y_pos() + slotSquareSprite.height() / 3, false, true});
}

void SlotGraphics::setErrorStringSecondString(Essentials& essentials, const sdl2::Font& arial, const std::string& error)
{
	scoreAndCoins.texture.loadBlendedText(essentials.logs, essentials.rndWnd, arial, error, RedColor);
	scoreAndCoins.resetSpritePosition(TexturePosition{slotSquareSprite.x_pos() + SQR_SIZE / 4, slotSquareSprite.y_pos() + slotSquareSprite.height() / 3, false, true});
}

void SlotGraphics::setTextIfSlotFree(Essentials& essentials, const sdl2::Font& arial, const TextsBlocks& localeTexts)
{
	campaignAndDate.texture.loadBlendedText(essentials.logs, essentials.rndWnd, arial, localeTexts[SaveNameThisSlotIsFree], MediumGrayColor);
	campaignAndDate.resetSpritePosition(TexturePosition{slotSquareSprite.x_pos() + SQR_SIZE / 4, slotSquareSprite.y_pos() + slotSquareSprite.height() / 3, false, true});
	scoreAndCoins.texture.loadBlendedText(essentials.logs, essentials.rndWnd, arial, "----", MediumGrayColor);
	scoreAndCoins.resetSpritePosition(TexturePosition{slotSquareSprite.x_pos() + SQR_SIZE / 4, slotSquareSprite.y_pos() + slotSquareSprite.height() * 2 / 3, false, true});
}

int slots::getXPosition(int rowNumber)
{
	return SQR_SIZE + rowNumber * (SaveSlotSquareWidth + SQR_SIZE * 2);
}

int slots::getYPosition(int lineNumber)
{
	return lineNumber * (SaveSlotSquareHeight + SQR_SIZE) + SQR_SIZE * 3;
}