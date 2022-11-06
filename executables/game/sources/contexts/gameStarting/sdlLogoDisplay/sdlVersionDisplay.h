#ifndef AT_START_SDL_VERSION_DISPLAYING_H
#define AT_START_SDL_VERSION_DISPLAYING_H

#include "texturing/texturesCombo.h"
#include "text/sdl2ttf_font.h"
#include "SDL_version.h"

struct Essentials;
struct Offset;

class SDL_VersionDisplay
{
private:
	SDL_version sdlVersion;
	const sdl2::Font arialFont;
	TextureCombo textTexture;
	bool isLoadingPerfect;

public:
	explicit SDL_VersionDisplay(Essentials& essentials);
	~SDL_VersionDisplay() = default;
	SDL_VersionDisplay( const SDL_VersionDisplay& ) = delete;
	SDL_VersionDisplay& operator= ( const SDL_VersionDisplay& ) = delete;
	SDL_VersionDisplay( SDL_VersionDisplay&& ) = default;
	SDL_VersionDisplay& operator= ( SDL_VersionDisplay&& ) = default;
	
	void drawVersion(Essentials& essentials) const;
};

#endif //AT_START_SDL_VERSION_DISPLAYING_H