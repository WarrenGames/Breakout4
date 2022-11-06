#include "contexts/options/joystickInterface/joystickGraphicsValues.h"
#include "logging/logsStruct.h"
#include "texturing/texturePosition.h"
#include "contexts/options/optionsLanguageConsts.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"
#include <algorithm>
#include <string>
#include <cassert>
#include <limits>

constexpr int ButtonsWidthNumber = 16; //The number of buttons states in one row
constexpr int ButtonsHeightNumber = 2;  //The number of buttons row : so it's 32 buttons max that are drawn.
constexpr double Sint16Max = std::numeric_limits<Sint16>::max();

JoyEventsInfos::JoyEventsInfos(const sdl2::JoystickEntity& joyEnt):
	joyButtons( joyEnt.getButtonsNumber() ),
	joyHats( joyEnt.getHatsNumber() ),
	joyAxes( joyEnt.getAxesNumber() ),
	joystickNumber{ joyEnt.getJoystickNumber() },
	escapeState{false},
	sdl_Quit{ false }
{
	std::fill( joyButtons.begin(), joyButtons.end(), false);
	std::fill( joyHats.begin(), joyHats.end(), SDL_HAT_CENTERED);
	std::fill( joyAxes.begin(), joyAxes.end(), 0);
}



JoystickValuesTextures::JoystickValuesTextures(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& arial, const TextsBlocks& joyLangTexts, const sdl2::JoystickEntity& joyEnt):
	hatsSquare{logs, rndWnd, WhiteColor, SQR_SIZE*3, SQR_SIZE*3, TexturePosition{} },
	buttonOff{logs, rndWnd, WhiteColor, SQR_SIZE/2, SQR_SIZE/2, TexturePosition{} },
	buttonPushed{logs, rndWnd, RedColor, SQR_SIZE/2, SQR_SIZE/2, TexturePosition{} },
	axisGradientOff{logs, rndWnd, WhiteColor, SQR_SIZE/2, SQR_SIZE*2, TexturePosition{} },
	axisGradientRed{logs, rndWnd, RedColor, SQR_SIZE/2, SQR_SIZE, TexturePosition{GameScreenWidth, GameScreenHeight} },
	buttonsText{logs, rndWnd, arial, joyLangTexts[joyStrings::ButtonNum], BlackColor, TexturePosition{SQR_SIZE, SQR_SIZE * 2 - SQR_SIZE / 4, false, true} },
	hatsText{logs, rndWnd, arial, joyLangTexts[joyStrings::HatNum], BlackColor, TexturePosition{SQR_SIZE, SQR_SIZE*5+SQR_SIZE/2, false, true} },
	axisText{logs, rndWnd, arial, joyLangTexts[joyStrings::AxisNum], BlackColor, TexturePosition{SQR_SIZE, SQR_SIZE*9, false, false} },
	joyEventsInfos{ joyEnt },
	numbersTextures( std::max(joyEnt.getButtonsNumber(), std::max(joyEnt.getHatsNumber(), joyEnt.getAxesNumber()) ) )
{
	createNumbersTextures(logs, rndWnd, arial);
}

void JoystickValuesTextures::updateEvents()
{
	SDL_Event ev;
	while( SDL_PollEvent(&ev) )
	{
		switch( ev.type )
		{
			case SDL_QUIT:
				joyEventsInfos.sdl_Quit = true;
				break;
			case SDL_KEYDOWN:
				appendEscapeKeyStatus(ev.key.keysym.sym, true);
				break;
			case SDL_KEYUP:
				appendEscapeKeyStatus(ev.key.keysym.sym, false);
				break;
			case SDL_JOYBUTTONDOWN:
				if( ev.jbutton.which == joyEventsInfos.joystickNumber )
					joyEventsInfos.joyButtons[ev.jbutton.button] = true;
				break;
			case SDL_JOYBUTTONUP:
				if( ev.jbutton.which == joyEventsInfos.joystickNumber )
					joyEventsInfos.joyButtons[ev.jbutton.button] = false;
				break;
			case SDL_JOYHATMOTION:
				if( ev.jbutton.which == joyEventsInfos.joystickNumber )
					joyEventsInfos.joyHats[ev.jhat.hat] = ev.jhat.value;
				break;
			case SDL_JOYAXISMOTION:
				if( ev.jbutton.which == joyEventsInfos.joystickNumber )
					joyEventsInfos.joyAxes[ev.jaxis.axis] = ev.jaxis.value;
				break;
		}
	}
}

