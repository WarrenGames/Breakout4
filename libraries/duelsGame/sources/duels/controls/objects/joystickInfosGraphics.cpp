#include "duels/controls/objects/joystickInfosGraphics.h"
#include "types/essentialsStruct.h"
#include "texts/textLoader.h"
#include "texturing/rendererWindow.h"
#include "texturing/texturePosition.h"
#include "text/sdl2ttf_font.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include "duels/controls/inputScreenConsts.h"

JoyInfosTextsGraphics::JoyInfosTextsGraphics(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, unsigned player, const TextsBlocks& texts):
	joyEnt{ static_cast<int>(player) },
	seeJoystickInfos{logs, rndWnd, fancyFont, texts[duels::TextSeeJoystickInfos], BlackColor, { static_cast<int>(player) * GameScreenWidth / 2 + SQR_SIZE, GameScreenHeight-SQR_SIZE*4, SQR_SIZE*6, SQR_SIZE}, GreenColor}
{
	resetTexts(logs, rndWnd, fancyFont, player, texts);
}

void JoyInfosTextsGraphics::resetTexts(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& fancyFont, unsigned player, const TextsBlocks& texts)
{
	if( joyEnt )
	{
		joyName.texture.loadBlendedText(logs, rndWnd, fancyFont, joyEnt.getName(), BlackColor);
		joyName.resetSpritePosition(TexturePosition{static_cast<int>(player) * GameScreenWidth/2 + SQR_SIZE, GameScreenHeight - SQR_SIZE*2, false, true });
		
		joyHatNum.texture.loadBlendedText(logs, rndWnd, fancyFont, getHatNumberText(texts), BlackColor);
		joyHatNum.resetSpritePosition(TexturePosition{static_cast<int>(player) * GameScreenWidth/2+SQR_SIZE, GameScreenHeight-SQR_SIZE-SQR_SIZE/2, false, true});
										
		joyAxesNum.texture.loadBlendedText(logs, rndWnd, fancyFont, getAxesNumberText(texts), BlackColor);
		joyAxesNum.resetSpritePosition(TexturePosition{static_cast<int>(player)*GameScreenWidth/2 + SQR_SIZE, GameScreenHeight - SQR_SIZE, false, true } );
									
		joyButtonsNum.texture.loadBlendedText(logs, rndWnd, fancyFont, getButtonsNumberText(texts), BlackColor);
		joyButtonsNum.resetSpritePosition(TexturePosition{ static_cast<int>(player)*GameScreenWidth/2 + SQR_SIZE, GameScreenHeight - SQR_SIZE/2, false, true } );
	}
	else{
		joyName.texture.loadBlendedText(logs, rndWnd, fancyFont, texts[duels::TextPlugJoystick] + std::to_string(player + 1), RedColor);
		joyName.resetSpritePosition(TexturePosition{static_cast<int>(player)*GameScreenWidth/2 + SQR_SIZE, GameScreenHeight - SQR_SIZE*2, false, true } );
	}
}

std::string JoyInfosTextsGraphics::getHatNumberText(const TextsBlocks& texts)
{
	return std::string{ std::to_string(joyEnt.getHatsNumber()) + texts[duels::TextHatsCount] };
}

std::string JoyInfosTextsGraphics::getAxesNumberText(const TextsBlocks& texts)
{
	return std::string{ std::to_string(joyEnt.getAxesNumber()) + texts[duels::TextAxesCount] };
}

std::string JoyInfosTextsGraphics::getButtonsNumberText(const TextsBlocks& texts)
{
	return std::string{ std::to_string(joyEnt.getButtonsNumber()) + texts[duels::TextButtonsCount] };
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