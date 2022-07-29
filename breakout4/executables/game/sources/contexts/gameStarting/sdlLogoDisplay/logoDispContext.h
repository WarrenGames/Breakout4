#ifndef SDL2_LOGO_DISPLAY_CONTEXT_H
#define SDL2_LOGO_DISPLAY_CONTEXT_H

struct Essentials;
struct TextureCombo;
class AccurateTimeDelay;
class SDL_VersionDisplay;

namespace logoDisplay{
	void mainContext(Essentials& essentials);
	
	void loopThings(Essentials& essentials, bool& quitLogoDisplay, const TextureCombo& sdlLogo, const SDL_VersionDisplay& versionDisplay, AccurateTimeDelay& displayDelay);
	
	void waitForKeyToBePushed(bool& quitLogoDisplay);
	
	void quitIfTimeElapsed(bool& quitLogoDisplay, AccurateTimeDelay& displayDelay);
	
	void resizeLogoIfNeeded(Essentials& essentials, TextureCombo& sdlLogo);
}

#endif //SDL2_LOGO_DISPLAY_CONTEXT_H