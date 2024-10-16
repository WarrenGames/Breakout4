#ifndef GAME_SLOT_GRAPHICS_H
#define GAME_SLOT_GRAPHICS_H

#include "texturing/texturesCombo.h"
#include "widgets/buttons/buttonFlatWidget.h"
#include <cstddef>

struct GameSlotData;
struct Essentials;
class TextsBlocks;

struct SlotGraphics
{
	sdl2::Sprite slotSquareSprite;
	TextureCombo campaignAndDate;
	TextureCombo scoreAndCoins;
	ButtonFlat deleteGameSaveButton;
	
	explicit SlotGraphics(Essentials& essentials, int row, int line, const sdl2::TextureLoader& squareTexture);//std::size_t gameSaveNumber);
	~SlotGraphics() = default;
	SlotGraphics( const SlotGraphics& ) = delete;
	SlotGraphics& operator= ( const SlotGraphics& ) = delete;
	SlotGraphics( SlotGraphics&& ) = default;
	SlotGraphics& operator= ( SlotGraphics&& ) = default;
	
	void drawSlot(Essentials& essentials) const;
	bool isMouseOverSlot(const Offset& mousePosition) const;
	void setSlotDataToFirstString(Essentials& essentials, const sdl2::Font& arial, const GameSlotData& slot);
	void setSlotDataToSecondString(Essentials& essentials, const sdl2::Font& arial, const GameSlotData& slots);
	void setErrorStringFirstString(Essentials& essentials, const sdl2::Font& arial, const TextsBlocks& localeTexts);
	void setErrorStringSecondString(Essentials& essentials, const sdl2::Font& arial, const std::string& error);
	void setTextIfSlotFree(Essentials& essentials, const sdl2::Font& arial, const TextsBlocks& localeTexts);
};

namespace slots{
	int getXPosition(int rowNumber);
	
	int getYPosition(int lineNumber);
}

#endif //GAME_SLOT_GRAPHICS_H