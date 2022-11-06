#ifndef SDL2_MODULES_H
#define SDL2_MODULES_H

class PrefPathFinder;
struct AppLogFiles;

namespace sdl2{ class ModuleInit; class TTFModule; class MixerModule; }

void loadSDL2_modules(AppLogFiles& logs, const PrefPathFinder& prefPath);

void checkEverythingWasInit(AppLogFiles& logs, const PrefPathFinder& prefPath, const sdl2::ModuleInit& sdl2Module, const sdl2::TTFModule& ttfModule, const sdl2::MixerModule& mixerInit);

#endif //SDL2_MODULES_H