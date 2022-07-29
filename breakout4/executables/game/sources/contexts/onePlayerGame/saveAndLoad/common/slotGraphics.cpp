#include "contexts/onePlayerGame/saveAndLoad/common/slotGraphics.h"
#include "types/essentialsStruct.h"
#include "texturing/texturePosition.h"
#include "gameSlots/gameSlotData.h"
#include "time/dateAndTime.h"
#include "texts/textLoader.h"
#include "gameSlots/slotConsts.h"
#include "consts/constPaths.h"
#include "consts/sdlColors.h"

SlotGraphics::SlotGraphics(Essentials& essentials, std::size_t gameSaveNumber):
	slotSquare{essentials.logs, essentials.rndWnd, SDL_Color{215, 207, 174, 255}, SAVE_SLOT_SQR_W, SAVE_SLOT_SQR_H,
		TexturePosition{static_cast<int>(gameSaveNumber) / SAVE_SLOT_LINES_NUM * GAME_SCREEN_WIDTH / 2 + SQR_SIZE, 
						(static_cast<int>(gameSaveNumber) % SAVE_SLOT_LINES_NUM) * (SAVE_SLOT_SQR_H + SQR_SIZE) + SQR_SIZE * 3} },
	deleteGameSaveButton{essentials.logs, essentials.rndWnd, "textures/gameGUI/buttons/binButton.png",
						static_cast<int>(gameSaveNumber) / SAVE_SLOT_LINES_NUM * GAME_SCREEN_WIDTH / 2 + SQR_SIZE + SAVE_SLOT_SQR_W, 
										(static_cast<int>(gameSaveNumber) % SAVE_SLOT_LINES_NUM) * (SAVE_SLOT_SQR_H + SQR_SIZE) + SQR_SIZE * 3} 
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
	campaignAndDate.texture.loadBlendedText(essentials.logs, essentials.rndWnd, arial, slot.campaignAndDateInfos, BLACK_COL);
	campaignAndDate.resetSpritePosition(TexturePosition{slotSquare.sprite.x_pos() + SQR_SIZE / 4, slotSquare.sprite.y_pos() + slotSquare.sprite.height() / 3, false, true});
}

void SlotGraphics::setSlotDataToSecondString(Essentials& essentials, const sdl2::Font& arial, const GameSlotData& slot)
{
	scoreAndCoins.texture.loadBlendedText(essentials.logs, essentials.rndWnd, arial, slot.scoreAndCoinsInfos, BLACK_COL);
	scoreAndCoins.resetSpritePosition(TexturePosition{slotSquare.sprite.x_pos() + SQR_SIZE / 4, slotSquare.sprite.y_pos() + slotSquare.sprite.height() * 2 / 3, false, true});
}

void SlotGraphics::setErrorStringFirstString(Essentials& essentials, const sdl2::Font& arial, const TextsBlocks& localeTexts)
{
	campaignAndDate.texture.loadBlendedText(essentials.logs, essentials.rndWnd, arial, localeTexts[SAVE_NAME_SAVING_GAVE_AN_ERROR], RED_COL);
	campaignAndDate.resetSpritePosition(TexturePosition{slotSquare.sprite.x_pos() + SQR_SIZE / 4, slotSquare.sprite.y_pos() + slotSquare.sprite.height() / 3, false, true});
}

void SlotGraphics::setErrorStringSecondString(Essentials& essentials, const sdl2::Font& arial, const std::string& error)
{
	scoreAndCoins.texture.loadBlendedText(essentials.logs, essentials.rndWnd, arial, error, RED_COL);
	scoreAndCoins.resetSpritePosition(TexturePosition{slotSquare.sprite.x_pos() + SQR_SIZE / 4, slotSquare.sprite.y_pos() + slotSquare.sprite.height() / 3, false, true});
}

void SlotGraphics::setTextIfSlotFree(Essentials& essentials, const sdl2::Font& arial, const TextsBlocks& localeTexts)
{
	campaignAndDate.texture.loadBlendedText(essentials.logs, essentials.rndWnd, arial, localeTexts[SAVE_NAME_THIS_SLOT_IS_FREE], MEDIUM_GRAY_COL);
	campaignAndDate.resetSpritePosition(TexturePosition{slotSquare.sprite.x_pos() + SQR_SIZE / 4, slotSquare.sprite.y_pos() + slotSquare.sprite.height() / 3, false, true});
	scoreAndCoins.texture.loadBlendedText(essentials.logs, essentials.rndWnd, arial, "----", MEDIUM_GRAY_COL);
	scoreAndCoins.resetSpritePosition(TexturePosition{slotSquare.sprite.x_pos() + SQR_SIZE / 4, slotSquare.sprite.y_pos() + slotSquare.sprite.height() * 2 / 3, false, true});
}