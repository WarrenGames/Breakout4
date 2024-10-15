#ifndef SDL2_LOGO_DISPLAY_AT_START_SDL_VERSION_DISPLAYING_H
#define SDL2_LOGO_DISPLAY_AT_START_SDL_VERSION_DISPLAYING_H

#include "texturing/texturesCombo.h"
#include "text/sdl2ttf_font.h"
#include "fileSystem/fileSystem.h"
#include "SDL_version.h"

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }

class SDL_VersionDisplay
{
private:
	SDL_version sdlVersion;
	sdl2::Font arialFont;
	TextureCombo textTexture;
	bool isLoadingPerfect;

public:
	explicit SDL_VersionDisplay(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const fs::path& languageFilePath, int fontSize, int squareSize);
	~SDL_VersionDisplay() = default;
	SDL_VersionDisplay( const SDL_VersionDisplay& ) = delete;
	SDL_VersionDisplay& operator= ( const SDL_VersionDisplay& ) = delete;
	SDL_VersionDisplay( SDL_VersionDisplay&& ) = default;
	SDL_VersionDisplay& operator= ( SDL_VersionDisplay&& ) = default;
	
	void drawVersion(sdl2::RendererWindow& rndWnd) const;
};

#endif //AT_START_SDL_VERSION_DISPLAYING_H