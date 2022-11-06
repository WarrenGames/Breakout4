#ifndef START_MINI_SCREEN_CONTEXT_H
#define START_MINI_SCREEN_CONTEXT_H

#include <string>

struct AppLogFiles;
class PrefPathFinder;
class TextsBlocks;
class MiniScreen;
struct Essentials;
namespace input{ class User; }
namespace sdl2{ class RendererWindow; }

namespace cntxt{

namespace miniScreen{

void mainContext(AppLogFiles& logs, const PrefPathFinder& prefPath, const std::string& chosenLang, sdl2::RendererWindow& rndWnd);

void waitForInput(AppLogFiles& logs, const PrefPathFinder& prefPath, const std::string& chosenLang, sdl2::RendererWindow& rndWnd, const MiniScreen& miniGUI);

void actWithInput(Essentials& essentials, bool& quitMiniScreen);

void actWithSDLQuit(input::User& userInput, bool& quitMiniScreen);

void actWithEscapeKey(input::User& userInput, bool& quitMiniScreen);

void changeScreenLayout(Essentials& essentials, bool& quitMiniScreen, bool isFullScreen, unsigned keyToSetToFalse);

void runFullScreenGame(Essentials& essentials, bool& quitMiniScreen);

void runWindowedGame(Essentials& essentials, bool& quitMiniScreen);

void drawEverything(sdl2::RendererWindow& rndWnd, const MiniScreen& miniGUI, bool& quitMiniScreen);

}

}

#endif //START_MINI_SCREEN_CONTEXT_H