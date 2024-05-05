#include "sdlLogoDisplay/logoDispContext.h"
#include "sdlLogoDisplay/sdlVersionDisplay.h"
#include "texturing/rendererWindow.h"
#include "texturing/texturesCombo.h"
#include "texturing/texturePosition.h"
#include "prefPath/prefPathFinder.h"
#include "time/accurateTime.h"
#include "logging/logsStruct.h"

constexpr SDL_Color BackgroundColor = { 128, 128, 128, 255 };
constexpr char SdlLogoTextureFilePath[] = "textures/sdlLogo/sdlLogo1280.png";

void logoDisplay::mainContext(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const fs::path& logoDisplayStatusFile, const fs::path& languageFilePath, unsigned fontSize, int squareSize)
{
	if( logoDisplay::getSdlLogoDisplayStatus(logs, logoDisplayStatusFile) )
	{
		TextureCombo sdlLogo{logs, rndWnd, SdlLogoTextureFilePath, TexturePosition{rndWnd.width() / 2, rndWnd.height() / 2, true, true} };
		resizeLogoIfNeeded(rndWnd, sdlLogo);
		const AccurateTimeDelay displayDelay;
		const SDL_VersionDisplay versionDisplay{logs, rndWnd, languageFilePath, fontSize, squareSize};
		bool quitLogoDisplay{false};
		while( false == quitLogoDisplay )
		{
			logoDisplay::loopThings(rndWnd, quitLogoDisplay, sdlLogo, versionDisplay, displayDelay);
		}
	}
}

void logoDisplay::loopThings(sdl2::RendererWindow& rndWnd, bool& quitLogoDisplay, const TextureCombo& sdlLogo, const SDL_VersionDisplay& versionDisplay, 
								const AccurateTimeDelay& displayDelay)
{
	logoDisplay::waitForKeyToBePushed(quitLogoDisplay);
	logoDisplay::quitIfTimeElapsed(quitLogoDisplay, displayDelay);
	rndWnd.clearScreen(BackgroundColor);
	sdlLogo.draw(rndWnd);
	versionDisplay.drawVersion(rndWnd);
	rndWnd.displayRenderer();
	SDL_Delay(16);
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
			case SDL_MOUSEBUTTONDOWN:
				quitLogoDisplay = true;
				break;
		}
	}
}

void logoDisplay::quitIfTimeElapsed(bool& quitLogoDisplay, const AccurateTimeDelay& displayDelay)
{
	if( displayDelay.hasTimeElapsed( std::chrono::milliseconds{6000} ) )
	{
		quitLogoDisplay = true;
	}
}

void logoDisplay::resizeLogoIfNeeded(sdl2::RendererWindow& rndWnd, TextureCombo& sdlLogo)
{
	if( sdlLogo.texture )
	{
		if( sdlLogo.sprite.width() > rndWnd.width() || sdlLogo.sprite.height() > rndWnd.height() )
		{
			double widthRatio{ static_cast<double>( rndWnd.width() ) / static_cast<double>( sdlLogo.sprite.width() ) };
			double heightRatio{ static_cast<double>( rndWnd.height() ) / static_cast<double>( sdlLogo.sprite.height() ) };
		
			if( widthRatio < heightRatio )
			{
				sdlLogo.sprite.setWidth( static_cast<int>( sdlLogo.sprite.width() * widthRatio ) );
				sdlLogo.sprite.setHeight( static_cast<int>( sdlLogo.sprite.height() * widthRatio ) );
			}
			else{
				sdlLogo.sprite.setWidth( static_cast<int>( sdlLogo.sprite.width() * heightRatio ) );
				sdlLogo.sprite.setHeight( static_cast<int>( sdlLogo.sprite.height() * heightRatio ) );
			}
		}
		sdlLogo.sprite.setTexturePosition( TexturePosition{rndWnd.width() / 2, rndWnd.height() / 2, true, true} );
	}
}

bool logoDisplay::getSdlLogoDisplayStatus(AppLogFiles& logs, const fs::path& logoDisplayStatusFilePath)
{
	if( std::ifstream logoDisplayStatusFile{ logoDisplayStatusFilePath } )
	{
		bool displayStatus{true};
		if( logoDisplayStatusFile >> displayStatus )
		{
			return displayStatus;
		}
		else{
			logs.error << "Error: couldn't 'read' '" << logoDisplayStatusFilePath.string() 
						<< "' file whether to show or not SDL logo at start up. That said the file was opened with success.\n";
			return true;
		}
	}
	else{
		logs.error << "Error: couldn't 'open' '" << logoDisplayStatusFilePath.string() << "' file whether to show or not SDL logo at start up.\n";
		return true;
	}
}