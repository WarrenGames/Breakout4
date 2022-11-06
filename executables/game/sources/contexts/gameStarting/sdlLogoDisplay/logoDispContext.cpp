#include "contexts/gameStarting/sdlLogoDisplay/logoDispContext.h"
#include "contexts/gameStarting/sdlLogoDisplay/sdlVersionDisplay.h"
#include "texturing/texturesCombo.h"
#include "texturing/texturePosition.h"
#include "time/accurateTime.h"
#include "types/essentialsStruct.h"
#include "consts/constexprScreen.h"
#include "consts/sdlColors.h"

void logoDisplay::mainContext(Essentials& essentials)
{
	TextureCombo sdlLogo{essentials.logs, essentials.rndWnd, "textures/gameGUI/sdlLogo/sdlLogo1280.png", TexturePosition{GameScreenWidth / 2, GameScreenHeight / 2, true, true} };
	resizeLogoIfNeeded(essentials, sdlLogo);
	AccurateTimeDelay displayDelay;
	const SDL_VersionDisplay versionDisplay{essentials};
	bool quitLogoDisplay{false};
	while( false == quitLogoDisplay )
	{
		logoDisplay::loopThings(essentials, quitLogoDisplay, sdlLogo, versionDisplay, displayDelay);
	}
}

void logoDisplay::loopThings(Essentials& essentials, bool& quitLogoDisplay, const TextureCombo& sdlLogo, const SDL_VersionDisplay& versionDisplay, AccurateTimeDelay& displayDelay)
{
	logoDisplay::waitForKeyToBePushed(quitLogoDisplay);
	logoDisplay::quitIfTimeElapsed(quitLogoDisplay, displayDelay);
	essentials.rndWnd.clearScreen(BlackColor);
	sdlLogo.draw(essentials.rndWnd);
	versionDisplay.drawVersion(essentials);
	essentials.rndWnd.displayRenderer();
	SDL_Delay(SdlDelayTime);
}

void logoDisplay::waitForKeyToBePushed(bool& quitLogoDisplay)
{
	SDL_Event events;
	while( SDL_PollEvent(&events) )
	{
		switch( events.type )
		{
			case SDL_KEYDOWN:
				quitLogoDisplay = true;
				break;
		}
	}
}

void logoDisplay::quitIfTimeElapsed(bool& quitLogoDisplay, AccurateTimeDelay& displayDelay)
{
	if( displayDelay.hasTimeElapsed( std::chrono::milliseconds{4000} ) )
	{
		quitLogoDisplay = true;
	}
}

void logoDisplay::resizeLogoIfNeeded(Essentials& essentials, TextureCombo& sdlLogo)
{
	if( sdlLogo.sprite.width() > essentials.rndWnd.width() || sdlLogo.sprite.height() > essentials.rndWnd.height() )
	{
		double widthRatio{ static_cast<double>( essentials.rndWnd.width() ) / static_cast<double>( sdlLogo.sprite.width() ) };
		double heightRatio{ static_cast<double>( essentials.rndWnd.height() ) / static_cast<double>( sdlLogo.sprite.height() ) };
		
		if( widthRatio < heightRatio )
		{
			sdlLogo.sprite.setWidth( static_cast<int>( sdlLogo.sprite.width() * widthRatio ) );
			sdlLogo.sprite.setHeight( static_cast<int>( sdlLogo.sprite.height() * widthRatio ) );
		}
		else{
			sdlLogo.sprite.setWidth( static_cast<int>( sdlLogo.sprite.width() * heightRatio ) );
			sdlLogo.sprite.setHeight( static_cast<int>( sdlLogo.sprite.height() * heightRatio ) );
		}
		sdlLogo.sprite.setTexturePosition( TexturePosition{GameScreenWidth / 2, GameScreenHeight / 2, true, true} );
	}
}