bool JoystickValuesTextures::isQuitTriggered() const
{
	return joyEventsInfos.escapeState || joyEventsInfos.sdl_Quit;
}

void JoystickValuesTextures::drawAll(sdl2::RendererWindow& rndWnd)
{
	buttonsText.draw(rndWnd);
	drawButtonsStates(rndWnd);
	hatsText.draw(rndWnd);
	drawHatsSurfaces(rndWnd);
	axisText.draw(rndWnd);
	drawAxesValues(rndWnd);
}

void JoystickValuesTextures::drawButtonsStates(sdl2::RendererWindow& rndWnd)
{
	std::size_t buttonIndex{0};
	
	for( int i{0} ; i < ButtonsHeightNumber ; ++i )
	{
		for( int j{0} ; j < ButtonsWidthNumber ; ++j )
		{
			if( buttonIndex < joyEventsInfos.joyButtons.size() )
			{
				drawSingleButtonSurface(rndWnd, SQR_SIZE * 3 + SQR_SIZE * j, SQR_SIZE * 2 + SQR_SIZE * i, joyEventsInfos.joyButtons[buttonIndex] );
				drawButtonsNumbers(rndWnd, buttonIndex, SQR_SIZE * 3 + SQR_SIZE * j + SQR_SIZE / 4, SQR_SIZE * 2 - SQR_SIZE / 4 + SQR_SIZE * i);
			}
			buttonIndex++;
		}
	}
}

void JoystickValuesTextures::drawButtonsNumbers(sdl2::RendererWindow& rndWnd, std::size_t figureNum, int x_center_pos, int y_center_pos)
{
	assert( figureNum < numbersTextures.size() );
	numbersTextures[figureNum].drawToCenter(rndWnd, x_center_pos, y_center_pos);
}

void JoystickValuesTextures::drawHatsSurfaces(sdl2::RendererWindow& rndWnd)
{
	if( false == joyEventsInfos.joyHats.empty() )
	{
		for( std::size_t i{0} ; i < joyEventsInfos.joyHats.size() ; ++i )
		{
			hatsSquare.draw(rndWnd, SQR_SIZE*4 + static_cast<int>(i) * SQR_SIZE * 4, SQR_SIZE*5);
			drawHatReticule(rndWnd, joyEventsInfos.joyHats[i], SQR_SIZE*4+ static_cast<int>(i)*SQR_SIZE*4 + hatsSquare.sprite.width() / 2, SQR_SIZE*5 + hatsSquare.sprite.height() / 2 );
			drawButtonsNumbers(rndWnd, i, SQR_SIZE*4 + static_cast<int>(i) * SQR_SIZE*4 + hatsSquare.sprite.width() / 2, SQR_SIZE*5 - SQR_SIZE/4);
		}
	}
}

void JoystickValuesTextures::drawAxesValues(sdl2::RendererWindow& rndWnd)
{
	if( false == joyEventsInfos.joyAxes.empty() )
	{
		for( std::size_t i{0} ; i < joyEventsInfos.joyAxes.size() ; ++i )
		{
			drawSingleAxisSurface(rndWnd, SQR_SIZE * 4 + SQR_SIZE * static_cast<int>(i), SQR_SIZE * 9, joyEventsInfos.joyAxes[i]);
			drawButtonsNumbers(rndWnd, i, SQR_SIZE * 4 + SQR_SIZE * static_cast<int>(i) + SQR_SIZE / 4, SQR_SIZE * 9 - SQR_SIZE / 4);
		}
	}
}

void JoystickValuesTextures::appendEscapeKeyStatus(SDL_Keycode keycode, bool valueToSet)
{
	if( SDLK_ESCAPE == keycode )
		joyEventsInfos.escapeState = valueToSet;
}

void JoystickValuesTextures::createNumbersTextures(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const sdl2::Font& arial)
{
	for( std::size_t i{0} ; i < numbersTextures.size() ; ++i )
	{
		numbersTextures[i].texture.loadBlendedText(logs, rndWnd, arial, std::to_string(i), BlackColor);
		numbersTextures[i].resetSpritePosition(TexturePosition{0, 0, false, false} );
	}
}

