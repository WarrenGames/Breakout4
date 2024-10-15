#ifndef SDL2_LOGO_DISPLAY_CONTEXT_H
#define SDL2_LOGO_DISPLAY_CONTEXT_H

#include "fileSystem/fileSystem.h"

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }
struct TextureCombo;
class AccurateTimeDelay;
class SDL_VersionDisplay;

namespace logoDisplay{
	void mainContext(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const fs::path& logoDisplayStatusFile, const fs::path& languageFilePath, int fontSize, int squareSize);
	
	void loopThings(sdl2::RendererWindow& rndWnd, bool& quitLogoDisplay, const TextureCombo& sdlLogo, const SDL_VersionDisplay& versionDisplay, const AccurateTimeDelay& displayDelay);
	
	void waitForKeyToBePushed(bool& quitLogoDisplay);
	
	void quitIfTimeElapsed(bool& quitLogoDisplay, const AccurateTimeDelay& displayDelay);
	
	void resizeLogoIfNeeded(sdl2::RendererWindow& rndWnd, TextureCombo& sdlLogo);
	
	bool getSdlLogoDisplayStatus(AppLogFiles& logs, const fs::path& logoDisplayStatusFilePath);
}

#endif //SDL2_LOGO_DISPLAY_CONTEXT_H