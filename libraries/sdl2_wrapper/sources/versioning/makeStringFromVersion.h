#ifndef SDL2_MAKE_STRING_FROM_VERSION_H
#define SDL2_MAKE_STRING_FROM_VERSION_H

#include <string>

struct SDL_version;

namespace sdl2{

std::string getVersionNumber(const SDL_version& version);

}

#endif //SDL2_MAKE_STRING_FROM_VERSION_H