void JoystickValuesTextures::drawSingleButtonSurface(sdl2::RendererWindow& rndWnd, int x_pos, int y_pos, bool buttonState)
{
	if( buttonState )
	{
		buttonPushed.draw(rndWnd, x_pos, y_pos);
	}
	else
		buttonOff.draw(rndWnd, x_pos, y_pos);
}

void JoystickValuesTextures::drawHatReticule(sdl2::RendererWindow& rndWnd, Uint8 hatValue, int x_pos, int y_pos)
{
	switch( hatValue )
	{
		case SDL_HAT_CENTERED:
			buttonPushed.drawToCenter(rndWnd, x_pos, y_pos);
			break;
		case SDL_HAT_LEFT:
			buttonPushed.drawToCenter(rndWnd, x_pos - hatsSquare.sprite.width() / 2 + buttonPushed.sprite.width() / 2, y_pos );
			break;
		case SDL_HAT_RIGHT:
			buttonPushed.drawToCenter(rndWnd, x_pos + hatsSquare.sprite.width() / 2 - buttonPushed.sprite.width() / 2, y_pos );
			break;
		case SDL_HAT_UP:
			buttonPushed.drawToCenter(rndWnd, x_pos, y_pos - hatsSquare.sprite.height() / 2 + buttonPushed.sprite.height() / 2 );
			break;
		case SDL_HAT_DOWN:
			buttonPushed.drawToCenter(rndWnd, x_pos, y_pos + hatsSquare.sprite.height() / 2 - buttonPushed.sprite.height() / 2 );
			break;
		case SDL_HAT_LEFTUP:
			buttonPushed.drawToCenter(rndWnd, x_pos - hatsSquare.sprite.width() / 2 + buttonPushed.sprite.width() / 2, y_pos - hatsSquare.sprite.height() / 2 + buttonPushed.sprite.height() / 2 );
			break;
		case SDL_HAT_LEFTDOWN:
			buttonPushed.drawToCenter(rndWnd, x_pos - hatsSquare.sprite.width() / 2 + buttonPushed.sprite.width() / 2, y_pos + hatsSquare.sprite.height() / 2 - buttonPushed.sprite.height() / 2 );
			break;
		case SDL_HAT_RIGHTUP:
			buttonPushed.drawToCenter(rndWnd, x_pos + hatsSquare.sprite.width() / 2 - buttonPushed.sprite.width() / 2, y_pos - hatsSquare.sprite.height() / 2 + buttonPushed.sprite.height() / 2 );
			break;
		case SDL_HAT_RIGHTDOWN:
			buttonPushed.drawToCenter(rndWnd, x_pos + hatsSquare.sprite.width() / 2 - buttonPushed.sprite.width() / 2, y_pos + hatsSquare.sprite.height() / 2 - buttonPushed.sprite.height() / 2 );
			break;
	}
}

void JoystickValuesTextures::drawSingleAxisSurface(sdl2::RendererWindow& rndWnd, int x_pos, int y_pos, Sint16 axisValue)
{
	axisGradientOff.draw(rndWnd, x_pos, y_pos);
	drawAxisValue(rndWnd, x_pos, y_pos, axisValue);
}

void JoystickValuesTextures::drawAxisValue(sdl2::RendererWindow& rndWnd, int x_pos, int y_pos, Sint16 axisValue)
{
	double multiplyHeight{ static_cast<double>(axisValue) / Sint16Max };
	
	if( axisValue > 0)
	{
		axisGradientRed.sprite.multiplyHeight( multiplyHeight );
		axisGradientRed.sprite.setDefaultCoord(x_pos, y_pos + SQR_SIZE - axisGradientRed.sprite.height());
		axisGradientRed.draw(rndWnd);
	}
	else if( axisValue < 0 )
	{
		axisGradientRed.sprite.multiplyHeight( -multiplyHeight );
		axisGradientRed.sprite.setDefaultCoord(x_pos, y_pos + SQR_SIZE);
		axisGradientRed.draw(rndWnd);
	}
	else{
		axisGradientRed.draw(rndWnd);
	}
}