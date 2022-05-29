#include "contexts/duels/controls/objects/joystickInfosGraphics.h"
#include "types/essentialsStruct.h"
#include "texts/textLoader.h"
#include "texturing/rendererWindow.h"
#include "texturing/texturePosition.h"
#include "text/sdl2ttf_font.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "contexts/duels/controls/inputScreenConsts.h"

JoyInfosTextsGraphics::JoyInfosTextsGraphics(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, unsigned player, const TextsBlocks& texts):
	joyEnt{ static_cast<int>(player) },
	seeJoystickInfos{logs, rndWnd, fancyFont, texts[duels::TXT_SEE_JOY_INFOS], BLACK_COL, { static_cast<int>(player) * GAME_SCREEN_WIDTH / 2 + SQR_SIZE, GAME_SCREEN_HEIGHT-SQR_SIZE*4, SQR_SIZE*6, SQR_SIZE}, GREEN_COL}
{
	resetTexts(logs, rndWnd, fancyFont, player, texts);
}

void JoyInfosTextsGraphics::resetTexts(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, unsigned player, const TextsBlocks& texts)
{
	if( joyEnt )
	{
		joyName.texture.loadBlendedText(logs, rndWnd, fancyFont, joyEnt.getName(), BLACK_COL);
		joyName.resetSpritePosition(TexturePosition{static_cast<int>(player) * GAME_SCREEN_WIDTH/2 + SQR_SIZE, GAME_SCREEN_HEIGHT - SQR_SIZE*2, false, true });
		
		joyHatNum.texture.loadBlendedText(logs, rndWnd, fancyFont, getHatNumberText(texts), BLACK_COL);
		joyHatNum.resetSpritePosition(TexturePosition{static_cast<int>(player) * GAME_SCREEN_WIDTH/2+SQR_SIZE, GAME_SCREEN_HEIGHT-SQR_SIZE-SQR_SIZE/2, false, true});
										
		joyAxesNum.texture.loadBlendedText(logs, rndWnd, fancyFont, getAxesNumberText(texts), BLACK_COL);
		joyAxesNum.resetSpritePosition(TexturePosition{static_cast<int>(player)*GAME_SCREEN_WIDTH/2 + SQR_SIZE, GAME_SCREEN_HEIGHT - SQR_SIZE, false, true } );
									
		joyButtonsNum.texture.loadBlendedText(logs, rndWnd, fancyFont, getButtonsNumberText(texts), BLACK_COL);
		joyButtonsNum.resetSpritePosition(TexturePosition{ static_cast<int>(player)*GAME_SCREEN_WIDTH/2 + SQR_SIZE, GAME_SCREEN_HEIGHT - SQR_SIZE/2, false, true } );
	}
	else{
		joyName.texture.loadBlendedText(logs, rndWnd, fancyFont, texts[duels::TXT_PLUG_A_JOYSTICK] + std::to_string(player + 1), RED_COL);
		joyName.resetSpritePosition(TexturePosition{static_cast<int>(player)*GAME_SCREEN_WIDTH/2 + SQR_SIZE, GAME_SCREEN_HEIGHT - SQR_SIZE*2, false, true } );
	}
}

std::string JoyInfosTextsGraphics::getHatNumberText(const TextsBlocks& texts)
{
	return std::string{ std::to_string(joyEnt.getHatsNumber()) + texts[duels::TXT_HATS_COUNT] };
}

std::string JoyInfosTextsGraphics::getAxesNumberText(const TextsBlocks& texts)
{
	return std::string{ std::to_string(joyEnt.getAxesNumber()) + texts[duels::TXT_AXES_COUNT] };
}

std::string JoyInfosTextsGraphics::getButtonsNumberText(const TextsBlocks& texts)
{
	return std::string{ std::to_string(joyEnt.getButtonsNumber()) + texts[duels::TXT_BTNS_COUNT] };
}

void JoyInfosTextsGraphics::update(Essentials& essentials)
{
	if( joyEnt )
	{
		seeJoystickInfos.updateButton(essentials.inp.getMousePosition(), essentials.inp.getMouseButtonState(SDL_BUTTON_LEFT));
	}
}

void JoyInfosTextsGraphics::drawTexts(sdl2::RendererWindow& rndWnd) const
{
	if( joyEnt )
	{
		joyName.draw(rndWnd);
		joyHatNum.draw(rndWnd);
		joyAxesNum.draw(rndWnd);
		joyButtonsNum.draw(rndWnd);
		seeJoystickInfos.drawButton(rndWnd);
	}
	else{
		joyName.draw(rndWnd);
	}
}